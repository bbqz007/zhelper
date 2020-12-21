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
```
2020-12-21T21:10:29+00:00
Running ./build-cb/ysample
Run on (8 X 1391 MHz CPU s)
Load Average: 7.80, 8.58, 8.87
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6258530 ns      6258190 ns          112
BM_cvnotify0              1118214 ns      1118133 ns          625
BM_yield                 39614689 ns       730523 ns          100
BM_yield2               259606623 ns       953715 ns           10
BM_deque0/0/0           457414985 ns      1068261 ns           10
BM_deque0/100/1         513746585 ns       984469 ns           10
BM_deque0/100/2         500229700 ns      1148215 ns           10
BM_deque0/100/3         504176631 ns      1183669 ns           10
BM_deque0/100/4         536882431 ns      1054785 ns           10
BM_deque0/1024/1        561731600 ns      1100085 ns           10
BM_deque0/1024/2        506252392 ns      1111946 ns           10
BM_deque0/1024/3        494779261 ns      1082800 ns           10
BM_deque0/1024/4        473133323 ns       974838 ns           10
BM_deque0/8192/1       1018630169 ns       973885 ns           10
BM_deque0/8192/2        976618331 ns      1172107 ns           10
BM_deque0/8192/3        943360977 ns      1151569 ns           10
BM_deque0/8192/4        905565308 ns      1065631 ns           10
BM_deque0/16384/1      1919328992 ns      1064108 ns           10
BM_deque0/16384/2      1873661646 ns       998077 ns           10
BM_deque0/16384/3      1814747485 ns      1119046 ns           10
BM_deque0/16384/4      1787401316 ns       957861 ns           10
BM_deque/0/0            343288938 ns      1175331 ns           10
BM_deque/100/1          608898646 ns      1189562 ns           10
BM_deque/100/2          515930446 ns      1226608 ns           10
BM_deque/100/3          512654185 ns      1147092 ns           10
BM_deque/100/4          537664385 ns      1226246 ns           10
BM_deque/1024/1         708835823 ns      1156815 ns           10
BM_deque/1024/2         554743085 ns      1173185 ns           10
BM_deque/1024/3         553023523 ns      1171800 ns           10
BM_deque/1024/4         534713308 ns      1000699 ns           10
BM_deque/8192/1        1158462569 ns      1182015 ns           10
BM_deque/8192/2        1051709577 ns      1220100 ns           10
BM_deque/8192/3        1009457185 ns      1180246 ns           10
BM_deque/8192/4         969527362 ns      1012592 ns           10
BM_deque/16384/1       2029063393 ns      1096900 ns           10
BM_deque/16384/2       1925264016 ns      1186277 ns           10
BM_deque/16384/3       1894455577 ns      1084100 ns           10
BM_deque/16384/4       1795102215 ns       977615 ns           10
BM_deque_lf/0/0        2668826923 ns      1049154 ns            1
BM_deque_lf/100/1      3066178154 ns      1051077 ns            1
BM_deque_lf/100/2      3089150308 ns      1026002 ns            1
BM_deque_lf/100/3      3052180462 ns       921847 ns            1
BM_deque_lf/100/4      2971565616 ns      1271383 ns            1
BM_deque_lf/1024/1     3366834154 ns      1390614 ns            1
BM_deque_lf/1024/2     3316689539 ns       958462 ns            1
BM_deque_lf/1024/3     3298593077 ns      1085770 ns            1
BM_deque_lf/1024/4     3263844615 ns       966000 ns            1
BM_deque_lf/8192/1     2771238616 ns      1202231 ns            1
BM_deque_lf/8192/2     2637715385 ns      1123615 ns            1
BM_deque_lf/8192/3     2760958616 ns      1018768 ns            1
BM_deque_lf/8192/4     2547510062 ns      1097369 ns           10
BM_deque_lf/16384/1    2390683823 ns      1095500 ns           10
BM_deque_lf/16384/2    2306625831 ns      1120969 ns           10
BM_deque_lf/16384/3    2243606485 ns      1148469 ns           10
BM_deque_lf/16384/4    2186393639 ns      1052008 ns           10
BM_deque_lf_s/0/0       781287685 ns      1144631 ns           10
BM_deque_lf_s/100/1    1279855192 ns      1053123 ns           10
BM_deque_lf_s/100/2    1320489223 ns      1064662 ns           10
BM_deque_lf_s/100/3    1270194039 ns       979100 ns           10
BM_deque_lf_s/100/4    1164092146 ns      1072538 ns           10
BM_deque_lf_s/1024/1   2543681462 ns      1348306 ns            1
BM_deque_lf_s/1024/2   2558828077 ns      1153306 ns            1
BM_deque_lf_s/1024/3   2491220531 ns      1053169 ns           10
BM_deque_lf_s/1024/4   2423997077 ns      1009376 ns           10
BM_deque_lf_s/8192/1   1877482223 ns      1137262 ns           10
BM_deque_lf_s/8192/2   1783843654 ns      1129000 ns           10
BM_deque_lf_s/8192/3   1756663962 ns      1173846 ns           10
BM_deque_lf_s/8192/4   1640447692 ns      1121916 ns           10
BM_deque_lf_s/16384/1  2163925700 ns      1178292 ns           10
BM_deque_lf_s/16384/2  2060893408 ns      1179069 ns           10
BM_deque_lf_s/16384/3  1999843185 ns      1192331 ns           10
BM_deque_lf_s/16384/4  1992349100 ns      1192870 ns           10
BM_deque2_lf/0/0       1291925615 ns      1196692 ns           10
BM_deque2_lf/100/1     2663039692 ns      1111923 ns            1
BM_deque2_lf/100/2     2733501446 ns      1204047 ns           10
BM_deque2_lf/100/3     2751256077 ns       989077 ns            1
BM_deque2_lf/100/4     2423945677 ns      1153138 ns           10
BM_deque2_lf/1024/1    3276899769 ns      1131153 ns            1
BM_deque2_lf/1024/2    3228666462 ns      1705077 ns            1
BM_deque2_lf/1024/3    3264471462 ns       980999 ns            1
BM_deque2_lf/1024/4    3254536693 ns      1040691 ns            1
BM_deque2_lf/8192/1    2305235800 ns      1151692 ns           10
BM_deque2_lf/8192/2    2284173523 ns      1259931 ns           10
BM_deque2_lf/8192/3    2307421539 ns      1255162 ns           10
BM_deque2_lf/8192/4    2106621062 ns      1043630 ns           10
BM_deque2_lf/16384/1   2225523231 ns      1093684 ns           10
BM_deque2_lf/16384/2   2186409716 ns      1234023 ns           10
BM_deque2_lf/16384/3   2130159223 ns      1199500 ns           10
BM_deque2_lf/16384/4   2074861131 ns      1028100 ns           10
BM_deque2_lf_s/0/0      368855677 ns      1010646 ns           10
BM_deque2_lf_s/100/1   1122695877 ns      1152876 ns           10
BM_deque2_lf_s/100/2   1015847885 ns      1146939 ns           10
BM_deque2_lf_s/100/3    899631077 ns      1031115 ns           10
BM_deque2_lf_s/100/4    729509392 ns      1118869 ns           10
BM_deque2_lf_s/1024/1  2374636869 ns      1122146 ns           10
BM_deque2_lf_s/1024/2  2357219754 ns      1115061 ns           10
BM_deque2_lf_s/1024/3  2314269000 ns      1148576 ns           10
BM_deque2_lf_s/1024/4  2209885585 ns      1075254 ns           10
BM_deque2_lf_s/8192/1  1398877877 ns      1170276 ns           10
BM_deque2_lf_s/8192/2  1405903700 ns      1191307 ns           10
BM_deque2_lf_s/8192/3  1354315608 ns      1154277 ns           10
BM_deque2_lf_s/8192/4  1283678092 ns      1124823 ns           10
BM_deque2_lf_s/16384/1 2073202569 ns      1150807 ns           10
BM_deque2_lf_s/16384/2 2033885292 ns      1109884 ns           10
BM_deque2_lf_s/16384/3 1949708862 ns      1154884 ns           10
BM_deque2_lf_s/16384/4 1942381000 ns      1004700 ns           10
BM_ypipe2/0/0           618639039 ns      1156239 ns           10
BM_ypipe2/100/1        1266815246 ns       910700 ns           10
BM_ypipe2/100/2         287214546 ns      1165284 ns           10
BM_ypipe2/100/3         274604885 ns      1099655 ns           10
BM_ypipe2/100/4         283250762 ns       999800 ns           10
BM_ypipe2/1024/1        946384985 ns       995770 ns           10
BM_ypipe2/1024/2        279194892 ns      1149315 ns           10
BM_ypipe2/1024/3        278182339 ns      1138785 ns           10
BM_ypipe2/1024/4        239824210 ns      1041123 ns          100
BM_ypipe2/8192/1       1062492238 ns      1264324 ns           10
BM_ypipe2/8192/2       1006686523 ns      1258223 ns           10
BM_ypipe2/8192/3        949991931 ns      1134893 ns           10
BM_ypipe2/8192/4        931968831 ns       996308 ns           10
BM_ypipe2/16384/1      2016995869 ns      1183784 ns           10
BM_ypipe2/16384/2      1952196469 ns      1129539 ns           10
BM_ypipe2/16384/3      1860959762 ns      1132385 ns           10
BM_ypipe2/16384/4      1835850169 ns      1097108 ns           10
BM_ypipe/0/0            263293761 ns      1216685 ns           10
BM_ypipe/100/1          504186846 ns       936731 ns           10
BM_ypipe/100/2          289071308 ns      1101946 ns           10
BM_ypipe/100/3          282847077 ns      1056661 ns           10
BM_ypipe/100/4          283090054 ns      1189223 ns           10
BM_ypipe/1024/1         497204892 ns      1068408 ns           10
BM_ypipe/1024/2         294843523 ns      1173292 ns           10
BM_ypipe/1024/3         286437338 ns      1272953 ns           10
BM_ypipe/1024/4         248977252 ns      1037874 ns          100
BM_ypipe/8192/1        1062059685 ns      1083700 ns           10
BM_ypipe/8192/2        1015035923 ns      1224262 ns           10
BM_ypipe/8192/3         958666769 ns      1268977 ns           10
BM_ypipe/8192/4         921878062 ns      1202847 ns           10
BM_ypipe/16384/1       2000526239 ns      1199692 ns           10
BM_ypipe/16384/2       1958272108 ns      1169085 ns           10
BM_ypipe/16384/3       1859959308 ns      1203946 ns           10
BM_ypipe/16384/4       1838848477 ns      1008454 ns           10
BM_ypipe_s/0/0          261844569 ns      1018615 ns           10
BM_ypipe_s/100/1        524962792 ns       943846 ns           10
BM_ypipe_s/100/2        289540585 ns      1042977 ns           10
BM_ypipe_s/100/3        287419808 ns      1080016 ns           10
BM_ypipe_s/100/4        261023700 ns      1261177 ns           10
BM_ypipe_s/1024/1       505298323 ns      1029439 ns           10
BM_ypipe_s/1024/2       287652862 ns      1207715 ns           10
BM_ypipe_s/1024/3       285985131 ns      1245946 ns           10
BM_ypipe_s/1024/4       247165870 ns      1028900 ns          100
BM_ypipe_s/8192/1      1058166239 ns      1192931 ns           10
BM_ypipe_s/8192/2      1007629146 ns      1299807 ns           10
BM_ypipe_s/8192/3       963762269 ns      1185785 ns           10
BM_ypipe_s/8192/4       927795416 ns      1111138 ns           10
BM_ypipe_s/16384/1     2000712508 ns      1311515 ns           10
BM_ypipe_s/16384/2     1961666523 ns      1196455 ns           10
BM_ypipe_s/16384/3     1866126231 ns      1184677 ns           10
BM_ypipe_s/16384/4     1826332931 ns      1069408 ns           10
BM_ypipe_lf/0/0         638899200 ns      1024846 ns           10
BM_ypipe_lf/100/1      2570754924 ns      1060307 ns            1
BM_ypipe_lf/100/2      2058594985 ns      1027015 ns           10
BM_ypipe_lf/100/3      1844119839 ns      1139269 ns           10
BM_ypipe_lf/100/4      1523430915 ns      1045031 ns           10
BM_ypipe_lf/1024/1     3127296231 ns      1391537 ns            1
BM_ypipe_lf/1024/2     3131615385 ns      1007077 ns            1
BM_ypipe_lf/1024/3     3094190384 ns      1170232 ns            1
BM_ypipe_lf/1024/4     3032956846 ns      1158230 ns            1
BM_ypipe_lf/8192/1     2104076662 ns      1309392 ns           10
BM_ypipe_lf/8192/2     2099411562 ns      1201085 ns           10
BM_ypipe_lf/8192/3     2111996585 ns      1181323 ns           10
BM_ypipe_lf/8192/4     1900837508 ns      1199754 ns           10
BM_ypipe_lf/16384/1    2147630531 ns      1150231 ns           10
BM_ypipe_lf/16384/2    2139315192 ns      1329330 ns           10
BM_ypipe_lf/16384/3    2061854523 ns      1153638 ns           10
BM_ypipe_lf/16384/4    2015159069 ns      1105477 ns           10
BM_ypipe_lf_s/0/0       386519661 ns      1101416 ns           10
BM_ypipe_lf_s/100/1    1115373362 ns      1132885 ns           10
BM_ypipe_lf_s/100/2     862643892 ns      1141684 ns           10
BM_ypipe_lf_s/100/3     823497146 ns      1150169 ns           10
BM_ypipe_lf_s/100/4     640515785 ns      1062092 ns           10
BM_ypipe_lf_s/1024/1   2196041477 ns      1249662 ns           10
BM_ypipe_lf_s/1024/2   2125478000 ns      1156600 ns           10
BM_ypipe_lf_s/1024/3   2071152415 ns      1222993 ns           10
BM_ypipe_lf_s/1024/4   2009609123 ns      1081238 ns           10
BM_ypipe_lf_s/8192/1   1349145362 ns      1159238 ns           10
BM_ypipe_lf_s/8192/2   1364879423 ns      1301484 ns           10
BM_ypipe_lf_s/8192/3   1295604992 ns      1367699 ns           10
BM_ypipe_lf_s/8192/4   1201466785 ns      1253384 ns           10
BM_ypipe_lf_s/16384/1  2091160962 ns      1325346 ns           10
BM_ypipe_lf_s/16384/2  2024924531 ns      1196469 ns           10
BM_ypipe_lf_s/16384/3  1939442677 ns      1281739 ns           10
BM_ypipe_lf_s/16384/4  1909186192 ns      1095384 ns           10
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

