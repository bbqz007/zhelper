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
```
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND   
  191 root      20   0       0      0      0 S  99.3  0.0 128:32.03 exe_cq    
  192 root      20   0       0      0      0 R  84.6  0.0  53:44.23 mmcqd/0   
 9106 root      20   0  334264 162636 157324 R  43.3  4.2   0:08.84 db_bench+ 
 196340	/tmp/leveldbtest-0/dbbench_mdb-1
```
2. leveldb good performance and less memory
```
fillrandbatch :      13.590 micros/op;    8.1 MB/s    
116952	/tmp/leveldbtest-0/dbbench
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND   
 9082 root      20   0  254636  13740   1636 S 108.2  0.4   0:16.26 db_bench 
```

3. bdb fits small values (size < 1024 byte), reading is faster than sqlite3.

4. sqlite3 is good at large values, while bdb is super poor.

5. when sqlite3 and bdb do transactions, they like to io the log on backend storage, and bdb like more. 
