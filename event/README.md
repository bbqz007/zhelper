## zhelper/event/zamples
libevent, libev and libuv samples, programming in c++11 and async coding with lambdas, are given.

these samples show you what are similar and different.

libev has a name closed to libevent, but it's apis are similar to libuv.

libuv support proact api uv_read_start/uv_write_start, and react api uv_poll_start.

libevent and libev only support react apis.

libevent can use buffer_event to emulate proact.

libuv use lt-epoll by default, while libev use et-epoll. and libevent can use either by choice.

**examples**

* 1. libuv-example.cpp shows proact mode using uv_tcp_t.

* 2. libuv-reactor.cpp shows react mode using uv_poll_t.

* 3. libev-reacotr.cpp fork libuv-reactor.cpp, shows react mode using ev_poll_t.

* 4. libevent-reactor.cpp fork libuv-reactor.cpp, shows react mode using event.

**tests**

use webbrowser to connect the sample, then an echo of request will return. 
