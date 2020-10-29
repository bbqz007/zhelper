/**
MIT License
Copyright (c) 2020 bbqz007 <cnblogs.com/bbqzsl, github.com/bbqz007>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <unistd.h>
#include <fcntl.h>
#include <event.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_compat.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <thread>
#include <memory>

using namespace std;

struct reactor_tcp
{
    shared_ptr<struct event> event_;
    shared_ptr<struct bufferevent> bev_;
    evutil_socket_t sock_;
    struct sockaddr_in addr_;
    vector<char> inbuf_;
    size_t wrpos_;
    size_t nread_;
    bool inuse_;
};

struct event_base* default_reactor = NULL;
struct event_base* evutil_default_reactor()
{
    static shared_ptr<struct event_base> default_reactor(event_base_new(), [](struct event_base* eb)
    { event_base_free(eb); });
    return default_reactor.get();
}
typedef void (*evutil_close_cb)(void*);
void evutil_close(void* handle, evutil_close_cb cb)
{
    cb(handle);
}
void evutil_ip4_addr(const char* ip, unsigned short port, struct sockaddr_in* in)
{
    memset(in, 0, sizeof(*in));
    in->sin_family = AF_INET;
    in->sin_port = htons(port);
}
#define EVUTIL_EV_NOTIMEOUT NULL
#define upcatst_poll_handle_to_reactor_tcp(handle) (reactor_tcp*)(handle)

int main()
{
    cout << "reactor mode on libevent" << endl;
    cout << "you should do a lot of underlying work about socket" << endl;
    cout << " except the poll(, select, epoll, kqueue, etc.)" << endl;
    cout << "and you should ctrl to add/remove writable to/from reactor on your full code path" << endl;
    cout << "you are free and can ctrl the thing you want" << endl;
    cout << "you can choose edeg-triggered mode by yourself" << endl;

    reactor_tcp listen_tcp;
    struct sockaddr_in& listen_addr = listen_tcp.addr_;
    evutil_ip4_addr("127.0.0.1", 12347, &listen_addr);
    listen_tcp.sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int flags = fcntl(listen_tcp.sock_, F_GETFL, 0);
    fcntl(listen_tcp.sock_, F_SETFL, flags | O_NONBLOCK);
    setsockopt(listen_tcp.sock_, SOL_SOCKET, SO_REUSEADDR, &(flags=1), 4);
    bind(listen_tcp.sock_, (struct sockaddr*)&listen_addr, sizeof(struct sockaddr));
    listen(listen_tcp.sock_, 1);
    listen_tcp.event_ = shared_ptr<struct event>(event_new(evutil_default_reactor(), listen_tcp.sock_, EV_READ | EV_PERSIST,
        // react cbs for listen_tcp
        [](evutil_socket_t, short events, void* handle) {
            if (0 == (events & EV_READ))
                return;
            reactor_tcp* rr_tcp = new reactor_tcp;
            reactor_tcp* listen_tcp = upcatst_poll_handle_to_reactor_tcp(handle);
            socklen_t socklen = sizeof(struct sockaddr);
            rr_tcp->sock_ = accept(listen_tcp->sock_, (struct sockaddr*)&rr_tcp->addr_, &socklen);
            if (rr_tcp->sock_ != -1)
            {
                rr_tcp->bev_.reset(
                    bufferevent_socket_new(evutil_default_reactor(), rr_tcp->sock_, BEV_OPT_CLOSE_ON_FREE)
                    , bufferevent_free);
                rr_tcp->inbuf_.reserve(1<<16);
                rr_tcp->wrpos_ = 0;
                rr_tcp->nread_ = 0;
                rr_tcp->inuse_ = false;
                bufferevent* bev = rr_tcp->bev_.get();
                bufferevent_setcb(bev,
                                  // bev_readcb
                                  [](bufferevent* bev, void* ctx){
                                      reactor_tcp* rr_tcp = (reactor_tcp*)ctx;
                                      evbuffer* evbuf = evbuffer_new();
                                      bufferevent_read_buffer(rr_tcp->bev_.get(), evbuf);
                                      bufferevent_write_buffer(rr_tcp->bev_.get(), evbuf);
                                      evbuffer_free(evbuf);
                                  },
                                  // bev_writecb
                                  [](bufferevent* bev, void* ctx){
                                      reactor_tcp* rr_tcp = (reactor_tcp*)ctx;
                                      if (0 == evbuffer_get_length(bufferevent_get_output(rr_tcp->bev_.get())))
                                      {
                                          shutdown(rr_tcp->sock_, SHUT_RDWR);
                                      }
                                  },
                                  // bev_eventcb
                                  [](bufferevent* bev, short what, void* ctx){
                                      reactor_tcp* rr_tcp = (reactor_tcp*)ctx;
                                      if (!(what & BEV_EVENT_CONNECTED))
                                      {
                                          bufferevent_disable(rr_tcp->bev_.get(), EV_READ|EV_WRITE);
                                          delete rr_tcp;
                                          return;
                                      }
                                  },
                                  rr_tcp);
                bufferevent_enable(rr_tcp->bev_.get(), EV_READ);
                cout << this_thread::get_id() << ": connection incoming" << endl;
            }
            else
            {
                delete rr_tcp;
            }
        },
        &listen_tcp),
        [](struct event* event) {
            event_free(event);
        }
    );
    event_add(listen_tcp.event_.get(), EVUTIL_EV_NOTIMEOUT);

    event_base_dispatch(evutil_default_reactor());

    close(listen_tcp.sock_);
    return 0;
}





























