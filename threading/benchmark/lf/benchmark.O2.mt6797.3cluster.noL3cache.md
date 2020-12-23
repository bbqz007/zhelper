### test number of threads (empty workload)
**8xW,8xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 9.56, 9.18, 8.93
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       286247792 ns       950954 ns           10
BM_deque/0/0        191299107 ns       797130 ns          100
BM_deque_lf/0/0    1093369562 ns       814684 ns           10
BM_deque_lf_s/0/0   420065285 ns       812300 ns           10
BM_deque2_lf/0/0    482431561 ns       731907 ns           10
BM_deque2_lf_s/0/0  189481817 ns       794663 ns          100
BM_ypipe/0/0        135752305 ns       749611 ns          100
BM_ypipe_s/0/0      129261987 ns       777886 ns          100
BM_ypipe_lf/0/0     393273138 ns       835677 ns           10
BM_ypipe_lf_s/0/0   197162484 ns       761805 ns          100
```
**10xW,10xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 8.66, 9.72, 9.32
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       256780292 ns      1131323 ns           10
BM_deque/0/0        170283915 ns       977651 ns          100
BM_deque_lf/0/0    1388369192 ns      1117016 ns           10
BM_deque_lf_s/0/0   435245446 ns      1014208 ns           10
BM_deque2_lf/0/0    356678423 ns      1037001 ns           10
BM_deque2_lf_s/0/0  168157128 ns       942873 ns          100
BM_ypipe/0/0        147725759 ns       953495 ns          100
BM_ypipe_s/0/0      144638262 ns      1019552 ns          100
BM_ypipe_lf/0/0     303235508 ns       891739 ns           10
BM_ypipe_lf_s/0/0   203974775 ns       891876 ns          100
```
**12xW,12xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 9.24, 11.08, 10.10
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       266686762 ns      1262885 ns           10
BM_deque/0/0        194030972 ns      1118587 ns          100
BM_deque_lf/0/0    2042281354 ns      1193338 ns           10
BM_deque_lf_s/0/0   463501115 ns      1094523 ns           10
BM_deque2_lf/0/0    623122392 ns      1143908 ns           10
BM_deque2_lf_s/0/0  202945300 ns      1109695 ns          100
BM_ypipe/0/0        149048372 ns      1106084 ns          100
BM_ypipe_s/0/0      150868607 ns      1107567 ns          100
BM_ypipe_lf/0/0     733530354 ns      1327585 ns           10
BM_ypipe_lf_s/0/0   227255445 ns      1117531 ns          100
```
### test number of threads (block quad times per msg)
**8xW,8xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 8.44, 8.52, 9.18
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       924933323 ns       778508 ns           10
BM_deque/0/0        907553615 ns       786546 ns           10
BM_deque_lf/0/0    2687161385 ns       761694 ns            1
BM_deque_lf_s/0/0  2151583462 ns       775723 ns           10
BM_deque2_lf/0/0   2612568770 ns       839383 ns            1
BM_deque2_lf_s/0/0 1999807546 ns       789331 ns           10
BM_ypipe/0/0        858867354 ns       810215 ns           10
BM_ypipe_s/0/0      854748723 ns       852000 ns           10
BM_ypipe_lf/0/0    2356951854 ns       848116 ns           10
BM_ypipe_lf_s/0/0  1632887846 ns       752245 ns           10
```
**10xW,10xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 9.15, 9.51, 9.50
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0      1026680408 ns      1047562 ns           10
BM_deque/0/0       1030741431 ns      1099123 ns           10
BM_deque_lf/0/0    3103780231 ns       953615 ns            1
BM_deque_lf_s/0/0  2375375277 ns       967707 ns           10
BM_deque2_lf/0/0   2844606461 ns      1012924 ns            1
BM_deque2_lf_s/0/0 2246861000 ns      1021669 ns           10
BM_ypipe/0/0        960203800 ns       993707 ns           10
BM_ypipe_s/0/0      965298885 ns      1065931 ns           10
BM_ypipe_lf/0/0    2910932462 ns       771154 ns            1
BM_ypipe_lf_s/0/0  2198896600 ns      1021331 ns           10
```
**12xW,12xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 8.84, 10.28, 9.94
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       987072662 ns      1173731 ns           10
BM_deque/0/0        971303000 ns      1258892 ns           10
BM_deque_lf/0/0    3085028538 ns      1017002 ns            1
BM_deque_lf_s/0/0  2024018185 ns      1180738 ns           10
BM_deque2_lf/0/0   2988766923 ns       954999 ns            1
BM_deque2_lf_s/0/0 2041733016 ns      1323169 ns           10
BM_ypipe/0/0        925946392 ns      1170662 ns           10
BM_ypipe_s/0/0      929588485 ns      1263516 ns           10
BM_ypipe_lf/0/0    3105752847 ns      1199154 ns            1
BM_ypipe_lf_s/0/0  2219016116 ns      1154316 ns           10
```
