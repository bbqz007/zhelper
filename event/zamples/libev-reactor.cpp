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
#include <netinet/in.h>
#include <sys/socket.h>
#include <ev.h>
#include <fcntl.h>
#include <vector>
#include <iostream>
#include <thread>

using namespace std;
typedef struct ev_io uv_poll_t;
typedef int uv_os_sock_t;
typedef struct ev_loop uv_loop_t;
#define uv_poll_start ev_io_start
#define uv_poll_stop ev_io_stop
#define uv_poll_fake_api_set ev_io_set
#define uv_poll_init_socket ev_io_init
#define uv_default_loop ev_default_loop
#define UV_READABLE EV_READ
#define UV_WRITABLE EV_WRITE
#define uv_loop_close(x)
#define uv_ip4_addr ev_ip4_addr
#define uv_run ev_loop
#define UV_RUN_DEFAULT 0
#define uv_close ev_close
#define uv_handle_t void
#define UV_DISCONNECT 0

struct reactor_tcp
{
    uv_poll_t reactor_;
    uv_os_sock_t sock_;
    struct sockaddr_in addr_;
    vector<char> inbuf_;
    size_t wrpos_;
    size_t nread_;
    bool inuse_;
};

#define upcatst_poll_handle_to_reactor_tcp(handle) (reactor_tcp*)(handle)
void ev_ip4_addr(const char* ip, unsigned short port, struct sockaddr_in* in)
{
    in->sin_addr.s_addr = INADDR_ANY;
    in->sin_family = AF_INET;
    in->sin_port = htons(port);
}
typedef void (*evutil_close_cb)(void*);
void ev_close(void* handle, evutil_close_cb cb)
{
    cb(handle);
}

void change_poll(reactor_tcp* rr_tcp, int events) {
                uv_poll_fake_api_set(&rr_tcp->reactor_, rr_tcp->sock_, events);
            };

int main()
{
    cout << "reactor mode on libev" << endl;
    cout << "you should do a lot of underlying work about socket" << endl;
    cout << " except the poll(, select, epoll, kqueue, etc.)" << endl;
    cout << "and you should ctrl to add/remove writable to/from reactor on your full code path" << endl;
    cout << "you are free and can ctrl the thing you want" << endl;
    cout << "libev use edge-triggered mode by default" << endl;

    reactor_tcp listen_tcp;
    struct sockaddr_in& listen_addr = listen_tcp.addr_;
    uv_ip4_addr("127.0.0.1", 12348, &listen_addr);
    listen_tcp.sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int flags = fcntl(listen_tcp.sock_, F_GETFL, 0);
    fcntl(listen_tcp.sock_, F_SETFL, flags | O_NONBLOCK);
    setsockopt(listen_tcp.sock_, SOL_SOCKET, SO_REUSEADDR, &(flags=1), 4);
    bind(listen_tcp.sock_, (struct sockaddr*)&listen_addr, sizeof(struct sockaddr));
    listen(listen_tcp.sock_, 1);
    uv_poll_init_socket(&listen_tcp.reactor_,
        // react cbs for listen_tcp
        [](uv_loop_t* loop, uv_poll_t* handle, int events) {
            if (0 == (events & UV_READABLE))
                return;
            reactor_tcp* rr_tcp = new reactor_tcp;
            reactor_tcp* listen_tcp = upcatst_poll_handle_to_reactor_tcp(handle);
            socklen_t socklen = sizeof(struct sockaddr);
            rr_tcp->sock_ = accept(listen_tcp->sock_, (struct sockaddr*)&rr_tcp->addr_, &socklen);
            if (rr_tcp->sock_ != -1)
            {
                cout << this_thread::get_id() << ": connection incoming" << endl;
                int flags = fcntl(rr_tcp->sock_, F_GETFL, 0);
                fcntl(rr_tcp->sock_, F_SETFL, flags | O_NONBLOCK);
                rr_tcp->inbuf_.reserve(1<<16);
                rr_tcp->wrpos_ = 0;
                rr_tcp->nread_ = 0;
                rr_tcp->inuse_ = false;
                uv_poll_init_socket(&rr_tcp->reactor_,
                        // react cbs for rr_tcp
                    [](uv_loop_t* loop, uv_poll_t* handle, int events) {
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
                                        change_poll(rr_tcp, UV_READABLE | UV_DISCONNECT);
                                        finish = true;
                                    }
                                    else
                                    {
                                        cout << this_thread::get_id() << ": add writable to poll" << endl;
                                        change_poll(rr_tcp, UV_READABLE | UV_WRITABLE | UV_DISCONNECT);
                                    }
                                return finish;
                            }
                         }
                        };
                        reactor_tcp* rr_tcp = upcatst_poll_handle_to_reactor_tcp(handle);
                        if (events & UV_READABLE)
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
                                cout << this_thread::get_id() << ": payload" << endl;
                                finish = lambda::rr_tcp_write(rr_tcp);
//                                 uv_work_t* work = new uv_work_t;
//                                 work->data = (void*) rr_tcp;
//                                 uv_queue_work(uv_default_loop(0), work,
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
                        else if (events & UV_WRITABLE)
                        {
                            cout << this_thread::get_id() << ": react to write" << endl;
                            finish = lambda::rr_tcp_write(rr_tcp);
                        }
                        if (finish || (events & UV_DISCONNECT))
                        {
                            if (finish)
                                close(rr_tcp->sock_);
                            uv_poll_stop(uv_default_loop(0), &rr_tcp->reactor_);
                            uv_close((uv_handle_t*)handle,
                                [](uv_handle_t* handle) {
                                    cout << this_thread::get_id() << ": connection quit" << endl;
                                    delete upcatst_poll_handle_to_reactor_tcp(handle);
                                }
                            );
                        }
                    },
                    rr_tcp->sock_,
                    UV_READABLE);
                uv_poll_start(uv_default_loop(0), &rr_tcp->reactor_);

                change_poll(rr_tcp, UV_READABLE);
            }
            else
            {
                delete rr_tcp;
            }
        },
        listen_tcp.sock_,
        UV_READABLE
    );
    uv_poll_start(uv_default_loop(0), &listen_tcp.reactor_);

    uv_run(uv_default_loop(0), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop(0));

    close(listen_tcp.sock_);
    return 0;
}





























