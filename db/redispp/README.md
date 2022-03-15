### about the origin
a lightweight wrapper of hiredis c client.

original code: https://github.com/petrohi/hiredispp

the good thing of hiredis c client is that, you can use lib(ae/ev/uv/event) easily with redis.

### patch `hiredispp` to support lambda and subscribe.
this version is a patch to a fork.

* 1. patch code at `hiredispp_async.h`

* 2. make it **fit** for c++ **lambda** and **fix** lifetime management **bugs**, and _support_ **publish/subscribe**.

* 3. the **aysnc_example_cpp11.cpp** show you how to use **lambda** with zhelper-hiredispp.

* 4. use disconnect lambda to manage your async redis connection object's lifetime.

### examples
there are async samples to show:
* 1. request/reply stateful
* 2. pipeline, non request/reply and stateless
* 3. publish/subscribe
* 4. blocking pop queue
