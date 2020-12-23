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
