# orignal benchmarks

http://www.lmdb.tech/bench/microbench/benchmark.html

http://www.lmdb.tech/bench/microbench/

# my patches
**db_bench_bdb.cc** add in memory mode, --use_in_memory=1

**db_bench_sqlite3.cc** add in memory mode, --use_in_memory=1

**db_bench_bdb2.cc** add put(DB_MULTIPLE) for batch and checkpoint to remove log.

# What do patches do
although sqlite3 has in memory mode, but it is not a memory database. you could use lmdb for nosql memory database. sqlite3 cannot be better than leveldb even under in-memory mode in benchmark case.

bdb can do as in-memory mode, but it just to make it could work on some no-disk platform, not for performance.

bdb has a api for multiple writing for batch with flag DB_MULTIPLE which the original benchmark code never use. i add it, but it never performances well, and so disappointing. partition does not bring a good performance.

# conclution
1. lmdb is a memory database.

2. bdb fits small values (size < 1024 byte), reading is faster than sqlite3.

3. sqlite3 is good at large values, while bdb is super poor.

4. when sqlite3 and bdb do transactions, they like to io the log on backend storage, and bdb like more. 
