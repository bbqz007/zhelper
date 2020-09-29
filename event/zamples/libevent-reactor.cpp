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
#include <string.h>
#include <vector>
#include <iostream>
#include <thread>
#include <memory>

using namespace std;

struct reactor_tcp
{
    shared_ptr<struct event> event_;
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

void change_poll(reactor_tcp* rr_tcp, int events) {
                event_assign(rr_tcp->event_.get(), evutil_default_reactor(), rr_tcp->sock_, events,
                    // react cbs for rr_tcp
                    [](evutil_socket_t, short events, void* handle) {
                        reactor_tcp* rr_tcp = upcatst_poll_handle_to_reactor_tcp(handle);
                        bool finish = false;
                         struct lambda {
                            static bool rr_tcp_write(reactor_tcp* rr_tcp) {
                                cout << this_thread::get_id() << ": write" << endl;
                                bool finish = false;
                                if (rr_tcp->nread_ > 0)
                                {
                                    // edge-triggered mode, can not mock that send would block
                                    //size_t towrite = min((size_t)32, rr_tcp->nread_ - rr_tcp->wrpos_);
                                    size_t towrite = rr_tcp->nread_ - rr_tcp->wrpos_;
                                    int nwritten = write(rr_tcp->sock_, &rr_tcp->inbuf_[rr_tcp->wrpos_], towrite);
                                    if (nwritten == -1 && (errno != EAGAIN || errno != EWOULDBLOCK))
                                        return finish;
                                    rr_tcp->wrpos_ += (size_t)max(nwritten, 0);
                                    if (rr_tcp->wrpos_ == rr_tcp->nread_)
                                    {
                                        change_poll(rr_tcp, EV_READ|EV_PERSIST|EV_ET);
                                        finish = true;
                                    }
                                    else
                                    {
                                        cout << this_thread::get_id() << ": add writable to poll" << endl;
                                        change_poll(rr_tcp, EV_READ|EV_WRITE|EV_PERSIST|EV_ET);
                                    }
                                return finish;
                            }
                         }
                        };

                        if (events & EV_READ)
                        {
                            cout << this_thread::get_id() << ": react to read" << endl;
                            // you should read by yourself and manage buffer
                            size_t toread = rr_tcp->inbuf_.capacity();
                            rr_tcp->nread_ = read(rr_tcp->sock_, &rr_tcp->inbuf_[0], toread);
                            if (rr_tcp->nread_ < 0)
                            {
                                finish = true;
                            }
                            else
                            {
                                // just assume complete read once
                                // dispatch a work for payload anywhere
                                cout << this_thread::get_id() << ": payload" << endl;
                                finish = lambda::rr_tcp_write(rr_tcp);
//                                 uv_work_t* work = new uv_work_t;
//                                 work->data = (void*) rr_tcp;
//                                 uv_queue_work(evutil_default_reactor(), work,
//                                     [](uv_work_t* work) {
//                                         reactor_tcp* rr_tcp = (reactor_tcp*)work->data;
//                                         cout << this_thread::get_id() << ": payload" << endl;
//                                         sleep(1);
//                                     },
//                                     [](uv_work_t* work, int status) {
//                                         cout << this_thread::get_id() << ": write after payload" << endl;
//                                         reactor_tcp* rr_tcp = (reactor_tcp*)work->data;
//                                         lambda::rr_tcp_write(rr_tcp);
//                                         delete work;
//                                     }
//                                 );
                            }
                        }
                        else if (events & EV_WRITE)
                        {
                            cout << this_thread::get_id() << ": react to write" << endl;
                            finish = lambda::rr_tcp_write(rr_tcp);
                        }
                        if (finish)
                        {
                            if (finish)
                                close(rr_tcp->sock_);
                            event_del(rr_tcp->event_.get());
                            evutil_close((void*)handle,
                                [](void* handle) {
                                    cout << this_thread::get_id() << ": connection quit" << endl;
                                    delete upcatst_poll_handle_to_reactor_tcp(handle);
                                }
                            );
                        }
                    },
                    rr_tcp
                );
                event_add(rr_tcp->event_.get(), EVUTIL_EV_NOTIMEOUT);
            };

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
                cout << this_thread::get_id() << ": connection incoming" << endl;
                int flags = fcntl(rr_tcp->sock_, F_GETFL, 0);
                fcntl(rr_tcp->sock_, F_SETFL, flags | O_NONBLOCK | O_NDELAY);
                rr_tcp->inbuf_.reserve(1<<16);
                rr_tcp->wrpos_ = 0;
                rr_tcp->nread_ = 0;
                rr_tcp->inuse_ = false;
                rr_tcp->event_ = shared_ptr<struct event>(event_new(evutil_default_reactor(), rr_tcp->sock_, 0, 0, 0), [](struct event* event) { event_free(event); });

                change_poll(rr_tcp, EV_READ|EV_PERSIST|EV_ET);
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





























