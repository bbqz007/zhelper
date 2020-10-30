# sprintf vs stringstream

output labels and argurments. 

sprintf(buf, "i = %d; i64 = %lld; d = %f; s = %s", i, i64, d, s);

vs

ss << "i = " << i
			<< "; i64 = " << i64
			<< "; d = " << d
			<< "; s = " << s;
      
that is unfair.

so i let sprintf to do appending like stringstream does, and let stringstream use buffer and avoid object constructure and destructure.

benchmark items:

sprintf_? and stream_? only output labels or argurments.

sprintf2_? and stream2_? output labels and argurments.

?_append_? calls sprintf or "<<" many times to output things one by one.

?_usebuf althought use buffer but still construct and destruct stringstream everytime.

_usebuf2 althought use buffer and avoid stringstream constructure and destructure.


```bash
-------------------------------------------------------------------------
Benchmark                               Time             CPU   Iterations
-------------------------------------------------------------------------
BM_sprintf                           1607 ns         1607 ns       436195
BM_sprintf_labels                     135 ns          135 ns      5146491
BM_sprintf_append_labels             60.2 ns         60.2 ns     11663467
BM_sprintf_append_args               1895 ns         1895 ns       368902
BM_sprintf2                          1689 ns         1689 ns       409096
BM_sprintf2_append                   1945 ns         1945 ns       358112
BM_sstream_noop                       947 ns          947 ns       737764
BM_sstream_labels                    1318 ns         1318 ns       530106
BM_sstream_labels_usebuf             1096 ns         1096 ns       637721
BM_sstream_labels_usebuf2            96.8 ns         96.8 ns      7062679
BM_sstream_append_labels             1393 ns         1392 ns       502278
BM_sstream_append_args               3256 ns         3256 ns       215067
BM_sstream_append_args_usebuf        2976 ns         2976 ns       235233
BM_sstream_append_args_usebuf2       1616 ns         1616 ns       430382
BM_sstream2                          3487 ns         3487 ns       202533
BM_sstream2_usebuf                   3264 ns         3264 ns       214259
BM_sstream2_usebuf2                  1812 ns         1812 ns       385628

```
