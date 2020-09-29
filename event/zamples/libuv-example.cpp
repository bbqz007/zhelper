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
#include <uv.h>
#include <vector>
#include <iostream>
#include <thread>

using namespace std;

struct one_rr_tcp
{
    uv_tcp_t tcp_;
    uv_write_t wr_;
    uv_buf_t wr_buf_;
    uv_work_t work_;
    vector<char> inbuf_;
    size_t nread_;
};
#define upcast_handle_to_rr_tcp(handle)  (one_rr_tcp*)handle

int main()
{
    uv_timer_t timer;
    uv_timer_init(uv_default_loop(), &timer);
    uv_timer_start(&timer, [](uv_timer_t*) {
        cout << this_thread::get_id() << ": timer fired" << endl;
    }, 1, 1000);

    uv_tcp_t listen_tcp;
    struct sockaddr_in listen_addr;
    uv_ip4_addr("127.0.0.1", 12345, &listen_addr);
    uv_tcp_init(uv_default_loop(), &listen_tcp);
    uv_tcp_bind(&listen_tcp, (const struct sockaddr*)&listen_addr, 0);
    int flags = 0;
    setsockopt(listen_tcp.u.fd, SOL_SOCKET, SO_REUSEADDR, &(flags=1), 4);
    uv_listen((uv_stream_t*)&listen_tcp, SOMAXCONN,
        // connection cb
        [](uv_stream_t* listen_server, int status) {
            cout << this_thread::get_id() << ": new rr object" << endl;
            one_rr_tcp& rr_tcp = * new one_rr_tcp;
            uv_tcp_init(uv_default_loop(), &rr_tcp.tcp_);
            uv_accept(listen_server, (uv_stream_t*)&rr_tcp.tcp_);
            uv_read_start((uv_stream_t*)&rr_tcp.tcp_,
                // alloc buf cb
                [](uv_handle_t* handle, size_t size, uv_buf_t* buf) {
                    one_rr_tcp* rr = upcast_handle_to_rr_tcp(handle);
                    rr->inbuf_.reserve(size);
                    buf->base = &rr->inbuf_[0];
                    buf->len = size;
                    cout << this_thread::get_id() << ": need " << size << " bytes buffer to read" << endl;
                },
                // complete read cb
                [](uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
                    one_rr_tcp* rr = upcast_handle_to_rr_tcp(handle);
                    rr->work_.data = (void*)rr;
                    rr->nread_ = (size_t)max((ssize_t)0, nread);
                    cout << this_thread::get_id() << ": complete read " << nread << " bytes" << endl;
                    uv_queue_work(uv_default_loop(), &rr->work_,
                        // work routine cb
                        [](uv_work_t* work) {
                            one_rr_tcp* rr = (one_rr_tcp*)work->data;
                            cout << this_thread::get_id() << ": payload work" << endl;
                            sleep(1);
                            rr->wr_buf_ = uv_buf_init(&rr->inbuf_[0], rr->nread_);
                            rr->wr_.bufs = &rr->wr_buf_;
                            uv_write(&rr->wr_, (uv_stream_t*)&rr->tcp_, rr->wr_.bufs, 1,
                                // close cb
                                [](uv_write_t* wr, int status) {
                                    cout << this_thread::get_id() << ": complete write" << endl;
                                    uv_close((uv_handle_t*)wr->handle,
                                        [](uv_handle_t* handle) {
                                            cout << this_thread::get_id() << ": delete rr object" << endl;
                                            delete upcast_handle_to_rr_tcp(handle);
                                        }
                                    );
                                }
                            );
                        },
                        // finalize work cb
                        [](uv_work_t* work, int status) {
                            cout << this_thread::get_id() << ": complete payload work" << endl;
                        }
                    );


                }
            );
        }
    );
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    return 0;
}
