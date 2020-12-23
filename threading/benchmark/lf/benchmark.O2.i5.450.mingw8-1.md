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
