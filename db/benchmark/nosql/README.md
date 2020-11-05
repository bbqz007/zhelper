# orignal benchmarks

http://www.lmdb.tech/bench/microbench/benchmark.html

http://www.lmdb.tech/bench/microbench/

# my patches
**db_bench_bdb.cc** add in memory mode, --use_in_memory=1

**db_bench_sqlite3.cc** add in memory mode, --use_in_memory=1

**db_bench_bdb2.cc** add put(DB_MULTIPLE) for batch and checkpoint to remove logs, add --use_partition, add --page_size.

# What do patches do
although sqlite3 has in memory mode, but it is not a memory database. you could use lmdb for nosql memory database. sqlite3 cannot be better than leveldb even under in-memory mode in benchmark case.

bdb can run as in-memory mode, but that just aim to make it could work on some no-disk platform, not for performance.

bdb has a api for multiple writing for batch with flag DB_MULTIPLE which the original benchmark code never use. i add it, but it never performances well, and so disappointing. partition does not bring a good performance.

# conclution
1. lmdb is a memory database. you need enough memory to run it.
```
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND   
  191 root      20   0       0      0      0 S  99.3  0.0 128:32.03 exe_cq    
  192 root      20   0       0      0      0 R  84.6  0.0  53:44.23 mmcqd/0   
 9106 root      20   0  334264 162636 157324 R  43.3  4.2   0:08.84 db_bench+ 
 196340	/tmp/leveldbtest-0/dbbench_mdb-1
 fillrandbatch :      14.442 micros/op;    7.7 MB/s    
```
the backend storage of the lmdb is not ok until your program noramlly exit, can you see it safely do transaction logs. it is a memory database. 
```
openat(AT_FDCWD, "/tmp/leveldbtest-0/dbbench_mdb-1/lock.mdb", O_RDWR|O_CREAT|O_CLOEXEC, 0664) = 3
mmap(NULL, 8256, PROT_READ|PROT_WRITE, MAP_SHARED, 3, 0) = 0x7e51984000
openat(AT_FDCWD, "/tmp/leveldbtest-0/dbbench_mdb-1/data.mdb", O_RDWR|O_CREAT, 0664) = 4
pread64(4, "", 152, 0)                  = 0
pwrite64(4, "\0\0\0\0\0\0\0\0\0\0\10\0\0\0\0\0\336\300\357\276\1\0\0\0\0\0\0\0\0\0\0\0"..., 8192, 0) = 8192
mmap(NULL, 64000000, PROT_READ|PROT_WRITE, MAP_SHARED, 4, 0) = 0x7e4d1b1000
fillrandbatch :       7.694 micros/op;   14.4 MB/s   
44856	/tmp/leveldbtest-0/dbbench_mdb-1
```
it cannot grow itself, you should specify the capacity before env open. and all database under this env share these spaces.
```
mdb_env_set_mapsize
```
2. leveldb good performance and less memory
```
fillrandbatch :      13.590 micros/op;    8.1 MB/s    
116952	/tmp/leveldbtest-0/dbbench
  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND   
 9082 root      20   0  254636  13740   1636 S 108.2  0.4   0:16.26 db_bench 
```
3. bdb's performance falls down when the count is 10W, 20W, 30W, 40W. -15%~-20% every 10W records.
```
Entries:    100000
fillrandbatch :      38.352 micros/op;    2.9 MB/s   
readrandom   :       9.150 micros/op;   
Entries:    200000
fillrandbatch :      44.806 micros/op;    2.5 MB/s   
readrandom   :      17.706 micros/op;   
Entries:    300000
fillrandbatch :      70.345 micros/op;    1.6 MB/s   
readrandom   :      18.748 micros/op;     
Entries:    400000
fillrandbatch :      85.569 micros/op;    1.3 MB/s   
readrandom   :      18.565 micros/op;                
Entries:    500000
fillrandbatch :     103.289 micros/op;    1.1 MB/s   
readrandom   :      18.344 micros/op;                
Entries:   1000000
fillrandbatch :     123.185 micros/op;    0.9 MB/s 
readrandom   :      22.032 micros/op;  
```
4. bdb's partition can raise write performance when the count is 50W. after the number there is no affect. but writing is still bad, even far from sqlite3.
```
--use_partition=1
Entries:    500000
fillrandbatch :      68.046 micros/op;    1.6 MB/s   
readrandom   :      20.343 micros/op;  
--use_partition=0
Entries:    500000
fillrandbatch :      97.021 micros/op;    1.1 MB/s   
readrandom   :      20.520 micros/op;         
sqlite3
Entries:    500000
fillrandbatch :      47.326 micros/op;    2.3 MB/s   
readrandom   :      40.542 micros/op;  
```
5. bdb's reading and sequance writing (small value cases) is twice faster than sqlite3, but random writing is poor.

3. bdb fits small values (size < 1024 byte), reading is faster than sqlite3.

4. sqlite3 is good at large values, while bdb is super poor.

5. when sqlite3 and bdb do transactions, they like to io the log on backend storage, and bdb like more. 
