### 8xr, 8xw, lf_s deprecated
```c++
[@localhost lf]$ ./LF_ypipe_benchmark 
2021-10-11T07:26:17-04:00
Running ./LF_ypipe_benchmark
Run on (4 X 2419.2 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x4)
Load Average: 0.22, 0.14, 0.15
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                64611321 ns     63009173 ns           10
BM_cvnotify0               157788 ns       153564 ns         4555
BM_yield                424987133 ns      1716520 ns           10
BM_yield2                10274038 ns      1494346 ns          490
BM_deque0/0/0            13856407 ns      1105799 ns          637
BM_deque0/100/1          36714591 ns      1434096 ns          100
BM_deque0/100/2          40373980 ns      1622247 ns          100
BM_deque0/100/3          31969270 ns      1532407 ns          100
BM_deque0/100/4          22607664 ns      1506993 ns          482
BM_deque0/1024/1         93298229 ns      1600104 ns          100
BM_deque0/1024/2         58672103 ns      1652183 ns          100
BM_deque0/1024/3         52532802 ns      1601777 ns          100
BM_deque0/1024/4         42674216 ns      1523839 ns          100
BM_deque0/8192/1        187468329 ns      1743897 ns          100
BM_deque0/8192/2        137933781 ns      1697300 ns          100
BM_deque0/8192/3        131462652 ns      1686926 ns          100
BM_deque0/8192/4        139081353 ns      1548885 ns          100
BM_deque0/16384/1       286418547 ns      1790190 ns           10
BM_deque0/16384/2       239659197 ns      1747878 ns          100
BM_deque0/16384/3       235738437 ns      1710833 ns          100
BM_deque0/16384/4       219026189 ns      1661526 ns          100
BM_deque/0/0             19909117 ns      1208888 ns          576
BM_deque/100/1           56559234 ns      1589808 ns          100
BM_deque/100/2           46004900 ns      1582627 ns          100
BM_deque/100/3           37481583 ns      1463411 ns          100
BM_deque/100/4           27490143 ns      1345877 ns          100
BM_deque/1024/1         102486100 ns      1690443 ns          100
BM_deque/1024/2          68399806 ns      1528893 ns          100
BM_deque/1024/3          60968465 ns      1543371 ns          100
BM_deque/1024/4          52119659 ns      1473832 ns          100
BM_deque/8192/1         198019209 ns      1734113 ns          100
BM_deque/8192/2         139392397 ns      1698066 ns          100
BM_deque/8192/3         138924304 ns      1651182 ns          100
BM_deque/8192/4         130488640 ns      1554995 ns          100
BM_deque/16384/1        315187160 ns      1792520 ns           10
BM_deque/16384/2        246140246 ns      1674648 ns          100
BM_deque/16384/3        245036408 ns      1688240 ns          100
BM_deque/16384/4        229316016 ns      1673712 ns          100
BM_deque_lf/0/0          28009093 ns      1234716 ns          100
BM_deque_lf/100/1       101817669 ns      1387822 ns          100
BM_deque_lf/100/2        90412593 ns      1378760 ns          100
BM_deque_lf/100/3        64528378 ns      1380567 ns          100
BM_deque_lf/100/4        41710535 ns      1289578 ns          100
BM_deque_lf/1024/1      257220703 ns      1312061 ns           10
BM_deque_lf/1024/2      218660660 ns      1419717 ns          100
BM_deque_lf/1024/3      190604516 ns      1427928 ns          100
BM_deque_lf/1024/4      154108769 ns      1349738 ns          100
BM_deque_lf/8192/1      618154826 ns      1362970 ns           10
BM_deque_lf/8192/2      632905653 ns      1487451 ns           10
BM_deque_lf/8192/3      640502056 ns      1283920 ns           10
BM_deque_lf/8192/4      519006268 ns      1454631 ns           10
BM_deque_lf/16384/1     784420835 ns      1479860 ns           10
BM_deque_lf/16384/2     672287631 ns      1438070 ns           10
BM_deque_lf/16384/3     828409215 ns      1293190 ns           10
BM_deque_lf/16384/4     645464689 ns      1353221 ns           10
BM_deque_lf_s/0/0        38119811 ns      1176374 ns          100
BM_deque_lf_s/100/1     115394705 ns      1433096 ns          100
BM_deque_lf_s/100/2      95071567 ns      1441453 ns          100
BM_deque_lf_s/100/3      73459325 ns      1331937 ns          100
BM_deque_lf_s/100/4      50141593 ns      1280358 ns          100
BM_deque_lf_s/1024/1    256358332 ns      1537341 ns           10
BM_deque_lf_s/1024/2    213144197 ns      1470752 ns          100
BM_deque_lf_s/1024/3    176976410 ns      1402283 ns          100
BM_deque_lf_s/1024/4    148229348 ns      1388712 ns          100
BM_deque_lf_s/8192/1    931718505 ns      1490180 ns           10
BM_deque_lf_s/8192/2   1014167083 ns      1325210 ns           10
BM_deque_lf_s/8192/3    944402360 ns      1488690 ns           10
BM_deque_lf_s/8192/4    828202256 ns      1524620 ns           10
BM_deque_lf_s/16384/1  1229485046 ns      1563500 ns           10
BM_deque_lf_s/16384/2  1347982042 ns      1668950 ns           10
BM_deque_lf_s/16384/3  1391188152 ns      1408680 ns           10
BM_deque_lf_s/16384/4  1176030390 ns      1343950 ns           10
BM_deque2_lf/0/0         20791514 ns      1195195 ns          583
BM_deque2_lf/100/1       88245338 ns      1351618 ns          100
BM_deque2_lf/100/2       70386416 ns      1357612 ns          100
BM_deque2_lf/100/3       51820920 ns      1393650 ns          100
BM_deque2_lf/100/4       36399454 ns      1266850 ns          100
BM_deque2_lf/1024/1     234654073 ns      1433625 ns          100
BM_deque2_lf/1024/2     190828191 ns      1444994 ns          100
BM_deque2_lf/1024/3     166008906 ns      1434874 ns          100
BM_deque2_lf/1024/4     139474508 ns      1348685 ns          100
BM_deque2_lf/8192/1     595019613 ns      1603051 ns           10
BM_deque2_lf/8192/2     548448061 ns      1390431 ns           10
BM_deque2_lf/8192/3     519922078 ns      1375140 ns           10
BM_deque2_lf/8192/4     457431548 ns      1521391 ns           10
BM_deque2_lf/16384/1    720914653 ns      1449620 ns           10
BM_deque2_lf/16384/2    674583951 ns      1371610 ns           10
BM_deque2_lf/16384/3    779956531 ns      1485390 ns           10
BM_deque2_lf/16384/4    578454316 ns      1570590 ns           10
BM_deque2_lf_s/0/0       37640759 ns      1330602 ns          100
BM_deque2_lf_s/100/1    107951571 ns      1559885 ns          100
BM_deque2_lf_s/100/2     88778758 ns      1504228 ns          100
BM_deque2_lf_s/100/3     70219010 ns      1519433 ns          100
BM_deque2_lf_s/100/4     53490899 ns      1449750 ns          100
BM_deque2_lf_s/1024/1   234773843 ns      1615770 ns          100
BM_deque2_lf_s/1024/2   196378576 ns      1515192 ns          100
BM_deque2_lf_s/1024/3   172558519 ns      1459570 ns          100
BM_deque2_lf_s/1024/4   155134265 ns      1490673 ns          100
BM_deque2_lf_s/8192/1   842545653 ns      1526830 ns           10
BM_deque2_lf_s/8192/2   896774577 ns      1529750 ns           10
BM_deque2_lf_s/8192/3   868387383 ns      1598831 ns           10
BM_deque2_lf_s/8192/4   806685614 ns      1583900 ns           10
BM_deque2_lf_s/16384/1 1043071126 ns      1604550 ns           10
BM_deque2_lf_s/16384/2 1166739816 ns      1556730 ns           10
BM_deque2_lf_s/16384/3 1101851164 ns      1628560 ns           10
BM_deque2_lf_s/16384/4 1020325675 ns      1447530 ns           10
BM_ypipe/0/0             20229761 ns      1060414 ns          706
BM_ypipe/100/1           58419116 ns      1741111 ns          100
BM_ypipe/100/2           36972098 ns      1946275 ns          100
BM_ypipe/100/3           30823035 ns      1629941 ns          100
BM_ypipe/100/4           26519808 ns      1304652 ns          100
BM_ypipe/1024/1          98266141 ns      1767374 ns          100
BM_ypipe/1024/2          59988410 ns      1953010 ns          100
BM_ypipe/1024/3          52072918 ns      1881349 ns          100
BM_ypipe/1024/4          42643367 ns      1704320 ns          100
BM_ypipe/8192/1         165669071 ns      1962527 ns          100
BM_ypipe/8192/2         136737305 ns      1827805 ns          100
BM_ypipe/8192/3         129610960 ns      1794661 ns          100
BM_ypipe/8192/4         143118468 ns      1864328 ns          100
BM_ypipe/16384/1        294941040 ns      2140510 ns           10
BM_ypipe/16384/2        270444769 ns      2049781 ns           10
BM_ypipe/16384/3        267181027 ns      2005791 ns           10
BM_ypipe/16384/4        270642294 ns      2026805 ns          100
BM_ypipe_s/0/0           21539402 ns      1107429 ns          619
BM_ypipe_s/100/1         59438360 ns      1734552 ns          100
BM_ypipe_s/100/2         36732914 ns      1821725 ns          100
BM_ypipe_s/100/3         30905603 ns      1596524 ns          100
BM_ypipe_s/100/4         27448806 ns      1339973 ns          100
BM_ypipe_s/1024/1        99882302 ns      1814236 ns          100
BM_ypipe_s/1024/2        59048085 ns      1903506 ns          100
BM_ypipe_s/1024/3        52243208 ns      1921126 ns          100
BM_ypipe_s/1024/4        44646550 ns      1758588 ns          100
BM_ypipe_s/8192/1       166343318 ns      1952595 ns          100
BM_ypipe_s/8192/2       130706081 ns      1861186 ns          100
BM_ypipe_s/8192/3       145988317 ns      1890682 ns          100
BM_ypipe_s/8192/4       136538253 ns      1852380 ns          100
BM_ypipe_s/16384/1      295521190 ns      2059681 ns           10
BM_ypipe_s/16384/2      268475608 ns      1764550 ns           10
BM_ypipe_s/16384/3      259808104 ns      1891811 ns           10
BM_ypipe_s/16384/4      256074192 ns      2173351 ns           10
BM_ypipe_lf/0/0          27661655 ns      1429795 ns          100
BM_ypipe_lf/100/1        98029212 ns      1488710 ns          100
BM_ypipe_lf/100/2        74453198 ns      1460685 ns          100
BM_ypipe_lf/100/3        55591721 ns      1477291 ns          100
BM_ypipe_lf/100/4        40095448 ns      1379938 ns          100
BM_ypipe_lf/1024/1      236663824 ns      1517355 ns          100
BM_ypipe_lf/1024/2      194324321 ns      1458608 ns          100
BM_ypipe_lf/1024/3      187758164 ns      1424188 ns          100
BM_ypipe_lf/1024/4      151654528 ns      1493025 ns          100
BM_ypipe_lf/8192/1      613412212 ns      1578491 ns           10
BM_ypipe_lf/8192/2      528734902 ns      1612201 ns           10
BM_ypipe_lf/8192/3      554650444 ns      1306961 ns           10
BM_ypipe_lf/8192/4      471346804 ns      1379940 ns           10
BM_ypipe_lf/16384/1     727906176 ns      1448540 ns           10
BM_ypipe_lf/16384/2     577474465 ns      1428721 ns           10
BM_ypipe_lf/16384/3     825958743 ns      1556851 ns           10
BM_ypipe_lf/16384/4     589845831 ns      1493570 ns           10
BM_ypipe_lf_s/0/0        47067733 ns      1339964 ns          100
BM_ypipe_lf_s/100/1     118750922 ns      1553035 ns          100
BM_ypipe_lf_s/100/2      96814970 ns      1526141 ns          100
BM_ypipe_lf_s/100/3      81361941 ns      1553354 ns          100
BM_ypipe_lf_s/100/4      62986305 ns      1537326 ns          100
BM_ypipe_lf_s/1024/1    237707169 ns      1506696 ns          100
BM_ypipe_lf_s/1024/2    201975589 ns      1506258 ns          100
BM_ypipe_lf_s/1024/3    181171602 ns      1520942 ns          100
BM_ypipe_lf_s/1024/4    157531298 ns      1463783 ns          100
BM_ypipe_lf_s/8192/1    869505723 ns      1594241 ns           10
BM_ypipe_lf_s/8192/2    896477558 ns      1938271 ns           10
BM_ypipe_lf_s/8192/3    869810193 ns      1488151 ns           10
BM_ypipe_lf_s/8192/4    804434983 ns      1506471 ns           10
BM_ypipe_lf_s/16384/1  1076096042 ns      1656921 ns           10
BM_ypipe_lf_s/16384/2  1092517289 ns      1486360 ns           10
BM_ypipe_lf_s/16384/3  1097797842 ns      1557931 ns           10
BM_ypipe_lf_s/16384/4   969938892 ns      1557081 ns           10

```

### 8xr, 8xw, lf_s
```
@localhost lf]$ ./LF_ypipe_benchmark --benchmark_filter=.*_s
2021-10-12T06:24:28-04:00
Running ./LF_ypipe_benchmark
Run on (4 X 2419.2 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x4)
Load Average: 0.06, 0.09, 0.25
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_deque_lf_s/0/0        26611407 ns      1269961 ns          100
BM_deque_lf_s/100/1      56658203 ns      1440619 ns          100
BM_deque_lf_s/100/2      72094298 ns      1461991 ns          100
BM_deque_lf_s/100/3      61173600 ns      1417056 ns          100
BM_deque_lf_s/100/4      40625175 ns      1337583 ns          100
BM_deque_lf_s/1024/1    215914573 ns      1534501 ns          100
BM_deque_lf_s/1024/2    179049788 ns      1443890 ns          100
BM_deque_lf_s/1024/3    159792914 ns      1454110 ns          100
BM_deque_lf_s/1024/4    143177074 ns      1380945 ns          100
BM_deque_lf_s/8192/1    522785016 ns      1474441 ns           10
BM_deque_lf_s/8192/2    560322083 ns      1587250 ns           10
BM_deque_lf_s/8192/3    572290895 ns      1436510 ns           10
BM_deque_lf_s/8192/4    429071941 ns      1450470 ns           10
BM_deque_lf_s/16384/1   685679081 ns      1568910 ns           10
BM_deque_lf_s/16384/2   666679961 ns      1409971 ns           10
BM_deque_lf_s/16384/3   808227281 ns      1564221 ns           10
BM_deque_lf_s/16384/4   630520877 ns      1503150 ns           10
BM_deque2_lf_s/0/0       21190915 ns      1287711 ns          554
BM_deque2_lf_s/100/1     84264606 ns      1494652 ns          100
BM_deque2_lf_s/100/2     63565845 ns      1435735 ns          100
BM_deque2_lf_s/100/3     49228274 ns      1412414 ns          100
BM_deque2_lf_s/100/4     36348791 ns      1431753 ns          100
BM_deque2_lf_s/1024/1   202279954 ns      1499352 ns          100
BM_deque2_lf_s/1024/2   166032393 ns      1529300 ns          100
BM_deque2_lf_s/1024/3   152391969 ns      1421852 ns          100
BM_deque2_lf_s/1024/4   131962479 ns      1410941 ns          100
BM_deque2_lf_s/8192/1   489987650 ns      1523801 ns           10
BM_deque2_lf_s/8192/2   456308752 ns      1512930 ns           10
BM_deque2_lf_s/8192/3   494099091 ns      1440900 ns           10
BM_deque2_lf_s/8192/4   401694539 ns      1495910 ns           10
BM_deque2_lf_s/16384/1  635458610 ns      1609810 ns           10
BM_deque2_lf_s/16384/2  565623897 ns      1323211 ns           10
BM_deque2_lf_s/16384/3  717373914 ns      1512009 ns           10
BM_deque2_lf_s/16384/4  528361310 ns      1442710 ns           10
BM_ypipe_s/0/0           19652768 ns      1097191 ns          666
BM_ypipe_s/100/1         47965007 ns      1595741 ns          100
BM_ypipe_s/100/2         27257969 ns      1523996 ns          100
BM_ypipe_s/100/3         25539334 ns      1484506 ns          100
BM_ypipe_s/100/4         23013455 ns      1178476 ns          606
BM_ypipe_s/1024/1        84227872 ns      1639818 ns          100
BM_ypipe_s/1024/2        52854691 ns      1849763 ns          100
BM_ypipe_s/1024/3        42895666 ns      1690974 ns          100
BM_ypipe_s/1024/4        34237869 ns      1536422 ns          100
BM_ypipe_s/8192/1       155339508 ns      1892902 ns          100
BM_ypipe_s/8192/2       135095104 ns      1785830 ns          100
BM_ypipe_s/8192/3       128243728 ns      1777605 ns          100
BM_ypipe_s/8192/4       119218660 ns      1809287 ns          100
BM_ypipe_s/16384/1      263995027 ns      2176611 ns           10
BM_ypipe_s/16384/2      263457635 ns      1797860 ns           10
BM_ypipe_s/16384/3      293630625 ns      1645420 ns           10
BM_ypipe_s/16384/4      213347280 ns      1774546 ns          100
BM_ypipe_lf/0/0          22784699 ns      1388741 ns          520
BM_ypipe_lf/100/1        54545494 ns      1537884 ns          100
BM_ypipe_lf/100/2        68160142 ns      1620599 ns          100
BM_ypipe_lf/100/3        53678188 ns      1604451 ns          100
BM_ypipe_lf/100/4        37215896 ns      1436496 ns          100
BM_ypipe_lf/1024/1      210183688 ns      1691307 ns          100
BM_ypipe_lf/1024/2      179221801 ns      1697636 ns          100
BM_ypipe_lf/1024/3      170559063 ns      1625860 ns          100
BM_ypipe_lf/1024/4      142617481 ns      1526510 ns          100
BM_ypipe_lf/8192/1      524565673 ns      1735250 ns           10
BM_ypipe_lf/8192/2      514719330 ns      1646120 ns           10
BM_ypipe_lf/8192/3      578257161 ns      1674400 ns           10
BM_ypipe_lf/8192/4      478283539 ns      1477870 ns           10
BM_ypipe_lf/16384/1     657733635 ns      1863210 ns           10
BM_ypipe_lf/16384/2     587695202 ns      1728570 ns           10
BM_ypipe_lf/16384/3     789027541 ns      1572070 ns           10
BM_ypipe_lf/16384/4     577321308 ns      1607850 ns           10
BM_ypipe_lf_s/0/0        21807037 ns      1262484 ns          552
BM_ypipe_lf_s/100/1      84107982 ns      1476081 ns          100
BM_ypipe_lf_s/100/2      63965484 ns      1434997 ns          100
BM_ypipe_lf_s/100/3      50252229 ns      1387171 ns          100
BM_ypipe_lf_s/100/4      36352182 ns      1269076 ns          100
BM_ypipe_lf_s/1024/1    200769383 ns      1448718 ns          100
BM_ypipe_lf_s/1024/2    164380045 ns      1435933 ns          100
BM_ypipe_lf_s/1024/3    149896899 ns      1438743 ns          100
BM_ypipe_lf_s/1024/4    130749006 ns      1389490 ns          100
BM_ypipe_lf_s/8192/1    496784270 ns      1617040 ns           10
BM_ypipe_lf_s/8192/2    456056815 ns      1441060 ns           10
BM_ypipe_lf_s/8192/3    458550703 ns      1392581 ns           10
BM_ypipe_lf_s/8192/4    354561358 ns      1478251 ns           10
BM_ypipe_lf_s/16384/1   634795139 ns      1720650 ns           10
BM_ypipe_lf_s/16384/2   578812213 ns      1539360 ns           10
BM_ypipe_lf_s/16384/3   695775711 ns      1446830 ns           10
BM_ypipe_lf_s/16384/4   452249472 ns      1417411 ns           10

```

### 2xr,2xw
```c++
@localhost lf]$ ./LF_ypipe_benchmark 
2021-10-11T08:10:05-04:00
Running ./LF_ypipe_benchmark
Run on (4 X 2419.2 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x4)
Load Average: 0.14, 0.40, 1.52
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                75750851 ns     70811114 ns           10
BM_cvnotify0               172239 ns       158705 ns         4402
BM_yield                443164590 ns      1782521 ns           10
BM_yield2                10187285 ns      1542433 ns          475
BM_deque0/0/0            16231040 ns       256012 ns         1000
BM_deque0/100/1          32447718 ns       294181 ns          100
BM_deque0/100/2          34831627 ns       330090 ns          100
BM_deque0/100/3          26583389 ns       314700 ns          100
BM_deque0/100/4          17914016 ns       278474 ns         1000
BM_deque0/1024/1         76723160 ns       340424 ns          100
BM_deque0/1024/2         51039549 ns       367187 ns          100
BM_deque0/1024/3         46696153 ns       345931 ns          100
BM_deque0/1024/4         41679045 ns       349112 ns          100
BM_deque0/8192/1        231288413 ns       417442 ns          100
BM_deque0/8192/2        212937946 ns       415687 ns          100
BM_deque0/8192/3        201058924 ns       391123 ns          100
BM_deque0/8192/4        199219551 ns       347984 ns          100
BM_deque0/16384/1       426141122 ns       443430 ns           10
BM_deque0/16384/2       432234694 ns       430250 ns           10
BM_deque0/16384/3       379584012 ns       360550 ns           10
BM_deque0/16384/4       373475950 ns       350010 ns           10
BM_deque/0/0             19524138 ns       260820 ns         1000
BM_deque/100/1           44034769 ns       298959 ns          100
BM_deque/100/2           38957077 ns       298075 ns          100
BM_deque/100/3           33100101 ns       309264 ns          100
BM_deque/100/4           28701751 ns       310709 ns          100
BM_deque/1024/1          92773120 ns       371739 ns          100
BM_deque/1024/2          50656349 ns       331919 ns          100
BM_deque/1024/3          45856989 ns       319187 ns          100
BM_deque/1024/4          41100697 ns       308015 ns          100
BM_deque/8192/1         215780541 ns       327761 ns          100
BM_deque/8192/2         206848763 ns       321917 ns          100
BM_deque/8192/3         191558046 ns       318069 ns          100
BM_deque/8192/4         183056637 ns       300647 ns          100
BM_deque/16384/1        399015962 ns       356400 ns           10
BM_deque/16384/2        394164627 ns       372959 ns           10
BM_deque/16384/3        371254319 ns       345130 ns           10
BM_deque/16384/4        346702362 ns       333159 ns           10
BM_deque_lf/0/0          19857178 ns       252460 ns         1000
BM_deque_lf/100/1        50667288 ns       281206 ns          100
BM_deque_lf/100/2        40285519 ns       272604 ns          100
BM_deque_lf/100/3        29489810 ns       290090 ns          100
BM_deque_lf/100/4        24049908 ns       276565 ns         1000
BM_deque_lf/1024/1      101739145 ns       277180 ns          100
BM_deque_lf/1024/2       73835156 ns       317191 ns          100
BM_deque_lf/1024/3       55621457 ns       270958 ns          100
BM_deque_lf/1024/4       48164605 ns       269641 ns          100
BM_deque_lf/8192/1      233352828 ns       315168 ns          100
BM_deque_lf/8192/2      223208398 ns       318962 ns          100
BM_deque_lf/8192/3      202039757 ns       340647 ns          100
BM_deque_lf/8192/4      189590002 ns       310684 ns          100
BM_deque_lf/16384/1     401638844 ns       345729 ns           10
BM_deque_lf/16384/2     426726455 ns       333260 ns           10
BM_deque_lf/16384/3     388011882 ns       342290 ns           10
BM_deque_lf/16384/4     354074779 ns       308890 ns           10
BM_deque_lf_s/0/0        20608222 ns       266611 ns         1000
BM_deque_lf_s/100/1      52460155 ns       298333 ns          100
BM_deque_lf_s/100/2      39380375 ns       286705 ns          100
BM_deque_lf_s/100/3      31015239 ns       289694 ns          100
BM_deque_lf_s/100/4      25055447 ns       286151 ns         1000
BM_deque_lf_s/1024/1     97902642 ns       291857 ns          100
BM_deque_lf_s/1024/2     66202110 ns       297365 ns          100
BM_deque_lf_s/1024/3     57775882 ns       292881 ns          100
BM_deque_lf_s/1024/4     49062525 ns       310343 ns          100
BM_deque_lf_s/8192/1    230607483 ns       319104 ns          100
BM_deque_lf_s/8192/2    209466897 ns       317868 ns          100
BM_deque_lf_s/8192/3    197242483 ns       304245 ns          100
BM_deque_lf_s/8192/4    187546358 ns       295965 ns          100
BM_deque_lf_s/16384/1   397572051 ns       313450 ns           10
BM_deque_lf_s/16384/2   413573462 ns       293840 ns           10
BM_deque_lf_s/16384/3   378703319 ns       331450 ns           10
BM_deque_lf_s/16384/4   353862524 ns       302700 ns           10
BM_deque2_lf/0/0         20385505 ns       266143 ns         1000
BM_deque2_lf/100/1       50906286 ns       299737 ns          100
BM_deque2_lf/100/2       31941727 ns       278649 ns          100
BM_deque2_lf/100/3       25047124 ns       288106 ns          100
BM_deque2_lf/100/4       20406393 ns       276140 ns         1000
BM_deque2_lf/1024/1      85989114 ns       309790 ns          100
BM_deque2_lf/1024/2      52067611 ns       281784 ns          100
BM_deque2_lf/1024/3      44835936 ns       272574 ns          100
BM_deque2_lf/1024/4      38336991 ns       256584 ns          100
BM_deque2_lf/8192/1     223717795 ns       329393 ns          100
BM_deque2_lf/8192/2     218648235 ns       317452 ns          100
BM_deque2_lf/8192/3     208204644 ns       306431 ns          100
BM_deque2_lf/8192/4     191538676 ns       301935 ns          100
BM_deque2_lf/16384/1    400832162 ns       349401 ns           10
BM_deque2_lf/16384/2    418728210 ns       284110 ns           10
BM_deque2_lf/16384/3    382153882 ns       311220 ns           10
BM_deque2_lf/16384/4    351673968 ns       346320 ns           10
BM_deque2_lf_s/0/0       20496033 ns       286321 ns         1000
BM_deque2_lf_s/100/1     52318578 ns       305847 ns          100
BM_deque2_lf_s/100/2     31744776 ns       305070 ns          100
BM_deque2_lf_s/100/3     25216557 ns       312767 ns          100
BM_deque2_lf_s/100/4     21389008 ns       287898 ns         1000
BM_deque2_lf_s/1024/1    90804742 ns       327121 ns          100
BM_deque2_lf_s/1024/2    55915443 ns       291619 ns          100
BM_deque2_lf_s/1024/3    48545725 ns       279162 ns          100
BM_deque2_lf_s/1024/4    42931910 ns       253254 ns          100
BM_deque2_lf_s/8192/1   224879668 ns       306352 ns          100
BM_deque2_lf_s/8192/2   213216540 ns       330850 ns          100
BM_deque2_lf_s/8192/3   207215313 ns       314130 ns          100
BM_deque2_lf_s/8192/4   184946923 ns       302339 ns          100
BM_deque2_lf_s/16384/1  409876069 ns       318020 ns           10
BM_deque2_lf_s/16384/2  432159475 ns       340951 ns           10
BM_deque2_lf_s/16384/3  392188013 ns       332870 ns           10
BM_deque2_lf_s/16384/4  361391032 ns       337640 ns           10
BM_ypipe/0/0             22368814 ns       277941 ns         1000
BM_ypipe/100/1           50845021 ns       302696 ns          100
BM_ypipe/100/2           33016116 ns       319131 ns          100
BM_ypipe/100/3           29938872 ns       322454 ns          100
BM_ypipe/100/4           25734841 ns       275863 ns         1000
BM_ypipe/1024/1          82277081 ns       329588 ns          100
BM_ypipe/1024/2          43480984 ns       328356 ns          100
BM_ypipe/1024/3          39615454 ns       305430 ns          100
BM_ypipe/1024/4          33105850 ns       273829 ns          100
BM_ypipe/8192/1         221105377 ns       337574 ns          100
BM_ypipe/8192/2         213706070 ns       325943 ns          100
BM_ypipe/8192/3         197608402 ns       324041 ns          100
BM_ypipe/8192/4         184913656 ns       289435 ns          100
BM_ypipe/16384/1        403521178 ns       331990 ns           10
BM_ypipe/16384/2        414600829 ns       313100 ns           10
BM_ypipe/16384/3        389664327 ns       335360 ns           10
BM_ypipe/16384/4        363606137 ns       323550 ns           10
BM_ypipe_s/0/0           23463769 ns       287658 ns         1000
BM_ypipe_s/100/1         51193357 ns       299549 ns          100
```

### 4xr,4xw
```
@localhost lf]$ ./LF_ypipe_benchmark 
2021-10-11T08:35:35-04:00
Running ./LF_ypipe_benchmark
Run on (4 X 2419.2 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x4)
Load Average: 0.57, 1.35, 1.68
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                61541798 ns     60734396 ns           11
BM_cvnotify0               153438 ns       152332 ns         4582
BM_yield                437202225 ns      1769820 ns           10
BM_yield2                10424189 ns      1575727 ns          421
BM_deque0/0/0            14035821 ns       469555 ns         1331
BM_deque0/100/1          32500604 ns       582290 ns          100
BM_deque0/100/2          38937293 ns       713713 ns          100
BM_deque0/100/3          31970753 ns       684912 ns          100
BM_deque0/100/4          21979456 ns       609557 ns         1136
BM_deque0/1024/1         95032160 ns       688432 ns          100
BM_deque0/1024/2         54959559 ns       716257 ns          100
BM_deque0/1024/3         54055057 ns       732592 ns          100
BM_deque0/1024/4         41672826 ns       653895 ns          100
BM_deque0/8192/1        189779579 ns       731178 ns          100
BM_deque0/8192/2        134897063 ns       714737 ns          100
BM_deque0/8192/3        137172037 ns       709198 ns          100
BM_deque0/8192/4        130310520 ns       714278 ns          100
BM_deque0/16384/1       306035957 ns       785660 ns           10
BM_deque0/16384/2       256485059 ns       707050 ns           10
BM_deque0/16384/3       272147528 ns       735090 ns           10
BM_deque0/16384/4       228826724 ns       697955 ns          100
BM_deque/0/0             20544666 ns       568461 ns         1211
BM_deque/100/1           56938449 ns       724353 ns          100
BM_deque/100/2           41430834 ns       676402 ns          100
BM_deque/100/3           35011968 ns       662657 ns          100
BM_deque/100/4           27040648 ns       614970 ns          100
BM_deque/1024/1          99827893 ns       700090 ns          100
BM_deque/1024/2          66117613 ns       710378 ns          100
BM_deque/1024/3          59213901 ns       696224 ns          100
BM_deque/1024/4          54004443 ns       657117 ns          100
BM_deque/8192/1         202593915 ns       736167 ns          100
BM_deque/8192/2         142269318 ns       721527 ns          100
BM_deque/8192/3         145123168 ns       718012 ns          100
BM_deque/8192/4         132376552 ns       639241 ns          100
BM_deque/16384/1        297625340 ns       744000 ns           10
BM_deque/16384/2        264645585 ns       706940 ns           10
BM_deque/16384/3        257100842 ns       689210 ns           10
BM_deque/16384/4        238215775 ns       708185 ns          100
BM_deque_lf/0/0          25190659 ns       588957 ns          100
BM_deque_lf/100/1        76585143 ns       662641 ns          100
BM_deque_lf/100/2        61984398 ns       628420 ns          100
BM_deque_lf/100/3        46797545 ns       627249 ns          100
BM_deque_lf/100/4        36216187 ns       580575 ns          100
BM_deque_lf/1024/1      176173672 ns       693404 ns          100
BM_deque_lf/1024/2      142957058 ns       650068 ns          100
BM_deque_lf/1024/3      130566561 ns       668799 ns          100
BM_deque_lf/1024/4      120587153 ns       617344 ns          100
BM_deque_lf/8192/1      410389857 ns       730060 ns           10
BM_deque_lf/8192/2      320767102 ns       734730 ns           10
BM_deque_lf/8192/3      349272278 ns       695470 ns           10
BM_deque_lf/8192/4      309011200 ns       672881 ns           10
BM_deque_lf/16384/1     501945589 ns       846110 ns           10
BM_deque_lf/16384/2     359972415 ns       762100 ns           10
BM_deque_lf/16384/3     497905241 ns       793090 ns           10
BM_deque_lf/16384/4     408857879 ns       674460 ns           10
BM_deque_lf_s/0/0        25790863 ns       577636 ns          100
BM_deque_lf_s/100/1      79679731 ns       680069 ns          100
BM_deque_lf_s/100/2      59614938 ns       654161 ns          100
BM_deque_lf_s/100/3      50375383 ns       648067 ns          100
BM_deque_lf_s/100/4      37729470 ns       610198 ns          100
BM_deque_lf_s/1024/1    176264622 ns       704876 ns          100
BM_deque_lf_s/1024/2    138783774 ns       687334 ns          100
BM_deque_lf_s/1024/3    123191936 ns       650668 ns          100
BM_deque_lf_s/1024/4    117316810 ns       644883 ns          100
BM_deque_lf_s/8192/1    465630300 ns       674670 ns           10
BM_deque_lf_s/8192/2    332339583 ns       656591 ns           10
BM_deque_lf_s/8192/3    393929394 ns       714320 ns           10
BM_deque_lf_s/8192/4    371924527 ns       679171 ns           10
BM_deque_lf_s/16384/1   558222657 ns       801150 ns           10
BM_deque_lf_s/16384/2   375155241 ns       702021 ns           10
BM_deque_lf_s/16384/3   542579149 ns       676840 ns           10
BM_deque_lf_s/16384/4   454390350 ns       747220 ns           10
BM_deque2_lf/0/0         16076761 ns       595894 ns         1242
BM_deque2_lf/100/1       79867814 ns       708026 ns          100
BM_deque2_lf/100/2       55048222 ns       647406 ns          100
BM_deque2_lf/100/3       40705485 ns       639656 ns          100
BM_deque2_lf/100/4       27844344 ns       587374 ns          100
BM_deque2_lf/1024/1     179434022 ns       677338 ns          100
BM_deque2_lf/1024/2     141890620 ns       660938 ns          100
BM_deque2_lf/1024/3     121817782 ns       662416 ns          100
BM_deque2_lf/1024/4     104988916 ns       642717 ns          100
BM_deque2_lf/8192/1     386776874 ns       761081 ns           10
BM_deque2_lf/8192/2     306700918 ns       721801 ns           10
BM_deque2_lf/8192/3     354169384 ns       610240 ns           10
BM_deque2_lf/8192/4     264754186 ns       659010 ns           10
BM_deque2_lf/16384/1    474504648 ns       773150 ns           10
BM_deque2_lf/16384/2    342557556 ns       695940 ns           10
BM_deque2_lf/16384/3    477366095 ns       731870 ns           10
BM_deque2_lf/16384/4    343621649 ns       673140 ns           10
BM_deque2_lf_s/0/0       17069891 ns       604011 ns         1246
BM_deque2_lf_s/100/1     81816591 ns       693228 ns          100
BM_deque2_lf_s/100/2     61227352 ns       696705 ns          100
BM_deque2_lf_s/100/3     40202137 ns       687805 ns          100
BM_deque2_lf_s/100/4     28464427 ns       611809 ns          100
BM_deque2_lf_s/1024/1   173583633 ns       700659 ns          100
BM_deque2_lf_s/1024/2   132944841 ns       647294 ns          100
BM_deque2_lf_s/1024/3   115588073 ns       646928 ns          100
BM_deque2_lf_s/1024/4   102309884 ns       611402 ns          100
BM_deque2_lf_s/8192/1   427649004 ns       771250 ns           10
BM_deque2_lf_s/8192/2   274821401 ns       637340 ns           10
BM_deque2_lf_s/8192/3   364353449 ns       711350 ns           10
BM_deque2_lf_s/8192/4   296426483 ns       682080 ns           10
BM_deque2_lf_s/16384/1  571128504 ns       811710 ns           10
BM_deque2_lf_s/16384/2  365865403 ns       698480 ns           10
BM_deque2_lf_s/16384/3  501652254 ns       739590 ns           10
BM_deque2_lf_s/16384/4  388833849 ns       691010 ns           10
BM_ypipe/0/0             21980612 ns       569011 ns         1236
BM_ypipe/100/1           55807961 ns       683603 ns          100
BM_ypipe/100/2           34729364 ns       724275 ns          100
BM_ypipe/100/3           29786337 ns       675486 ns          100
BM_ypipe/100/4           26757150 ns       599682 ns          100
BM_ypipe/1024/1          95278723 ns       698895 ns          100
BM_ypipe/1024/2          51722286 ns       728017 ns          100
BM_ypipe/1024/3          47284423 ns       737622 ns          100
BM_ypipe/1024/4          38889528 ns       641645 ns          100
BM_ypipe/8192/1         159869797 ns       759035 ns          100
BM_ypipe/8192/2         130340591 ns       706922 ns          100
BM_ypipe/8192/3         130391315 ns       701073 ns          100
BM_ypipe/8192/4         119036000 ns       671842 ns          100
BM_ypipe/16384/1        276585405 ns       743470 ns           10
BM_ypipe/16384/2        240293074 ns       688140 ns          100
BM_ypipe/16384/3        238446574 ns       708288 ns          100
BM_ypipe/16384/4        219522722 ns       682446 ns          100
BM_ypipe_s/0/0           20968081 ns       546292 ns         1305
BM_ypipe_s/100/1         54374877 ns       646065 ns          100
BM_ypipe_s/100/2         32654533 ns       664724 ns          100
BM_ypipe_s/100/3         28389731 ns       639969 ns          100
BM_ypipe_s/100/4         25782448 ns       575364 ns          100
BM_ypipe_s/1024/1        89048302 ns       662557 ns          100
BM_ypipe_s/1024/2        49711150 ns       703515 ns          100
BM_ypipe_s/1024/3        44991600 ns       707114 ns          100
BM_ypipe_s/1024/4        36584838 ns       617245 ns          100
BM_ypipe_s/8192/1       158740219 ns       784893 ns          100
BM_ypipe_s/8192/2       131457286 ns       712254 ns          100

```
