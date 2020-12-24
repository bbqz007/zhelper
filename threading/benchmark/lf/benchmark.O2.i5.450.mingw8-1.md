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
BM_yield0                 3605192 ns      3600023 ns          195
BM_cvnotify0              1020008 ns      1022159 ns          641
BM_yield                 33109345 ns      1404009 ns          100
BM_yield2                76906650 ns      1213341 ns           90
BM_deque0/0/0            56198323 ns       468003 ns          100
BM_deque0/100/1          83880046 ns      1092007 ns          100
BM_deque0/100/2          61039210 ns      1092007 ns          100
BM_deque0/100/3          63681734 ns       624004 ns          100
BM_deque0/100/4          59691459 ns       780005 ns          100
BM_deque0/1024/1        112762673 ns       468003 ns          100
BM_deque0/1024/2         97001393 ns       780005 ns          100
BM_deque0/1024/3         98663353 ns       156001 ns          100
BM_deque0/1024/4         87248949 ns       936006 ns          100
BM_deque0/8192/1        273088519 ns      1560010 ns           10
BM_deque0/8192/2        351950714 ns        0.000 ns           10
BM_deque0/8192/3        347133693 ns        0.000 ns           10
BM_deque0/8192/4        235974407 ns       624004 ns          100
BM_deque0/16384/1       526597144 ns        0.000 ns           10
BM_deque0/16384/2       654667123 ns        0.000 ns           10
BM_deque0/16384/3       654149403 ns      1560010 ns           10
BM_deque0/16384/4       660017349 ns      1560010 ns           10
BM_deque/0/0             98363807 ns       468003 ns          100
BM_deque/100/1          118612885 ns       624004 ns          100
BM_deque/100/2          101662255 ns       624004 ns          100
BM_deque/100/3           96931160 ns       936006 ns          100
BM_deque/100/4           98053012 ns       780005 ns          100
BM_deque/1024/1         137538276 ns      1248008 ns          100
BM_deque/1024/2         112516494 ns      1248008 ns          100
BM_deque/1024/3         105747468 ns       312002 ns          100
BM_deque/1024/4         102017781 ns       936006 ns          100
BM_deque/8192/1         261687024 ns      1560010 ns           10
BM_deque/8192/2         343276065 ns      1560010 ns           10
BM_deque/8192/3         358489422 ns      1560010 ns           10
BM_deque/8192/4         222178949 ns        0.000 ns          100
BM_deque/16384/1        497882237 ns      3120020 ns           10
BM_deque/16384/2        654152097 ns        0.000 ns           10
BM_deque/16384/3        664868716 ns        0.000 ns           10
BM_deque/16384/4        654921749 ns        0.000 ns           10
BM_deque_lf/0/0         283133307 ns        0.000 ns           10
BM_deque_lf/100/1       349946342 ns        0.000 ns           10
BM_deque_lf/100/2       367167749 ns        0.000 ns           10
BM_deque_lf/100/3       367469639 ns        0.000 ns           10
BM_deque_lf/100/4       336096280 ns        0.000 ns           10
BM_deque_lf/1024/1      434543587 ns      3120020 ns           10
BM_deque_lf/1024/2      456142654 ns      1560010 ns           10
BM_deque_lf/1024/3      464113948 ns      1560010 ns           10
BM_deque_lf/1024/4      474645190 ns      1560010 ns           10
BM_deque_lf/8192/1      301283823 ns        0.000 ns           10
BM_deque_lf/8192/2      354867086 ns        0.000 ns           10
BM_deque_lf/8192/3      355380872 ns      1560010 ns           10
BM_deque_lf/8192/4      271173414 ns        0.000 ns           10
BM_deque_lf/16384/1     520951017 ns        0.000 ns           10
BM_deque_lf/16384/2     656649339 ns        0.000 ns           10
BM_deque_lf/16384/3     658800337 ns      1560010 ns           10
BM_deque_lf/16384/4     652235024 ns      1560010 ns           10
BM_deque_lf_s/0/0       190927774 ns       156001 ns          100
BM_deque_lf_s/100/1     253911843 ns        0.000 ns           10
BM_deque_lf_s/100/2     273348791 ns      1560010 ns           10
BM_deque_lf_s/100/3     280751166 ns        0.000 ns           10
BM_deque_lf_s/100/4     234223737 ns       624004 ns          100
BM_deque_lf_s/1024/1    336176650 ns        0.000 ns           10
BM_deque_lf_s/1024/2    313310655 ns      1560010 ns           10
BM_deque_lf_s/1024/3    322666759 ns        0.000 ns           10
BM_deque_lf_s/1024/4    301743416 ns        0.000 ns           10
BM_deque_lf_s/8192/1    296592255 ns        0.000 ns           10
BM_deque_lf_s/8192/2    352689099 ns        0.000 ns           10
BM_deque_lf_s/8192/3    356113055 ns        0.000 ns           10
BM_deque_lf_s/8192/4    224583486 ns       936006 ns          100
BM_deque_lf_s/16384/1   532377834 ns      1560010 ns           10
BM_deque_lf_s/16384/2   660072012 ns        0.000 ns           10
BM_deque_lf_s/16384/3   662092638 ns        0.000 ns           10
BM_deque_lf_s/16384/4   663813898 ns        0.000 ns           10
BM_deque2_lf/0/0        168241199 ns       624004 ns          100
BM_deque2_lf/100/1      225279535 ns       624004 ns          100
BM_deque2_lf/100/2      256633941 ns      1560010 ns           10
BM_deque2_lf/100/3      292394883 ns        0.000 ns           10
BM_deque2_lf/100/4      234559024 ns       468003 ns          100
BM_deque2_lf/1024/1     274851050 ns      1248008 ns          100
BM_deque2_lf/1024/2     369774233 ns        0.000 ns           10
BM_deque2_lf/1024/3     385392048 ns      1560010 ns           10
BM_deque2_lf/1024/4     387714607 ns        0.000 ns           10
BM_deque2_lf/8192/1     275430454 ns        0.000 ns           10
BM_deque2_lf/8192/2     334547137 ns        0.000 ns           10
BM_deque2_lf/8192/3     336908448 ns      1560010 ns           10
BM_deque2_lf/8192/4     225591728 ns       780005 ns          100
BM_deque2_lf/16384/1    518093158 ns      1560010 ns           10
BM_deque2_lf/16384/2    651396978 ns        0.000 ns           10
BM_deque2_lf/16384/3    666737883 ns        0.000 ns           10
BM_deque2_lf/16384/4    650728056 ns      3120020 ns           10
BM_deque2_lf_s/0/0      120250648 ns      1248008 ns          100
BM_deque2_lf_s/100/1    181674543 ns       936006 ns          100
BM_deque2_lf_s/100/2    214569970 ns       780005 ns          100
BM_deque2_lf_s/100/3    231200262 ns       312002 ns          100
BM_deque2_lf_s/100/4    176740403 ns       780005 ns          100
BM_deque2_lf_s/1024/1   194391787 ns       936006 ns          100
BM_deque2_lf_s/1024/2   197786987 ns       780005 ns          100
BM_deque2_lf_s/1024/3   197826261 ns       624004 ns          100
BM_deque2_lf_s/1024/4   195950057 ns       312002 ns          100
BM_deque2_lf_s/8192/1   268637334 ns        0.000 ns           10
BM_deque2_lf_s/8192/2   341716657 ns        0.000 ns           10
BM_deque2_lf_s/8192/3   334396877 ns        0.000 ns           10
BM_deque2_lf_s/8192/4   202762065 ns       624004 ns          100
BM_deque2_lf_s/16384/1  510950029 ns      1560010 ns           10
BM_deque2_lf_s/16384/2  656983779 ns        0.000 ns           10
BM_deque2_lf_s/16384/3  649170701 ns        0.000 ns           10
BM_deque2_lf_s/16384/4  652722932 ns      3120020 ns           10
BM_ypipe/0/0            129994008 ns       468003 ns          100
BM_ypipe/100/1          147844721 ns       468003 ns          100
BM_ypipe/100/2           69414745 ns       780005 ns          100
BM_ypipe/100/3           57259411 ns       312002 ns          100
BM_ypipe/100/4           80932248 ns       468003 ns          100
BM_ypipe/1024/1          53448311 ns        0.000 ns          100
BM_ypipe/1024/2          57074611 ns       624004 ns          100
BM_ypipe/1024/3          58756195 ns       156001 ns          100
BM_ypipe/1024/4          46730898 ns       312002 ns          100
BM_ypipe/8192/1         261486249 ns      1560010 ns           10
BM_ypipe/8192/2         329460991 ns        0.000 ns           10
BM_ypipe/8192/3         328629746 ns        0.000 ns           10
BM_ypipe/8192/4         203961878 ns       936006 ns          100
BM_ypipe/16384/1        502428849 ns        0.000 ns           10
BM_ypipe/16384/2        647340200 ns        0.000 ns           10
BM_ypipe/16384/3        642803555 ns        0.000 ns           10
BM_ypipe/16384/4        649181694 ns        0.000 ns           10
BM_ypipe_s/0/0          128583073 ns       468003 ns          100
BM_ypipe_s/100/1        142449350 ns       780005 ns          100
BM_ypipe_s/100/2         67162274 ns       156001 ns          100
BM_ypipe_s/100/3         43557026 ns       312002 ns          100
BM_ypipe_s/100/4         88514196 ns       780005 ns          100
BM_ypipe_s/1024/1        52963606 ns       624004 ns          100
BM_ypipe_s/1024/2        57364273 ns       780005 ns          100
BM_ypipe_s/1024/3        58808498 ns      1404009 ns          100
BM_ypipe_s/1024/4        47592512 ns       624004 ns          100
BM_ypipe_s/8192/1       270131043 ns        0.000 ns           10
BM_ypipe_s/8192/2       332270645 ns      1560010 ns           10
BM_ypipe_s/8192/3       329877854 ns        0.000 ns           10
BM_ypipe_s/8192/4       204560269 ns       156001 ns          100
BM_ypipe_s/16384/1      518811654 ns        0.000 ns           10
BM_ypipe_s/16384/2      643121099 ns        0.000 ns           10
BM_ypipe_s/16384/3      644107011 ns        0.000 ns           10
BM_ypipe_s/16384/4      647632637 ns      1560010 ns           10
BM_ypipe_lf/0/0         188289592 ns       468003 ns          100
BM_ypipe_lf/100/1       271391811 ns        0.000 ns           10
BM_ypipe_lf/100/2       298799798 ns        0.000 ns           10
BM_ypipe_lf/100/3       318409805 ns      1560010 ns           10
BM_ypipe_lf/100/4       256902426 ns        0.000 ns           10
BM_ypipe_lf/1024/1      316314113 ns        0.000 ns           10
BM_ypipe_lf/1024/2      398773963 ns        0.000 ns           10
BM_ypipe_lf/1024/3      407969455 ns        0.000 ns           10
BM_ypipe_lf/1024/4      421312618 ns        0.000 ns           10
BM_ypipe_lf/8192/1      270032666 ns      1560010 ns           10
BM_ypipe_lf/8192/2      332654488 ns        0.000 ns           10
BM_ypipe_lf/8192/3      338608407 ns        0.000 ns           10
BM_ypipe_lf/8192/4      220055386 ns      1092007 ns          100
BM_ypipe_lf/16384/1     524929008 ns        0.000 ns           10
BM_ypipe_lf/16384/2     648469100 ns        0.000 ns           10
BM_ypipe_lf/16384/3     649757629 ns        0.000 ns           10
BM_ypipe_lf/16384/4     650890977 ns      4680030 ns           10
BM_ypipe_lf_s/0/0       144624295 ns       624004 ns          100
BM_ypipe_lf_s/100/1     217989670 ns       624004 ns          100
BM_ypipe_lf_s/100/2     245970921 ns       156001 ns          100
BM_ypipe_lf_s/100/3     279714997 ns        0.000 ns           10
BM_ypipe_lf_s/100/4     201826327 ns       468003 ns          100
BM_ypipe_lf_s/1024/1    217215073 ns       312002 ns          100
BM_ypipe_lf_s/1024/2    218336389 ns       624004 ns          100
BM_ypipe_lf_s/1024/3    213722060 ns       624004 ns          100
BM_ypipe_lf_s/1024/4    214512359 ns       624004 ns          100
BM_ypipe_lf_s/8192/1    266953757 ns        0.000 ns           10
BM_ypipe_lf_s/8192/2    333664052 ns      1560010 ns           10
BM_ypipe_lf_s/8192/3    336632906 ns      1560010 ns           10
BM_ypipe_lf_s/8192/4    214949034 ns       624004 ns          100
BM_ypipe_lf_s/16384/1   507913038 ns        0.000 ns           10
BM_ypipe_lf_s/16384/2   648986779 ns      1560010 ns           10
BM_ypipe_lf_s/16384/3   648157116 ns        0.000 ns           10
BM_ypipe_lf_s/16384/4   650086550 ns      3120020 ns           10

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
