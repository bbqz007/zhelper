**platform**
a 3 clusters cpu of arm arch. 2x1.3(a53), 4x1.8(a53), 2x2.3(a72). no L3 cache, cores in the same cluster share L2 cache.
linux kerenl 3.18.
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
### affine
```Run on (8 X 1391 MHz CPU s)
Load Average: 7.72, 9.16, 14.56
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6195304 ns      6193542 ns          113
BM_cvnotify0               792196 ns       791967 ns          881
BM_yield                 39809763 ns       713133 ns          100
BM_yield2               160736718 ns       920124 ns          100
BM_deque0/0/0           290572338 ns       869423 ns           10
BM_deque0/100/1         552458508 ns       742954 ns           10
BM_deque0/100/2         338197654 ns       828054 ns           10
BM_deque0/100/3         332591015 ns       825193 ns           10
BM_deque0/100/4         336848000 ns       849408 ns           10
BM_deque0/1024/1        591850262 ns       931861 ns           10
BM_deque0/1024/2        409752854 ns       960246 ns           10
BM_deque0/1024/3        406467408 ns       857376 ns           10
BM_deque0/1024/4        387634239 ns       900016 ns           10
BM_deque0/8192/1        698219538 ns       987769 ns           10
BM_deque0/8192/2        469947715 ns      1017331 ns           10
BM_deque0/8192/3        447544200 ns      1064968 ns           10
BM_deque0/8192/4        381849146 ns       747946 ns           10
BM_deque0/16384/1       852111677 ns      1118415 ns           10
BM_deque0/16384/2       642927846 ns      1059585 ns           10
BM_deque0/16384/3       583760892 ns       932638 ns           10
BM_deque0/16384/4       491163492 ns       873738 ns           10
BM_deque/0/0            168610617 ns       815142 ns          100
BM_deque/100/1          490858738 ns      1022685 ns           10
BM_deque/100/2          282048862 ns       854362 ns           10
BM_deque/100/3          276943738 ns       921600 ns           10
BM_deque/100/4          256273769 ns       848169 ns           10
BM_deque/1024/1         639007285 ns       951953 ns           10
BM_deque/1024/2         395619854 ns      1015931 ns           10
BM_deque/1024/3         390480900 ns       879484 ns           10
BM_deque/1024/4         407520308 ns       789185 ns           10
BM_deque/8192/1         821297246 ns      1108531 ns           10
BM_deque/8192/2         477389400 ns      1087831 ns           10
BM_deque/8192/3         476804831 ns      1283654 ns           10
BM_deque/8192/4         387755792 ns       863469 ns           10
BM_deque/16384/1       1003727954 ns      1201039 ns           10
BM_deque/16384/2        664642746 ns      1086838 ns           10
BM_deque/16384/3        611587623 ns      1133185 ns           10
BM_deque/16384/4        508987046 ns      1072016 ns           10
BM_deque_lf/0/0        1174454915 ns       872323 ns           10
BM_deque_lf/100/1      2418596277 ns      1006569 ns           10
BM_deque_lf/100/2      2190728662 ns       966830 ns           10
BM_deque_lf/100/3      2047156862 ns       906954 ns           10
BM_deque_lf/100/4      1611365908 ns       956546 ns           10
BM_deque_lf/1024/1     2704806154 ns       930076 ns            1
BM_deque_lf/1024/2     2518223800 ns       982261 ns           10
BM_deque_lf/1024/3     2494467992 ns       997769 ns           10
BM_deque_lf/1024/4     2393456477 ns       859600 ns           10
BM_deque_lf/8192/1     3100409001 ns      1081154 ns            1
BM_deque_lf/8192/2     2868553385 ns      1120384 ns            1
BM_deque_lf/8192/3     2911669847 ns      1437617 ns            1
BM_deque_lf/8192/4     2786085000 ns       914922 ns            1
BM_deque_lf/16384/1    3025026461 ns      1176384 ns            1
BM_deque_lf/16384/2    2889063154 ns      1243156 ns            1
BM_deque_lf/16384/3    2834230615 ns       983771 ns            1
BM_deque_lf/16384/4    2759212385 ns       861230 ns            1
BM_deque_lf_s/0/0       465612331 ns       964931 ns           10
BM_deque_lf_s/100/1    1177949392 ns      1019346 ns           10
BM_deque_lf_s/100/2    1012991246 ns       937569 ns           10
BM_deque_lf_s/100/3     967555323 ns      1049608 ns           10
BM_deque_lf_s/100/4     704973631 ns       897354 ns           10
BM_deque_lf_s/1024/1   1762063408 ns      1070830 ns           10
BM_deque_lf_s/1024/2   1532407016 ns      1077762 ns           10
BM_deque_lf_s/1024/3   1491644500 ns      1089661 ns           10
BM_deque_lf_s/1024/4   1234840969 ns      1046315 ns           10
BM_deque_lf_s/8192/1   2534607477 ns      1105785 ns           10
BM_deque_lf_s/8192/2   2367112500 ns       974992 ns           10
BM_deque_lf_s/8192/3   2367440731 ns       977284 ns           10
BM_deque_lf_s/8192/4   2232681969 ns       901554 ns           10
BM_deque_lf_s/16384/1  1978555746 ns      1146031 ns           10
BM_deque_lf_s/16384/2  1799401400 ns      1051653 ns           10
BM_deque_lf_s/16384/3  1755530277 ns      1079361 ns           10
BM_deque_lf_s/16384/4  1466809700 ns       859431 ns           10
BM_deque2_lf/0/0        654328331 ns       898031 ns           10
BM_deque2_lf/100/1     2122408669 ns       845831 ns           10
BM_deque2_lf/100/2     1658076362 ns       971531 ns           10
BM_deque2_lf/100/3     1713868785 ns      1389124 ns           10
BM_deque2_lf/100/4     1135500500 ns       918154 ns           10
BM_deque2_lf/1024/1    2575518538 ns       805846 ns            1
BM_deque2_lf/1024/2    2366938916 ns       863846 ns           10
BM_deque2_lf/1024/3    2306956485 ns       912300 ns           10
BM_deque2_lf/1024/4    2144642846 ns       919961 ns           10
BM_deque2_lf/8192/1    2919250692 ns       868537 ns            1
BM_deque2_lf/8192/2    2860507769 ns       855769 ns            1
BM_deque2_lf/8192/3    2852842846 ns       879845 ns            1
BM_deque2_lf/8192/4    2738124231 ns       945538 ns            1
BM_deque2_lf/16384/1   2714411000 ns      1243308 ns            1
BM_deque2_lf/16384/2   2752186847 ns      1227154 ns            1
BM_deque2_lf/16384/3   2756083769 ns       780000 ns            1
BM_deque2_lf/16384/4   2595217693 ns       798155 ns            1
BM_deque2_lf_s/0/0      224717929 ns       949050 ns          100
BM_deque2_lf_s/100/1    939773023 ns       883815 ns           10
BM_deque2_lf_s/100/2    740365438 ns       860231 ns           10
BM_deque2_lf_s/100/3    712237239 ns       886100 ns           10
BM_deque2_lf_s/100/4    485169046 ns       803862 ns           10
BM_deque2_lf_s/1024/1  1623870692 ns       887338 ns           10
BM_deque2_lf_s/1024/2  1356202762 ns       880431 ns           10
BM_deque2_lf_s/1024/3  1297426392 ns       893378 ns           10
BM_deque2_lf_s/1024/4  1045070069 ns       907738 ns           10
BM_deque2_lf_s/8192/1  2124951885 ns       991607 ns           10
BM_deque2_lf_s/8192/2  2034684177 ns      2671038 ns           10
BM_deque2_lf_s/8192/3  2007886962 ns       923639 ns           10
BM_deque2_lf_s/8192/4  1923684023 ns       876054 ns           10
BM_deque2_lf_s/16384/1 1494537331 ns      1031069 ns           10
BM_deque2_lf_s/16384/2 1364193108 ns      1091231 ns           10
BM_deque2_lf_s/16384/3 1323755169 ns      1039423 ns           10
BM_deque2_lf_s/16384/4 1123307216 ns       854900 ns           10
BM_ypipe/0/0            133285535 ns       821748 ns          100
BM_ypipe/100/1          402432285 ns       730600 ns           10
BM_ypipe/100/2          177143194 ns      1589396 ns          100
BM_ypipe/100/3          163885353 ns       891376 ns          100
BM_ypipe/100/4          136182628 ns       844145 ns          100
BM_ypipe/1024/1         523509962 ns       792385 ns           10
BM_ypipe/1024/2         248397698 ns       957998 ns          100
BM_ypipe/1024/3         237474988 ns       943773 ns          100
BM_ypipe/1024/4         212018369 ns       815508 ns          100
BM_ypipe/8192/1         574730685 ns      1193346 ns           10
BM_ypipe/8192/2         347471231 ns      1248585 ns           10
BM_ypipe/8192/3         318378669 ns      1058270 ns           10
BM_ypipe/8192/4         251735069 ns      1068838 ns           10
BM_ypipe/16384/1        768429208 ns      1182592 ns           10
BM_ypipe/16384/2        586220331 ns      1339269 ns           10
BM_ypipe/16384/3        539857908 ns      1104354 ns           10
BM_ypipe/16384/4        444543823 ns       908985 ns           10
BM_ypipe_s/0/0          128692848 ns       860031 ns          100
BM_ypipe_s/100/1        402536408 ns       747570 ns           10
BM_ypipe_s/100/2        175506232 ns       910642 ns          100
BM_ypipe_s/100/3        164956680 ns       908709 ns          100
BM_ypipe_s/100/4        137115895 ns       847944 ns          100
BM_ypipe_s/1024/1       522325054 ns       840385 ns           10
BM_ypipe_s/1024/2       247154771 ns       936665 ns          100
BM_ypipe_s/1024/3       236813021 ns       973080 ns          100
BM_ypipe_s/1024/4       210958016 ns       840239 ns          100
BM_ypipe_s/8192/1       574252046 ns      1020908 ns           10
BM_ypipe_s/8192/2       349835062 ns      1096269 ns           10
BM_ypipe_s/8192/3       324389292 ns      1167754 ns           10
BM_ypipe_s/8192/4       251007762 ns       881192 ns           10
BM_ypipe_s/16384/1      769154969 ns      1040177 ns           10
BM_ypipe_s/16384/2      591830823 ns      1306769 ns           10
BM_ypipe_s/16384/3      534237354 ns      1220338 ns           10
BM_ypipe_s/16384/4      449667223 ns      1137438 ns           10
BM_ypipe_lf/0/0         576307977 ns       805184 ns           10
BM_ypipe_lf/100/1      2155937585 ns       794416 ns           10
BM_ypipe_lf/100/2      1712446939 ns       850400 ns           10
BM_ypipe_lf/100/3      1633488377 ns       904708 ns           10
BM_ypipe_lf/100/4      1117636762 ns       817977 ns           10
BM_ypipe_lf/1024/1     2536752462 ns       901461 ns            1
BM_ypipe_lf/1024/2     2304516615 ns       929876 ns           10
BM_ypipe_lf/1024/3     2267285093 ns       916923 ns           10
BM_ypipe_lf/1024/4     2081753531 ns       769077 ns           10
BM_ypipe_lf/8192/1     2890409308 ns       930460 ns            1
BM_ypipe_lf/8192/2     2819386154 ns       685462 ns            1
BM_ypipe_lf/8192/3     2771563847 ns       895538 ns            1
BM_ypipe_lf/8192/4     2728862308 ns       822232 ns            1
BM_ypipe_lf/16384/1    2680233847 ns       818537 ns            1
BM_ypipe_lf/16384/2    2687268770 ns       985153 ns            1
BM_ypipe_lf/16384/3    2590864000 ns       859152 ns            1
BM_ypipe_lf/16384/4    2516374946 ns       880977 ns           10
BM_ypipe_lf_s/0/0       254905015 ns       852453 ns           10
BM_ypipe_lf_s/100/1     941720315 ns       966908 ns           10
BM_ypipe_lf_s/100/2     722502362 ns       827862 ns           10
BM_ypipe_lf_s/100/3     691748462 ns       958262 ns           10
BM_ypipe_lf_s/100/4     453788692 ns       861723 ns           10
BM_ypipe_lf_s/1024/1   1605510908 ns      5908946 ns           10
BM_ypipe_lf_s/1024/2   1356969108 ns       978846 ns           10
BM_ypipe_lf_s/1024/3   1288886300 ns       971061 ns           10
BM_ypipe_lf_s/1024/4   1043131008 ns       822169 ns           10
BM_ypipe_lf_s/8192/1   1938715485 ns      1021254 ns           10
BM_ypipe_lf_s/8192/2   1865589731 ns       964099 ns           10
BM_ypipe_lf_s/8192/3   1841923200 ns       942908 ns           10
BM_ypipe_lf_s/8192/4   1742709246 ns       862369 ns           10
BM_ypipe_lf_s/16384/1  1406819677 ns       964738 ns           10
BM_ypipe_lf_s/16384/2  1255395931 ns      1006870 ns           10
BM_ypipe_lf_s/16384/3  1197471208 ns      1107662 ns           10
BM_ypipe_lf_s/16384/4   940539369 ns       835623 ns           10
```
### affine and block quad times per msg.
**8xW,8xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 7.99, 8.37, 10.09
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6217436 ns      6211919 ns          112
BM_cvnotify0               769922 ns       769216 ns          909
BM_yield                 39195876 ns       686956 ns          100
BM_yield2               152882112 ns       871401 ns          100
BM_deque0/0/0           928053146 ns       818807 ns           10
BM_deque0/100/1        1275606508 ns       866593 ns           10
BM_deque0/100/2        1126800677 ns       862892 ns           10
BM_deque0/100/3        1118069131 ns       863984 ns           10
BM_deque0/100/4         942005046 ns       852877 ns           10
BM_deque0/1024/1       1329693054 ns       874115 ns           10
BM_deque0/1024/2       1149860192 ns       904992 ns           10
BM_deque0/1024/3       1135432154 ns       912985 ns           10
BM_deque0/1024/4        950755123 ns       857562 ns           10
BM_deque0/8192/1       1428701500 ns       823770 ns           10
BM_deque0/8192/2       1225343900 ns       815592 ns           10
BM_deque0/8192/3       1204013692 ns       854515 ns           10
BM_deque0/8192/4        947500500 ns       828946 ns           10
BM_deque0/16384/1      1506309892 ns       849669 ns           10
BM_deque0/16384/2      1265804746 ns       761008 ns           10
BM_deque0/16384/3      1230705538 ns       837223 ns           10
BM_deque0/16384/4       941517077 ns       840400 ns           10
BM_deque/0/0            906537054 ns       814369 ns           10
BM_deque/100/1         1277389100 ns       845100 ns           10
BM_deque/100/2         1116404885 ns       847954 ns           10
BM_deque/100/3         1091800016 ns       833730 ns           10
BM_deque/100/4          915044146 ns       753385 ns           10
BM_deque/1024/1        1331465139 ns       894562 ns           10
BM_deque/1024/2        1149566108 ns       849315 ns           10
BM_deque/1024/3        1118944892 ns       846670 ns           10
BM_deque/1024/4         911535646 ns       803185 ns           10
BM_deque/8192/1        1431829116 ns       834901 ns           10
BM_deque/8192/2        1207525031 ns       961500 ns           10
BM_deque/8192/3        1189456892 ns       902907 ns           10
BM_deque/8192/4         916124323 ns       795800 ns           10
BM_deque/16384/1       1517438454 ns       859038 ns           10
BM_deque/16384/2       1260603254 ns       991946 ns           10
BM_deque/16384/3       1215660716 ns      1002354 ns           10
BM_deque/16384/4        918659623 ns       802515 ns           10
BM_deque_lf/0/0        2661110462 ns       710230 ns            1
BM_deque_lf/100/1      2702376154 ns       738616 ns            1
BM_deque_lf/100/2      2663728539 ns       821924 ns            1
BM_deque_lf/100/3      2661277077 ns       765307 ns            1
BM_deque_lf/100/4      2630651923 ns       864846 ns            1
BM_deque_lf/1024/1     2784052154 ns      1116000 ns            1
BM_deque_lf/1024/2     2680052308 ns       862462 ns            1
BM_deque_lf/1024/3     2694348462 ns       666000 ns            1
BM_deque_lf/1024/4     2637788077 ns       802308 ns            1
BM_deque_lf/8192/1     2821709692 ns       640154 ns            1
BM_deque_lf/8192/2     2725076693 ns       906001 ns            1
BM_deque_lf/8192/3     2699575693 ns       934461 ns            1
BM_deque_lf/8192/4     2645264769 ns       617615 ns            1
BM_deque_lf/16384/1    2867075615 ns       919076 ns            1
BM_deque_lf/16384/2    2769655615 ns       922078 ns            1
BM_deque_lf/16384/3    2766254154 ns       751692 ns            1
BM_deque_lf/16384/4    2678466615 ns       664846 ns            1
BM_deque_lf_s/0/0      2055772708 ns       792808 ns           10
BM_deque_lf_s/100/1    2046458146 ns       815684 ns           10
BM_deque_lf_s/100/2    2024307985 ns       841546 ns           10
BM_deque_lf_s/100/3    2028538139 ns       781723 ns           10
BM_deque_lf_s/100/4    2069079339 ns       790054 ns           10
BM_deque_lf_s/1024/1   2093500154 ns       890031 ns           10
BM_deque_lf_s/1024/2   2045208085 ns       858039 ns           10
BM_deque_lf_s/1024/3   2057299877 ns       879592 ns           10
BM_deque_lf_s/1024/4   2100004608 ns       828954 ns           10
BM_deque_lf_s/8192/1   2207719915 ns       930331 ns           10
BM_deque_lf_s/8192/2   2175838054 ns       877746 ns           10
BM_deque_lf_s/8192/3   2144508069 ns       879577 ns           10
BM_deque_lf_s/8192/4   2117004877 ns       802215 ns           10
BM_deque_lf_s/16384/1  2300966439 ns       882200 ns           10
BM_deque_lf_s/16384/2  2281869200 ns       872908 ns           10
BM_deque_lf_s/16384/3  2288302846 ns       856985 ns           10
BM_deque_lf_s/16384/4  2122935062 ns       898992 ns           10
BM_deque2_lf/0/0       2473010916 ns       829930 ns           10
BM_deque2_lf/100/1     2396012292 ns       800007 ns           10
BM_deque2_lf/100/2     2445088639 ns       775677 ns           10
BM_deque2_lf/100/3     2443572939 ns       824607 ns           10
BM_deque2_lf/100/4     2464043392 ns       799431 ns           10
BM_deque2_lf/1024/1    2392647723 ns       803092 ns           10
BM_deque2_lf/1024/2    2483663239 ns       784346 ns           10
BM_deque2_lf/1024/3    2493158939 ns       846746 ns           10
BM_deque2_lf/1024/4    2459255477 ns       827400 ns           10
BM_deque2_lf/8192/1    2443975392 ns       852115 ns           10
BM_deque2_lf/8192/2    2509808923 ns       801925 ns            1
BM_deque2_lf/8192/3    2500519693 ns      1096000 ns            1
BM_deque2_lf/8192/4    2461597569 ns       759916 ns           10
BM_deque2_lf/16384/1   2479748008 ns       962308 ns           10
BM_deque2_lf/16384/2   2560967385 ns      1057769 ns            1
BM_deque2_lf/16384/3   2548946154 ns       893386 ns            1
BM_deque2_lf/16384/4   2487861808 ns       755408 ns           10
BM_deque2_lf_s/0/0     1624388939 ns       769723 ns           10
BM_deque2_lf_s/100/1   1570083215 ns       854600 ns           10
BM_deque2_lf_s/100/2   1466100539 ns       747908 ns           10
BM_deque2_lf_s/100/3   1458617739 ns       792046 ns           10
BM_deque2_lf_s/100/4   1625954439 ns       934784 ns           10
BM_deque2_lf_s/1024/1  1606163531 ns       858377 ns           10
BM_deque2_lf_s/1024/2  1498292746 ns       814231 ns           10
BM_deque2_lf_s/1024/3  1527559723 ns       895616 ns           10
BM_deque2_lf_s/1024/4  1636865977 ns       834754 ns           10
BM_deque2_lf_s/8192/1  1714700677 ns       940331 ns           10
BM_deque2_lf_s/8192/2  1627176392 ns       950631 ns           10
BM_deque2_lf_s/8192/3  1567347377 ns       912561 ns           10
BM_deque2_lf_s/8192/4  1600032038 ns       825708 ns           10
BM_deque2_lf_s/16384/1 1776181838 ns       829061 ns           10
BM_deque2_lf_s/16384/2 1695841046 ns      1089447 ns           10
BM_deque2_lf_s/16384/3 1639867523 ns       962815 ns           10
BM_deque2_lf_s/16384/4 1587611977 ns       801547 ns           10
BM_ypipe/0/0            880019785 ns       810031 ns           10
BM_ypipe/100/1         1287890792 ns       843761 ns           10
BM_ypipe/100/2         1096072146 ns       812331 ns           10
BM_ypipe/100/3         1058110008 ns       794346 ns           10
BM_ypipe/100/4          875055731 ns       743477 ns           10
BM_ypipe/1024/1        1338456231 ns       849592 ns           10
BM_ypipe/1024/2        1115174346 ns       809254 ns           10
BM_ypipe/1024/3        1088091854 ns       858846 ns           10
BM_ypipe/1024/4         871700923 ns       784415 ns           10
BM_ypipe/8192/1        1423915500 ns       927200 ns           10
BM_ypipe/8192/2        1175665169 ns      1017061 ns           10
BM_ypipe/8192/3        1157934339 ns       963300 ns           10
BM_ypipe/8192/4         878366531 ns       813354 ns           10
BM_ypipe/16384/1       1494886200 ns       821053 ns           10
BM_ypipe/16384/2       1215538916 ns       925969 ns           10
BM_ypipe/16384/3       1189759500 ns       939908 ns           10
BM_ypipe/16384/4        876474431 ns       778723 ns           10
BM_ypipe_s/0/0          873766215 ns       759100 ns           10
BM_ypipe_s/100/1       1276603462 ns       837954 ns           10
BM_ypipe_s/100/2       1098818331 ns       814854 ns           10
BM_ypipe_s/100/3       1067332308 ns       827561 ns           10
BM_ypipe_s/100/4        874555669 ns       758776 ns           10
BM_ypipe_s/1024/1      1331538600 ns       749954 ns           10
BM_ypipe_s/1024/2      1109753785 ns       820877 ns           10
BM_ypipe_s/1024/3      1089572377 ns       885454 ns           10
BM_ypipe_s/1024/4       875613623 ns       792492 ns           10
BM_ypipe_s/8192/1      1439769869 ns       820300 ns           10
BM_ypipe_s/8192/2      1182159238 ns       977885 ns           10
BM_ypipe_s/8192/3      1140820877 ns       848130 ns           10
BM_ypipe_s/8192/4       880725592 ns       837054 ns           10
BM_ypipe_s/16384/1     1490544731 ns       880938 ns           10
BM_ypipe_s/16384/2     1222919662 ns       951077 ns           10
BM_ypipe_s/16384/3     1190344962 ns      1039646 ns           10
BM_ypipe_s/16384/4      877611816 ns       814800 ns           10
BM_ypipe_lf/0/0        2566300692 ns       725540 ns            1
BM_ypipe_lf/100/1      2475120246 ns       760408 ns           10
BM_ypipe_lf/100/2      2522924146 ns       738453 ns           10
BM_ypipe_lf/100/3      2536730839 ns       789407 ns           10
BM_ypipe_lf/100/4      2506133000 ns       863693 ns            1
BM_ypipe_lf/1024/1     2476256669 ns       831154 ns           10
BM_ypipe_lf/1024/2     2562395231 ns       917156 ns            1
BM_ypipe_lf/1024/3     2591816923 ns       857462 ns            1
BM_ypipe_lf/1024/4     2512426385 ns      1156847 ns            1
BM_ypipe_lf/8192/1     2519309769 ns       968307 ns            1
BM_ypipe_lf/8192/2     2608857385 ns       648770 ns            1
BM_ypipe_lf/8192/3     2620517462 ns       969845 ns            1
BM_ypipe_lf/8192/4     2529045231 ns       685614 ns            1
BM_ypipe_lf/16384/1    2580884693 ns       822384 ns            1
BM_ypipe_lf/16384/2    2666952001 ns       757538 ns            1
BM_ypipe_lf/16384/3    2648609846 ns       615768 ns            1
BM_ypipe_lf/16384/4    2508722154 ns       769155 ns            1
BM_ypipe_lf_s/0/0      1738855516 ns       764323 ns           10
BM_ypipe_lf_s/100/1    1657466431 ns       833831 ns           10
BM_ypipe_lf_s/100/2    1577014277 ns       868630 ns           10
BM_ypipe_lf_s/100/3    1587816638 ns       824300 ns           10
BM_ypipe_lf_s/100/4    1771883146 ns       907654 ns           10
BM_ypipe_lf_s/1024/1   1696368592 ns       920692 ns           10
BM_ypipe_lf_s/1024/2   1584702315 ns       914900 ns           10
BM_ypipe_lf_s/1024/3   1604057823 ns       915777 ns           10
BM_ypipe_lf_s/1024/4   1764219892 ns       827746 ns           10
BM_ypipe_lf_s/8192/1   1791619146 ns       864039 ns           10
BM_ypipe_lf_s/8192/2   1686152569 ns       872592 ns           10
BM_ypipe_lf_s/8192/3   1685648593 ns       895454 ns           10
BM_ypipe_lf_s/8192/4   1746304108 ns       790932 ns           10
BM_ypipe_lf_s/16384/1  1838788031 ns       928716 ns           10
BM_ypipe_lf_s/16384/2  1802953354 ns       976146 ns           10
BM_ypipe_lf_s/16384/3  1804821362 ns       952092 ns           10
BM_ypipe_lf_s/16384/4  1766426762 ns       827700 ns           10
```
**8xW,8xR**
```
Run on (8 X 1391 MHz CPU s)
Load Average: 8.75, 9.69, 11.56
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6203947 ns      6203791 ns          112
BM_cvnotify0               786212 ns       785978 ns          895
BM_yield                 40597766 ns       715323 ns          100
BM_yield2               158354952 ns       861688 ns          100
BM_deque0/0/0           928022223 ns       770430 ns           10
BM_deque0/100/1        1299767708 ns       851492 ns           10
BM_deque0/100/2        1143656931 ns       835954 ns           10
BM_deque0/100/3        1115375246 ns       816192 ns           10
BM_deque0/100/4         943641569 ns       837184 ns           10
BM_deque0/1024/1       1385342808 ns       857324 ns           10
BM_deque0/1024/2       1163989354 ns       881024 ns           10
BM_deque0/1024/3       1140634515 ns       831808 ns           10
BM_deque0/1024/4        948574769 ns       832438 ns           10
BM_deque0/8192/1       1375026062 ns       970238 ns           10
BM_deque0/8192/2       1095755500 ns      1003485 ns           10
BM_deque0/8192/3       1082050616 ns       995762 ns           10
BM_deque0/8192/4        862822062 ns       864416 ns           10
BM_deque0/16384/1      1417475777 ns      1133346 ns           10
BM_deque0/16384/2      1168031154 ns       933907 ns           10
BM_deque0/16384/3      1101252392 ns      1000269 ns           10
BM_deque0/16384/4       878887423 ns      1010961 ns           10
BM_deque/0/0            921167638 ns       766784 ns           10
BM_deque/100/1         1310131862 ns       848192 ns           10
BM_deque/100/2         1133055216 ns       811477 ns           10
BM_deque/100/3         1115640731 ns       852554 ns           10
BM_deque/100/4          931631046 ns       811031 ns           10
BM_deque/1024/1        1363231400 ns       882962 ns           10
BM_deque/1024/2        1152884623 ns       866138 ns           10
BM_deque/1024/3        1151274354 ns       901377 ns           10
BM_deque/1024/4         920866754 ns       871161 ns           10
BM_deque/8192/1        1367201377 ns      1038169 ns           10
BM_deque/8192/2        1076176339 ns      1174161 ns           10
BM_deque/8192/3        1052283292 ns       982762 ns           10
BM_deque/8192/4         825481285 ns       861539 ns           10
BM_deque/16384/1       1419018892 ns      1007584 ns           10
BM_deque/16384/2       1119086277 ns      1024638 ns           10
BM_deque/16384/3       1084682715 ns      1096054 ns           10
BM_deque/16384/4        842686908 ns       882392 ns           10
BM_deque_lf/0/0        2945944154 ns       938308 ns            1
BM_deque_lf/100/1      2855462231 ns      1114309 ns            1
BM_deque_lf/100/2      2847265616 ns       859154 ns            1
BM_deque_lf/100/3      2860295923 ns       939847 ns            1
BM_deque_lf/100/4      2814816077 ns       844309 ns            1
BM_deque_lf/1024/1     2785850077 ns       765693 ns            1
BM_deque_lf/1024/2     2812568539 ns       812537 ns            1
BM_deque_lf/1024/3     2816769923 ns       708383 ns            1
BM_deque_lf/1024/4     2766235616 ns       774155 ns            1
BM_deque_lf/8192/1     2950846000 ns      1099461 ns            1
BM_deque_lf/8192/2     2857421923 ns       895924 ns            1
BM_deque_lf/8192/3     2862639846 ns       737847 ns            1
BM_deque_lf/8192/4     2764052461 ns       874000 ns            1
BM_deque_lf/16384/1    2556145077 ns      1013230 ns            1
BM_deque_lf/16384/2    2380476823 ns       882101 ns           10
BM_deque_lf/16384/3    2383352208 ns       975008 ns           10
BM_deque_lf/16384/4    2293241208 ns       928007 ns           10
BM_deque_lf_s/0/0      2153975062 ns       772807 ns           10
BM_deque_lf_s/100/1    2234896954 ns       893392 ns           10
BM_deque_lf_s/100/2    2181947562 ns       830538 ns           10
BM_deque_lf_s/100/3    2200473446 ns       913762 ns           10
BM_deque_lf_s/100/4    2177651131 ns       847123 ns           10
BM_deque_lf_s/1024/1   2373969562 ns       884846 ns           10
BM_deque_lf_s/1024/2   2270672785 ns       874654 ns           10
BM_deque_lf_s/1024/3   2260937785 ns       891316 ns           10
BM_deque_lf_s/1024/4   2295420331 ns       871446 ns           10
BM_deque_lf_s/8192/1   2160801169 ns       948023 ns           10
BM_deque_lf_s/8192/2   2076816585 ns      1006270 ns           10
BM_deque_lf_s/8192/3   2112292777 ns       939322 ns           10
BM_deque_lf_s/8192/4   2176025600 ns       906761 ns           10
BM_deque_lf_s/16384/1  1695659423 ns       977330 ns           10
BM_deque_lf_s/16384/2  1491360731 ns       996408 ns           10
BM_deque_lf_s/16384/3  1470164708 ns      1027369 ns           10
BM_deque_lf_s/16384/4  1216253592 ns       935177 ns           10
BM_deque2_lf/0/0       2757073769 ns       935769 ns            1
BM_deque2_lf/100/1     2664216231 ns       812384 ns            1
BM_deque2_lf/100/2     2729156078 ns      1408772 ns            1
BM_deque2_lf/100/3     2653135307 ns       904923 ns            1
BM_deque2_lf/100/4     2623632154 ns       727154 ns            1
BM_deque2_lf/1024/1    2539630077 ns       891693 ns            1
BM_deque2_lf/1024/2    2631695384 ns       703847 ns            1
BM_deque2_lf/1024/3    2665307000 ns       850846 ns            1
BM_deque2_lf/1024/4    2647640077 ns       957769 ns            1
BM_deque2_lf/8192/1    2669869077 ns       970153 ns            1
BM_deque2_lf/8192/2    2665298846 ns      1206537 ns            1
BM_deque2_lf/8192/3    2636376692 ns      1266539 ns            1
BM_deque2_lf/8192/4    2615751923 ns       825387 ns            1
BM_deque2_lf/16384/1   2256862900 ns      1070454 ns           10
BM_deque2_lf/16384/2   2078793323 ns       980385 ns           10
BM_deque2_lf/16384/3   2074526946 ns       977000 ns           10
BM_deque2_lf/16384/4   1866008223 ns       912608 ns           10
BM_deque2_lf_s/0/0     1857364931 ns       912384 ns           10
BM_deque2_lf_s/100/1   1735864477 ns       854939 ns           10
BM_deque2_lf_s/100/2   1693622800 ns       826892 ns           10
BM_deque2_lf_s/100/3   1690851846 ns       927401 ns           10
BM_deque2_lf_s/100/4   1862654331 ns       885492 ns           10
BM_deque2_lf_s/1024/1  1784196362 ns       990938 ns           10
BM_deque2_lf_s/1024/2  1730007231 ns       884846 ns           10
BM_deque2_lf_s/1024/3  1705664323 ns       808361 ns           10
BM_deque2_lf_s/1024/4  1884526869 ns       803416 ns           10
BM_deque2_lf_s/8192/1  1555758969 ns       974608 ns           10
BM_deque2_lf_s/8192/2  1452646285 ns      1023785 ns           10
BM_deque2_lf_s/8192/3  1437198631 ns       981424 ns           10
BM_deque2_lf_s/8192/4  1258983616 ns       917793 ns           10
BM_deque2_lf_s/16384/1 1471988585 ns      1126993 ns           10
BM_deque2_lf_s/16384/2 1283201654 ns      1076192 ns           10
BM_deque2_lf_s/16384/3 1229390938 ns       982754 ns           10
BM_deque2_lf_s/16384/4  953904408 ns       918162 ns           10
BM_ypipe/0/0            870266839 ns       879584 ns           10
BM_ypipe/100/1         1320506085 ns       840292 ns           10
BM_ypipe/100/2         1086520408 ns       896407 ns           10
BM_ypipe/100/3         1058345446 ns       878469 ns           10
BM_ypipe/100/4          862800208 ns       848323 ns           10
BM_ypipe/1024/1        1385056815 ns       879146 ns           10
BM_ypipe/1024/2        1107440277 ns       894507 ns           10
BM_ypipe/1024/3        1093137600 ns       908930 ns           10
BM_ypipe/1024/4         870592262 ns       852254 ns           10
BM_ypipe/8192/1        1368881123 ns       948892 ns           10
BM_ypipe/8192/2        1050463300 ns      1016915 ns           10
BM_ypipe/8192/3        1015962623 ns       967523 ns           10
BM_ypipe/8192/4         805177862 ns       836731 ns           10
BM_ypipe/16384/1       1422466738 ns      1089131 ns           10
BM_ypipe/16384/2       1125394685 ns      1062285 ns           10
BM_ypipe/16384/3       1062991662 ns      1039423 ns           10
BM_ypipe/16384/4        838457485 ns       919154 ns           10
BM_ypipe_s/0/0          875498100 ns       836085 ns           10
BM_ypipe_s/100/1       1315290069 ns       844023 ns           10
BM_ypipe_s/100/2       1088398292 ns       881939 ns           10
BM_ypipe_s/100/3       1074287177 ns       879977 ns           10
BM_ypipe_s/100/4        871634931 ns       815085 ns           10
BM_ypipe_s/1024/1      1375572423 ns       859546 ns           10
BM_ypipe_s/1024/2      1110033516 ns       979823 ns           10
BM_ypipe_s/1024/3      1092908969 ns       914369 ns           10
BM_ypipe_s/1024/4       867054685 ns       818061 ns           10
BM_ypipe_s/8192/1      1369780862 ns      1092985 ns           10
BM_ypipe_s/8192/2      1057224831 ns       963553 ns           10
BM_ypipe_s/8192/3      1039102338 ns       966038 ns           10
BM_ypipe_s/8192/4       802830892 ns       983569 ns           10
BM_ypipe_s/16384/1     1421176046 ns       985638 ns           10
BM_ypipe_s/16384/2     1114084823 ns       980700 ns           10
BM_ypipe_s/16384/3     1071337277 ns       992570 ns           10
BM_ypipe_s/16384/4      842631800 ns       927100 ns           10
BM_ypipe_lf/0/0        2912510308 ns       719000 ns            1
BM_ypipe_lf/100/1      2782879231 ns       849538 ns            1
BM_ypipe_lf/100/2      2848054462 ns       695692 ns            1
BM_ypipe_lf/100/3      2784517077 ns       765539 ns            1
BM_ypipe_lf/100/4      2805440462 ns       709155 ns            1
BM_ypipe_lf/1024/1     2697236692 ns       860310 ns            1
BM_ypipe_lf/1024/2     2731852154 ns       733308 ns            1
BM_ypipe_lf/1024/3     2809195231 ns       929077 ns            1
BM_ypipe_lf/1024/4     2788165077 ns       904003 ns            1
BM_ypipe_lf/8192/1     2847430616 ns       947770 ns            1
BM_ypipe_lf/8192/2     2819695615 ns      1054463 ns            1
BM_ypipe_lf/8192/3     2800845154 ns       969695 ns            1
BM_ypipe_lf/8192/4     2743392077 ns       867614 ns            1
BM_ypipe_lf/16384/1    2391992246 ns      1059662 ns           10
BM_ypipe_lf/16384/2    2269147446 ns       969185 ns           10
BM_ypipe_lf/16384/3    2232400800 ns       874754 ns           10
BM_ypipe_lf/16384/4    2118152423 ns       832200 ns           10
BM_ypipe_lf_s/0/0      2131646015 ns       831215 ns           10
BM_ypipe_lf_s/100/1    1990108162 ns       898485 ns           10
BM_ypipe_lf_s/100/2    1976086254 ns       815369 ns           10
BM_ypipe_lf_s/100/3    1983000292 ns       878723 ns           10
BM_ypipe_lf_s/100/4    2167874677 ns       875884 ns           10
BM_ypipe_lf_s/1024/1   2104455792 ns       979347 ns           10
BM_ypipe_lf_s/1024/2   2028247016 ns       850438 ns           10
BM_ypipe_lf_s/1024/3   2040175223 ns       883461 ns           10
BM_ypipe_lf_s/1024/4   2169564762 ns       876362 ns           10
BM_ypipe_lf_s/8192/1   1747838846 ns      1027669 ns           10
BM_ypipe_lf_s/8192/2   1719851738 ns      1043353 ns           10
BM_ypipe_lf_s/8192/3   1703174900 ns      1027423 ns           10
BM_ypipe_lf_s/8192/4   1614312869 ns       915869 ns           10
BM_ypipe_lf_s/16384/1  1559835185 ns       993492 ns           10
BM_ypipe_lf_s/16384/2  1447302177 ns      1114523 ns           10
BM_ypipe_lf_s/16384/3  1394074700 ns      1068784 ns           10
BM_ypipe_lf_s/16384/4  1058858169 ns       950277 ns           10
```
**2xW,2xR,2xa72@2.3+1xa53@1.3(for hardware interrput)**
```
Run on (3 X 1391 MHz CPU s)
Load Average: 9.79, 9.46, 9.28
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6239994 ns      6214844 ns          112
BM_cvnotify0               793906 ns       790936 ns          887
BM_yield                113161229 ns       829560 ns          100
BM_yield2                87814216 ns       869947 ns          100
BM_deque0/0/0           223576058 ns       182239 ns          100
BM_deque0/100/1         270214700 ns       218939 ns           10
BM_deque0/100/2         258553769 ns       194323 ns           10
BM_deque0/100/3         255734677 ns       160546 ns           10
BM_deque0/100/4         232478648 ns       174163 ns          100
BM_deque0/1024/1        440035400 ns       235870 ns           10
BM_deque0/1024/2        361468500 ns       195200 ns           10
BM_deque0/1024/3        325714415 ns       210439 ns           10
BM_deque0/1024/4        283321323 ns       196715 ns           10
BM_deque0/8192/1       1027817269 ns       280238 ns           10
BM_deque0/8192/2        901238631 ns       250100 ns           10
BM_deque0/8192/3        814945639 ns       194077 ns           10
BM_deque0/8192/4        648946546 ns       184854 ns           10
BM_deque0/16384/1      1635071423 ns       272092 ns           10
BM_deque0/16384/2      1697034800 ns       437508 ns           10
BM_deque0/16384/3      1411773208 ns       228192 ns           10
BM_deque0/16384/4      1114110292 ns       220646 ns           10
BM_deque/0/0            246779158 ns       185925 ns          100
BM_deque/100/1          338888515 ns       179146 ns           10
BM_deque/100/2          262923846 ns       212054 ns           10
BM_deque/100/3          272060808 ns       196546 ns           10
BM_deque/100/4          251067199 ns       181707 ns          100
BM_deque/1024/1         424672231 ns       204469 ns           10
BM_deque/1024/2         365986908 ns       271131 ns           10
BM_deque/1024/3         329742461 ns       240292 ns           10
BM_deque/1024/4         296254662 ns       157746 ns           10
BM_deque/8192/1        1004571754 ns       242538 ns           10
BM_deque/8192/2         944689469 ns       282592 ns           10
BM_deque/8192/3         878421915 ns       235731 ns           10
BM_deque/8192/4         689963000 ns       179892 ns           10
BM_deque/16384/1       1877014346 ns       332569 ns           10
BM_deque/16384/2       1795929308 ns       277162 ns           10
BM_deque/16384/3       1465948285 ns       240892 ns           10
BM_deque/16384/4       1138799192 ns       206915 ns           10
BM_deque_lf/0/0         238244920 ns       201376 ns          100
BM_deque_lf/100/1       319501939 ns       209031 ns           10
BM_deque_lf/100/2       261230862 ns       178723 ns           10
BM_deque_lf/100/3       256848308 ns       187484 ns           10
BM_deque_lf/100/4       257190262 ns       211792 ns           10
BM_deque_lf/1024/1      439383115 ns       259923 ns           10
BM_deque_lf/1024/2      361115731 ns       217631 ns           10
BM_deque_lf/1024/3      340242023 ns       239816 ns           10
BM_deque_lf/1024/4      287013285 ns       189900 ns           10
BM_deque_lf/8192/1     1125754746 ns       346631 ns           10
BM_deque_lf/8192/2     1025201385 ns       442454 ns           10
BM_deque_lf/8192/3     1026367646 ns       333284 ns           10
BM_deque_lf/8192/4      699040492 ns       167346 ns           10
BM_deque_lf/16384/1    1998914192 ns       322992 ns           10
BM_deque_lf/16384/2    1863607100 ns       278892 ns           10
BM_deque_lf/16384/3    1594649131 ns       331184 ns           10
BM_deque_lf/16384/4    1176376246 ns       244616 ns           10
BM_deque_lf_s/0/0       251703354 ns       176669 ns           10
BM_deque_lf_s/100/1     349264892 ns       204954 ns           10
BM_deque_lf_s/100/2     283716069 ns       187315 ns           10
BM_deque_lf_s/100/3     297755000 ns       191269 ns           10
BM_deque_lf_s/100/4     260672777 ns       218239 ns           10
BM_deque_lf_s/1024/1    492499677 ns       230500 ns           10
BM_deque_lf_s/1024/2    397179008 ns       284446 ns           10
BM_deque_lf_s/1024/3    384612185 ns       188377 ns           10
BM_deque_lf_s/1024/4    313066131 ns       175577 ns           10
BM_deque_lf_s/8192/1   1232974754 ns       297616 ns           10
BM_deque_lf_s/8192/2   1029388485 ns       344215 ns           10
BM_deque_lf_s/8192/3    986914562 ns       274269 ns           10
BM_deque_lf_s/8192/4    705795623 ns       175577 ns           10
BM_deque_lf_s/16384/1  1929887162 ns       341715 ns           10
BM_deque_lf_s/16384/2  1781119677 ns       343054 ns           10
BM_deque_lf_s/16384/3  1640133615 ns       345192 ns           10
BM_deque_lf_s/16384/4  1194101000 ns       263085 ns           10
BM_deque2_lf/0/0        222996929 ns       176919 ns          100
BM_deque2_lf/100/1      302631523 ns       212554 ns           10
BM_deque2_lf/100/2      255362675 ns       189995 ns          100
BM_deque2_lf/100/3      257891862 ns       184230 ns           10
BM_deque2_lf/100/4      231618929 ns       178875 ns          100
BM_deque2_lf/1024/1     440274238 ns       208254 ns           10
BM_deque2_lf/1024/2     351378623 ns       218385 ns           10
BM_deque2_lf/1024/3     339848854 ns       223023 ns           10
BM_deque2_lf/1024/4     286285854 ns       203385 ns           10
BM_deque2_lf/8192/1    1111999731 ns       327592 ns           10
BM_deque2_lf/8192/2    1004032731 ns       275739 ns           10
BM_deque2_lf/8192/3     970986908 ns       274938 ns           10
BM_deque2_lf/8192/4     702815831 ns       218062 ns           10
BM_deque2_lf/16384/1   1809632808 ns       309469 ns           10
BM_deque2_lf/16384/2   1777126677 ns       340169 ns           10
BM_deque2_lf/16384/3   1541370492 ns       282908 ns           10
BM_deque2_lf/16384/4   1170148308 ns       201684 ns           10
BM_deque2_lf_s/0/0      230547881 ns       186686 ns          100
BM_deque2_lf_s/100/1    314737923 ns       194069 ns           10
BM_deque2_lf_s/100/2    258242185 ns       199723 ns           10
BM_deque2_lf_s/100/3    274519308 ns       196039 ns           10
BM_deque2_lf_s/100/4    235575498 ns       192713 ns          100
BM_deque2_lf_s/1024/1   446473600 ns       238785 ns           10
BM_deque2_lf_s/1024/2   445617831 ns       282185 ns           10
BM_deque2_lf_s/1024/3   343403146 ns       210353 ns           10
BM_deque2_lf_s/1024/4   286879946 ns       168939 ns           10
BM_deque2_lf_s/8192/1  1150347392 ns       360654 ns           10
BM_deque2_lf_s/8192/2   988324777 ns       229269 ns           10
BM_deque2_lf_s/8192/3   927385031 ns       284654 ns           10
BM_deque2_lf_s/8192/4   699256777 ns       172823 ns           10
BM_deque2_lf_s/16384/1 1879224123 ns       305469 ns           10
BM_deque2_lf_s/16384/2 1825821123 ns       308192 ns           10
BM_deque2_lf_s/16384/3 1582028200 ns       374938 ns           10
BM_deque2_lf_s/16384/4 1194978869 ns       200500 ns           10
BM_ypipe/0/0            244927500 ns       186851 ns          100
BM_ypipe/100/1          315469708 ns       190793 ns           10
BM_ypipe/100/2          256224415 ns       178562 ns           10
BM_ypipe/100/3          296316015 ns       215831 ns           10
BM_ypipe/100/4          239570272 ns       187879 ns          100
BM_ypipe/1024/1         457199800 ns       231000 ns           10
BM_ypipe/1024/2         338011585 ns       245623 ns           10
BM_ypipe/1024/3         331561746 ns       211331 ns           10
BM_ypipe/1024/4         289720969 ns       152361 ns           10
BM_ypipe/8192/1        1196057423 ns       322992 ns           10
BM_ypipe/8192/2         947053754 ns       330446 ns           10
BM_ypipe/8192/3         885458323 ns       320316 ns           10
BM_ypipe/8192/4         684616446 ns       192962 ns           10
BM_ypipe/16384/1       1856517885 ns       379123 ns           10
BM_ypipe/16384/2       1777690146 ns       252723 ns           10
BM_ypipe/16384/3       1518108692 ns       266269 ns           10
BM_ypipe/16384/4       1189210577 ns       229577 ns           10
BM_ypipe_s/0/0          233793270 ns       187192 ns          100
BM_ypipe_s/100/1        341409954 ns       238977 ns           10
BM_ypipe_s/100/2        267538892 ns       204946 ns           10
BM_ypipe_s/100/3        259553715 ns       179292 ns           10
BM_ypipe_s/100/4        242626771 ns       188831 ns          100
BM_ypipe_s/1024/1       472246992 ns       264777 ns           10
BM_ypipe_s/1024/2       336554308 ns       215169 ns           10
BM_ypipe_s/1024/3       342722762 ns       213277 ns           10
BM_ypipe_s/1024/4       284209239 ns       221092 ns           10
BM_ypipe_s/8192/1      1170406939 ns       285585 ns           10
BM_ypipe_s/8192/2      1102904415 ns       375223 ns           10
BM_ypipe_s/8192/3       946363731 ns       367200 ns           10
BM_ypipe_s/8192/4       716953900 ns       239684 ns           10
BM_ypipe_s/16384/1     1543968269 ns       401962 ns           10
BM_ypipe_s/16384/2     1584098892 ns       265016 ns           10
BM_ypipe_s/16384/3     1396178985 ns       263685 ns           10
BM_ypipe_s/16384/4     1175688316 ns       163246 ns           10
BM_ypipe_lf/0/0         224454196 ns       194064 ns          100
BM_ypipe_lf/100/1       319497031 ns       207254 ns           10
BM_ypipe_lf/100/2       263048054 ns       200277 ns           10
BM_ypipe_lf/100/3       252176885 ns       154715 ns           10
BM_ypipe_lf/100/4       229739472 ns       201654 ns          100
BM_ypipe_lf/1024/1      439799946 ns       210408 ns           10
BM_ypipe_lf/1024/2      332215300 ns       197823 ns           10
BM_ypipe_lf/1024/3      320039415 ns       187962 ns           10
BM_ypipe_lf/1024/4      274434223 ns       178331 ns           10
BM_ypipe_lf/8192/1     1000464754 ns       293893 ns           10
BM_ypipe_lf/8192/2      895455015 ns       264869 ns           10
BM_ypipe_lf/8192/3      855823715 ns       345077 ns           10
BM_ypipe_lf/8192/4      700058039 ns       177369 ns           10
BM_ypipe_lf/16384/1    1613021062 ns       277816 ns           10
BM_ypipe_lf/16384/2    1576180631 ns       349915 ns           10
BM_ypipe_lf/16384/3    1460879939 ns       268146 ns           10
BM_ypipe_lf/16384/4    1165068285 ns       165616 ns           10
BM_ypipe_lf_s/0/0       238799673 ns       170581 ns          100
BM_ypipe_lf_s/100/1     324900715 ns       215446 ns           10
BM_ypipe_lf_s/100/2     271622623 ns       175292 ns           10
BM_ypipe_lf_s/100/3     255035923 ns       173469 ns           10
BM_ypipe_lf_s/100/4     238640542 ns       183419 ns          100
BM_ypipe_lf_s/1024/1    484511123 ns       213054 ns           10
BM_ypipe_lf_s/1024/2    353272523 ns       221469 ns           10
BM_ypipe_lf_s/1024/3    335782962 ns       213254 ns           10
BM_ypipe_lf_s/1024/4    280501508 ns       169923 ns           10
BM_ypipe_lf_s/8192/1   1023385900 ns       365423 ns           10
BM_ypipe_lf_s/8192/2    925074039 ns       239838 ns           10
BM_ypipe_lf_s/8192/3    869407223 ns       229385 ns           10
BM_ypipe_lf_s/8192/4    709253192 ns       164207 ns           10
BM_ypipe_lf_s/16384/1  1715741323 ns       289877 ns           10
BM_ypipe_lf_s/16384/2  1722309438 ns       330585 ns           10
BM_ypipe_lf_s/16384/3  1534608523 ns       521723 ns           10
BM_ypipe_lf_s/16384/4  1193713692 ns       208831 ns           10
```
### access redis quad times per msg
100 times slower. amount of total messages is reduced to 1/100. 

the affect of the overhead of threading model comes down.

in this case, taking more threads is more important than applying to what threading model.
**2xW,2xR**
```
Run on (3 X 1391 MHz CPU s)
Load Average: 10.18, 13.05, 16.31
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
BM_ypipe_lf/0/0       11931431232 ns       328154 ns            1
BM_ypipe_lf/100/1     9230981847 ns       144461 ns            1
BM_ypipe_lf/100/2     7767948001 ns       193384 ns            1
BM_ypipe_lf/100/3     7527216077 ns       122769 ns            1
BM_ypipe_lf/100/4     11320469231 ns       120384 ns            1
BM_ypipe_lf/1024/1    9094339231 ns       250999 ns            1
BM_ypipe_lf/1024/2    17340780770 ns       144461 ns            1
BM_ypipe_lf/1024/3    11875902000 ns       171770 ns            1
BM_ypipe_lf/1024/4    9734181923 ns       127924 ns            1
BM_ypipe_lf/8192/1    7257554462 ns       197230 ns            1
BM_ypipe_lf/8192/2    8784138923 ns       114691 ns            1
BM_ypipe_lf/8192/3    7512531539 ns       123000 ns            1
BM_ypipe_lf/8192/4    9012952078 ns       115692 ns            1
BM_ypipe_lf/16384/1   10217849616 ns       227000 ns            1
BM_ypipe_lf/16384/2   12511126770 ns       731000 ns            1
BM_ypipe_lf/16384/3   9149388308 ns       111615 ns            1
BM_ypipe_lf/16384/4   9551957462 ns       117769 ns            1
BM_ypipe_lf_s/0/0     9085018001 ns       200463 ns            1
BM_ypipe_lf_s/100/1   11134297539 ns       796078 ns            1
BM_ypipe_lf_s/100/2   10532710385 ns       108923 ns            1
BM_ypipe_lf_s/100/3   15746312001 ns       130691 ns            1
BM_ypipe_lf_s/100/4   10474258231 ns       129615 ns            1
BM_ypipe_lf_s/1024/1  12098786693 ns       213462 ns            1
BM_ypipe_lf_s/1024/2  15625324770 ns       127998 ns            1
BM_ypipe_lf_s/1024/3  9413957539 ns       115615 ns            1
BM_ypipe_lf_s/1024/4  10630501539 ns       124232 ns            1
BM_ypipe_lf_s/8192/1  15143394232 ns       124923 ns            1
BM_ypipe_lf_s/8192/2  13337908154 ns       661308 ns            1
BM_ypipe_lf_s/8192/3  9287315155 ns       134615 ns            1
BM_ypipe_lf_s/8192/4  10738824616 ns       126538 ns            1
BM_ypipe_lf_s/16384/1 18269860386 ns       196154 ns            1
BM_ypipe_lf_s/16384/2 13342044386 ns       218384 ns            1
BM_ypipe_lf_s/16384/3 10060926616 ns       736384 ns            1
BM_ypipe_lf_s/16384/4 7574335846 ns       134231 ns            1

Run on (3 X 1391 MHz CPU s)
Load Average: 7.55, 9.23, 13.42
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BM_ypipe/0/0     5026263000 ns       173847 ns            1
BM_ypipe/100/1   8777136077 ns       116616 ns            1
BM_ypipe/100/2   8978420924 ns       120077 ns            1
BM_ypipe/100/3   7784578693 ns       145001 ns            1
BM_ypipe/100/4   7382878385 ns       121462 ns            1
BM_ypipe/1024/1  7697488385 ns       131385 ns            1
BM_ypipe/1024/2  8203490616 ns       130307 ns            1
BM_ypipe/1024/3  9076550770 ns       129308 ns            1
BM_ypipe/1024/4  7716133001 ns       232538 ns            1
BM_ypipe/8192/1  7356941924 ns       771923 ns            1
BM_ypipe/8192/2  8168360155 ns       104615 ns            1
BM_ypipe/8192/3  8561146385 ns       102616 ns            1
BM_ypipe/8192/4  13330339463 ns       108691 ns            1
BM_ypipe/16384/1 9243608923 ns       144615 ns            1
BM_ypipe/16384/2 9107775386 ns       121692 ns            1
BM_ypipe/16384/3 7705608231 ns       125154 ns            1
BM_ypipe/16384/4 7668513001 ns       255000 ns            1

Run on (3 X 1391 MHz CPU s)
Load Average: 7.44, 8.32, 12.23
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BM_deque/0/0     7755087231 ns       193847 ns            1
BM_deque/100/1   9760274847 ns       218692 ns            1
BM_deque/100/2   9721650078 ns       164308 ns            1
BM_deque/100/3   9317227386 ns       116306 ns            1
BM_deque/100/4   9411130616 ns       107461 ns            1
BM_deque/1024/1  11374817078 ns       141153 ns            1
BM_deque/1024/2  12714148924 ns       191385 ns            1
BM_deque/1024/3  9852095001 ns       183999 ns            1
BM_deque/1024/4  9834991847 ns       111155 ns            1
BM_deque/8192/1  10043024154 ns       116538 ns            1
BM_deque/8192/2  10099136001 ns       142539 ns            1
BM_deque/8192/3  8127706770 ns       188921 ns            1
BM_deque/8192/4  6933406001 ns       728231 ns            1
BM_deque/16384/1 8424789693 ns       107616 ns            1
BM_deque/16384/2 8620007923 ns       116463 ns            1
BM_deque/16384/3 8456856847 ns       120078 ns            1
BM_deque/16384/4 7070060308 ns       273922 ns            1
```
**8xW,8xR**
```
Run on (3 X 1391 MHz CPU s)
Load Average: 8.93, 8.27, 11.25
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BM_ypipe/0/0     3836061924 ns       632538 ns            1
BM_ypipe/100/1   4740753270 ns      1191177 ns           10
BM_ypipe/100/2   2971674385 ns      1259923 ns            1
BM_ypipe/100/3   3982867385 ns       646461 ns            1
BM_ypipe/100/4   4944977692 ns      2189845 ns            1
BM_ypipe/1024/1  2728583115 ns      1004639 ns           10
BM_ypipe/1024/2  2539928331 ns       907738 ns           10
BM_ypipe/1024/3  3385754770 ns       682539 ns            1
BM_ypipe/1024/4  3323195385 ns       609691 ns            1
BM_ypipe/8192/1  2895098085 ns       901954 ns           10
BM_ypipe/8192/2  3000201924 ns      1195769 ns            1
BM_ypipe/8192/3  5462275385 ns      2749076 ns            1
BM_ypipe/8192/4  3232908769 ns       611770 ns            1
BM_ypipe/16384/1 4052949616 ns       615153 ns            1
BM_ypipe/16384/2 3460483231 ns      1268539 ns            1
BM_ypipe/16384/3 4097771916 ns       989977 ns           10
BM_ypipe/16384/4 3565441308 ns       691000 ns            1

Run on (3 X 1391 MHz CPU s)
Load Average: 8.26, 8.22, 10.53
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
BM_ypipe_lf_s/0/0     4079309131 ns      1043439 ns           10
BM_ypipe_lf_s/100/1   3850407770 ns       634924 ns            1
BM_ypipe_lf_s/100/2   4928500462 ns       710078 ns            1
BM_ypipe_lf_s/100/3   3502437693 ns       782768 ns            1
BM_ypipe_lf_s/100/4   3293010000 ns       733536 ns            1
BM_ypipe_lf_s/1024/1  3469353846 ns      2255848 ns            1
BM_ypipe_lf_s/1024/2  2583805616 ns       810385 ns            1
BM_ypipe_lf_s/1024/3  2897404700 ns      1284469 ns           10
BM_ypipe_lf_s/1024/4  3053080462 ns       944301 ns           10
BM_ypipe_lf_s/8192/1  3047359300 ns      1120469 ns           10
BM_ypipe_lf_s/8192/2  3884588539 ns      1050462 ns            1
BM_ypipe_lf_s/8192/3  3354758924 ns      1432539 ns            1
BM_ypipe_lf_s/8192/4  3878311092 ns      1132008 ns           10
BM_ypipe_lf_s/16384/1 3793031300 ns      1048354 ns           10
BM_ypipe_lf_s/16384/2 2637969462 ns       943770 ns            1
BM_ypipe_lf_s/16384/3 3270587069 ns      1001069 ns           10
BM_ypipe_lf_s/16384/4 5774170155 ns      1356153 ns            1
```
