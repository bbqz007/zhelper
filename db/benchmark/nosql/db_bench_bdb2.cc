// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <stdio.h>
#include <stdlib.h>
#include <db.h>
#include "util/histogram.h"
#include "util/random.h"
#include "util/testutil.h"

// Comma-separated list of operations to run in the specified order
//   Actual benchmarks:
//
//   fillseq       -- write N values in sequential key order in async mode
//   fillrandom    -- write N values in random key order in async mode
//   overwrite     -- overwrite N values in random key order in async mode
//   fillseqsync   -- write N/100 values in sequential key order in sync mode
//   fillseqbatch  -- batch write N values in sequential key order in async mode
//   fillrandsync  -- write N/100 values in random key order in sync mode
//   fillrandbatch  -- batch write N values in random key order in async mode
//   fillrand100K  -- write N/1000 100K values in random order in async mode
//   fillseq100K   -- write N/1000 100K values in seq order in async mode
//   readseq       -- read N times sequentially
//   readreverse   -- read N times in reverse order
//   readseq100K   -- read N/1000 100K values in sequential order in async mode
//   readrand100K  -- read N/1000 100K values in sequential order in async mode
//   readrandom    -- read N times in random order
static const char* FLAGS_benchmarks =
    "fillseqsync,"
    "fillrandsync,"
    "fillseq,"
    "fillseqbatch,"
    "fillrandom,"
    "fillrandbatch,"
    "overwrite,"
#if 0
    "overwritebatch,"
#endif
    "readrandom,"
    "readseq,"
    "readreverse,"
#if 0
    "fillrand100K,"
    "fillseq100K,"
    "readseq100K,"
    "readrand100K,"
#endif
    ;

// Number of key/values to place in database
static int FLAGS_num = 1000000;

// Number of read operations to do.  If negative, do FLAGS_num reads.
static int FLAGS_reads = -1;

// Size of each value
static int FLAGS_value_size = 100;

// Arrange to generate values that shrink to this fraction of
// their original size after compression
static double FLAGS_compression_ratio = 0.5;

// Print histogram of operation timings
static bool FLAGS_histogram = false;

// Cache size. Default 4 MB
static int FLAGS_cache_size = 4194304;

// Page size. Default 1 KB
static int FLAGS_page_size = 4096;

// If true, do not destroy the existing database.  If you set this
// flag and also specify a benchmark that wants a fresh database, that
// benchmark will fail.
static bool FLAGS_use_existing_db = false;

// If true, we allow batch writes to occur
static bool FLAGS_transaction = true;

// Use the db with the following name.
static const char* FLAGS_db = NULL;

static int *shuff = NULL;

static bool FLAGS_use_same_env = false;

static bool FLAGS_new_shuff = false;

static bool FLAGS_use_partition = false;

static bool FLAGS_use_multiple_put = false;

static bool FLAGS_use_in_memory = false;

static bool FLAGS_use_system_mem = false;

static int run_round = 0;

__attribute_noinline__
void volatilecpy(void* dst, const void* src, size_t sz)
{
    if (0 == (((intptr_t)dst & 7) | ((intptr_t)src & 7)))
        (void)0;
    if (sz > 512)
        (void)0;
    register char* pd = (char*) dst;
    register char* ps = (char*) src;
    if (sz & 31)
    {
        size_t partial = sz & 7;
        switch(partial)
        {
    case 1:
        pd[0] = ps[0];
        break;
    case 2:
        *(short*)pd = *(short*)ps;
        break;
    case 3:
        pd[0] = ps[0];
        *(short*)(pd+1) = *(short*)(ps+1);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        *(int*)pd = *(int*)ps;
        *(int*)(pd + partial - 4) = *(int*)(ps + partial - 4);
        break;
        }
        pd += partial;
        ps += partial;

        partial = sz & 24;
        switch(partial)
        {
    case 24:
        *(int64_t*)(pd + 16) = *(int64_t*)(ps + 16);
    case 16:
        *(int64_t*)(pd + 8) = *(int64_t*)(ps + 8);
    case 8:
        *(int64_t*)pd = *(int64_t*)ps;
        break;
        }
        pd += partial;
        ps += partial;
    }
    size_t odd = sz & ~(size_t)31;
    register volatile int64_t* di64p = (volatile int64_t*)pd;
    register volatile int64_t* si64p = (volatile int64_t*)ps;

    for (int i = 0; i < odd; i += 32, di64p += 4, si64p += 4)
    {
        *di64p = *si64p;
        *(1+di64p) = *(1+si64p);
        *(2+di64p) = *(2+si64p);
        *(3+di64p) = *(3+si64p);
    }
}

namespace leveldb {

// Helper for quickly generating random data.
namespace {
class RandomGenerator {
 private:
  std::string data_;
  int pos_;

 public:
  RandomGenerator() {
    // We use a limited amount of data over and over again and ensure
    // that it is larger than the compression window (32KB), and also
    // large enough to serve all typical value sizes we want to write.
    Random rnd(301);
    std::string piece;
    while (data_.size() < 1048576) {
      // Add a short fragment that is as compressible as specified
      // by FLAGS_compression_ratio.
      test::CompressibleString(&rnd, FLAGS_compression_ratio, 100, &piece);
      data_.append(piece);
    }
    pos_ = 0;
  }

  Slice Generate(int len) {
    if (pos_ + len > data_.size()) {
      pos_ = 0;
      assert(len < data_.size());
    }
    pos_ += len;
    return Slice(data_.data() + pos_ - len, len);
  }
};

static Slice TrimSpace(Slice s) {
  int start = 0;
  while (start < s.size() && isspace(s[start])) {
    start++;
  }
  int limit = s.size();
  while (limit > start && isspace(s[limit-1])) {
    limit--;
  }
  return Slice(s.data() + start, limit - start);
}

}  // namespace

class Benchmark {
 private:
  DB_ENV *db_;
  DB *dbh_;
  int db_num_;
  int num_;
  int reads_;
  double start_;
  double last_op_finish_;
  int64_t bytes_;
  std::string message_;
  Histogram hist_;
  RandomGenerator gen_;
  Random rand_;

  // State kept for progress messages
  int done_;
  int next_report_;     // When to report next

  void PrintHeader() {
    const int kKeySize = 16;
    PrintEnvironment();
    fprintf(stdout, "Keys:       %d bytes each\n", kKeySize);
    fprintf(stdout, "Values:     %d bytes each (%d bytes after compression)\n",
            FLAGS_value_size,
            static_cast<int>(FLAGS_value_size * FLAGS_compression_ratio + 0.5));
    fprintf(stdout, "Entries:    %d\n", num_);
    fprintf(stdout, "RawSize:    %.1f MB (estimated)\n",
            ((static_cast<int64_t>(kKeySize + FLAGS_value_size) * num_)
             / 1048576.0));
    fprintf(stdout, "FileSize:   %.1f MB (estimated)\n",
            (((kKeySize + FLAGS_value_size * FLAGS_compression_ratio) * num_)
             / 1048576.0));
    PrintWarnings();
    fprintf(stdout, "------------------------------------------------\n");
  }

  void PrintWarnings() {
#if defined(__GNUC__) && !defined(__OPTIMIZE__)
    fprintf(stdout,
            "WARNING: Optimization is disabled: benchmarks unnecessarily slow\n"
            );
#endif
#ifndef NDEBUG
    fprintf(stdout,
            "WARNING: Assertions are enabled; benchmarks unnecessarily slow\n");
#endif
  }

  void PrintEnvironment() {
    fprintf(stderr, "BerkeleyDB:    version %s\n", DB_VERSION_STRING);

#if defined(__linux)
    time_t now = time(NULL);
    fprintf(stderr, "Date:           %s", ctime(&now));  // ctime() adds newline

    FILE* cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo != NULL) {
      char line[1000];
      int num_cpus = 0;
      std::string cpu_type;
      std::string cache_size;
      while (fgets(line, sizeof(line), cpuinfo) != NULL) {
        const char* sep = strchr(line, ':');
        if (sep == NULL) {
          continue;
        }
        Slice key = TrimSpace(Slice(line, sep - 1 - line));
        Slice val = TrimSpace(Slice(sep + 1));
        if (key == "model name") {
          ++num_cpus;
          cpu_type = val.ToString();
        } else if (key == "cache size") {
          cache_size = val.ToString();
        }
      }
      fclose(cpuinfo);
      fprintf(stderr, "CPU:            %d * %s\n", num_cpus, cpu_type.c_str());
      fprintf(stderr, "CPUCache:       %s\n", cache_size.c_str());
    }
#endif
  }

  void Start() {
    start_ = Env::Default()->NowMicros() * 1e-6;
    bytes_ = 0;
    message_.clear();
    last_op_finish_ = start_;
    hist_.Clear();
    done_ = 0;
    next_report_ = 100;
  }

  void FinishedSingleOp() {
    if (FLAGS_histogram) {
      double now = Env::Default()->NowMicros() * 1e-6;
      double micros = (now - last_op_finish_) * 1e6;
      hist_.Add(micros);
      if (micros > 20000) {
        fprintf(stderr, "long op: %.1f micros%30s\r", micros, "");
        fflush(stderr);
      }
      last_op_finish_ = now;
    }

    done_++;
    if (done_ >= next_report_) {
      if      (next_report_ < 1000)   next_report_ += 100;
      else if (next_report_ < 5000)   next_report_ += 500;
      else if (next_report_ < 10000)  next_report_ += 1000;
      else if (next_report_ < 50000)  next_report_ += 5000;
      else if (next_report_ < 100000) next_report_ += 10000;
      else if (next_report_ < 500000) next_report_ += 50000;
      else                            next_report_ += 100000;
      fprintf(stderr, "... finished %d ops%30s\r", done_, "");
      fflush(stderr);
    }
  }

  void Stop(const Slice& name) {
    double finish = Env::Default()->NowMicros() * 1e-6;

    // Pretend at least one op was done in case we are running a benchmark
    // that does not call FinishedSingleOp().
    if (done_ < 1) done_ = 1;

    if (bytes_ > 0) {
      char rate[100];
      snprintf(rate, sizeof(rate), "%6.1f MB/s",
               (bytes_ / 1048576.0) / (finish - start_));
      if (!message_.empty()) {
        message_  = std::string(rate) + " " + message_;
      } else {
        message_ = rate;
      }
    }

    fprintf(stdout, "%-12s : %11.3f micros/op;%s%s\n",
            name.ToString().c_str(),
            (finish - start_) * 1e6 / done_,
            (message_.empty() ? "" : " "),
            message_.c_str());
    if (FLAGS_histogram) {
      fprintf(stdout, "Microseconds per op:\n%s\n", hist_.ToString().c_str());
    }
    fflush(stdout);
  }

 public:
  enum Order {
    SEQUENTIAL,
    RANDOM
  };
  enum DBState {
    FRESH,
    EXISTING
  };
  enum DBFlags {
    NONE = 0,
  	SYNC,
	INT,
  };

  Benchmark()
  : db_(NULL),
  	dbh_(NULL),
    db_num_(0),
    num_(FLAGS_num),
    reads_(FLAGS_reads < 0 ? FLAGS_num : FLAGS_reads),
    bytes_(0),
    rand_(301) {
    std::vector<std::string> files;
    std::string test_dir;
    Env::Default()->GetTestDirectory(&test_dir);
    Env::Default()->GetChildren(test_dir.c_str(), &files);
    if (!FLAGS_use_existing_db) {
      for (int i = 0; i < files.size(); i++) {
        if (Slice(files[i]).starts_with("dbbench_bdb")) {
          std::string file_name(test_dir);
          file_name += "/";
          file_name += files[i];
          Env::Default()->DeleteFile(file_name.c_str());
        }
      }
    }
  }

  ~Benchmark() {
  	if (dbh_)
		dbh_->close(dbh_, 0);
	if (db_)
		db_->close(db_, 0);
  }

  void Run() {
    PrintHeader();

    const char* benchmarks = FLAGS_benchmarks;
    --run_round;
    while (benchmarks != NULL) {
      ++run_round;
      const char* sep = strchr(benchmarks, ',');
      Slice name;
      if (sep == NULL) {
        name = benchmarks;
        benchmarks = NULL;
      } else {
        name = Slice(benchmarks, sep - benchmarks);
        benchmarks = sep + 1;
      }

	  num_ = FLAGS_num;
      Start();

      bool known = true, writer = false;
	  DBFlags flags = NONE;
      if (name == Slice("fillseq")) {
	writer = true;
        Write(flags, SEQUENTIAL, FRESH, num_, FLAGS_value_size, 1);
      } else if (name == Slice("fillseqbatch")) {
	writer = true;
        Write(flags, SEQUENTIAL, FRESH, num_, FLAGS_value_size, 1000);
      } else if (name == Slice("fillrandom")) {
	writer = true;
        Write(flags, RANDOM, FRESH, num_, FLAGS_value_size, 1);
      } else if (name == Slice("fillrandbatch")) {
	writer = true;
        Write(flags, RANDOM, FRESH, num_, FLAGS_value_size, 1000);
      } else if (name == Slice("overwrite")) {
	writer = true;
        Write(flags, RANDOM, EXISTING, num_, FLAGS_value_size, 1);
      } else if (name == Slice("overwritebatch")) {
	writer = true;
        Write(flags, RANDOM, EXISTING, num_, FLAGS_value_size, 1000);
      } else if (name == Slice("fillrandsync")) {
	writer = true;
        flags = SYNC;
#if 1
		num_ /= 1000;
		if (num_<10) num_=10;
#endif
        Write(flags, RANDOM, FRESH, num_, FLAGS_value_size, 1);
      } else if (name == Slice("fillseqsync")) {
	writer = true;
        flags = SYNC;
#if 1
		num_ /= 1000;
		if (num_<10) num_=10;
#endif
        Write(flags, SEQUENTIAL, FRESH, num_, FLAGS_value_size, 1);
      } else if (name == Slice("fillrand100K")) {
	writer = true;
        Write(flags, RANDOM, FRESH, num_ / 1000, 100 * 1000, 1);
      } else if (name == Slice("fillseq100K")) {
	writer = true;
        Write(flags, SEQUENTIAL, FRESH, num_ / 1000, 100 * 1000, 1);
      } else if (name == Slice("readseq")) {
        ReadSequential();
      } else if (name == Slice("readreverse")) {
        ReadReverse();
      } else if (name == Slice("readrandom")) {
        ReadRandom();
      } else if (name == Slice("readrand100K")) {
        int n = reads_;
        reads_ /= 1000;
        ReadRandom();
        reads_ = n;
      } else if (name == Slice("readseq100K")) {
        int n = reads_;
        reads_ /= 1000;
        ReadSequential();
        reads_ = n;
      } else {
        known = false;
        if (name != Slice()) {  // No error message for empty name
          fprintf(stderr, "unknown benchmark '%s'\n", name.ToString().c_str());
        }
      }
      if (known) {
        Stop(name);
	if (writer) {
	  char cmd[200];
	  std::string test_dir;
	  Env::Default()->GetTestDirectory(&test_dir);
	  sprintf(cmd, "du %s", test_dir.c_str());
	  system(cmd);
	}
      }
    }
  }

 private:
    void Open(DBFlags flags) {
    assert(db_ == NULL);
	int rc;
	DB_TXN *txn;

    char file_name[100], cmd[200];
    db_num_++;
    std::string test_dir;
    Env::Default()->GetTestDirectory(&test_dir);
    snprintf(file_name, sizeof(file_name),
             "%s/dbbench_bdb-%d",
             test_dir.c_str(),
             (FLAGS_use_same_env) ? 1 : db_num_);

	sprintf(cmd, "mkdir -p %s", file_name);
	system(cmd);

	int env_opt = DB_REGION_INIT;

    // Create tuning options and open the database
	rc = db_env_create(&db_, 0);
	rc = db_->set_cachesize(db_, 0, FLAGS_cache_size, 1);
	if (FLAGS_transaction)
    {
        rc = db_->set_lk_max_locks(db_, 100000);
        rc = db_->set_lk_max_objects(db_, 100000);
        if (flags != SYNC && FLAGS_transaction)
        {
            env_opt |= DB_TXN_WRITE_NOSYNC;
        }
    }
    if (FLAGS_use_in_memory)
        db_->log_set_config(db_, DB_LOG_IN_MEMORY, 1);
	rc =db_->set_flags(db_, env_opt, 1);
	if (FLAGS_transaction)
        rc =db_->log_set_config(db_, DB_LOG_AUTO_REMOVE, 1);
#define TXN_FLAGS	(DB_INIT_LOCK|DB_INIT_LOG|DB_INIT_TXN|DB_INIT_MPOOL|DB_CREATE|DB_THREAD)
#define CDB_FLAGS   (DB_INIT_CDB|DB_INIT_MPOOL|DB_CREATE|DB_THREAD)
	if (!FLAGS_use_in_memory)
        rc = db_->open(db_, file_name, (FLAGS_transaction) ?TXN_FLAGS : CDB_FLAGS, 0664);
	else
        rc = db_->open(db_, NULL, DB_PRIVATE
                                    | ((FLAGS_transaction) ?TXN_FLAGS : CDB_FLAGS)
                                    | ((FLAGS_use_system_mem) ?DB_SYSTEM_MEM : 0),
                       0664);
	if (rc) {
      fprintf(stderr, "open error: %s\n", db_strerror(rc));
    }
	rc = db_create(&dbh_, db_, 0);
	rc = dbh_->set_pagesize(dbh_, FLAGS_page_size);

	DBT partkey[] = {
        //{(void*)"0000000000100000", 16 },
        {(void*)"0000000000200000",16 },
        //{(void*)"0000000000300000",16 },
        {(void*)"0000000000400000",16 },
        //{(void*)"0000000000500000",16 },
        {(void*)"0000000000600000",16 },
        //{(void*)"0000000000700000",16 },
        {(void*)"0000000000800000",16 },
        //{(void*)"0000000000900000",16 },
        {(void*)"0000000001000000",16 }
	};
	if (FLAGS_use_partition)
        rc = dbh_->set_partition(dbh_, sizeof(partkey)/sizeof(DBT) + 1, partkey, 0);
	//rc = dbh_->set_bt_compare(dbh_, [](DB*, const DBT* L, const DBT* R){
    //                        return memcmp(L->data, R->data, 16);
     //                      });
	if (!FLAGS_use_in_memory)
        rc = dbh_->open(dbh_, NULL, "data.bdb", NULL, DB_BTREE, ((FLAGS_transaction)?DB_AUTO_COMMIT:0)|DB_CREATE|DB_THREAD, 0664);
    else
        rc = dbh_->open(dbh_, NULL, NULL, NULL, DB_BTREE, ((FLAGS_transaction)?DB_AUTO_COMMIT:0)|DB_CREATE|DB_THREAD, 0664);
    if (FLAGS_use_in_memory)
    {
        DB_MPOOLFILE* mpf = dbh_->get_mpf(dbh_);
        rc = mpf->set_flags(mpf, DB_MPOOL_NOFILE, 1);
    }
  }

  void Write(DBFlags flags, Order order, DBState state,
             int num_entries, int value_size, int entries_per_batch) {
    // Create new database if state == FRESH
    if (state == FRESH) {
      if (FLAGS_use_existing_db) {
        message_ = "skipping (--use_existing_db is true)";
        //return;
      }
      else
      {
          if (db_) {
		  char cmd[200];
		  sprintf(cmd, "rm -rf %s*", FLAGS_db);
		  dbh_->close(dbh_, 0);
		  db_->close(db_, 0);
		  if (!FLAGS_use_existing_db)
            system(cmd);
		  db_ = NULL;
		  dbh_ = NULL;
          }
          Open(flags);
      }
    } else {
        if (!db_)
            Open(flags);
        if (FLAGS_transaction)
            db_->txn_checkpoint(db_,0,0,0);
    }

    if (order == RANDOM)
	  rand_.Shuffle(shuff, num_entries);

    Start();  // Do not count time taken to destroy/open

    if (num_entries != num_) {
      char msg[100];
      snprintf(msg, sizeof(msg), "(%d ops)", num_entries);
      message_ = msg;
    }

	DBT mkey, mval;
	DB_TXN *txn = 0;
	char key[100];
	mkey.data = key;
	mval.size = value_size;
	mkey.flags = 0; mval.flags = 0;
	void *kd, *dd;
	if (entries_per_batch > 1)
    {
        mkey.ulen = (16 + sizeof(uint32_t) * 2) * entries_per_batch + sizeof(uint32_t) *8;
        kd = malloc(mkey.ulen);
        mkey.data = kd;
        mval.ulen = (value_size + sizeof(uint32_t) * 2) * entries_per_batch  + sizeof(uint32_t) *8;
        dd = malloc(mval.ulen);
        mval.data = dd;
        for (int sz = 0; sz < mval.ulen; sz += (1<<20))
        {
            memcpy((char*)mval.data + sz,
                   (void*)gen_.Generate((1<<20)).data(),
                   (sz + (1<<20) > mval.ulen)? mval.ulen - sz : (1<<20));
        }
    }
    // Write to database
    for (int i = 0; i < num_entries; i+= entries_per_batch)
    {
        if (i > 0 && 0 == (i % 100000))
        {
            if (FLAGS_transaction)
                db_->txn_checkpoint(db_,0,0,DB_FORCE);
            dbh_->close(dbh_, 0);
            db_->close(db_, 0);
            db_ = NULL;
            dbh_ = NULL;
            db_num_--;
            Open(flags);
        }

      if (entries_per_batch == 1 || !FLAGS_use_multiple_put)
      {
          if (FLAGS_transaction)
              db_->txn_begin(db_, NULL, &txn, DB_TXN_WAIT|((flags==SYNC)?0:DB_TXN_WRITE_NOSYNC));

          for (int j=0; j < entries_per_batch; j++) {
              const int k = ((order == SEQUENTIAL) ? i+j : shuff[i+j])
                            + ((FLAGS_new_shuff) ? (FLAGS_num * run_round) : 0);
              int rc, flag = 0;
              mkey.size = snprintf(key, sizeof(key), "%016d", k);
              bytes_ += value_size + mkey.size;
              mval.data = (void *)gen_.Generate(value_size).data();
              rc = dbh_->put(dbh_, txn, &mkey, &mval, 0);
              if (rc) {
                fprintf(stderr, "set error: %s\n", db_strerror(rc));
              }
          FinishedSingleOp();
          }
          if (FLAGS_transaction)
              txn->commit(txn, 0);
      }
      else
      {
          mkey.flags = DB_DBT_USERMEM;
          mval.flags = DB_DBT_USERMEM;
          void *kp, *vp, *kdstp, *vdstp;
          DB_MULTIPLE_WRITE_INIT(kp, &mkey);
          DB_MULTIPLE_WRITE_INIT(vp, &mval);
          for (int j=0; j < entries_per_batch; j++) {
              const int k = ((order == SEQUENTIAL) ? i+j : shuff[i+j])
                            + ((FLAGS_new_shuff) ? (FLAGS_num * run_round) : 0);
#if 1
              DB_MULTIPLE_RESERVE_NEXT(kp, &mkey, kdstp, 16);
              int sz = 16;snprintf((char*)kdstp, 17, "%016d", k);
              DB_MULTIPLE_RESERVE_NEXT(vp, &mval, vdstp, value_size);
              memcpy(vdstp, gen_.Generate(value_size).data(), value_size);
#else
              int sz = 16;snprintf(key, sizeof(key), "%016d", k);
              DB_MULTIPLE_WRITE_NEXT(kp, &mkey, key, sz);
              DB_MULTIPLE_WRITE_NEXT(vp, &mval, (void *)gen_.Generate(value_size).data(), value_size);
#endif
              bytes_ += sz + value_size;
              FinishedSingleOp();
          }
          if (FLAGS_transaction)
              db_->txn_begin(db_, NULL, &txn, DB_TXN_NOWAIT|((flags==SYNC)?0:DB_TXN_WRITE_NOSYNC));
          int rc, flag = 0;
          rc = dbh_->put(dbh_, txn, &mkey, &mval, DB_MULTIPLE);
          if (rc) {
            fprintf(stderr, "set error: %s\n", db_strerror(rc));
          }
          if (FLAGS_transaction)
              txn->commit(txn, 0);
      }

    }
    if (entries_per_batch > 1)
    {
        free(kd);
        free(dd);
    }
  }

  void ReadReverse() {
    DB_TXN *txn = 0;
	DBC *cursor;
	DBT key, data;

	key.flags = 0; data.flags = 0;
	if (FLAGS_transaction)
        db_->txn_begin(db_, NULL, &txn, DB_READ_UNCOMMITTED);
	dbh_->cursor(dbh_, txn, &cursor, 0);
    while (cursor->get(cursor, &key, &data, DB_PREV) == 0) {
      bytes_ += key.size + data.size;
      FinishedSingleOp();
    }
	cursor->close(cursor);
	if (FLAGS_transaction)
        txn->abort(txn);
  }

  void ReadSequential() {
    DB_TXN *txn = 0;
	DBC *cursor;
	DBT key, data;

	key.flags = 0; data.flags = 0;
	if (FLAGS_transaction)
        db_->txn_begin(db_, NULL, &txn, DB_READ_UNCOMMITTED);
	dbh_->cursor(dbh_, txn, &cursor, 0);
    while (cursor->get(cursor, &key, &data, DB_NEXT) == 0) {
      bytes_ += key.size + data.size;
      FinishedSingleOp();
    }
	cursor->close(cursor);
	if (FLAGS_transaction)
        txn->abort(txn);
  }

  void ReadRandom() {
    DB_TXN *txn = 0;
	DBC *cursor;
	DBT key, data;
    char ckey[100];

	key.flags = 0; data.flags = 0;
	key.data = ckey;
	if (FLAGS_transaction)
        db_->txn_begin(db_, NULL, &txn, DB_READ_UNCOMMITTED);
	dbh_->cursor(dbh_, txn, &cursor, 0);
    for (int i = 0; i < reads_; i++) {
      const int k = rand_.Next() % reads_;
      key.size = snprintf(ckey, sizeof(ckey), "%016d", k);
	  cursor->get(cursor, &key, &data, DB_SET);
      FinishedSingleOp();
    }
	cursor->close(cursor);
	if (FLAGS_transaction)
        txn->abort(txn);
  }
};

}  // namespace leveldb

int main(int argc, char** argv) {
  std::string default_db_path;
  for (int i = 1; i < argc; i++) {
    double d;
    int n;
    char junk;
    if (leveldb::Slice(argv[i]).starts_with("--benchmarks=")) {
      FLAGS_benchmarks = argv[i] + strlen("--benchmarks=");
    } else if (sscanf(argv[i], "--compression_ratio=%lf%c", &d, &junk) == 1) {
      FLAGS_compression_ratio = d;
    } else if (sscanf(argv[i], "--histogram=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_histogram = n;
    } else if (sscanf(argv[i], "--use_same_env=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_same_env = n;
    } else if (sscanf(argv[i], "--new_shuff=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_new_shuff = n;
    } else if (sscanf(argv[i], "--use_existing_db=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_existing_db = n;
    } else if (sscanf(argv[i], "--use_partition=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_partition = n;
    } else if (sscanf(argv[i], "--use_transaction=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_transaction = n;
    } else if (sscanf(argv[i], "--use_multiple_put=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_multiple_put = n;
    } else if (sscanf(argv[i], "--use_in_memory=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_in_memory = n;
    } else if (sscanf(argv[i], "--use_system_mem=%d%c", &n, &junk) == 1 &&
               (n == 0 || n == 1)) {
      FLAGS_use_system_mem = n;
    } else if (sscanf(argv[i], "--num=%d%c", &n, &junk) == 1) {
      FLAGS_num = n;
    } else if (sscanf(argv[i], "--reads=%d%c", &n, &junk) == 1) {
      FLAGS_reads = n;
    } else if (sscanf(argv[i], "--value_size=%d%c", &n, &junk) == 1) {
      FLAGS_value_size = n;
    } else if (sscanf(argv[i], "--cache_size=%d%c", &n, &junk) == 1) {
      FLAGS_cache_size = n;
    } else if (sscanf(argv[i], "--page_size=%d%c", &n, &junk) == 1) {
      FLAGS_page_size = n;
    } else if (strncmp(argv[i], "--db=", 5) == 0) {
      FLAGS_db = argv[i] + 5;
    } else {
      fprintf(stderr, "Invalid flag '%s'\n", argv[i]);
      exit(1);
    }
  }

  // Choose a location for the test database if none given with --db=<path>
  if (FLAGS_db == NULL) {
      leveldb::Env::Default()->GetTestDirectory(&default_db_path);
      default_db_path += "/dbbench";
      FLAGS_db = default_db_path.c_str();
  }

  shuff = (int *)malloc(FLAGS_num * sizeof(int));
  for (int i=0; i<FLAGS_num; i++)
   shuff[i] = i;
  leveldb::Benchmark benchmark;
  benchmark.Run();
  return 0;
}
