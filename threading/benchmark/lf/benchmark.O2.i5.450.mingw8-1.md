### test number of threads (empty workload)
**4xW,4xR**
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0        39479755 ns       156001 ns          100
BM_deque/0/0        106396044 ns       468003 ns          100
BM_deque_lf/0/0     187522258 ns       468003 ns          100
BM_deque_lf_s/0/0   116256472 ns       780005 ns          100
BM_deque2_lf/0/0    105841872 ns      1248008 ns          100
BM_deque2_lf_s/0/0   68081554 ns       780005 ns          100
BM_ypipe/0/0        150148832 ns       936006 ns          100
BM_ypipe_s/0/0      150068222 ns      1092007 ns          100
BM_ypipe_lf/0/0     107663823 ns       468003 ns          100
BM_ypipe_lf_s/0/0    59149139 ns      1092007 ns          100
```
**6xW,6xR**
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0        41441911 ns       936006 ns          100
BM_deque/0/0        110067641 ns      1560010 ns          100
BM_deque_lf/0/0     285479476 ns      1560010 ns           10
BM_deque_lf_s/0/0   120437501 ns      1092007 ns          100
BM_deque2_lf/0/0    160701421 ns       780005 ns          100
BM_deque2_lf_s/0/0   55270728 ns      1404009 ns          100
BM_ypipe/0/0        147726720 ns      1560010 ns          100
BM_ypipe_s/0/0      146804057 ns      1248008 ns          100
BM_ypipe_lf/0/0     168861262 ns       936006 ns          100
BM_ypipe_lf_s/0/0    74053853 ns       624004 ns          100
```
### test number of threads (block quad times per msg)
**4xW,4xR**
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       117318707 ns       312002 ns          100
BM_deque/0/0        118011005 ns       780005 ns          100
BM_deque_lf/0/0     414273170 ns      3120020 ns           10
BM_deque_lf_s/0/0   291389253 ns        0.000 ns           10
BM_deque2_lf/0/0    264134821 ns        0.000 ns           10
BM_deque2_lf_s/0/0  148938001 ns       780005 ns          100
BM_ypipe/0/0         87379016 ns       936006 ns          100
BM_ypipe_s/0/0       89787330 ns       468003 ns          100
BM_ypipe_lf/0/0     311045412 ns        0.000 ns           10
BM_ypipe_lf_s/0/0   175865632 ns       780005 ns          100
```
**10xW,10xR**
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_deque0/0/0       120572586 ns      2964019 ns          100
BM_deque/0/0        123363642 ns      2184014 ns          100
BM_deque_lf/0/0     608205560 ns        0.000 ns           10
BM_deque_lf_s/0/0  1365699062 ns      1560010 ns           10
BM_deque2_lf/0/0    434231432 ns      3120020 ns           10
BM_deque2_lf_s/0/0 1005023869 ns        0.000 ns           10
BM_ypipe/0/0         87838879 ns      1404009 ns          100
BM_ypipe_s/0/0       90575507 ns      2496016 ns          100
BM_ypipe_lf/0/0     455624591 ns      1560010 ns           10
BM_ypipe_lf_s/0/0  1391371032 ns        0.000 ns           10
```
### affine
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 3548637 ns      3520023 ns          195
BM_cvnotify0              1020823 ns      1021932 ns          748
BM_yield                 33319334 ns      2184014 ns          100
BM_yield2                73797558 ns      2184014 ns          100
BM_deque0/0/0            40046169 ns       780005 ns          100
BM_deque0/100/1         100945461 ns      1092007 ns          100
BM_deque0/100/2          51391516 ns       468003 ns          100
BM_deque0/100/3          53754645 ns       936006 ns          100
BM_deque0/100/4          40907226 ns      1248008 ns          100
BM_deque0/1024/1        179971308 ns       936006 ns          100
BM_deque0/1024/2         60772612 ns       624004 ns          100
BM_deque0/1024/3         58578812 ns      1248008 ns          100
BM_deque0/1024/4         40517101 ns      1248008 ns          100
BM_deque0/8192/1        274896496 ns      1092007 ns          100
BM_deque0/8192/2         85606126 ns      1092007 ns          100
BM_deque0/8192/3         69872653 ns      1248008 ns          100
BM_deque0/8192/4         40760850 ns       624004 ns          100
BM_deque0/16384/1       366468158 ns        0.000 ns           10
BM_deque0/16384/2       123031965 ns      1248008 ns          100
BM_deque0/16384/3        99762534 ns       468003 ns          100
BM_deque0/16384/4        39988340 ns      1092007 ns          100
BM_deque/0/0            108096396 ns      1404009 ns          100
BM_deque/100/1          160747894 ns      1404009 ns          100
BM_deque/100/2           94780621 ns      1092007 ns          100
BM_deque/100/3           96819066 ns      1092007 ns          100
BM_deque/100/4          110423668 ns       468003 ns          100
BM_deque/1024/1         220499414 ns       936006 ns          100
BM_deque/1024/2          96324442 ns       936006 ns          100
BM_deque/1024/3          98551767 ns       936006 ns          100
BM_deque/1024/4         105683262 ns       780005 ns          100
BM_deque/8192/1         366516150 ns      1560010 ns           10
BM_deque/8192/2         110322913 ns      1092007 ns          100
BM_deque/8192/3          96687574 ns       780005 ns          100
BM_deque/8192/4         105745471 ns       780005 ns          100
BM_deque/16384/1        377885779 ns        0.000 ns           10
BM_deque/16384/2        135356697 ns       936006 ns          100
BM_deque/16384/3        104984133 ns       975006 ns          112
BM_deque/16384/4        109033341 ns       936006 ns          100
BM_deque_lf/0/0         193786583 ns      1092007 ns          100
BM_deque_lf/100/1       236029866 ns       312002 ns          100
BM_deque_lf/100/2       280817164 ns      3120020 ns           10
BM_deque_lf/100/3       291088347 ns      1560010 ns           10
BM_deque_lf/100/4       187373922 ns      1248008 ns          100
BM_deque_lf/1024/1      240369287 ns       936006 ns          100
BM_deque_lf/1024/2      341384484 ns        0.000 ns           10
BM_deque_lf/1024/3      335914025 ns        0.000 ns           10
BM_deque_lf/1024/4      193277955 ns      1248008 ns          100
BM_deque_lf/8192/1      223026969 ns      1092007 ns          100
BM_deque_lf/8192/2      409777971 ns        0.000 ns           10
BM_deque_lf/8192/3      408971534 ns      1560010 ns           10
BM_deque_lf/8192/4      191289538 ns      1092007 ns          100
BM_deque_lf/16384/1     197176577 ns       156001 ns          100
BM_deque_lf/16384/2     457452483 ns      1560010 ns           10
BM_deque_lf/16384/3     454195554 ns      1560010 ns           10
BM_deque_lf/16384/4     193353672 ns      1404009 ns          100
BM_deque_lf_s/0/0       119149845 ns       624004 ns          100
BM_deque_lf_s/100/1     148810598 ns      1248008 ns          100
BM_deque_lf_s/100/2     184193788 ns       936006 ns          100
BM_deque_lf_s/100/3     200111098 ns       624004 ns          100
BM_deque_lf_s/100/4     116409979 ns      1248008 ns          100
BM_deque_lf_s/1024/1    161694912 ns       624004 ns          100
BM_deque_lf_s/1024/2    255526000 ns        0.000 ns           10
BM_deque_lf_s/1024/3    235580526 ns       624004 ns          100
BM_deque_lf_s/1024/4    119961770 ns       780005 ns          100
BM_deque_lf_s/8192/1    164237938 ns      1248008 ns          100
BM_deque_lf_s/8192/2    342525789 ns        0.000 ns           10
BM_deque_lf_s/8192/3    382273447 ns        0.000 ns           10
BM_deque_lf_s/8192/4    118813369 ns       936006 ns          100
BM_deque_lf_s/16384/1   166486842 ns      1092007 ns          100
BM_deque_lf_s/16384/2   340943498 ns      3120020 ns           10
BM_deque_lf_s/16384/3   335919372 ns      1560010 ns           10
BM_deque_lf_s/16384/4   115256035 ns       936006 ns          100
BM_deque2_lf/0/0         93151096 ns      1248008 ns          100
BM_deque2_lf/100/1      122104247 ns       624004 ns          100
BM_deque2_lf/100/2      159489854 ns       780005 ns          100
BM_deque2_lf/100/3      179528769 ns       780005 ns          100
BM_deque2_lf/100/4       82273678 ns       312002 ns          100
BM_deque2_lf/1024/1     105650943 ns       936006 ns          100
BM_deque2_lf/1024/2     234204002 ns       624004 ns          100
BM_deque2_lf/1024/3     235216060 ns      1404009 ns          100
BM_deque2_lf/1024/4      98591135 ns      1248008 ns          100
BM_deque2_lf/8192/1     150907137 ns      2028013 ns          100
BM_deque2_lf/8192/2     329460563 ns        0.000 ns           10
BM_deque2_lf/8192/3     328715078 ns      1560010 ns           10
BM_deque2_lf/8192/4      97155580 ns       780005 ns          100
BM_deque2_lf/16384/1    176588919 ns      1092007 ns          100
BM_deque2_lf/16384/2    387932748 ns        0.000 ns           10
BM_deque2_lf/16384/3    377229902 ns        0.000 ns           10
BM_deque2_lf/16384/4    100702525 ns      1560010 ns          100
BM_deque2_lf_s/0/0       56832629 ns       780005 ns          100
BM_deque2_lf_s/100/1     75561364 ns       312002 ns          100
BM_deque2_lf_s/100/2    116914753 ns       624004 ns          100
BM_deque2_lf_s/100/3    144859549 ns      1092007 ns          100
BM_deque2_lf_s/100/4     52540917 ns       936006 ns          100
BM_deque2_lf_s/1024/1   105015781 ns       624004 ns          100
BM_deque2_lf_s/1024/2   171663281 ns       936006 ns          100
BM_deque2_lf_s/1024/3   177174520 ns      1248008 ns          100
BM_deque2_lf_s/1024/4    53753759 ns        0.000 ns          100
BM_deque2_lf_s/8192/1   155844472 ns      1092007 ns          100
BM_deque2_lf_s/8192/2   265711295 ns        0.000 ns           10
BM_deque2_lf_s/8192/3   265049559 ns      1560010 ns           10
BM_deque2_lf_s/8192/4    53632580 ns       780005 ns          100
BM_deque2_lf_s/16384/1  181351866 ns       936006 ns          100
BM_deque2_lf_s/16384/2  265122743 ns        0.000 ns           10
BM_deque2_lf_s/16384/3  252919601 ns        0.000 ns           10
BM_deque2_lf_s/16384/4   56687668 ns      1248008 ns          100
BM_ypipe/0/0            158067054 ns       780005 ns          100
BM_ypipe/100/1          217354537 ns      1248008 ns          100
BM_ypipe/100/2          130137869 ns       624004 ns          100
BM_ypipe/100/3          102822546 ns      1092007 ns          100
BM_ypipe/100/4          156972308 ns       936006 ns          100
BM_ypipe/1024/1         250455166 ns      3120020 ns           10
BM_ypipe/1024/2          80633990 ns      1092007 ns          100
BM_ypipe/1024/3          72825377 ns       312002 ns          100
BM_ypipe/1024/4         154702886 ns       780005 ns          100
BM_ypipe/8192/1         338467770 ns        0.000 ns           10
BM_ypipe/8192/2          46623000 ns       312002 ns          100
BM_ypipe/8192/3          35838463 ns      1092007 ns          100
BM_ypipe/8192/4         151744973 ns       312002 ns          100
BM_ypipe/16384/1        376437238 ns      1560010 ns           10
BM_ypipe/16384/2         89762671 ns       780005 ns          100
BM_ypipe/16384/3         50645248 ns       780005 ns          100
BM_ypipe/16384/4        151121535 ns       468003 ns          100
BM_ypipe_s/0/0          144712424 ns       624004 ns          100
BM_ypipe_s/100/1        198720694 ns      1248008 ns          100
BM_ypipe_s/100/2        128093419 ns       780005 ns          100
BM_ypipe_s/100/3         87250561 ns      1248008 ns          100
BM_ypipe_s/100/4        151357811 ns       780005 ns          100
BM_ypipe_s/1024/1       239724364 ns       936006 ns          100
BM_ypipe_s/1024/2        72485835 ns       936006 ns          100
BM_ypipe_s/1024/3        64722005 ns       468003 ns          100
BM_ypipe_s/1024/4       150990620 ns       468003 ns          100
BM_ypipe_s/8192/1       339161928 ns      1560010 ns           10
BM_ypipe_s/8192/2        46846239 ns      1404009 ns          100
BM_ypipe_s/8192/3        34710713 ns       936006 ns          100
BM_ypipe_s/8192/4       152851665 ns      1092007 ns          100
BM_ypipe_s/16384/1      371647635 ns        0.000 ns           10
BM_ypipe_s/16384/2       90027007 ns      1560010 ns          100
BM_ypipe_s/16384/3       53677183 ns       780005 ns          100
BM_ypipe_s/16384/4      152590662 ns       468003 ns          100
BM_ypipe_lf/0/0         113250453 ns       936006 ns          100
BM_ypipe_lf/100/1       144996542 ns      1248008 ns          100
BM_ypipe_lf/100/2       184677928 ns       312002 ns          100
BM_ypipe_lf/100/3       215610163 ns       780005 ns          100
BM_ypipe_lf/100/4       114886958 ns       936006 ns          100
BM_ypipe_lf/1024/1      106002620 ns      1092007 ns          100
BM_ypipe_lf/1024/2      251925294 ns      1092007 ns          100
BM_ypipe_lf/1024/3      267344657 ns        0.000 ns           10
BM_ypipe_lf/1024/4      112787322 ns      1092007 ns          100
BM_ypipe_lf/8192/1      163873951 ns      1092007 ns          100
BM_ypipe_lf/8192/2      343725692 ns      1560010 ns           10
BM_ypipe_lf/8192/3      353861371 ns      1560010 ns           10
BM_ypipe_lf/8192/4      112666370 ns       936006 ns          100
BM_ypipe_lf/16384/1     187567452 ns      1404009 ns          100
BM_ypipe_lf/16384/2     388832215 ns      1560010 ns           10
BM_ypipe_lf/16384/3     398244394 ns        0.000 ns           10
BM_ypipe_lf/16384/4     114084923 ns       780005 ns          100
BM_ypipe_lf_s/0/0        68683221 ns       624004 ns          100
BM_ypipe_lf_s/100/1      94965934 ns      1248008 ns          100
BM_ypipe_lf_s/100/2     140387264 ns       936006 ns          100
BM_ypipe_lf_s/100/3     176632170 ns       624004 ns          100
BM_ypipe_lf_s/100/4      71794812 ns       624004 ns          100
BM_ypipe_lf_s/1024/1    113747125 ns       624004 ns          100
BM_ypipe_lf_s/1024/2    208888547 ns       780005 ns          100
BM_ypipe_lf_s/1024/3    220930251 ns       468003 ns          100
BM_ypipe_lf_s/1024/4     69505115 ns       468003 ns          100
BM_ypipe_lf_s/8192/1    170781051 ns      1404009 ns          100
BM_ypipe_lf_s/8192/2    299222777 ns        0.000 ns           10
BM_ypipe_lf_s/8192/3    287949686 ns      3120020 ns           10
BM_ypipe_lf_s/8192/4     70149816 ns      1248008 ns          100
BM_ypipe_lf_s/16384/1   195021799 ns      2028013 ns          100
BM_ypipe_lf_s/16384/2   273338825 ns      1560010 ns           10
BM_ypipe_lf_s/16384/3   269461735 ns        0.000 ns           10
BM_ypipe_lf_s/16384/4    69789404 ns      1248008 ns          100
```
### affine and block quad times per msg
```
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_yield0                 3539249 ns      3594141 ns          204
BM_cvnotify0              1037110 ns      1021932 ns          748
BM_yield                 32422621 ns      2028013 ns          100
BM_yield2                73901954 ns      2340015 ns          100
BM_deque0/0/0           115121665 ns       936006 ns          100
BM_deque0/100/1         122033744 ns       936006 ns          100
BM_deque0/100/2         119112008 ns       780005 ns          100
BM_deque0/100/3         119758976 ns      1092007 ns          100
BM_deque0/100/4         116202241 ns      1248008 ns          100
BM_deque0/1024/1        124387980 ns      1092007 ns          100
BM_deque0/1024/2        120476154 ns      1248008 ns          100
BM_deque0/1024/3        121930209 ns      1248008 ns          100
BM_deque0/1024/4        115990554 ns       624004 ns          100
BM_deque0/8192/1        127183109 ns      2184014 ns          100
BM_deque0/8192/2        134210379 ns      1092007 ns          100
BM_deque0/8192/3        131518705 ns       624004 ns          100
BM_deque0/8192/4        115731159 ns      1404009 ns          100
BM_deque0/16384/1       154194194 ns      1404009 ns          100
BM_deque0/16384/2       159574788 ns      1248008 ns          100
BM_deque0/16384/3       146947033 ns       936006 ns          100
BM_deque0/16384/4       116474236 ns      1092007 ns          100
BM_deque/0/0            115717309 ns      1404009 ns          100
BM_deque/100/1          122729391 ns      1560010 ns          100
BM_deque/100/2          119115666 ns       936006 ns          100
BM_deque/100/3          120645757 ns      1248008 ns          100
BM_deque/100/4          118443847 ns      1248008 ns          100
BM_deque/1024/1         132892359 ns      1092007 ns          100
BM_deque/1024/2         120327660 ns       624004 ns          100
BM_deque/1024/3         121152819 ns       624004 ns          100
BM_deque/1024/4         118188978 ns      1092007 ns          100
BM_deque/8192/1         150380498 ns      1248008 ns          100
BM_deque/8192/2         132113712 ns      1248008 ns          100
BM_deque/8192/3         128820803 ns       624004 ns          100
BM_deque/8192/4         116181727 ns      1092007 ns          100
BM_deque/16384/1        169561336 ns      1404009 ns          100
BM_deque/16384/2        152362816 ns       780005 ns          100
BM_deque/16384/3        141342156 ns       780005 ns          100
BM_deque/16384/4        117690367 ns      1248008 ns          100
BM_deque_lf/0/0         397636936 ns        0.000 ns           10
BM_deque_lf/100/1       392934632 ns      1560010 ns           10
BM_deque_lf/100/2       379436076 ns        0.000 ns           10
BM_deque_lf/100/3       378126846 ns      1560010 ns           10
BM_deque_lf/100/4       400531366 ns        0.000 ns           10
BM_deque_lf/1024/1      366139707 ns      1560010 ns           10
BM_deque_lf/1024/2      350363846 ns      1560010 ns           10
BM_deque_lf/1024/3      352367363 ns        0.000 ns           10
BM_deque_lf/1024/4      395173997 ns        0.000 ns           10
BM_deque_lf/8192/1      319987989 ns        0.000 ns           10
BM_deque_lf/8192/2      287283201 ns      1560010 ns           10
BM_deque_lf/8192/3      294029742 ns        0.000 ns           10
BM_deque_lf/8192/4      403529048 ns        0.000 ns           10
BM_deque_lf/16384/1     299303917 ns        0.000 ns           10
BM_deque_lf/16384/2     272288456 ns      3120020 ns           10
BM_deque_lf/16384/3     277734321 ns        0.000 ns           10
BM_deque_lf/16384/4     398244608 ns      1560010 ns           10
BM_deque_lf_s/0/0       280527978 ns      3120020 ns           10
BM_deque_lf_s/100/1     289295358 ns      1560010 ns           10
BM_deque_lf_s/100/2     290273014 ns      1560010 ns           10
BM_deque_lf_s/100/3     289611491 ns        0.000 ns           10
BM_deque_lf_s/100/4     276239286 ns        0.000 ns           10
BM_deque_lf_s/1024/1    300343037 ns        0.000 ns           10
BM_deque_lf_s/1024/2    292501986 ns        0.000 ns           10
BM_deque_lf_s/1024/3    292026011 ns        0.000 ns           10
BM_deque_lf_s/1024/4    280081088 ns        0.000 ns           10
BM_deque_lf_s/8192/1    315193082 ns      1560010 ns           10
BM_deque_lf_s/8192/2    272153465 ns        0.000 ns           10
BM_deque_lf_s/8192/3    281014988 ns        0.000 ns           10
BM_deque_lf_s/8192/4    287350183 ns      1560010 ns           10
BM_deque_lf_s/16384/1   316310263 ns      3120020 ns           10
BM_deque_lf_s/16384/2   263127310 ns        0.000 ns           10
BM_deque_lf_s/16384/3   263670224 ns      1560010 ns           10
BM_deque_lf_s/16384/4   254955925 ns      3120020 ns           10
BM_deque2_lf/0/0        256617859 ns      1560010 ns           10
BM_deque2_lf/100/1      207643467 ns       936006 ns          100
BM_deque2_lf/100/2      236878340 ns       780005 ns          100
BM_deque2_lf/100/3      234296344 ns       936006 ns          100
BM_deque2_lf/100/4      250224706 ns      1248008 ns          100
BM_deque2_lf/1024/1     139236259 ns       780005 ns          100
BM_deque2_lf/1024/2     222743211 ns      1872012 ns          100
BM_deque2_lf/1024/3     219019534 ns      1092007 ns          100
BM_deque2_lf/1024/4     255644566 ns        0.000 ns           10
BM_deque2_lf/8192/1     122667200 ns      1248008 ns          100
BM_deque2_lf/8192/2     187872528 ns      1404009 ns          100
BM_deque2_lf/8192/3     191528889 ns      1092007 ns          100
BM_deque2_lf/8192/4     251168559 ns      1092007 ns          100
BM_deque2_lf/16384/1    140209287 ns      2496016 ns          100
BM_deque2_lf/16384/2    195346140 ns      1092007 ns          100
BM_deque2_lf/16384/3    193311990 ns      1404009 ns          100
BM_deque2_lf/16384/4    261846481 ns      1560010 ns           10
BM_deque2_lf_s/0/0      138970320 ns      1404009 ns          100
BM_deque2_lf_s/100/1    142457635 ns       468003 ns          100
BM_deque2_lf_s/100/2    156405685 ns      1092007 ns          100
BM_deque2_lf_s/100/3    148577743 ns      1092007 ns          100
BM_deque2_lf_s/100/4    143084221 ns       624004 ns          100
BM_deque2_lf_s/1024/1   128734266 ns       936006 ns          100
BM_deque2_lf_s/1024/2   161948524 ns       468003 ns          100
BM_deque2_lf_s/1024/3   155905458 ns       780005 ns          100
BM_deque2_lf_s/1024/4   142832589 ns      1092007 ns          100
BM_deque2_lf_s/8192/1   123246466 ns       468003 ns          100
BM_deque2_lf_s/8192/2   166422520 ns      1248008 ns          100
BM_deque2_lf_s/8192/3   171528782 ns      1092007 ns          100
BM_deque2_lf_s/8192/4   141069480 ns       936006 ns          100
BM_deque2_lf_s/16384/1  139447304 ns      1716011 ns          100
BM_deque2_lf_s/16384/2  189331454 ns       780005 ns          100
BM_deque2_lf_s/16384/3  183704840 ns      1248008 ns          100
BM_deque2_lf_s/16384/4  140938690 ns       780005 ns          100
BM_ypipe/0/0             84298196 ns       624004 ns          100
BM_ypipe/100/1           94435984 ns       780005 ns          100
BM_ypipe/100/2           89322262 ns      1092007 ns          100
BM_ypipe/100/3           90407342 ns      1248008 ns          100
BM_ypipe/100/4           84197813 ns      1092007 ns          100
BM_ypipe/1024/1          99395040 ns       936006 ns          100
BM_ypipe/1024/2          92122947 ns      1404009 ns          100
BM_ypipe/1024/3          90701242 ns      1092007 ns          100
BM_ypipe/1024/4          85602931 ns       624004 ns          100
BM_ypipe/8192/1         110828182 ns      1404009 ns          100
BM_ypipe/8192/2         105559491 ns       780005 ns          100
BM_ypipe/8192/3         102084986 ns      1092007 ns          100
BM_ypipe/8192/4          85603606 ns      1404009 ns          100
BM_ypipe/16384/1        124542954 ns      1404009 ns          100
BM_ypipe/16384/2        130815774 ns      1092007 ns          100
BM_ypipe/16384/3        117679862 ns      1092007 ns          100
BM_ypipe/16384/4         84170768 ns      1092007 ns          100
BM_ypipe_s/0/0           85467461 ns       624004 ns          100
BM_ypipe_s/100/1         93674369 ns       780005 ns          100
BM_ypipe_s/100/2         90746084 ns      1092007 ns          100
BM_ypipe_s/100/3         90213598 ns       624004 ns          100
BM_ypipe_s/100/4         85346534 ns       936006 ns          100
BM_ypipe_s/1024/1       101336168 ns      1092007 ns          100
BM_ypipe_s/1024/2        91908027 ns       780005 ns          100
BM_ypipe_s/1024/3        90689997 ns       936006 ns          100
BM_ypipe_s/1024/4        87748526 ns       780005 ns          100
BM_ypipe_s/8192/1       110273245 ns      1248008 ns          100
BM_ypipe_s/8192/2       107592662 ns      1404009 ns          100
BM_ypipe_s/8192/3       102757116 ns       156001 ns          100
BM_ypipe_s/8192/4        86464959 ns       312002 ns          100
BM_ypipe_s/16384/1      127055359 ns      1560010 ns          100
BM_ypipe_s/16384/2      132924448 ns       468003 ns          100
BM_ypipe_s/16384/3      117707703 ns      1248008 ns          100
BM_ypipe_s/16384/4       86432884 ns       780005 ns          100
BM_ypipe_lf/0/0         303460142 ns        0.000 ns           10
BM_ypipe_lf/100/1       263169954 ns      1560010 ns           10
BM_ypipe_lf/100/2       288009354 ns      1560010 ns           10
BM_ypipe_lf/100/3       262742612 ns      1560010 ns           10
BM_ypipe_lf/100/4       297685953 ns      1560010 ns           10
BM_ypipe_lf/1024/1      141055827 ns       936006 ns          100
BM_ypipe_lf/1024/2      254758606 ns       936006 ns          100
BM_ypipe_lf/1024/3      251944683 ns      1560010 ns           10
BM_ypipe_lf/1024/4      288064530 ns      1560010 ns           10
BM_ypipe_lf/8192/1      129433317 ns       936006 ns          100
BM_ypipe_lf/8192/2      206432045 ns       468003 ns          100
BM_ypipe_lf/8192/3      205810464 ns      1092007 ns          100
BM_ypipe_lf/8192/4      293415739 ns        0.000 ns           10
BM_ypipe_lf/16384/1     139313057 ns      1716011 ns          100
BM_ypipe_lf/16384/2     206122123 ns      1248008 ns          100
BM_ypipe_lf/16384/3     207150571 ns       936006 ns          100
BM_ypipe_lf/16384/4     290465962 ns      3120020 ns           10
BM_ypipe_lf_s/0/0       173246094 ns       624004 ns          100
BM_ypipe_lf_s/100/1     170178165 ns       780005 ns          100
BM_ypipe_lf_s/100/2     192052586 ns       468003 ns          100
BM_ypipe_lf_s/100/3     190206605 ns       624004 ns          100
BM_ypipe_lf_s/100/4     181913822 ns      1092007 ns          100
BM_ypipe_lf_s/1024/1    132562586 ns      1560010 ns          100
BM_ypipe_lf_s/1024/2    181503940 ns       624004 ns          100
BM_ypipe_lf_s/1024/3    193260975 ns      1092007 ns          100
BM_ypipe_lf_s/1024/4    173278897 ns      1092007 ns          100
BM_ypipe_lf_s/8192/1    130606953 ns       624004 ns          100
BM_ypipe_lf_s/8192/2    176387117 ns      1092007 ns          100
BM_ypipe_lf_s/8192/3    181487212 ns      1404009 ns          100
BM_ypipe_lf_s/8192/4    180549552 ns       936006 ns          100
BM_ypipe_lf_s/16384/1   140024757 ns      2028013 ns          100
BM_ypipe_lf_s/16384/2   185719747 ns       624004 ns          100
BM_ypipe_lf_s/16384/3   169364226 ns       780005 ns          100
BM_ypipe_lf_s/16384/4   171335548 ns      1092007 ns          100
```
