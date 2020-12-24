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
```
Run on (8 X 1391 MHz CPU s)
Load Average: 8.48, 8.27, 8.38
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 6186910 ns      6186656 ns          113
BM_cvnotify0               780447 ns       780391 ns          897
BM_yield                 38793733 ns       713015 ns          100
BM_yield2               160333481 ns       883572 ns          100
BM_deque0/0/0           272453377 ns       859193 ns           10
BM_deque0/100/1         737978585 ns       862561 ns           10
BM_deque0/100/2         334479715 ns       801577 ns           10
BM_deque0/100/3         314597108 ns       868346 ns           10
BM_deque0/100/4         273100469 ns       674415 ns           10
BM_deque0/1024/1       1066444592 ns       928800 ns           10
BM_deque0/1024/2        385205000 ns       925046 ns           10
BM_deque0/1024/3        368988285 ns       960531 ns           10
BM_deque0/1024/4        267905546 ns       835731 ns           10
BM_deque0/8192/1       1520719538 ns       941208 ns           10
BM_deque0/8192/2        470274785 ns      1082461 ns           10
BM_deque0/8192/3        447172885 ns      1070723 ns           10
BM_deque0/8192/4        261768862 ns       762692 ns           10
BM_deque0/16384/1      1786003323 ns       769877 ns           10
BM_deque0/16384/2       509982323 ns      1023508 ns           10
BM_deque0/16384/3       486670446 ns      1031977 ns           10
BM_deque0/16384/4       272103638 ns       794700 ns           10
BM_deque/0/0            173560295 ns       774686 ns          100
BM_deque/100/1          428460523 ns       803115 ns           10
BM_deque/100/2          293633761 ns       867246 ns           10
BM_deque/100/3          290078262 ns       876908 ns           10
BM_deque/100/4          176582448 ns       783311 ns          100
BM_deque/1024/1         576001769 ns       816101 ns           10
BM_deque/1024/2         356683246 ns       953200 ns           10
BM_deque/1024/3         332994223 ns       923092 ns           10
BM_deque/1024/4         174781017 ns       781222 ns          100
BM_deque/8192/1         911509715 ns       886077 ns           10
BM_deque/8192/2         471750877 ns      1004439 ns           10
BM_deque/8192/3         451282292 ns      1071115 ns           10
BM_deque/8192/4         176945451 ns       767195 ns          100
BM_deque/16384/1       1093723531 ns       846331 ns           10
BM_deque/16384/2        534462292 ns       953870 ns           10
BM_deque/16384/3        519158085 ns      1031885 ns           10
BM_deque/16384/4        175059188 ns       790679 ns          100
BM_deque_lf/0/0        1037183900 ns       939170 ns           10
BM_deque_lf/100/1      1320915300 ns       838446 ns           10
BM_deque_lf/100/2      2065142423 ns       738154 ns           10
BM_deque_lf/100/3      1961360623 ns       872731 ns           10
BM_deque_lf/100/4       971455077 ns       727946 ns           10
BM_deque_lf/1024/1     1359757062 ns       865861 ns           10
BM_deque_lf/1024/2     2292776015 ns       802800 ns           10
BM_deque_lf/1024/3     2214968839 ns       909769 ns           10
BM_deque_lf/1024/4     1042982239 ns       821992 ns           10
BM_deque_lf/8192/1     1479995285 ns       829569 ns           10
BM_deque_lf/8192/2     2586448000 ns       955307 ns            1
BM_deque_lf/8192/3     2591908308 ns       799461 ns            1
BM_deque_lf/8192/4     1050223931 ns       817553 ns           10
BM_deque_lf/16384/1    1567731646 ns      1020000 ns           10
BM_deque_lf/16384/2    2811379462 ns       860770 ns            1
BM_deque_lf/16384/3    2698312154 ns       836152 ns            1
BM_deque_lf/16384/4    1031344339 ns       892453 ns           10
BM_deque_lf_s/0/0       422496185 ns       794993 ns           10
BM_deque_lf_s/100/1     679270792 ns       851439 ns           10
BM_deque_lf_s/100/2    1111852285 ns       838770 ns           10
BM_deque_lf_s/100/3    1052322885 ns       840116 ns           10
BM_deque_lf_s/100/4     412133262 ns       855370 ns           10
BM_deque_lf_s/1024/1    761101154 ns       850161 ns           10
BM_deque_lf_s/1024/2   1128857131 ns       844130 ns           10
BM_deque_lf_s/1024/3   1131554931 ns       877669 ns           10
BM_deque_lf_s/1024/4    431781169 ns       796484 ns           10
BM_deque_lf_s/8192/1    883397677 ns       976676 ns           10
BM_deque_lf_s/8192/2   1612630654 ns      1003470 ns           10
BM_deque_lf_s/8192/3   1507343354 ns       992331 ns           10
BM_deque_lf_s/8192/4    439086692 ns       796693 ns           10
BM_deque_lf_s/16384/1   958881154 ns       908300 ns           10
BM_deque_lf_s/16384/2  1950552500 ns       952538 ns           10
BM_deque_lf_s/16384/3  1837836785 ns       945884 ns           10
BM_deque_lf_s/16384/4   430761169 ns       809408 ns           10
BM_deque2_lf/0/0        545531608 ns       783415 ns           10
BM_deque2_lf/100/1     1012439092 ns       867308 ns           10
BM_deque2_lf/100/2     1772799823 ns       841092 ns           10
BM_deque2_lf/100/3     1537328123 ns       817900 ns           10
BM_deque2_lf/100/4      547628815 ns       843470 ns           10
BM_deque2_lf/1024/1    1055136292 ns       877492 ns           10
BM_deque2_lf/1024/2    2078116069 ns       892808 ns           10
BM_deque2_lf/1024/3    1952096539 ns       842962 ns           10
BM_deque2_lf/1024/4     495787031 ns       804846 ns           10
BM_deque2_lf/8192/1    1151036531 ns       976939 ns           10
BM_deque2_lf/8192/2    2483362946 ns       921931 ns           10
BM_deque2_lf/8192/3    2454667569 ns       851208 ns           10
BM_deque2_lf/8192/4     537893877 ns       818477 ns           10
BM_deque2_lf/16384/1   1205668008 ns       944100 ns           10
BM_deque2_lf/16384/2   2719872692 ns       561616 ns            1
BM_deque2_lf/16384/3   2631592385 ns      1025770 ns            1
BM_deque2_lf/16384/4    508518862 ns       880477 ns           10
BM_deque2_lf_s/0/0      290025323 ns       844654 ns           10
BM_deque2_lf_s/100/1    607301969 ns       845862 ns           10
BM_deque2_lf_s/100/2    928048985 ns       824654 ns           10
BM_deque2_lf_s/100/3    854982900 ns       817838 ns           10
BM_deque2_lf_s/100/4    294546677 ns       899054 ns           10
BM_deque2_lf_s/1024/1   668763654 ns       967261 ns           10
BM_deque2_lf_s/1024/2   968311008 ns       883131 ns           10
BM_deque2_lf_s/1024/3   917609831 ns       881800 ns           10
BM_deque2_lf_s/1024/4   293927054 ns       862200 ns           10
BM_deque2_lf_s/8192/1   762199292 ns       930039 ns           10
BM_deque2_lf_s/8192/2  1550767508 ns       852800 ns           10
BM_deque2_lf_s/8192/3  1431551208 ns       977408 ns           10
BM_deque2_lf_s/8192/4   287964315 ns       758392 ns           10
BM_deque2_lf_s/16384/1  835571146 ns       845423 ns           10
BM_deque2_lf_s/16384/2 1902318408 ns       910792 ns           10
BM_deque2_lf_s/16384/3 1798374762 ns      1012816 ns           10
BM_deque2_lf_s/16384/4  294667215 ns       883000 ns           10
BM_ypipe/0/0            195096699 ns       839215 ns          100
BM_ypipe/100/1          469940446 ns       855808 ns           10
BM_ypipe/100/2          225177570 ns       833568 ns          100
BM_ypipe/100/3          222528732 ns       844632 ns          100
BM_ypipe/100/4          192700239 ns       815123 ns          100
BM_ypipe/1024/1         699183346 ns       918916 ns           10
BM_ypipe/1024/2         256869008 ns       989262 ns           10
BM_ypipe/1024/3         245717105 ns       918897 ns          100
BM_ypipe/1024/4         196063253 ns       848385 ns          100
BM_ypipe/8192/1         975298346 ns       876762 ns           10
BM_ypipe/8192/2         346221515 ns      1096107 ns           10
BM_ypipe/8192/3         324139392 ns      1003316 ns           10
BM_ypipe/8192/4         195583657 ns       840435 ns          100
BM_ypipe/16384/1       1158631523 ns       982162 ns           10
BM_ypipe/16384/2        407032738 ns      1174585 ns           10
BM_ypipe/16384/3        378670431 ns      1207046 ns           10
BM_ypipe/16384/4        191959736 ns       815123 ns          100
BM_ypipe_s/0/0          195270895 ns       847319 ns          100
BM_ypipe_s/100/1        501646477 ns       778538 ns           10
BM_ypipe_s/100/2        229640071 ns       813918 ns          100
BM_ypipe_s/100/3        224661417 ns       828014 ns          100
BM_ypipe_s/100/4        196135055 ns       801741 ns          100
BM_ypipe_s/1024/1       702887738 ns       915092 ns           10
BM_ypipe_s/1024/2       257167239 ns       961908 ns           10
BM_ypipe_s/1024/3       252241854 ns       912961 ns           10
BM_ypipe_s/1024/4       195632238 ns       793323 ns          100
BM_ypipe_s/8192/1       979163131 ns       914161 ns           10
BM_ypipe_s/8192/2       344285008 ns      1106161 ns           10
BM_ypipe_s/8192/3       324141769 ns      1016792 ns           10
BM_ypipe_s/8192/4       193270770 ns       849694 ns          100
BM_ypipe_s/16384/1     1149635954 ns       938777 ns           10
BM_ypipe_s/16384/2      410199346 ns      1156693 ns           10
BM_ypipe_s/16384/3      380352131 ns      1135585 ns           10
BM_ypipe_s/16384/4      198189308 ns       817941 ns          100
BM_ypipe_lf/0/0         565431239 ns       830622 ns           10
BM_ypipe_lf/100/1      1074146623 ns       804700 ns           10
BM_ypipe_lf/100/2      1709412839 ns       853300 ns           10
BM_ypipe_lf/100/3      1697839277 ns       827492 ns           10
BM_ypipe_lf/100/4       551036277 ns       866169 ns           10
BM_ypipe_lf/1024/1     1079873600 ns       904054 ns           10
BM_ypipe_lf/1024/2     2084277046 ns       892631 ns           10
BM_ypipe_lf/1024/3     1948667869 ns       871154 ns           10
BM_ypipe_lf/1024/4      518227139 ns       808892 ns           10
BM_ypipe_lf/8192/1     1169936331 ns       954515 ns           10
BM_ypipe_lf/8192/2     2471232216 ns       863838 ns           10
BM_ypipe_lf/8192/3     2428107592 ns       849246 ns           10
BM_ypipe_lf/8192/4      510033223 ns       795830 ns           10
BM_ypipe_lf/16384/1    1253490162 ns      1049208 ns           10
BM_ypipe_lf/16384/2    2722843154 ns       809925 ns            1
BM_ypipe_lf/16384/3    2645532078 ns      1040076 ns            1
BM_ypipe_lf/16384/4     609801377 ns       801830 ns           10
BM_ypipe_lf_s/0/0       265033438 ns       772369 ns           10
BM_ypipe_lf_s/100/1     608827169 ns       856577 ns           10
BM_ypipe_lf_s/100/2     901404485 ns       829654 ns           10
BM_ypipe_lf_s/100/3     866636469 ns       883939 ns           10
BM_ypipe_lf_s/100/4     262039423 ns       864832 ns           10
BM_ypipe_lf_s/1024/1    635233023 ns       881785 ns           10
BM_ypipe_lf_s/1024/2    983685208 ns       924231 ns           10
BM_ypipe_lf_s/1024/3    925771862 ns       945530 ns           10
BM_ypipe_lf_s/1024/4    262933277 ns       763276 ns           10
BM_ypipe_lf_s/8192/1    765321462 ns       910969 ns           10
BM_ypipe_lf_s/8192/2   1545372646 ns       860531 ns           10
BM_ypipe_lf_s/8192/3   1401979231 ns       860347 ns           10
BM_ypipe_lf_s/8192/4    255453200 ns       826415 ns           10
BM_ypipe_lf_s/16384/1   825610700 ns       903477 ns           10
BM_ypipe_lf_s/16384/2  1903962408 ns      1045846 ns           10
BM_ypipe_lf_s/16384/3  1781425677 ns       923970 ns           10
BM_ypipe_lf_s/16384/4   263259954 ns       789854 ns           10
```
### affine and block quad times per msg.
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
