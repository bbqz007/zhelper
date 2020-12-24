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
BM_yield0                 3588326 ns      3520023 ns          195
BM_cvnotify0              1021076 ns      1021932 ns          748
BM_yield                 31957827 ns      1716011 ns          100
BM_yield2                74025413 ns      1872012 ns          100
BM_deque0/0/0           119726575 ns       624004 ns          100
BM_deque0/100/1         128135328 ns       156001 ns          100
BM_deque0/100/2         124958774 ns      1404009 ns          100
BM_deque0/100/3         125697882 ns       936006 ns          100
BM_deque0/100/4         122882180 ns       780005 ns          100
BM_deque0/1024/1        149578821 ns       624004 ns          100
BM_deque0/1024/2        153456596 ns       312002 ns          100
BM_deque0/1024/3        153741146 ns       624004 ns          100
BM_deque0/1024/4        147631889 ns        0.000 ns          100
BM_deque0/8192/1        337039418 ns        0.000 ns           10
BM_deque0/8192/2        416788163 ns        0.000 ns           10
BM_deque0/8192/3        420341121 ns        0.000 ns           10
BM_deque0/8192/4        309280011 ns        0.000 ns           10
BM_deque0/16384/1       587420159 ns        0.000 ns           10
BM_deque0/16384/2       743886346 ns        0.000 ns           10
BM_deque0/16384/3       733607635 ns        0.000 ns           10
BM_deque0/16384/4       739520022 ns      1560010 ns           10
BM_deque/0/0            117158330 ns       936006 ns          100
BM_deque/100/1          126390898 ns       936006 ns          100
BM_deque/100/2          121243433 ns       624004 ns          100
BM_deque/100/3          121630949 ns       624004 ns          100
BM_deque/100/4          119568060 ns       468003 ns          100
BM_deque/1024/1         149059851 ns       624004 ns          100
BM_deque/1024/2         145057014 ns      1092007 ns          100
BM_deque/1024/3         142935282 ns       624004 ns          100
BM_deque/1024/4         136972021 ns       624004 ns          100
BM_deque/8192/1         337209739 ns      1560010 ns           10
BM_deque/8192/2         397184871 ns      1560010 ns           10
BM_deque/8192/3         401209056 ns      1560010 ns           10
BM_deque/8192/4         291606795 ns      1560010 ns           10
BM_deque/16384/1        595290767 ns      1560010 ns           10
BM_deque/16384/2        722166447 ns        0.000 ns           10
BM_deque/16384/3        732690203 ns        0.000 ns           10
BM_deque/16384/4        715199028 ns        0.000 ns           10
BM_deque_lf/0/0         361144923 ns        0.000 ns           10
BM_deque_lf/100/1       323883771 ns        0.000 ns           10
BM_deque_lf/100/2       286877031 ns        0.000 ns           10
BM_deque_lf/100/3       290120187 ns      1560010 ns           10
BM_deque_lf/100/4       305972868 ns        0.000 ns           10
BM_deque_lf/1024/1      245638124 ns       780005 ns          100
BM_deque_lf/1024/2      216634296 ns      1092007 ns          100
BM_deque_lf/1024/3      211327460 ns      1092007 ns          100
BM_deque_lf/1024/4      245933050 ns       624004 ns          100
BM_deque_lf/8192/1      356682617 ns        0.000 ns           10
BM_deque_lf/8192/2      406142975 ns        0.000 ns           10
BM_deque_lf/8192/3      409245451 ns        0.000 ns           10
BM_deque_lf/8192/4      320042696 ns      1560010 ns           10
BM_deque_lf/16384/1     598359752 ns      3120020 ns           10
BM_deque_lf/16384/2     721870630 ns        0.000 ns           10
BM_deque_lf/16384/3     726083743 ns      1560010 ns           10
BM_deque_lf/16384/4     715948919 ns        0.000 ns           10
BM_deque_lf_s/0/0       279203178 ns        0.000 ns           10
BM_deque_lf_s/100/1     289958677 ns        0.000 ns           10
BM_deque_lf_s/100/2     274534793 ns      1560010 ns           10
BM_deque_lf_s/100/3     275278568 ns        0.000 ns           10
BM_deque_lf_s/100/4     282290128 ns        0.000 ns           10
BM_deque_lf_s/1024/1    250228043 ns      3120020 ns           10
BM_deque_lf_s/1024/2    199105537 ns       936006 ns          100
BM_deque_lf_s/1024/3    199954285 ns       468003 ns          100
BM_deque_lf_s/1024/4    223063429 ns       624004 ns          100
BM_deque_lf_s/8192/1    355639091 ns        0.000 ns           10
BM_deque_lf_s/8192/2    411328910 ns      1560010 ns           10
BM_deque_lf_s/8192/3    413047346 ns        0.000 ns           10
BM_deque_lf_s/8192/4    307907863 ns      1560010 ns           10
BM_deque_lf_s/16384/1   593323607 ns      1560010 ns           10
BM_deque_lf_s/16384/2   724467747 ns      1560010 ns           10
BM_deque_lf_s/16384/3   732873056 ns        0.000 ns           10
BM_deque_lf_s/16384/4   728596811 ns        0.000 ns           10
BM_deque2_lf/0/0        206768153 ns       624004 ns          100
BM_deque2_lf/100/1      165354357 ns       156001 ns          100
BM_deque2_lf/100/2      164615715 ns       468003 ns          100
BM_deque2_lf/100/3      156174318 ns       312002 ns          100
BM_deque2_lf/100/4      169714355 ns      1716011 ns          100
BM_deque2_lf/1024/1     162998372 ns       936006 ns          100
BM_deque2_lf/1024/2     154692826 ns       624004 ns          100
BM_deque2_lf/1024/3     151066610 ns       936006 ns          100
BM_deque2_lf/1024/4     164454017 ns       936006 ns          100
BM_deque2_lf/8192/1     343990455 ns      1560010 ns           10
BM_deque2_lf/8192/2     396904624 ns        0.000 ns           10
BM_deque2_lf/8192/3     402622438 ns      1560010 ns           10
BM_deque2_lf/8192/4     312508111 ns      1560010 ns           10
BM_deque2_lf/16384/1    587687403 ns        0.000 ns           10
BM_deque2_lf/16384/2    721456890 ns      1560010 ns           10
BM_deque2_lf/16384/3    721220656 ns      1560010 ns           10
BM_deque2_lf/16384/4    720289836 ns      1560010 ns           10
BM_deque2_lf_s/0/0      137060154 ns       624004 ns          100
BM_deque2_lf_s/100/1    151315659 ns      1092007 ns          100
BM_deque2_lf_s/100/2    150361678 ns       468003 ns          100
BM_deque2_lf_s/100/3    145623650 ns       780005 ns          100
BM_deque2_lf_s/100/4    139840265 ns       312002 ns          100
BM_deque2_lf_s/1024/1   156938025 ns      1092007 ns          100
BM_deque2_lf_s/1024/2   143320266 ns      1248008 ns          100
BM_deque2_lf_s/1024/3   146043378 ns       468003 ns          100
BM_deque2_lf_s/1024/4   145465806 ns       624004 ns          100
BM_deque2_lf_s/8192/1   340746529 ns        0.000 ns           10
BM_deque2_lf_s/8192/2   402714357 ns        0.000 ns           10
BM_deque2_lf_s/8192/3   407938145 ns        0.000 ns           10
BM_deque2_lf_s/8192/4   331094438 ns        0.000 ns           10
BM_deque2_lf_s/16384/1  585198502 ns      1560010 ns           10
BM_deque2_lf_s/16384/2  725556099 ns        0.000 ns           10
BM_deque2_lf_s/16384/3  723494497 ns      1560010 ns           10
BM_deque2_lf_s/16384/4  718013644 ns        0.000 ns           10
BM_ypipe/0/0             90598223 ns       624004 ns          100
BM_ypipe/100/1          102765320 ns      1404009 ns          100
BM_ypipe/100/2           94941823 ns      1092007 ns          100
BM_ypipe/100/3           98804272 ns      1248008 ns          100
BM_ypipe/100/4           95021269 ns       624004 ns          100
BM_ypipe/1024/1         133048801 ns       936006 ns          100
BM_ypipe/1024/2         126922747 ns      1092007 ns          100
BM_ypipe/1024/3         128281717 ns       624004 ns          100
BM_ypipe/1024/4         119844068 ns      1248008 ns          100
BM_ypipe/8192/1         331406722 ns      3120020 ns           10
BM_ypipe/8192/2         398759420 ns        0.000 ns           10
BM_ypipe/8192/3         400087898 ns        0.000 ns           10
BM_ypipe/8192/4         292144491 ns        0.000 ns           10
BM_ypipe/16384/1        579413278 ns        0.000 ns           10
BM_ypipe/16384/2        721053714 ns        0.000 ns           10
BM_ypipe/16384/3        720421448 ns      1560010 ns           10
BM_ypipe/16384/4        722912531 ns        0.000 ns           10
BM_ypipe_s/0/0           90904968 ns       468003 ns          100
BM_ypipe_s/100/1        102567702 ns       780005 ns          100
BM_ypipe_s/100/2         95810485 ns       936006 ns          100
BM_ypipe_s/100/3         98003998 ns       624004 ns          100
BM_ypipe_s/100/4         95057266 ns       624004 ns          100
BM_ypipe_s/1024/1       131940359 ns       624004 ns          100
BM_ypipe_s/1024/2       126391779 ns       312002 ns          100
BM_ypipe_s/1024/3       127536959 ns       312002 ns          100
BM_ypipe_s/1024/4       119753822 ns       468003 ns          100
BM_ypipe_s/8192/1       329307480 ns        0.000 ns           10
BM_ypipe_s/8192/2       403609846 ns      1560010 ns           10
BM_ypipe_s/8192/3       406228263 ns      1560010 ns           10
BM_ypipe_s/8192/4       290192045 ns      1560010 ns           10
BM_ypipe_s/16384/1      577815118 ns      1560010 ns           10
BM_ypipe_s/16384/2      725191761 ns      1560010 ns           10
BM_ypipe_s/16384/3      726435335 ns      3120020 ns           10
BM_ypipe_s/16384/4      725357762 ns      3120020 ns           10
BM_ypipe_lf/0/0         250656369 ns      1560010 ns           10
BM_ypipe_lf/100/1       196101964 ns       780005 ns          100
BM_ypipe_lf/100/2       196876967 ns       312002 ns          100
BM_ypipe_lf/100/3       185058237 ns       312002 ns          100
BM_ypipe_lf/100/4       199540407 ns      1404009 ns          100
BM_ypipe_lf/1024/1      172135475 ns       624004 ns          100
BM_ypipe_lf/1024/2      160523482 ns       468003 ns          100
BM_ypipe_lf/1024/3      156024430 ns       936006 ns          100
BM_ypipe_lf/1024/4      182831571 ns       624004 ns          100
BM_ypipe_lf/8192/1      341474607 ns        0.000 ns           10
BM_ypipe_lf/8192/2      397062370 ns        0.000 ns           10
BM_ypipe_lf/8192/3      402670258 ns        0.000 ns           10
BM_ypipe_lf/8192/4      312458879 ns        0.000 ns           10
BM_ypipe_lf/16384/1     591080092 ns        0.000 ns           10
BM_ypipe_lf/16384/2     720938528 ns        0.000 ns           10
BM_ypipe_lf/16384/3     722799953 ns        0.000 ns           10
BM_ypipe_lf/16384/4     717466538 ns        0.000 ns           10
BM_ypipe_lf_s/0/0       170380600 ns      1560010 ns          100
BM_ypipe_lf_s/100/1     171136706 ns       624004 ns          100
BM_ypipe_lf_s/100/2     181915546 ns       936006 ns          100
BM_ypipe_lf_s/100/3     177552836 ns       624004 ns          100
BM_ypipe_lf_s/100/4     178653446 ns       624004 ns          100
BM_ypipe_lf_s/1024/1    166401848 ns       780005 ns          100
BM_ypipe_lf_s/1024/2    152297211 ns       468003 ns          100
BM_ypipe_lf_s/1024/3    146466268 ns      1092007 ns          100
BM_ypipe_lf_s/1024/4    160243727 ns       468003 ns          100
BM_ypipe_lf_s/8192/1    340238347 ns        0.000 ns           10
BM_ypipe_lf_s/8192/2    401498670 ns        0.000 ns           10
BM_ypipe_lf_s/8192/3    399492673 ns      1560010 ns           10
BM_ypipe_lf_s/8192/4    293612365 ns      1560010 ns           10
BM_ypipe_lf_s/16384/1   583380918 ns        0.000 ns           10
BM_ypipe_lf_s/16384/2   726878289 ns      1560010 ns           10
BM_ypipe_lf_s/16384/3   724682509 ns        0.000 ns           10
BM_ypipe_lf_s/16384/4   725859742 ns      1560010 ns           10
```
