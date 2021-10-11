# orignal benchmarks

http://www.lmdb.tech/bench/microbench/benchmark.html

http://www.lmdb.tech/bench/microbench/

```
/** add this member method to leveldb/util/Random.h */
void Shuffle(int *array, int n) {
 if (n > 1) {
 int i;
 for(i=0;i<n-1;++i){
  int j = i + Next() / (2147483647 / (n-i) + 1);
  int t = array[i];
  array[j] = array[i];
  array[i] = t;
 }
 }
} 
```

# my patches
**db_bench_bdb.cc** add in memory mode, --use_in_memory=1

**db_bench_sqlite3.cc** add in memory mode, --use_in_memory=1

**db_bench_bdb2.cc** add put(DB_MULTIPLE) for batch and checkpoint to remove logs, add --use_partition, add --page_size, add --use_transaction, add --use_multiple_put, add --use_in_memory, add --use_system_mem.

# What do patches do
although sqlite3 has in memory mode, but it is not a memory database. you could use lmdb for nosql memory database. sqlite3 cannot be better than leveldb even under in-memory mode in benchmark case.

bdb can run as in-memory mode, but you should use CDB rather than TDB. logs are still wrtiten in disk (may be current run directory) in TDB (log | txn) mode.

bdb has a api for multiple writing for batch with flag DB_MULTIPLE which the original benchmark code never use. i add it, but it never performances well, and so disappointing. partition does not bring a good performance.

bdb has two transaction/concurrent data stroage systems. they are based on two exclusive lock subssytem, lock|txn and cdb. when you use cdb, you can not use txn.

bdb's txn, will deadlock if there are more than one batch writing. because of the page lock, if two batch want to modify two same page, each holds the other page, and wait for the page the other held. if you want multiple writer transactions, don't use batch.

# in memory
1. leveldb does not support in memory mode, the contributor says https://github.com/sigp/lighthouse/issues/1139

2. lmdb is a memory db, no matter if you use backend stroage or not. you should specify enough virtual memory space before using. 

3. sqilte3 support in memory mode.

4. bdb support in memory mode. you should specify the whole memory space via cache size, all the pages are located at heap. and you should use CDB to avoid txn and logs and lock subsystem.

```bash
[root@localhost build]#  ./db_bench_bdb2 --benchmarks=fillrand100K,readrandom --use_transaction=0 --use_multiple_put=1 --use_in_memory=1 --cache_size=167776700 --page_size=8192 --use_system_mem=0
BerkeleyDB:    version Berkeley DB 5.3.21: (May 11, 2012)
fillrand100K :     172.363 micros/op;  553.4 MB/s (1000 ops)
readrandom   :       3.190 micros/op;   
[root@localhost build]#  ./db_bench_bdb2 --benchmarks=fillrandbatch,readrandom --use_transaction=0 --use_multiple_put=1 --use_in_memory=1 --cache_size=167776700 --page_size=8192 --use_system_mem=0
fillrandbatch :       9.158 micros/op;   12.1 MB/s    
readrandom   :       6.430 micros/op;                 
```
```bash
[root@localhost build]# ./db_bench_sqlite3 --benchmarks=fillrand100K,readrandom --use_in_memory=1 --cache_size=167776700
SQLite:     version 3.33.0
fillrand100K :     319.812 micros/op;  298.2 MB/s (1000 ops)
readrandom   :      12.667 micros/op;     
[root@localhost build]# ./db_bench_sqlite3 --benchmarks=fillrandbatch,readrandom --use_in_memory=1 --cache_size=167776700
SQLite:     version 3.33.0
fillrandbatch :      37.808 micros/op;    2.9 MB/s    
readrandom   :      27.765 micros/op;                 
```
```bash
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrand100K,readrandom    
MDB:    version LMDB 0.9.22: (March 21, 2018)
fillrand100K :     263.855 micros/op;  361.5 MB/s (1000 ops)
readrandom   :       0.373 micros/op;     
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrandbatch,readrandom
fillrandbatch :      14.729 micros/op;    7.5 MB/s    
readrandom   :       3.898 micros/op;             
```
# concurrency
fill data to a 100w leveldb
```bash
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrandom --num=200001
fillrandom   :      88.642 micros/op;    1.2 MB/s   
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrandom --num=200000
fillrandom   :      81.131 micros/op;    1.4 MB/s    
```
fill data to an empty leveldb
```
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrandom --num=200001
fillrandom   :      30.057 micros/op;    3.7 MB/s 
[root@localhost build]# ./db_bench_mdb --benchmarks=fillrandom --num=200000
fillrandom   :      31.137 micros/op;    3.6 MB/s  
```
fill data to an empty sqlite3db
```
[root@localhost build]# ./db_bench_sqlite3 --benchmarks=fillrandom --num=200001
fillrandom   :      91.782 micros/op;    1.2 MB/s    
[root@localhost build]# ./db_bench_sqlite3 --benchmarks=fillrandom --num=200000
fillrandom   :      90.644 micros/op;    1.2 MB/s    
```
fill data to an empty bdb
```
[root@localhost build]# ./db_bench_bdb --benchmarks=fillrandom --num=200001
fillrandom   :      82.491 micros/op;    1.3 MB/s    
[root@localhost build]# ./db_bench_bdb --benchmarks=fillrandom --num=200000
fillrandom   :      75.996 micros/op;    1.5 MB/s    
```

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
leveldb use mmap and multi-thread io for good performance
```
eveldb 20w rand batch
strace: Process 23228 attached
strace: Process 23229 attached                      
fillrandbatch :      12.879 micros/op;    8.6 MB/s   
strace: Process 23230 attached
24616	/tmp/leveldbtest-0/dbbench
24620	/tmp/leveldbtest-0
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 89.66    0.480000        2043       235        93 futex
  4.06    0.021752         837        26           fdatasync
  3.74    0.020000       20000         1           wait4
  1.73    0.009248         343        27           unlinkat
  0.53    0.002817         939         3           madvise
  0.25    0.001346           0      6356           write
  0.04    0.000195           0      1816           mprotect
  0.00    0.000000           0        24           fcntl
  0.00    0.000000           0         6         4 mkdirat
  0.00    0.000000           0         6         2 renameat
  0.00    0.000000           0        13         5 faccessat
  0.00    0.000000           0       182       103 openat
  0.00    0.000000           0        83           close
  0.00    0.000000           0        30           getdents64
  0.00    0.000000           0        58           read
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

4. bdb is good at Synchronous Writes on SSD and HDD, even in large values case.

4. bdb is also good at in memory if you use C(oncurrency)DB rather than T(ransactional)DB.

5. when sqlite3 and bdb do transactions, they like to io the log on backend storage, and bdb like more. 

## 20w rand／seq batches profiles
**sqlite3** 20w rand batch
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 58.04    0.014356        4785         3           unlinkat
 32.90    0.008138           0    238164           pwrite64
  6.78    0.001678           6       296           brk
  2.09    0.000517           0     26893           pread64
  0.18    0.000044           2        24           ftruncate
  0.00    0.000000           0        20           fcntl
  0.00    0.000000           0         4         4 mkdirat
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0         2           fchown
  0.00    0.000000           0        80        63 openat
  0.00    0.000000           0        17           close
  0.00    0.000000           0         2           getdents64
  0.00    0.000000           0        13           read
  0.00    0.000000           0        50           write
  0.00    0.000000           0        27        20 newfstatat
  0.00    0.000000           0        45           fstat
  0.00    0.000000           0         7           fdatasync
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0        10           rt_sigaction
  0.00    0.000000           0         5           rt_sigprocmask
  0.00    0.000000           0         2           getrlimit
  0.00    0.000000           0         6           geteuid
  0.00    0.000000           0         6           munmap
  0.00    0.000000           0         2           clone
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        36           mmap
  0.00    0.000000           0        18           mprotect
  0.00    0.000000           0         2           wait4
------ ----------- ----------- --------- --------- ----------------
100.00    0.024733                265740        88 total
```
**sqlite3** 20w seq batch    
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 92.40    0.010000        3333         3           unlinkat
  6.17    0.000668           0     26324           pwrite64
  1.42    0.000154           0      7692           pread64
  0.00    0.000000           0        20           fcntl
  0.00    0.000000           0         4         4 mkdirat
  0.00    0.000000           0         3           ftruncate
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0         2           fchown
  0.00    0.000000           0        80        63 openat
  0.00    0.000000           0        17           close
  0.00    0.000000           0         2           getdents64
  0.00    0.000000           0        13           read
  0.00    0.000000           0        50           write
  0.00    0.000000           0        27        20 newfstatat
  0.00    0.000000           0        24           fstat
  0.00    0.000000           0         7           fdatasync
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0        10           rt_sigaction
  0.00    0.000000           0         5           rt_sigprocmask
  0.00    0.000000           0         2           getrlimit
  0.00    0.000000           0         6           geteuid
  0.00    0.000000           0       282           brk
  0.00    0.000000           0         6           munmap
  0.00    0.000000           0         2           clone
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        36           mmap
  0.00    0.000000           0        18           mprotect
  0.00    0.000000           0         2           wait4
------ ----------- ----------- --------- --------- ----------------
100.00    0.010822                 34643        88 total
```
**bdb** 20w rand batch
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 70.60    0.082816         116       713           fdatasync
 20.87    0.024478        3497         7         1 unlinkat
  5.80    0.006806           0    167481           pwrite64
  2.74    0.003211           0    165559           pread64
  0.00    0.000000           0         6           getcwd
  0.00    0.000000           0        50           fcntl
  0.00    0.000000           0         5         5 mkdirat
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0        99        60 openat
  0.00    0.000000           0        39           close
  0.00    0.000000           0         2           getdents64
  0.00    0.000000           0         8           lseek
  0.00    0.000000           0        28           read
  0.00    0.000000           0        57           write
  0.00    0.000000           0        36        19 newfstatat
  0.00    0.000000           0        24           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0        14           rt_sigaction
  0.00    0.000000           0         7           rt_sigprocmask
  0.00    0.000000           0         2           getrlimit
  0.00    0.000000           0         5           geteuid
  0.00    0.000000           0        12           brk
  0.00    0.000000           0        13           munmap
  0.00    0.000000           0         3           clone
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        37           mmap
  0.00    0.000000           0        14           mprotect
  0.00    0.000000           0         3           wait4
------ ----------- ----------- --------- --------- ----------------
100.00    0.117311                334230        86 total
```

**bdb** 20w seq batch
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 83.27    0.050000        2000        25           fdatasync
  7.78    0.004674        1558         3           unlinkat
  4.71    0.002827         217        13           munmap
  2.41    0.001446          54        27           read
  0.92    0.000555           0      9332           pwrite64
  0.91    0.000547           2       286           write
  0.00    0.000000           0         8           getcwd
  0.00    0.000000           0        52           fcntl
  0.00    0.000000           0         5         5 mkdirat
  0.00    0.000000           0         1           renameat
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0       100        59 openat
  0.00    0.000000           0        41           close
  0.00    0.000000           0         4           getdents64
  0.00    0.000000           0        22           lseek
  0.00    0.000000           0        12           pread64
  0.00    0.000000           0        42        22 newfstatat
  0.00    0.000000           0        22           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0        14           rt_sigaction
  0.00    0.000000           0         7           rt_sigprocmask
  0.00    0.000000           0         2           getrlimit
  0.00    0.000000           0         5           geteuid
  0.00    0.000000           0        12           brk
  0.00    0.000000           0         3           clone
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        37           mmap
  0.00    0.000000           0        14           mprotect
  0.00    0.000000           0         3           wait4
------ ----------- ----------- --------- --------- ----------------
100.00    0.060049                 10098        87 total
```
**leveldb** 20w rand batch
```
strace: Process 23228 attached
strace: Process 23229 attached                      
fillrandbatch :      12.879 micros/op;    8.6 MB/s   
strace: Process 23230 attached
24616	/tmp/leveldbtest-0/dbbench
24620	/tmp/leveldbtest-0
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 89.66    0.480000        2043       235        93 futex
  4.06    0.021752         837        26           fdatasync
  3.74    0.020000       20000         1           wait4
  1.73    0.009248         343        27           unlinkat
  0.53    0.002817         939         3           madvise
  0.25    0.001346           0      6356           write
  0.04    0.000195           0      1816           mprotect
  0.00    0.000000           0        24           fcntl
  0.00    0.000000           0         6         4 mkdirat
  0.00    0.000000           0         6         2 renameat
  0.00    0.000000           0        13         5 faccessat
  0.00    0.000000           0       182       103 openat
  0.00    0.000000           0        83           close
  0.00    0.000000           0        30           getdents64
  0.00    0.000000           0        58           read
  0.00    0.000000           0       375       316 newfstatat
  0.00    0.000000           0        21           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         3           set_robust_list
  0.00    0.000000           0        19           rt_sigaction
  0.00    0.000000           0        12           rt_sigprocmask
  0.00    0.000000           0         1           getpgid
  0.00    0.000000           0         1           uname
  0.00    0.000000           0         3           getrlimit
  0.00    0.000000           0         1           getpid
  0.00    0.000000           0         1           getppid
  0.00    0.000000           0         9           getuid
  0.00    0.000000           0        11           geteuid
  0.00    0.000000           0         9           getgid
  0.00    0.000000           0         9           getegid
  0.00    0.000000           0        47           brk
  0.00    0.000000           0        22           munmap
  0.00    0.000000           0         3           clone
  0.00    0.000000           0         3           execve
  0.00    0.000000           0        64           mmap
------ ----------- ----------- --------- --------- ----------------
100.00    0.535358                  9481       523 total
```

**lmdb** 20w rand batch
```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0         2           fcntl
  0.00    0.000000           0         4         4 mkdirat
  0.00    0.000000           0         1           fstatfs
  0.00    0.000000           0         2           ftruncate
  0.00    0.000000           0         1         1 faccessat
  0.00    0.000000           0        67        56 openat
  0.00    0.000000           0        11           close
  0.00    0.000000           0         2           getdents64
  0.00    0.000000           0         1           lseek
  0.00    0.000000           0        10           read
  0.00    0.000000           0        51           write
  0.00    0.000000           0         1           pread64
  0.00    0.000000           0         1           pwrite64
  0.00    0.000000           0        16        13 newfstatat
  0.00    0.000000           0         9           fstat
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_robust_list
  0.00    0.000000           0        10           rt_sigaction
  0.00    0.000000           0         5           rt_sigprocmask
  0.00    0.000000           0         1           uname
  0.00    0.000000           0         2           getrlimit
  0.00    0.000000           0         4           geteuid
  0.00    0.000000           0        10           brk
  0.00    0.000000           0        10           munmap
  0.00    0.000000           0         2           clone
  0.00    0.000000           0         1           execve
  0.00    0.000000           0        34           mmap
  0.00    0.000000           0        14           mprotect
  0.00    0.000000           0         2           wait4
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                   278        74 total
```
