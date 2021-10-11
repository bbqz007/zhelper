```bash
[@localhost build]$ ./db_bench_bdb2 --benchmarks=fillrand100K,readrandom --use_transaction=0 --use_multiple_put=1 --use_in_memory=1 --cache_size=167776700 --page_size=8192 --use_system_mem=0;
BerkeleyDB:    version Berkeley DB 5.3.28: (September  9, 2013)
Date:           Mon Oct 11 06:22:27 2021
CPU:            4 * 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
CPUCache:       8192 KB
Keys:       16 bytes each
Values:     100 bytes each (50 bytes after compression)
Entries:    1000000
RawSize:    110.6 MB (estimated)
FileSize:   62.9 MB (estimated)
------------------------------------------------
fillrand100K :      37.799 micros/op; 2523.4 MB/s (1000 ops)
0	/tmp/leveldbtest-1000/dbbench_bdb-1
0	/tmp/leveldbtest-1000
readrandom   :       0.754 micros/op;     

[@localhost build]$ ./db_bench_bdb2 --benchmarks=fillrandbatch,readrandom --use_transaction=0 --use_multiple_put=1 --use_in_memory=1 --cache_size=167776700 --page_size=8192 --use_system_mem=0;
BerkeleyDB:    version Berkeley DB 5.3.28: (September  9, 2013)
Date:           Mon Oct 11 06:22:28 2021
CPU:            4 * 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
CPUCache:       8192 KB
Keys:       16 bytes each
Values:     100 bytes each (50 bytes after compression)
Entries:    1000000
RawSize:    110.6 MB (estimated)
FileSize:   62.9 MB (estimated)
------------------------------------------------
fillrandbatch :       1.606 micros/op;   68.9 MB/s    
0	/tmp/leveldbtest-1000/dbbench_bdb-1
0	/tmp/leveldbtest-1000
readrandom   :       1.402 micros/op;    

[@localhost build]$ ./db_bench_sqlite3_2 --benchmarks=fillrand100K,readrandom --use_in_memory=1 --cache_size=167776700;
SQLite:     version 3.26.0
Date:       Mon Oct 11 06:22:31 2021
CPU:        4 * 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
CPUCache:   8192 KB
Keys:       16 bytes each
Values:     100 bytes each
Entries:    1000000
RawSize:    110.6 MB (estimated)
------------------------------------------------
fillrand100K :      74.029 micros/op; 1288.5 MB/s (1000 ops)
du: cannot access '/tmp/leveldbtest-1000/*': No such file or directory
readrandom   :       0.540 micros/op;   

[@localhost build]$ ./db_bench_sqlite3_2 --benchmarks=fillrandbatch,readrandom --use_in_memory=1 --cache_size=167776700
SQLite:     version 3.26.0
Date:       Mon Oct 11 06:22:31 2021
CPU:        4 * 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
CPUCache:   8192 KB
Keys:       16 bytes each
Values:     100 bytes each
Entries:    1000000
RawSize:    110.6 MB (estimated)
------------------------------------------------
fillrandbatch :       4.149 micros/op;   26.7 MB/s    
du: cannot access '/tmp/leveldbtest-1000/*': No such file or directory
readrandom   :       2.049 micros/op; 
```
