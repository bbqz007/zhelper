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
