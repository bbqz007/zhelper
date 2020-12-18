# empty payload while processing msg.
```
2020-12-15T12:28:36+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 9.62, 9.98, 9.39
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_deque0       437105654 ns       906246 ns           10
BM_deque        303977738 ns      1225462 ns           10
BM_deque_lf    2378193631 ns      1011692 ns           10
BM_deque_lf_s   810258823 ns      1065492 ns           10
BM_deque2_lf   1348414185 ns      1008884 ns           10
BM_deque2_lf_s  370199446 ns       923346 ns           10
BM_ypipe2       556124677 ns       967569 ns           10
BM_ypipe        272269823 ns       928639 ns           10
BM_ypipe_s      276644085 ns      1051539 ns           10
BM_ypipe_lf     700218854 ns      1055654 ns           10
BM_ypipe_lf_s   385290462 ns      1094277 ns           10
```
# some payload while processing msg.
```
2020-12-15T12:32:41+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 8.41, 9.76, 9.52
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_deque0       669427338 ns       992993 ns           10
BM_deque        742035623 ns       945639 ns           10
BM_deque_lf    2810051308 ns      1054615 ns            1
BM_deque_lf_s  2079515108 ns       896354 ns           10
BM_deque2_lf   2711695462 ns       949076 ns            1
BM_deque2_lf_s 1684400431 ns       958600 ns           10
BM_ypipe2       648851069 ns       932554 ns           10
BM_ypipe        656406154 ns       885708 ns           10
BM_ypipe_s      664041015 ns       947492 ns           10
BM_ypipe_lf    2871353539 ns       985076 ns            1
BM_ypipe_lf_s  1706803669 ns       950215 ns           10
```
```
2020-12-15T12:34:58+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 11.47, 11.10, 10.10
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_deque0       689681862 ns       978485 ns           10
BM_deque        753563746 ns       880685 ns           10
BM_deque_lf    2904524923 ns       992694 ns            1
BM_deque_lf_s  2154291177 ns       991016 ns           10
BM_deque2_lf   2801130846 ns       852693 ns            1
BM_deque2_lf_s 1749350546 ns       943200 ns           10
BM_ypipe2       661359131 ns      1033961 ns           10
BM_ypipe        679750585 ns       958569 ns           10
BM_ypipe_s      685690608 ns       973607 ns           10
BM_ypipe_lf    2681418154 ns       948230 ns            1
BM_ypipe_lf_s  1479695246 ns      1074076 ns           10

```
# block twice every processing msg
(io, rpc, redis, memcached, database, etc.)
```
2020-12-18T12:02:54+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 9.65, 9.68, 9.40
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_deque0      1383219754 ns       947969 ns           10
BM_deque       1425159854 ns       979593 ns           10
BM_deque_lf    1850069615 ns      1078908 ns           10
BM_deque_lf_s  1535946677 ns       971100 ns           10
BM_deque2_lf   1843269831 ns       974161 ns           10
BM_deque2_lf_s 1506488054 ns      1023677 ns           10
BM_ypipe2      1369727592 ns       900431 ns           10
BM_ypipe       1423148023 ns       921755 ns           10
BM_ypipe_s     1395538600 ns      1063323 ns           10
BM_ypipe_lf    1744946746 ns       957177 ns           10
BM_ypipe_lf_s  1489239477 ns      1002100 ns           10

```
# block quard times every processing msg
(io, rpc, redis, memcached, database, etc.)
```
2020-12-18T12:15:04+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 9.24, 9.77, 10.07
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_deque0      2544782215 ns       946792 ns           10
BM_deque       2638691385 ns       796924 ns            1
BM_deque_lf    2654305692 ns       918922 ns            1
BM_deque_lf_s  2657601001 ns       873692 ns            1
BM_deque2_lf   2668659692 ns       995923 ns            1
BM_deque2_lf_s 2650412693 ns      1121616 ns            1
BM_ypipe2      2605346308 ns      1047308 ns            1
BM_ypipe       2618035154 ns      1028538 ns            1
BM_ypipe_s     2651578693 ns      1491232 ns            1
BM_ypipe_lf    2689262692 ns       982462 ns            1
BM_ypipe_lf_s  2630038231 ns       958000 ns            1

```
### history benchmark
```
Run on (7 X 1391 MHz CPU s)
Load Average: 8.96, 9.03, 9.14
-------------------------------------------------------
Benchmark             Time             CPU   Iterations
-------------------------------------------------------
BM_yield0       6251015 ns      6250401 ns          110
BM_cvnotify0    1057620 ns      1057589 ns          661
BM_yield       42631200 ns       778752 ns          100
BM_yield2     241884073 ns       950623 ns          100
BM_deque0     399871946 ns      1061908 ns           10
BM_deque      291839992 ns      1028031 ns           10
BM_deque_lf   516897385 ns      1056969 ns           10
BM_ypipe2     369288900 ns       910716 ns           10
BM_ypipe      180525448 ns      1037321 ns          100
```

