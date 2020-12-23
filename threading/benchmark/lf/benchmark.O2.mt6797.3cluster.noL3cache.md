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
