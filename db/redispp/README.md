a lightweight wrapper of hiredis c client.

origin code: https://github.com/petrohi/hiredispp

the good thing of hiredis c client is that, you can use lib(ae/ev/uv/event) easily with redis.

this is a fork version.

almost changed code at hiredispp_async.h

make it fit for c++ lambda and fix lifetime management bugs, and support publish/subscribe.

the aysnc_example_cpp11.cpp show you how to use lambda with zhelper-hiredispp.

use disconnect lambda to manage your async redis connection object's lifetime.
