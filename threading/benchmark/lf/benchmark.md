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

may be read a value from redis, send request and block to recv respone.

then update a value to redis, send request and block to recv respone.
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
# affine cache
benchmark/msgsize/policy

policy: 0. empty msg; 1. bad affine; 2. good affine.
```
2020-12-20T12:14:09+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 8.54, 8.98, 9.15
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
BM_deque0/0/0          460263092 ns      1013831 ns           10
BM_deque0/100/1        543731946 ns      1099162 ns           10
BM_deque0/100/2        514671331 ns      1035000 ns           10
BM_deque0/1024/1       631534754 ns      1123430 ns           10
BM_deque0/1024/2       551457792 ns      1121077 ns           10
BM_deque0/8192/1       817013069 ns      1195992 ns           10
BM_deque0/8192/2       736480454 ns      1260684 ns           10
BM_deque/0/0           334201577 ns      1062515 ns           10
BM_deque/100/1         562195423 ns      1157007 ns           10
BM_deque/100/2         482713923 ns      1154616 ns           10
BM_deque/1024/1        716193239 ns      1076900 ns           10
BM_deque/1024/2        544684300 ns      1106099 ns           10
BM_deque/8192/1        961161669 ns      1027954 ns           10
BM_deque/8192/2        788024769 ns      1060085 ns           10
BM_deque_lf/0/0       2507887231 ns       960845 ns            1
BM_deque_lf/100/1     2944434462 ns      1063692 ns            1
BM_deque_lf/100/2     2989829384 ns      1199767 ns            1
BM_deque_lf/1024/1    3307002923 ns      1087385 ns            1
BM_deque_lf/1024/2    3239655154 ns       813922 ns            1
BM_deque_lf/8192/1    3108513308 ns      1108384 ns            1
BM_deque_lf/8192/2    3020595154 ns       969770 ns            1
BM_deque_lf_s/0/0      783674200 ns      1051508 ns           10
BM_deque_lf_s/100/1   1174130669 ns      1171662 ns           10
BM_deque_lf_s/100/2   1202411954 ns      1122808 ns           10
BM_deque_lf_s/1024/1  2181430592 ns      1060785 ns           10
BM_deque_lf_s/1024/2  2127477046 ns       981362 ns           10
BM_deque_lf_s/8192/1  2361141777 ns      1098039 ns           10
BM_deque_lf_s/8192/2  2161509254 ns      1164377 ns           10
BM_deque2_lf/0/0       885732854 ns      1077576 ns           10
BM_deque2_lf/100/1    2670369308 ns      1149694 ns            1
BM_deque2_lf/100/2    2586101077 ns      1373619 ns            1
BM_deque2_lf/1024/1   3151291539 ns      1225077 ns            1
BM_deque2_lf/1024/2   3102237000 ns      1077999 ns            1
BM_deque2_lf/8192/1   2953772846 ns      1183923 ns            1
BM_deque2_lf/8192/2   2872048077 ns       947077 ns            1
BM_deque2_lf_s/0/0     341067438 ns       934246 ns           10
BM_deque2_lf_s/100/1   979686377 ns      1027869 ns           10
BM_deque2_lf_s/100/2   752468608 ns      1064408 ns           10
BM_deque2_lf_s/1024/1 2036569862 ns      1143915 ns           10
BM_deque2_lf_s/1024/2 1977876285 ns      1075823 ns           10
BM_deque2_lf_s/8192/1 1680677554 ns      1058454 ns           10
BM_deque2_lf_s/8192/2 1650201400 ns      1081616 ns           10
BM_ypipe2/0/0          823684938 ns       938331 ns           10
BM_ypipe2/100/1       1322318992 ns       959131 ns           10
BM_ypipe2/100/2        227087970 ns      1115919 ns          100
BM_ypipe2/1024/1      1052851754 ns      1003554 ns           10
BM_ypipe2/1024/2       275377608 ns      1095885 ns           10
BM_ypipe2/8192/1       797503539 ns      1063700 ns           10
BM_ypipe2/8192/2       701391438 ns      1188377 ns           10
BM_ypipe/0/0           233252908 ns      1038547 ns          100
BM_ypipe/100/1         475601577 ns       956846 ns           10
BM_ypipe/100/2         243740583 ns      1032005 ns          100
BM_ypipe/1024/1        535145277 ns       990554 ns           10
BM_ypipe/1024/2        280795831 ns      1376777 ns           10
BM_ypipe/8192/1        812910654 ns      1063146 ns           10
BM_ypipe/8192/2        714253808 ns      1242808 ns           10
BM_ypipe_s/0/0         230490296 ns      1045536 ns          100
BM_ypipe_s/100/1       474671331 ns      1035431 ns           10
BM_ypipe_s/100/2       245182119 ns      1076981 ns          100
BM_ypipe_s/1024/1      544223992 ns       944054 ns           10
BM_ypipe_s/1024/2      279394431 ns      1254407 ns           10
BM_ypipe_s/8192/1      813842808 ns      1077577 ns           10
BM_ypipe_s/8192/2      718482862 ns      1150715 ns           10
BM_ypipe_lf/0/0        907345608 ns      1048908 ns           10
BM_ypipe_lf/100/1     2612345000 ns      1325615 ns            1
BM_ypipe_lf/100/2     1979895769 ns      1202731 ns           10
BM_ypipe_lf/1024/1    3219559077 ns      1519155 ns            1
BM_ypipe_lf/1024/2    3178703462 ns      1148153 ns            1
BM_ypipe_lf/8192/1    2940031923 ns      1170079 ns            1
BM_ypipe_lf/8192/2    2835176923 ns      1211845 ns            1
BM_ypipe_lf_s/0/0      425571854 ns      1159861 ns           10
BM_ypipe_lf_s/100/1   1079632569 ns      1065131 ns           10
BM_ypipe_lf_s/100/2    893351846 ns      1031000 ns           10
BM_ypipe_lf_s/1024/1  2131990369 ns      1092816 ns           10
BM_ypipe_lf_s/1024/2  2066249869 ns      1024577 ns           10
BM_ypipe_lf_s/8192/1  1628899108 ns      1205131 ns           10
BM_ypipe_lf_s/8192/2  1589511985 ns      1121154 ns           10

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

