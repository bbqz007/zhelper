/**
 * MIT License
 *
 *  Copyright (c) 2020 bbqz007 <cnblogs.com/bbqzsl, github.com/bbqz007>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *     SOFTWARE.
 *
 */

#include "ypipe.hpp"
#include <string.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <benchmark/benchmark.h>

void BM_yield0(benchmark::State& state)
{
    using namespace std;
    while (state.KeepRunning())
    for (int i = 0; i < 10000; ++i)
    {
        this_thread::yield();
    }
}

void BM_cvnotify0(benchmark::State& state)
{
    using namespace std;
    condition_variable_any can_read;
    while (state.KeepRunning())
    for (int i = 0; i < 10000; ++i)
    {
        can_read.notify_one();
    }
}

#define DEBUG_CHECK_STAT 0
static unsigned char payload_stat[100000];

template<class T>
void payload(T& j)
{
#if DEBUG_CHECK_STAT
    ++payload_stat[j];
#endif
    (void) j;
#if 0
    for (int y = 0; y < 4; ++y)
    {
        /// mock a io, rpc, access database
        std::this_thread::yield();
        int x = 10000 % rand();
        for (int i = 0; i < x; ++i)
            (void)i;
    }
#elif 0
    /// heavy payload
    int x = 10000 % rand();
    x *= 100;
    for (int i = 0; i < x; ++i)
        (void)i;
#endif
}

void __check_payload_stat(int percnt, int cnt)
{
    for (int i = 0; i < cnt; ++i)
    {
        if (payload_stat[i] != percnt)
            std::cerr << "bug: " << payload_stat[i] << "@" << i << std::endl;
    }
}

void __reset_payload_stat()
{
    memset(payload_stat, 0, sizeof(payload_stat));
}

#if DEBUG_CHECK_STAT
#define    check_payload_stat(i, j) __check_payload_stat(i, j)
#define    reset_payload_stat() __reset_payload_stat()
#else
#define    check_payload_stat(i, j)
#define    reset_payload_stat()
#endif

void BM_yield(benchmark::State& state)
{
    using namespace std;
    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    this_thread::yield();
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    this_thread::yield();
                    // cout << j << "\n";
                }

                //p0.pop_front();
            })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}

void BM_yield2(benchmark::State& state)
{
    using namespace std;
    while (state.KeepRunning())
    {
        condition_variable_any can_read;
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    //this_thread::yield();
                    can_read.notify_one();
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    //this_thread::yield();
                    can_read.notify_one();
                    // cout << j << "\n";
                }

                //p0.pop_front();
            })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}

void BM_ypipe(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    condition_variable_any can_read;
    bool all_quit = false;
    //deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    p0.write(i, false);
                    p0.flush();
                    {
                        /// avoid from paralleling cond.notify and cond.wait
                        /// or queue is a monitor object.
                        lock_guard<mutex> lgd2(qlock);
                        can_read.notify_one();
                    }
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int bugcnt = 0;
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            if (p0.read(&j))
                                break;
                            {
                                // fix-me: a writer notify and a reader wait are parallel,
                                lock_guard<mutex> lgd2(qlock);
                                // read again, maybe a notify done before.
                                if (p0.read(&j))
                                    break;
                                can_read.wait(qlock);
                                while (!p0.read(&j))
                                {
                                    /// !!!
                                    /// writer flush and get interrupt before notify.
                                    /// at the same time, all readers are doing payload, then one finish and read the queue.
                                    /// the next reader block and wait for queue signal.
                                    /// the interrupted writer return user space and notify.
                                    /// the blocking reader wake up and read an empty queue here.
                                    ++bugcnt;
                                    can_read.wait(qlock);
                                }
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
                if (bugcnt)
                {
                    /// how many time the writers were interrupted before notify.
                    //cerr << "bugs :" << bugcnt << endl;
                }
        })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}

void BM_ypipe_s(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    condition_variable_any can_read;
    bool all_quit = false;
    //deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    p0.write(i, false);
                    p0.flush();
                    {
                        /// avoid from paralleling cond.notify and cond.wait
                        lock_guard<mutex> lgd2(qlock);
                        can_read.notify_one();
                    }
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            if (p0.read(&j))
                                break;
                            {
                                // fix-me: a writer notify and a reader wait are parallel,
                                while (!qlock.try_lock());
                                lock_guard<mutex> lgd2(qlock, std::adopt_lock);

                                /// read again, maybe a notify done before.
                                if (p0.read(&j))
                                    break;
                                can_read.wait(qlock);
                                while (!p0.read(&j))
                                    can_read.wait(qlock);
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
        })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}



void BM_ypipe2(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    ypipe_i0 p0;
    mutex rlock, wlock;
    mutex cvlock;
    condition_variable_any can_read;
    bool all_quit = false;
    //deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    p0.write(i, false);
                    p0.flush();
                    can_read.notify_one();
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;

                        {
                            lock_guard<mutex> lgd(rlock);
                            if (p0.read(&j))
                                break;
                            /// the difference with BM_ypipe
                            /// once p0 is empty, all reader awake from rlock and wait for cond
                            can_read.wait(rlock);
                            while (!p0.read(&j))
                                can_read.wait(rlock);
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}



void BM_deque(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    condition_variable_any can_read;
    deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int bugcnt = 0;
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;

                        {
                            lock_guard<mutex> lgd(rlock);
                            lock_guard<mutex> lgd2(qlock);
                            if (!p0.empty())
                            {
                                j = p0.front();
                                p0.pop_front();
                                break;
                            }

                            can_read.wait(qlock);
                            if (p0.empty())
                            {
                                ++bugcnt;
                                continue;
                            }
                            j = p0.front();
                            p0.pop_front();
                            notify = !p0.empty();
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
                if (bugcnt)
                {
                    cerr << "bugs :" << bugcnt << endl;
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_deque0(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    condition_variable_any can_read;
    deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    //lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }

            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            //lock_guard<mutex> lgd(rlock);
                            lock_guard<mutex> lgd2(qlock);
                            if (!p0.empty())
                            {
                                j = p0.front();
                                p0.pop_front();
                                break;
                            }

                            can_read.wait(qlock);
                            if (p0.empty())
                                continue;
                            j = p0.front();
                            p0.pop_front();
                            notify = !p0.empty();
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_deque_lf(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    bool leader = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            /// bug: A after process arrived here
                            ///      B notify waitup C
                            ///      A steal the rlock and become leader again
                            ///      C awake up after A, no idea about the steal.
//                               if (leader)
//                               {
//                                   ++follower;
//                                   can_lead.wait(rlock);
//                               }
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                            }

                            leader = true;
                        }

                        {
                            lock_guard<mutex> lgd2(qlock);
                            if (!p0.empty())
                            {
                                j = p0.front();
                                p0.pop_front();
                                //break;
                            }
                            else
                            {
                                can_read.wait(qlock);
                                j = p0.front();
                                p0.pop_front();
                            }
                        }

                        {
                            lock_guard<mutex> lgd(rlock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_deque2_lf(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    bool leader = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    deque_i p2, p1;
    deque_i* pr = &p1;
    deque_i* pw = &p2;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    pw->push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                                if (!leader)
                                    break;
                            }

                            leader = true;
                        }

                        {
                            if (!pr->empty())
                            {
                                j = pr->front();
                                pr->pop_front();
                                //break;
                            }
                            else
                            {
                                deque_i* pc = NULL;
                                {
                                    lock_guard<mutex> lgd2(qlock);
                                    if (!pw->empty())
                                    {
                                        swap(pr, pw);
                                        pc = pr;
                                    }
                                    else
                                    {
                                        can_read.wait(qlock);
                                        if (pw->empty())
                                            cerr << "bug" << endl;
                                        j = pw->front();
                                        pw->pop_front();
                                        if (!pw->empty())
                                            swap(pr, pw);
                                    }
                                }
                                if (pc)
                                {
                                    j = pc->front();
                                    pc->pop_front();
                                    //break;
                                }
                            }
                        }

                        {
                            lock_guard<mutex> lgd(rlock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_deque2_lf_s(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    bool leader = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    deque_i p2, p1;
    deque_i* pr = &p1;
    deque_i* pw = &p2;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < 10000; ++i)
                {
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    pw->push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                            }

                            leader = true;
                        }

                        {
                            if (!pr->empty())
                            {
                                j = pr->front();
                                pr->pop_front();
                            }
                            else
                            {
                                deque_i* pc = NULL;
                                {
                                    lock_guard<mutex> lgd2(qlock);
                                    if (!pw->empty())
                                    {
                                        swap(pr, pw);
                                        pc = pr;
                                    }
                                    else
                                    {
                                        can_read.wait(qlock);
                                        if (pw->empty())
                                            cerr << "bug" << endl;
                                        j = pw->front();
                                        pw->pop_front();
                                        if (!pw->empty())
                                            swap(pr, pw);
                                    }
                                }
                                if (pc)
                                {
                                    j = pc->front();
                                    pc->pop_front();
                                }
                            }
                        }

                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_ypipe_lf(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    ypipe_i0 p0;
    mutex rlock, wlock, buglock;
    mutex qlock;
    volatile bool leader = false;
    bool promote = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    //deque_i p0;

    while (state.KeepRunning())
    {
        reset_payload_stat();
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                  for (int i = 0; i < 10000; ++i)
                  {
                        lock_guard<mutex> lgd(wlock);
                        p0.write(i, false);
                        p0.flush();
                        {
                            // avoid from paralleling cond.notify and cond.wait
                            lock_guard<mutex> lgd2(qlock);
                            can_read.notify_one();
                        }
                  }

            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                            }
                            leader = true;
                        }

                        if (1)
                        {
                            if (!p0.read(&j))
                            {
                                /// fix-me: a writer notify and a reader wait are parallel,
                                /// yes, we use monitor object pattern here.
                                lock_guard<mutex> lgd2(qlock);
                                /// read again, maybe a notify done before.
                                /// some difference with BM_ypipe,
                                if (!p0.read(&j))
                                {
                                    can_read.wait(qlock);
                                    bool bug = false;
                                    while (!p0.read(&j))
                                    {
                                        // bug = true;
                                        // cerr << "q bug pre " << j << endl;

                                        /// !!!
                                        /// This is not a bug?
                                        /// a writer flush, and interrupted before notify
                                        /// a leader read, and the next leader block and wait for queue event.
                                        /// the interrupted writer return user space and notify, but the message is already read.
                                        /// the blocking leader wake up and read an empty queue.

                                        /// before sleep, we try our effort again to avoid sleeping.
                                        if (!p0.check_read())
                                            can_read.wait(qlock);
                                    }

                                    if (bug)
                                    {
                                        // cerr << "q bug on " << j << endl;
                                    }
                                }
                            }
                            notify = p0.check_read();
                        }
                        /// implement 2
                        else if (1)
                        {
                            if (!p0.read(&j))
                            {
                                /// fix-me: a writer notify and a reader wait are parallel,
                                lock_guard<mutex> lgd2(qlock);
                                /// read again, maybe a notify done before.
                                if (!p0.read(&j))
                                {
                                    can_read.wait(qlock);
                                    while (!p0.read(&j))
                                    {
                                        can_read.wait(qlock);
                                    }
                                    notify = p0.check_read();
                                }
                            }
                        }
                        /// implement 3
                        else
                        {
                            while (1)
                            {
                                bool notify = false;
                                {
                                    if (p0.read(&j))
                                        break;
                                    {
                                        // fix-me: a writer notify and a reader wait are parallel,
                                        lock_guard<mutex> lgd2(qlock);
                                        // read again, maybe a notify done before.
                                        if (p0.read(&j))
                                            break;
                                        can_read.wait(qlock);
                                    }

                                    if (!p0.read(&j))
                                    {
                                        //++bugcnt;
                                        continue;
                                    }
                                    notify = p0.check_read();
                                }

                                break;
                            }
                        }

                        {
                            /// to-fix-me:
                            /// race condition when a leader want to peekup a follower,
                            ///                   there may already be some processor want to know if it can be a leader.
                            lock_guard<mutex> lgd(rlock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }


            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
            if (p0.check_read())
                cerr << "qe bug" << endl;
            check_payload_stat(1, 100);
        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_deque_lf_s(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    //ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    bool leader = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                  for (int i = 0; i < 10000; ++i)
                  {
                        lock_guard<mutex> lgd(wlock);
                        lock_guard<mutex> lgd2(qlock);
                        p0.push_back(i);
                        can_read.notify_one();
                  }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                            }

                            leader = true;
                        }


                        {
                            lock_guard<mutex> lgd2(qlock);
                            if (!p0.empty())
                            {
                                j = p0.front();
                                p0.pop_front();
                            }
                            else
                            {
                                can_read.wait(qlock);
                                j = p0.front();
                                p0.pop_front();
                            }
                        }

                        /// fix-me: try lock (spinlock) against sleeping.
                        /// race condition when a leader want to peekup a follower,
                        ///                   there may already be some processor want to know if it can be a leader.
                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

void BM_ypipe_lf_s(benchmark::State& state)
{
    using namespace zmq;
    using namespace std;
    typedef ypipe_t<int, 128> ypipe_i0;
    typedef deque<int> deque_i;
    ypipe_i0 p0;
    mutex rlock, wlock;
    mutex qlock;
    bool leader = false;
    bool promote = false;
    int follower = 0;
    condition_variable_any can_read;
    condition_variable_any can_lead;
    //deque_i p0;

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                  for (int i = 0; i < 10000; ++i)
                  {
                        lock_guard<mutex> lgd(wlock);
                        p0.write(i, false);
                        p0.flush();
                        {
                            // avoid from paralleling cond.notify and cond.wait
                            lock_guard<mutex> lgd2(qlock);
                            can_read.notify_one();
                        }
                  }
            })));

        for (int cnt = 0; cnt < 10; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            while (leader)
                            {
                                ++follower;
                                can_lead.wait(rlock);
                                if (!leader)
                                    break;
                            }
                            leader = true;
                        }


                        {
                            while (1)
                            {
                                bool notify = false;
                                {
                                    //lock_guard<mutex> lgd(rlock);
                                    if (p0.read(&j))
                                        break;
                                    {
                                        // fix-me: a writer notify and a reader wait are parallel,
                                        lock_guard<mutex> lgd2(qlock);
                                        // read again, maybe a notify done before.
                                        if (p0.read(&j))
                                            break;
                                        can_read.wait(qlock);
                                        while (!p0.read(&j))
                                            can_read.wait(qlock);
                                    }
                                }
                                break;
                            }
                        }

                        {
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
                            leader = false;
                            if (follower)
                            {
                                --follower;
                                can_lead.notify_one();
                            }
                        }
                        break;
                    }
                    // cout << j << "\n";
                    payload(j);
                }
            })));
        try
        {
            for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });

        }
        catch (exception& e)
        {
            cout << e.what() << endl;
        }
    }
}

BENCHMARK(BM_yield0);
BENCHMARK(BM_cvnotify0);
BENCHMARK(BM_yield);
BENCHMARK(BM_yield2);
BENCHMARK(BM_deque0);
BENCHMARK(BM_deque);
BENCHMARK(BM_deque_lf);
BENCHMARK(BM_deque_lf_s);
BENCHMARK(BM_deque2_lf);
BENCHMARK(BM_deque2_lf_s);
BENCHMARK(BM_ypipe2);
BENCHMARK(BM_ypipe);
BENCHMARK(BM_ypipe_s);
BENCHMARK(BM_ypipe_lf);
BENCHMARK(BM_ypipe_lf_s);

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();
}
