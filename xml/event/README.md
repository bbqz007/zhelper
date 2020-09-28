## zhelper/event/zamples
libevent, libev and libuv samples, programming in c++11, are given.

these samples show you what are similar and different.

libev has a name closed to libevent, but it's apis are similar to libuv.

libuv support proact api uv_read_start/uv_write_start, and react api uv_poll_start.

libevent and libev only support react apis.

libevent can use buffer_event to emulate proact.

libuv use lt-epoll by default, which libev use et-epoll. and libevent can use either by choice.
