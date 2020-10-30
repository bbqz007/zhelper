# sprintf vs stringstream

output labels and argurments. 
```c++
sprintf(buf, "i = %d; i64 = %lld; d = %f; s = %s", i, i64, d, s);
```
vs
```c++
ss << "i = " << i
			<< "; i64 = " << i64
			<< "; d = " << d
			<< "; s = " << s;
```
that is unfair.

so i let sprintf to do appending like stringstream does, and let stringstream use buffer and avoid object constructure and destructure.

benchmark items:

sprintf_? and stream_? only output labels or argurments.

sprintf2_? and stream2_? output labels and argurments.

?_append_? calls sprintf or "<<" many times to output things one by one.

?_usebuf althought use buffer but still construct and destruct stringstream everytime.

?_usebuf2 althought use buffer and avoid stringstream constructure and destructure.


```bash
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
BM_sprintf                             1581 ns         1581 ns       442887
BM_sprintf_labels                       127 ns          127 ns      5492423
BM_sprintf_append_labels               60.1 ns         60.1 ns     11624550
BM_sprintf_append_args                 1836 ns         1836 ns       375866
BM_sprintf2                            1693 ns         1693 ns       409709
BM_sprintf2_append                     1914 ns         1914 ns       365496
BM_sstream_noop                         969 ns          969 ns       718716
BM_sstream_labels                      1346 ns         1346 ns       516102
BM_sstream_labels_usebuf               1129 ns         1129 ns       616867
BM_sstream_labels_usebuf2               110 ns          110 ns      6241238
BM_sstream_append_labels               1411 ns         1411 ns       494950
BM_sstream_append_labels_usebuf        1230 ns         1230 ns       567330
BM_sstream_append_labels_usebuf2        238 ns          238 ns      2942621
BM_sstream_append_args                 3156 ns         3156 ns       221718
BM_sstream_append_args_usebuf          2911 ns         2911 ns       240717
BM_sstream_append_args_usebuf2         1537 ns         1537 ns       453092
BM_sstream2                            3283 ns         3283 ns       213107
BM_sstream2_usebuf                     3127 ns         3127 ns       221646
BM_sstream2_usebuf2                    1737 ns         1737 ns       400074

```

the costs of constructure and destructure of stringstream are high. see BM_sstream_noop.

BM_sprintf_labels **worse** than BM_sstream_labels_usebuf2

BM_sprintf_append_labels **better** than BM_sstream_append_labels_usebuf2

BM_sprintf_append_args **worse** than BM_sstream_append_args_usebuf2

BM_sprintf2_append **worse** than BM_sstream2_usebuf2
