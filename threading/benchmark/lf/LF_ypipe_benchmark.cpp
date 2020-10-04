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

template<class T>
void payload(T&)
{

}

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
                        {
                            // avoid from paralleling cond.notify and cond.wait
                            lock_guard<mutex> lgd2(cvlock);
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
                                    lock_guard<mutex> lgd2(cvlock);
                                    // read again, maybe a notify done before.
                                    if (p0.read(&j))
                                        break;
                                    can_read.wait(cvlock);
                                }

                               if (!p0.read(&j))
                                    continue;
                                notify = p0.check_read();
                           }
                           if (notify)
                                can_read.notify_one();
                            break;
                       }
                       // cout << j << "\n";
                       payload(j);
                   }

                        //p0.pop_front();
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
                                // the difference with BM_ypipe
                                // once p0 is empty, all reader awake from rlock and wait for cond
                                can_read.wait(rlock);
                               if (!p0.read(&j))
                                    continue;
                                notify = p0.check_read();
                           }
                           if (notify)
                                can_read.notify_one();
                            break;
                       }
                       // cout << j << "\n";
                       payload(j);
                   }

                        //p0.pop_front();
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
                                   continue;
                                   j = p0.front();
                               p0.pop_front();
                               notify = !p0.empty();
                           }
                           //if (notify)
                                //can_read.notify_one();
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
                           //if (notify)
                                //can_read.notify_one();
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
                               if (leader)
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

                               //if (p0.empty())
                               //     continue;

                                //notify = !p0.empty();
                           }
                           //if (notify)
                               // can_read.notify_one();
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

BENCHMARK(BM_yield0);
BENCHMARK(BM_cvnotify0);
BENCHMARK(BM_yield);
BENCHMARK(BM_yield2);
BENCHMARK(BM_deque0);
BENCHMARK(BM_deque);
BENCHMARK(BM_deque_lf);
BENCHMARK(BM_ypipe2);
BENCHMARK(BM_ypipe);

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();
}
