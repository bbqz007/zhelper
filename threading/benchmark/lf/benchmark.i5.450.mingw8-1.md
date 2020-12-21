```
2020-12-21T09:23:16-00:00
Running ysample.exe
Run on (4 X 2394 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
***WARNING*** Library was built as DEBUG. Timings may be affected.
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
