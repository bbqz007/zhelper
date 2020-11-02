# orignal benchmarks

http://www.lmdb.tech/bench/microbench/benchmark.html

http://www.lmdb.tech/bench/microbench/

# my patches
**db_bench_bdb.cc** add in memory mode, --use_in_memory=1

**db_bench_sqlite3.cc** add in memory mode, --use_in_memory=1

**db_bench_bdb2.cc** add put(DB_MULTIPLE) for batch and checkpoint to remove log.
