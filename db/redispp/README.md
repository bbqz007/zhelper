a lightweight wrapper of hiredis c client.

original code: https://github.com/petrohi/hiredispp

the good thing of hiredis c client is that, you can use lib(ae/ev/uv/event) easily with redis.

this version is a fork.

* 1. almost changed code at hiredispp_async.h

* 2. make it fit for c++ lambda and fix lifetime management bugs, and support publish/subscribe.

* 3. the aysnc_example_cpp11.cpp show you how to use lambda with zhelper-hiredispp.

* 4. use disconnect lambda to manage your async redis connection object's lifetime.

there are async samples to show:
* 1. request/reply stateful
* 2. pipeline, non request/reply and stateless
* 3. publish/subscribe
* 4. blocking pop queue
