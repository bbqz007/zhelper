```
2020-12-21T09:23:16-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
BM_yield0                4465345 ns      4485029 ns          160
BM_cvnotify0             2824190 ns      2819295 ns          249
BM_yield                41358708 ns      1560010 ns          100
BM_yield2              117925840 ns       780005 ns          100
BM_deque0/0/0          129025265 ns      2184014 ns          100
BM_deque0/100/1        192576207 ns      1092007 ns          100
BM_deque0/100/2        184588581 ns      1950012 ns          112
BM_deque0/1024/1       283351091 ns        0.000 ns           10
BM_deque0/1024/2       258830283 ns      4680030 ns           10
BM_deque0/8192/1      1008158561 ns        0.000 ns           10
BM_deque0/8192/2      1009637635 ns      1560010 ns           10
BM_deque/0/0           377570597 ns      1560010 ns           10
BM_deque/100/1         346133941 ns      1560010 ns           10
BM_deque/100/2         311075819 ns        0.000 ns           10
BM_deque/1024/1        301945594 ns        0.000 ns           10
BM_deque/1024/2        288980983 ns      1560010 ns           10
BM_deque/8192/1       1012232859 ns      3120020 ns           10
BM_deque/8192/2       1021465609 ns        0.000 ns           10
BM_deque_lf/0/0        803872582 ns      1560010 ns           10
BM_deque_lf/100/1      836145827 ns      3120020 ns           10
BM_deque_lf/100/2      836368244 ns      1560010 ns           10
BM_deque_lf/1024/1     866937431 ns      1560010 ns           10
BM_deque_lf/1024/2     857707033 ns      1560010 ns           10
BM_deque_lf/8192/1    1036051685 ns        0.000 ns           10
BM_deque_lf/8192/2    1045008510 ns      1560010 ns           10
BM_deque_lf_s/0/0      668250377 ns      3120020 ns           10
BM_deque_lf_s/100/1    735104059 ns        0.000 ns           10
BM_deque_lf_s/100/2    740729973 ns      1560010 ns           10
BM_deque_lf_s/1024/1   695777410 ns      1560010 ns           10
BM_deque_lf_s/1024/2   666618861 ns      1560010 ns           10
BM_deque_lf_s/8192/1  1092783675 ns        0.000 ns           10
BM_deque_lf_s/8192/2  1085451265 ns      3120020 ns           10
BM_deque2_lf/0/0       754745891 ns      1560010 ns           10
BM_deque2_lf/100/1     807077699 ns      3120020 ns           10
BM_deque2_lf/100/2     821354187 ns      4680030 ns           10
BM_deque2_lf/1024/1    796460316 ns      6240040 ns           10
BM_deque2_lf/1024/2    811467230 ns      1560010 ns           10
BM_deque2_lf/8192/1   1027947060 ns        0.000 ns           10
BM_deque2_lf/8192/2   1032730996 ns        0.000 ns           10
BM_deque2_lf_s/0/0     600649373 ns        0.000 ns           10
BM_deque2_lf_s/100/1   623492642 ns      1560010 ns           10
BM_deque2_lf_s/100/2   663673331 ns      3120020 ns           10
BM_deque2_lf_s/1024/1  535433279 ns      1560010 ns           10
BM_deque2_lf_s/1024/2  507115981 ns      1560010 ns           10
BM_deque2_lf_s/8192/1 1083759911 ns        0.000 ns           10
BM_deque2_lf_s/8192/2 1044461449 ns      4680030 ns           10
BM_ypipe2/0/0          895204002 ns      1560010 ns           10
BM_ypipe2/100/1        852969804 ns        0.000 ns           10
BM_ypipe2/100/2        838894946 ns      4680030 ns           10
BM_ypipe2/1024/1       153192315 ns      2028013 ns          100
BM_ypipe2/1024/2       151839292 ns      2184014 ns          100
BM_ypipe2/8192/1       996487947 ns      1560010 ns           10
BM_ypipe2/8192/2       997084710 ns      1560010 ns           10
BM_ypipe/0/0           364309016 ns        0.000 ns           10
BM_ypipe/100/1         331865152 ns      1560010 ns           10
BM_ypipe/100/2         262408846 ns        0.000 ns           10
BM_ypipe/1024/1        155981268 ns      2496016 ns          100
BM_ypipe/1024/2        155706651 ns      2184014 ns          100
BM_ypipe/8192/1       1000556727 ns        0.000 ns           10
BM_ypipe/8192/2       1011750513 ns      1560010 ns           10
BM_ypipe_s/0/0         335660530 ns      1560010 ns           10
BM_ypipe_s/100/1       323696368 ns      3120020 ns           10
BM_ypipe_s/100/2       250318010 ns      2028013 ns          100
BM_ypipe_s/1024/1      156221346 ns      2496016 ns          100
BM_ypipe_s/1024/2      157802497 ns      1716011 ns          100
BM_ypipe_s/8192/1     1009848718 ns        0.000 ns           10
BM_ypipe_s/8192/2     1026000995 ns        0.000 ns           10
BM_ypipe_lf/0/0        716551473 ns      1560010 ns           10
BM_ypipe_lf/100/1      795698965 ns      1560010 ns           10
BM_ypipe_lf/100/2      802301077 ns        0.000 ns           10
BM_ypipe_lf/1024/1     734383727 ns      3120020 ns           10
BM_ypipe_lf/1024/2     753974531 ns      3120020 ns           10
BM_ypipe_lf/8192/1    1010031228 ns        0.000 ns           10
BM_ypipe_lf/8192/2    1010527646 ns      4680030 ns           10
BM_ypipe_lf_s/0/0      472062350 ns      1560010 ns           10
BM_ypipe_lf_s/100/1    589260202 ns      4680030 ns           10
BM_ypipe_lf_s/100/2    571230938 ns      6240040 ns           10
BM_ypipe_lf_s/1024/1   450195449 ns        0.000 ns           10
BM_ypipe_lf_s/1024/2   435990434 ns      3120020 ns           10
BM_ypipe_lf_s/8192/1  1037672507 ns      1560010 ns           10
BM_ypipe_lf_s/8192/2  1045463438 ns        0.000 ns           10
```
```
2020-12-21T21:07:04-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 4554525 ns      4629707 ns          155
BM_cvnotify0              2821810 ns      2836382 ns          264
BM_yield                 42254086 ns      1560010 ns          100
BM_yield2               116260379 ns      1560010 ns          100
BM_deque0/0/0           147561823 ns      1560010 ns          100
BM_deque0/100/1         205455938 ns      1248008 ns          100
BM_deque0/100/2         203432031 ns       780005 ns          100
BM_deque0/100/3         203299785 ns      2340015 ns          100
BM_deque0/100/4         185927267 ns      1872012 ns          100
BM_deque0/1024/1        289123019 ns        0.000 ns           10
BM_deque0/1024/2        262193814 ns        0.000 ns           10
BM_deque0/1024/3        260255552 ns      1560010 ns           10
BM_deque0/1024/4        262719068 ns      3120020 ns           10
BM_deque0/8192/1       1002734611 ns      1560010 ns           10
BM_deque0/8192/2       1012644151 ns      1560010 ns           10
BM_deque0/8192/3       1009684253 ns      1560010 ns           10
BM_deque0/8192/4       1019261788 ns        0.000 ns           10
BM_deque0/16384/1      1976977089 ns        0.000 ns           10
BM_deque0/16384/2      1983108996 ns        0.000 ns           10
BM_deque0/16384/3      1964323315 ns      1560010 ns           10
BM_deque0/16384/4      1963604556 ns      4680030 ns           10
BM_deque/0/0            402724945 ns      3120020 ns           10
BM_deque/100/1          327025787 ns        0.000 ns           10
BM_deque/100/2          309068492 ns      1560010 ns           10
BM_deque/100/3          308201011 ns      1560010 ns           10
BM_deque/100/4          309100401 ns      1560010 ns           10
BM_deque/1024/1         298733190 ns      1560010 ns           10
BM_deque/1024/2         291794583 ns      1560010 ns           10
BM_deque/1024/3         289691131 ns        0.000 ns           10
BM_deque/1024/4         287370349 ns        0.000 ns           10
BM_deque/8192/1        1017738681 ns      1560010 ns           10
BM_deque/8192/2        1013387076 ns      1560010 ns           10
BM_deque/8192/3        1003874172 ns        0.000 ns           10
BM_deque/8192/4        1010322299 ns      3120020 ns           10
BM_deque/16384/1       1976610439 ns      1560010 ns           10
BM_deque/16384/2       1977416155 ns      1560010 ns           10
BM_deque/16384/3       1976908995 ns      3120020 ns           10
BM_deque/16384/4       1978615042 ns      1560010 ns           10
BM_deque_lf/0/0         826564008 ns        0.000 ns           10
BM_deque_lf/100/1       833140926 ns        0.000 ns           10
BM_deque_lf/100/2       839133135 ns      1560010 ns           10
BM_deque_lf/100/3       842320115 ns      1560010 ns           10
BM_deque_lf/100/4       833973718 ns        0.000 ns           10
BM_deque_lf/1024/1      858783046 ns      3120020 ns           10
BM_deque_lf/1024/2      863405832 ns      1560010 ns           10
BM_deque_lf/1024/3      867355584 ns      3120020 ns           10
BM_deque_lf/1024/4      870625586 ns      1560010 ns           10
BM_deque_lf/8192/1     1039691366 ns      3120020 ns           10
BM_deque_lf/8192/2     1044991208 ns      3120020 ns           10
BM_deque_lf/8192/3     1041719837 ns      4680030 ns           10
BM_deque_lf/8192/4     1040880586 ns      3120020 ns           10
BM_deque_lf/16384/1    1992911773 ns      3120020 ns           10
BM_deque_lf/16384/2    1982324751 ns      3120020 ns           10
BM_deque_lf/16384/3    2002857541 ns      1560010 ns           10
BM_deque_lf/16384/4    1981943686 ns      1560010 ns           10
BM_deque_lf_s/0/0       659658226 ns      1560010 ns           10
BM_deque_lf_s/100/1     741658501 ns      3120020 ns           10
BM_deque_lf_s/100/2     746073452 ns        0.000 ns           10
BM_deque_lf_s/100/3     745006264 ns        0.000 ns           10
BM_deque_lf_s/100/4     721572775 ns        0.000 ns           10
BM_deque_lf_s/1024/1    684771671 ns      4680030 ns           10
BM_deque_lf_s/1024/2    684347276 ns      4680030 ns           10
BM_deque_lf_s/1024/3    674827400 ns      3120020 ns           10
BM_deque_lf_s/1024/4    676270478 ns        0.000 ns           10
BM_deque_lf_s/8192/1   1084481199 ns        0.000 ns           10
BM_deque_lf_s/8192/2   1089495744 ns      1560010 ns           10
BM_deque_lf_s/8192/3   1111319040 ns        0.000 ns           10
BM_deque_lf_s/8192/4   1115345485 ns      1560010 ns           10
BM_deque_lf_s/16384/1  2149774351 ns        0.000 ns           10
BM_deque_lf_s/16384/2  2261661546 ns        0.000 ns           10
BM_deque_lf_s/16384/3  2139329207 ns      1560010 ns           10
BM_deque_lf_s/16384/4  2415034995 ns        0.000 ns           10
BM_deque2_lf/0/0        790939378 ns      1560010 ns           10
BM_deque2_lf/100/1      828896809 ns      3120020 ns           10
BM_deque2_lf/100/2      833574431 ns        0.000 ns           10
BM_deque2_lf/100/3      834800222 ns      6240040 ns           10
BM_deque2_lf/100/4      822438288 ns      3120020 ns           10
BM_deque2_lf/1024/1     811589281 ns      1560010 ns           10
BM_deque2_lf/1024/2     815485652 ns        0.000 ns           10
BM_deque2_lf/1024/3     824801544 ns        0.000 ns           10
BM_deque2_lf/1024/4     824221968 ns      4680030 ns           10
BM_deque2_lf/8192/1    1026475340 ns      3120020 ns           10
BM_deque2_lf/8192/2    1021140938 ns        0.000 ns           10
BM_deque2_lf/8192/3    1015084868 ns        0.000 ns           10
BM_deque2_lf/8192/4    1023279250 ns      3120020 ns           10
BM_deque2_lf/16384/1   2013581694 ns      4680030 ns           10
BM_deque2_lf/16384/2   1979590952 ns      1560010 ns           10
BM_deque2_lf/16384/3   1988346645 ns      1560010 ns           10
BM_deque2_lf/16384/4   1984125455 ns      1560010 ns           10
BM_deque2_lf_s/0/0      577137702 ns      3120020 ns           10
BM_deque2_lf_s/100/1    652403655 ns        0.000 ns           10
BM_deque2_lf_s/100/2    661832681 ns      1560010 ns           10
BM_deque2_lf_s/100/3    664974492 ns        0.000 ns           10
BM_deque2_lf_s/100/4    644414798 ns        0.000 ns           10
BM_deque2_lf_s/1024/1   573767954 ns      4680030 ns           10
BM_deque2_lf_s/1024/2   539375573 ns        0.000 ns           10
BM_deque2_lf_s/1024/3   549087586 ns        0.000 ns           10
BM_deque2_lf_s/1024/4   529185357 ns        0.000 ns           10
BM_deque2_lf_s/8192/1  1031432740 ns      4680030 ns           10
BM_deque2_lf_s/8192/2  1051363328 ns      1560010 ns           10
BM_deque2_lf_s/8192/3  1033765284 ns      1560010 ns           10
BM_deque2_lf_s/8192/4  1092159266 ns        0.000 ns           10
BM_deque2_lf_s/16384/1 2151226497 ns        0.000 ns           10
BM_deque2_lf_s/16384/2 2253090890 ns      3120020 ns           10
BM_deque2_lf_s/16384/3 2147949822 ns      1560010 ns           10
BM_deque2_lf_s/16384/4 2535384075 ns        0.000 ns           10
BM_ypipe2/0/0           868542024 ns      1560010 ns           10
BM_ypipe2/100/1         829318552 ns        0.000 ns           10
BM_ypipe2/100/2         738661776 ns        0.000 ns           10
BM_ypipe2/100/3         778116179 ns      1560010 ns           10
BM_ypipe2/100/4         803115335 ns        0.000 ns           10
BM_ypipe2/1024/1        157621252 ns      2808018 ns          100
BM_ypipe2/1024/2        154509733 ns      1404009 ns          100
BM_ypipe2/1024/3        153872807 ns      2028013 ns          100
BM_ypipe2/1024/4        154433263 ns      1716011 ns          100
BM_ypipe2/8192/1       1004873993 ns      3120020 ns           10
BM_ypipe2/8192/2       1018142031 ns        0.000 ns           10
BM_ypipe2/8192/3        991008286 ns        0.000 ns           10
BM_ypipe2/8192/4       1036473120 ns      3120020 ns           10
BM_ypipe2/16384/1      2004964714 ns      3120020 ns           10
BM_ypipe2/16384/2      1971943895 ns      1560010 ns           10
BM_ypipe2/16384/3      1953872354 ns        0.000 ns           10
BM_ypipe2/16384/4      1992495463 ns        0.000 ns           10
BM_ypipe/0/0            335404606 ns        0.000 ns           10
BM_ypipe/100/1          312768749 ns      3120020 ns           10
BM_ypipe/100/2          199692932 ns      2340015 ns          100
BM_ypipe/100/3          192226095 ns      1872012 ns          100
BM_ypipe/100/4          248218523 ns      1716011 ns          100
BM_ypipe/1024/1         161337750 ns      1404009 ns          100
BM_ypipe/1024/2         162077219 ns      1716011 ns          100
BM_ypipe/1024/3         162731848 ns      1560010 ns          100
BM_ypipe/1024/4         163027556 ns      1872012 ns          100
BM_ypipe/8192/1        1030446564 ns      3120020 ns           10
BM_ypipe/8192/2        1012788210 ns      1560010 ns           10
BM_ypipe/8192/3        1017527083 ns        0.000 ns           10
BM_ypipe/8192/4        1015774798 ns        0.000 ns           10
BM_ypipe/16384/1       1963336027 ns      1560010 ns           10
BM_ypipe/16384/2       2006697965 ns        0.000 ns           10
BM_ypipe/16384/3       1979991223 ns      1560010 ns           10
BM_ypipe/16384/4       1993324833 ns      1560010 ns           10
BM_ypipe_s/0/0          318645257 ns        0.000 ns           10
BM_ypipe_s/100/1        297810446 ns      4680030 ns           10
BM_ypipe_s/100/2        197168101 ns      1716011 ns          100
BM_ypipe_s/100/3        196303657 ns      1872012 ns          100
BM_ypipe_s/100/4        239303158 ns      1404009 ns          100
BM_ypipe_s/1024/1       158736654 ns      1092007 ns          100
BM_ypipe_s/1024/2       159498926 ns      1872012 ns          100
BM_ypipe_s/1024/3       158722723 ns      2340015 ns          100
BM_ypipe_s/1024/4       159823694 ns      1560010 ns          100
BM_ypipe_s/8192/1      1010123020 ns      3120020 ns           10
BM_ypipe_s/8192/2      1015791180 ns      1560010 ns           10
BM_ypipe_s/8192/3      1009715178 ns      3120020 ns           10
BM_ypipe_s/8192/4      1022809259 ns        0.000 ns           10
BM_ypipe_s/16384/1     1993888197 ns        0.000 ns           10
BM_ypipe_s/16384/2     1978972539 ns      1560010 ns           10
BM_ypipe_s/16384/3     1993689388 ns        0.000 ns           10
BM_ypipe_s/16384/4     1985806737 ns      1560010 ns           10
BM_ypipe_lf/0/0         748834455 ns        0.000 ns           10
BM_ypipe_lf/100/1       751406700 ns      1560010 ns           10
BM_ypipe_lf/100/2       750636741 ns      1560010 ns           10
BM_ypipe_lf/100/3       770778072 ns        0.000 ns           10
BM_ypipe_lf/100/4       785301971 ns      1560010 ns           10
BM_ypipe_lf/1024/1      772834260 ns        0.000 ns           10
BM_ypipe_lf/1024/2      793037825 ns      1560010 ns           10
BM_ypipe_lf/1024/3      787478736 ns        0.000 ns           10
BM_ypipe_lf/1024/4      779008255 ns      3120020 ns           10
BM_ypipe_lf/8192/1     1017135795 ns        0.000 ns           10
BM_ypipe_lf/8192/2     1006887664 ns      3120020 ns           10
BM_ypipe_lf/8192/3     1010988618 ns        0.000 ns           10
BM_ypipe_lf/8192/4     1016484874 ns        0.000 ns           10
BM_ypipe_lf/16384/1    1969746899 ns      6240040 ns           10
BM_ypipe_lf/16384/2    2001251498 ns        0.000 ns           10
BM_ypipe_lf/16384/3    1978158995 ns      4680030 ns           10
BM_ypipe_lf/16384/4    1970633842 ns        0.000 ns           10
BM_ypipe_lf_s/0/0       549365098 ns        0.000 ns           10
BM_ypipe_lf_s/100/1     560145240 ns      1560010 ns           10
BM_ypipe_lf_s/100/2     560532764 ns        0.000 ns           10
BM_ypipe_lf_s/100/3     556618386 ns        0.000 ns           10
BM_ypipe_lf_s/100/4     561759753 ns      3120020 ns           10
BM_ypipe_lf_s/1024/1    438939758 ns      4680030 ns           10
BM_ypipe_lf_s/1024/2    453261554 ns      1560010 ns           10
BM_ypipe_lf_s/1024/3    449336226 ns      1560010 ns           10
BM_ypipe_lf_s/1024/4    479761189 ns      1560010 ns           10
BM_ypipe_lf_s/8192/1   1078076529 ns        0.000 ns           10
BM_ypipe_lf_s/8192/2   1031973948 ns      3120020 ns           10
BM_ypipe_lf_s/8192/3   1053252102 ns        0.000 ns           10
BM_ypipe_lf_s/8192/4   1122326565 ns        0.000 ns           10
BM_ypipe_lf_s/16384/1  2465283998 ns      3120020 ns           10
BM_ypipe_lf_s/16384/2  3161683959 ns     15600100 ns            1
BM_ypipe_lf_s/16384/3  2276192545 ns        0.000 ns           10
BM_ypipe_lf_s/16384/4  2793873526 ns        0.000 ns            1
```
# 4 threads fit amount of cpu cores
```
2020-12-21T21:58:28-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                11226430 ns     11212572 ns           64
BM_cvnotify0              6933930 ns      6933378 ns           90
BM_yield                 42564546 ns       780005 ns          100
BM_yield2               111435118 ns       780005 ns          100
BM_deque0/0/0           145788913 ns       624004 ns          100
BM_deque0/100/1         207077260 ns       624004 ns          100
BM_deque0/100/2         215861247 ns       468003 ns          100
BM_deque0/100/3         223940945 ns       936006 ns          100
BM_deque0/100/4         189585495 ns      1248008 ns          100
BM_deque0/1024/1        287495161 ns        0.000 ns           10
BM_deque0/1024/2        259409372 ns        0.000 ns           10
BM_deque0/1024/3        259273867 ns      3120020 ns           10
BM_deque0/1024/4        261891494 ns      1560010 ns           10
BM_deque0/8192/1       1003169015 ns      1560010 ns           10
BM_deque0/8192/2        999352544 ns        0.000 ns           10
BM_deque0/8192/3        993747431 ns        0.000 ns           10
BM_deque0/8192/4        999189621 ns        0.000 ns           10
BM_deque0/16384/1      1950625749 ns      1560010 ns           10
BM_deque0/16384/2      1946490661 ns      1560010 ns           10
BM_deque0/16384/3      1944153369 ns        0.000 ns           10
BM_deque0/16384/4      1942862605 ns        0.000 ns           10
BM_deque/0/0            378183975 ns      3120020 ns           10
BM_deque/100/1          329218634 ns        0.000 ns           10
BM_deque/100/2          317599284 ns        0.000 ns           10
BM_deque/100/3          306197435 ns        0.000 ns           10
BM_deque/100/4          328396108 ns        0.000 ns           10
BM_deque/1024/1         299439715 ns        0.000 ns           10
BM_deque/1024/2         294241674 ns        0.000 ns           10
BM_deque/1024/3         294507551 ns        0.000 ns           10
BM_deque/1024/4         287675578 ns      1560010 ns           10
BM_deque/8192/1         999449168 ns      3120020 ns           10
BM_deque/8192/2         999932504 ns      1560010 ns           10
BM_deque/8192/3         998808171 ns        0.000 ns           10
BM_deque/8192/4        1000531926 ns        0.000 ns           10
BM_deque/16384/1       1952890498 ns        0.000 ns           10
BM_deque/16384/2       1964991045 ns        0.000 ns           10
BM_deque/16384/3       1960525279 ns      3120020 ns           10
BM_deque/16384/4       1948937410 ns      1560010 ns           10
BM_deque_lf/0/0         672562950 ns      1560010 ns           10
BM_deque_lf/100/1       711538638 ns      1560010 ns           10
BM_deque_lf/100/2       695280932 ns        0.000 ns           10
BM_deque_lf/100/3       690427170 ns      1560010 ns           10
BM_deque_lf/100/4       728940181 ns        0.000 ns           10
BM_deque_lf/1024/1      773370891 ns        0.000 ns           10
BM_deque_lf/1024/2      757098214 ns      3120020 ns           10
BM_deque_lf/1024/3      772473426 ns      1560010 ns           10
BM_deque_lf/1024/4      783951326 ns      1560010 ns           10
BM_deque_lf/8192/1     1012699028 ns      1560010 ns           10
BM_deque_lf/8192/2     1014383048 ns        0.000 ns           10
BM_deque_lf/8192/3     1015666582 ns        0.000 ns           10
BM_deque_lf/8192/4     1012609676 ns        0.000 ns           10
BM_deque_lf/16384/1    1968327688 ns        0.000 ns           10
BM_deque_lf/16384/2    1957923478 ns        0.000 ns           10
BM_deque_lf/16384/3    1957916848 ns        0.000 ns           10
BM_deque_lf/16384/4    1954798348 ns      1560010 ns           10
BM_deque_lf_s/0/0       657524362 ns      1560010 ns           10
BM_deque_lf_s/100/1     737648738 ns      3120020 ns           10
BM_deque_lf_s/100/2     718056742 ns        0.000 ns           10
BM_deque_lf_s/100/3     722748094 ns        0.000 ns           10
BM_deque_lf_s/100/4     704430821 ns      1560010 ns           10
BM_deque_lf_s/1024/1    601042851 ns        0.000 ns           10
BM_deque_lf_s/1024/2    602894711 ns        0.000 ns           10
BM_deque_lf_s/1024/3    599563501 ns      1560010 ns           10
BM_deque_lf_s/1024/4    587690035 ns      1560010 ns           10
BM_deque_lf_s/8192/1   1022805965 ns      3120020 ns           10
BM_deque_lf_s/8192/2   1024275649 ns        0.000 ns           10
BM_deque_lf_s/8192/3   1023397688 ns      1560010 ns           10
BM_deque_lf_s/8192/4   1024795855 ns      3120020 ns           10
BM_deque_lf_s/16384/1  1968998242 ns      1560010 ns           10
BM_deque_lf_s/16384/2  1965888125 ns        0.000 ns           10
BM_deque_lf_s/16384/3  1979703403 ns        0.000 ns           10
BM_deque_lf_s/16384/4  1974426146 ns        0.000 ns           10
BM_deque2_lf/0/0        582338652 ns        0.000 ns           10
BM_deque2_lf/100/1      663881512 ns        0.000 ns           10
BM_deque2_lf/100/2      666102675 ns        0.000 ns           10
BM_deque2_lf/100/3      664514725 ns      1560010 ns           10
BM_deque2_lf/100/4      634033472 ns      1560010 ns           10
BM_deque2_lf/1024/1     675889798 ns      1560010 ns           10
BM_deque2_lf/1024/2     650880120 ns      3120020 ns           10
BM_deque2_lf/1024/3     683670991 ns      1560010 ns           10
BM_deque2_lf/1024/4     644959385 ns      3120020 ns           10
BM_deque2_lf/8192/1    1003231207 ns      1560010 ns           10
BM_deque2_lf/8192/2    1000687620 ns        0.000 ns           10
BM_deque2_lf/8192/3     999288213 ns        0.000 ns           10
BM_deque2_lf/8192/4     995953923 ns      1560010 ns           10
BM_deque2_lf/16384/1   1970582728 ns        0.000 ns           10
BM_deque2_lf/16384/2   1951640241 ns        0.000 ns           10
BM_deque2_lf/16384/3   1961773141 ns        0.000 ns           10
BM_deque2_lf/16384/4   1955868788 ns      1560010 ns           10
BM_deque2_lf_s/0/0      582308412 ns        0.000 ns           10
BM_deque2_lf_s/100/1    672544943 ns        0.000 ns           10
BM_deque2_lf_s/100/2    655433101 ns      1560010 ns           10
BM_deque2_lf_s/100/3    643472635 ns        0.000 ns           10
BM_deque2_lf_s/100/4    681336736 ns      1560010 ns           10
BM_deque2_lf_s/1024/1   466428093 ns      1560010 ns           10
BM_deque2_lf_s/1024/2   468425510 ns        0.000 ns           10
BM_deque2_lf_s/1024/3   465670710 ns      4680030 ns           10
BM_deque2_lf_s/1024/4   457754268 ns        0.000 ns           10
BM_deque2_lf_s/8192/1  1016951314 ns      1560010 ns           10
BM_deque2_lf_s/8192/2  1000238289 ns      1560010 ns           10
BM_deque2_lf_s/8192/3  1001477297 ns        0.000 ns           10
BM_deque2_lf_s/8192/4  1005365584 ns        0.000 ns           10
BM_deque2_lf_s/16384/1 1984528677 ns        0.000 ns           10
BM_deque2_lf_s/16384/2 1965801125 ns      1560010 ns           10
BM_deque2_lf_s/16384/3 1954387128 ns        0.000 ns           10
BM_deque2_lf_s/16384/4 1950935511 ns        0.000 ns           10
BM_ypipe2/0/0           864348893 ns      1560010 ns           10
BM_ypipe2/100/1         718278863 ns        0.000 ns           10
BM_ypipe2/100/2         356666805 ns      1560010 ns           10
BM_ypipe2/100/3         445173464 ns        0.000 ns           10
BM_ypipe2/100/4         542848790 ns        0.000 ns           10
BM_ypipe2/1024/1        157322906 ns       624004 ns          100
BM_ypipe2/1024/2        157818487 ns       624004 ns          100
BM_ypipe2/1024/3        157147686 ns       780005 ns          100
BM_ypipe2/1024/4        158756920 ns       780005 ns          100
BM_ypipe2/8192/1       1006764306 ns        0.000 ns           10
BM_ypipe2/8192/2        993735326 ns        0.000 ns           10
BM_ypipe2/8192/3        991956565 ns      3120020 ns           10
BM_ypipe2/8192/4        988777156 ns      1560010 ns           10
BM_ypipe2/16384/1      1968068954 ns        0.000 ns           10
BM_ypipe2/16384/2      1947284059 ns        0.000 ns           10
BM_ypipe2/16384/3      1959241103 ns      3120020 ns           10
BM_ypipe2/16384/4      1975484651 ns        0.000 ns           10
BM_ypipe/0/0            350399436 ns        0.000 ns           10
BM_ypipe/100/1          321887542 ns        0.000 ns           10
BM_ypipe/100/2          203649262 ns       780005 ns          100
BM_ypipe/100/3          201430772 ns       936006 ns          100
BM_ypipe/100/4          256642510 ns      1560010 ns           10
BM_ypipe/1024/1         164138244 ns      1248008 ns          100
BM_ypipe/1024/2         164642646 ns      1248008 ns          100
BM_ypipe/1024/3         164176693 ns       780005 ns          100
BM_ypipe/1024/4         165684624 ns      1248008 ns          100
BM_ypipe/8192/1         997354998 ns        0.000 ns           10
BM_ypipe/8192/2        1012799973 ns        0.000 ns           10
BM_ypipe/8192/3         993286337 ns      1560010 ns           10
BM_ypipe/8192/4         998309736 ns      3120020 ns           10
BM_ypipe/16384/1       1947669060 ns        0.000 ns           10
BM_ypipe/16384/2       1955700133 ns      1560010 ns           10
BM_ypipe/16384/3       1952558108 ns      1560010 ns           10
BM_ypipe/16384/4       1952010527 ns        0.000 ns           10
BM_ypipe_s/0/0          338426524 ns      1560010 ns           10
BM_ypipe_s/100/1        300352536 ns        0.000 ns           10
BM_ypipe_s/100/2        205813401 ns       936006 ns          100
BM_ypipe_s/100/3        204937186 ns      1248008 ns          100
BM_ypipe_s/100/4        250612789 ns        0.000 ns           10
BM_ypipe_s/1024/1       160852065 ns      1092007 ns          100
BM_ypipe_s/1024/2       161292654 ns       780005 ns          100
BM_ypipe_s/1024/3       160120881 ns      1092007 ns          100
BM_ypipe_s/1024/4       161417615 ns      1092007 ns          100
BM_ypipe_s/8192/1      1004886055 ns      3120020 ns           10
BM_ypipe_s/8192/2      1009380693 ns      1560010 ns           10
BM_ypipe_s/8192/3       995436583 ns        0.000 ns           10
BM_ypipe_s/8192/4      1016673418 ns      3120020 ns           10
BM_ypipe_s/16384/1     1963508231 ns        0.000 ns           10
BM_ypipe_s/16384/2     1958897079 ns        0.000 ns           10
BM_ypipe_s/16384/3     1949941251 ns      1560010 ns           10
BM_ypipe_s/16384/4     1957677233 ns        0.000 ns           10
BM_ypipe_lf/0/0         497685206 ns        0.000 ns           10
BM_ypipe_lf/100/1       387637553 ns        0.000 ns           10
BM_ypipe_lf/100/2       382377704 ns        0.000 ns           10
BM_ypipe_lf/100/3       427131607 ns      1560010 ns           10
BM_ypipe_lf/100/4       421869962 ns        0.000 ns           10
BM_ypipe_lf/1024/1      557385992 ns        0.000 ns           10
BM_ypipe_lf/1024/2      550182534 ns        0.000 ns           10
BM_ypipe_lf/1024/3      554727773 ns      1560010 ns           10
BM_ypipe_lf/1024/4      528381394 ns        0.000 ns           10
BM_ypipe_lf/8192/1     1001865719 ns      1560010 ns           10
BM_ypipe_lf/8192/2      996718492 ns        0.000 ns           10
BM_ypipe_lf/8192/3      994012795 ns      1560010 ns           10
BM_ypipe_lf/8192/4      996292857 ns        0.000 ns           10
BM_ypipe_lf/16384/1    1952914237 ns      1560010 ns           10
BM_ypipe_lf/16384/2    1951932167 ns      1560010 ns           10
BM_ypipe_lf/16384/3    1947533897 ns        0.000 ns           10
BM_ypipe_lf/16384/4    1952280212 ns        0.000 ns           10
BM_ypipe_lf_s/0/0       517402485 ns      3120020 ns           10
BM_ypipe_lf_s/100/1     554806048 ns        0.000 ns           10
BM_ypipe_lf_s/100/2     541158441 ns        0.000 ns           10
BM_ypipe_lf_s/100/3     546755982 ns        0.000 ns           10
BM_ypipe_lf_s/100/4     561047752 ns      3120020 ns           10
BM_ypipe_lf_s/1024/1    380505184 ns        0.000 ns           10
BM_ypipe_lf_s/1024/2    381619936 ns      1560010 ns           10
BM_ypipe_lf_s/1024/3    386603599 ns        0.000 ns           10
BM_ypipe_lf_s/1024/4    388707479 ns      3120020 ns           10
BM_ypipe_lf_s/8192/1   1005588688 ns        0.000 ns           10
BM_ypipe_lf_s/8192/2   1008421164 ns      1560010 ns           10
BM_ypipe_lf_s/8192/3   1007456246 ns        0.000 ns           10
BM_ypipe_lf_s/8192/4   1008070425 ns      1560010 ns           10
BM_ypipe_lf_s/16384/1  1976582636 ns      3120020 ns           10
BM_ypipe_lf_s/16384/2  1972617186 ns        0.000 ns           10
BM_ypipe_lf_s/16384/3  1955612406 ns        0.000 ns           10
BM_ypipe_lf_s/16384/4  1956840421 ns        0.000 ns           10
```
# block quad times (4 threads version)
```
2020-12-21T23:03:28-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0      1827383070 ns        0.000 ns           10
BM_deque/0/0       1806371050 ns        0.000 ns           10
BM_deque_lf/0/0    1813095663 ns      1560010 ns           10
BM_deque_lf_s/0/0  1863728769 ns        0.000 ns           10
BM_deque2_lf/0/0   1813235403 ns      3120020 ns           10
BM_deque2_lf_s/0/0 1811919190 ns      1560010 ns           10
BM_ypipe2/0/0      1816969578 ns        0.000 ns           10
BM_ypipe/0/0       1820658457 ns      1560010 ns           10
BM_ypipe_s/0/0     1828531613 ns        0.000 ns           10
BM_ypipe_lf/0/0    1806074248 ns        0.000 ns           10
BM_ypipe_lf_s/0/0  1823153582 ns        0.000 ns           10
```
# block quad times.
```
2020-12-21T23:09:01-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0      1862343477 ns      1560010 ns           10
BM_deque/0/0       1848038662 ns      1560010 ns           10
BM_deque_lf/0/0    1810511912 ns      3120020 ns           10
BM_deque_lf_s/0/0  1904029395 ns      6240040 ns           10
BM_deque2_lf/0/0   1820376198 ns      1560010 ns           10
BM_deque2_lf_s/0/0 1855551668 ns      4680030 ns           10
BM_ypipe2/0/0      1826288250 ns        0.000 ns           10
BM_ypipe/0/0       1854204487 ns      3120020 ns           10
BM_ypipe_s/0/0     1824756675 ns      1560010 ns           10
BM_ypipe_lf/0/0    1796128480 ns      4680030 ns           10
BM_ypipe_lf_s/0/0  1843398381 ns      1560010 ns           10
```
# block quad times and test affine.
```
2020-12-21T23:14:55-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
BM_deque_lf/1024/4    1877473642 ns      1560010 ns           10
BM_deque2_lf/1024/4   1861744911 ns      6240040 ns           10
BM_ypipe_lf/1024/4    1859985953 ns      1560010 ns           10
BM_deque_lf_s/1024/4  1946218881 ns      1560010 ns           10
BM_deque2_lf_s/1024/4 1892955787 ns      4680030 ns           10
BM_ypipe_lf_s/1024/4  1878758588 ns        0.000 ns           10
BM_deque/1024/1       1903486092 ns      1560010 ns           10
BM_ypipe/1024/1       1896910543 ns        0.000 ns           10
```
