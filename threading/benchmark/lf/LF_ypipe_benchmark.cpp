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

//#define WORKLOAD_WITH_REDIS 1
//#define WORKLOAD_WITH_MEMCACHE 1
//#define WORKLOAD_WITH_MEMCACHE_USE_BINARY_KEY 1
//#define WORKLOAD_WITH_MEMCACHE_ON_UDP 1

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
#ifdef WORKLOAD_WITH_REDIS
#include <hiredis/hiredis.h>
#endif // WORKLOAD_WITH_REDIS
#ifdef WORKLOAD_WITH_MEMCACHE
#include <libmemcached/memcached.hpp>
#include <libmemcached/memcached.h>
#endif // WORKLOAD_WITH_MEMCACHE

#define ON 1
#define OFF 0

/// Z#20211012 macro DEPRECATED_USE_SPINLOCK
///  
#define DEPRECATED_USE_SPINLOCK OFF



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
/// mock affine base memory access
static const int affine_mem_cnt = 12;
static const int affine_L3_size = 3*(1<<20);
static char affine_mem_r[(affine_mem_cnt+1)*affine_L3_size];
static char affine_mem_w[(affine_mem_cnt+1)*affine_L3_size];
static volatile int affine_mem_cur = 0;
thread_local int tls_id;

#ifdef WORKLOAD_WITH_MEMCACHE
using namespace memcache;
thread_local memcache::Memcache* tls_memcache = 0;
static const char* memcache_host = "192.168.43.1";
static int memcache_port = 11211;
static int memcache_udp_port = 11222;
#endif // WORKLOAD_WITH_MEMCACHE


#ifdef WORKLOAD_WITH_REDIS
thread_local redisContext* tls_redis = 0;
static const char* redis_host = "192.168.43.1";
static int redis_port = 6379;
#endif // WORKLOAD_WITH_REDIS

void rthread_init_local()
{
#ifdef WORKLOAD_WITH_REDIS
    tls_redis = redisConnect(redis_host, redis_port);
#endif // WORKLOAD_WITH_REDIS
#ifdef WORKLOAD_WITH_MEMCACHE
    tls_memcache = new memcache::Memcache;
# ifdef WORKLOAD_WITH_MEMCACHE_ON_UDP
    tls_memcache->addServer(memcache_host, memcache_udp_port);
    tls_memcache->setBehavior(MEMCACHED_BEHAVIOR_USE_UDP, 1);
# else
    tls_memcache->addServer(memcache_host, memcache_port);
# endif
# ifdef WORKLOAD_WITH_MEMCACHE_USE_BINARY_KEY
    tls_memcache->setBehavior(MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 1);
# endif
#endif // WORKLOAD_WITH_MEMCACHE
}

void rthread_free_local()
{
#ifdef WORKLOAD_WITH_REDIS
    redisFree(tls_redis);
    tls_redis = 0;
#endif // WORKLOAD_WITH_REDIS
#ifdef WORKLOAD_WITH_MEMCACHE
    delete tls_memcache;
    tls_memcache = 0;
#endif // WORKLOAD_WITH_MEMCACHE
}

#if defined(WORKLOAD_WITH_REDIS) || defined(WORKLOAD_WITH_MEMCACHE)
#define N_TOTAL_MSG 1000
#else
#define N_TOTAL_MSG 100000
#endif // WORKLOAD_WITH_REDIS || WORKLOAD_WITH_MEMCACHE
#define N_RTHREADS 4
#define N_RMSG_PER_THREAD (N_TOTAL_MSG/N_RTHREADS)
#define N_WTHREADS 4
#define N_WMSG_PER_THREAD (N_TOTAL_MSG/N_WTHREADS)

#if (N_RTHREADS*N_RMSG_PER_THREAD) != (N_WTHREADS*N_WMSG_PER_THREAD)
#error "(N_RTHREADS*N_RMSG_PER_THREAD) != (N_WTHREADS*N_WMSG_PER_THREAD)"
#endif

template<class T>
void mock_affine_write(T& j, int size, int policy)
{
    if (1 == policy)
    {
        int cur = affine_mem_cur++;
        cur %= affine_mem_cnt;
        char* p = affine_mem_w + cur * affine_L3_size + (rand() % affine_L3_size);
        memset(p, cur, size);
    }
    else if (2 == policy)
    {

    }
}

/// affine policy
/// 0: non
/// 1: bad, writer thread and reader thread access different memory address
/// 2: so so, no writer accession. reader thread write and read the same memory locations.
/// 3: good, no writer accession. reader thread has private memory locations.
/// 4: very good, no writer accession. reader thread only use stack.
template<class T>
int mock_affine_read(T& j, int size, int policy)
{
    int sum = 0;
    if (1 == policy)
    {
        int cur = affine_mem_cur++;
        cur %= affine_mem_cnt;
        char* p = affine_mem_r + cur * affine_L3_size + (rand() % affine_L3_size);
        for (int i = 0; i < size; ++i)
        {
            //(void) (*p == '\0');
            /// avoid -O2 optimization
            sum += *p;
            ++p;
        }
    }
    else if (2 == policy)
    {
        int cur = affine_mem_cur++;
        cur %= affine_mem_cnt;
        char* p = affine_mem_r + cur * affine_L3_size + (rand() % affine_L3_size);
        memset(p, cur, size);

        for (int i = 0; i < size; ++i)
        {
            //(void) (*p == '\0');
            sum += *p;
            ++p;
        }
    }
    else if (3 == policy)
    {
        int cur = tls_id;
        cur %= affine_mem_cnt;
        char* p = affine_mem_r + cur * affine_L3_size + (rand() % affine_L3_size);
        memset(p, cur, size);

        for (int i = 0; i < size; ++i)
        {
            //(void) (*p == '\0');
            sum += *p;
            ++p;
        }
    }
    else if (4 == policy)
    {
        char buf[1<<16];
        char* p = buf;
        memset(p, 0, size);

        for (int i = 0; i < size; ++i)
        {
            //(void) (*p == '\0');
            sum += *p;
            ++p;
        }
    }
    return sum;
}

template<class T>
int payload(T& j, int size = 0, int policy = 0)
{
    mock_affine_read(j, size, policy);
#if DEBUG_CHECK_STAT
    ++payload_stat[j];
#endif
#ifdef WORKLOAD_WITH_REDIS
    if (tls_redis)
    {
        for (int y = 0; y < 2; ++y)
        {
            redisReply* reply;
            reply = (redisReply*)redisCommand(tls_redis,"SET %d %d", j, j);
            freeReplyObject(reply);
            reply = (redisReply*)redisCommand(tls_redis,"GET %d %d", j);
            freeReplyObject(reply);
        }
    }
#endif // WORKLOAD_WITH_REDIS
#ifdef WORKLOAD_WITH_MEMCACHE
    if (tls_memcache)
    {
        for (int y = 0; y < 2; ++y)
        {
            char* res = 0;
            size_t reslen = 0;
            memcached_return_t err;
            char key[64];
            sprintf(key, "%d", j);
            memcached_set((memcached_st*)tls_memcache->getImpl(),
# ifndef WORKLOAD_WITH_MEMCACHE_USE_BINARY_KEY
                          (const char*)key, strlen(key),
                          (const char*)key, strlen(key),
# else
                          (const char*)&j, sizeof(j),
                          (const char*)&j, sizeof(j),
# endif
                          time_t(0), 0);
            res = memcached_get((memcached_st*)tls_memcache->getImpl(),
# ifdef WORKLOAD_WITH_MEMCACHE_USE_BINARY_KEY
                                  (const char*)&j, sizeof(j),
# else
                                  (const char*)key, strlen(key),
# endif
                                  &reslen, 0, &err);
            free(res);
        }
    }
#endif // WORKLOAD_WITH_MEMCACHE
    (void) j;
#if 0
    for (int y = 0; y < 4; ++y)
    {
        /// mock a io, rpc, access database
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::this_thread::yield();
        int x = 10000 % rand();
        for (int i = 0; i < x; ++i)
            (void)i;
    }
#elif 0
    /// heavy payload
    {
        int x = 10000 % rand();
        x *= 1;
        register int y = 0;
        for (int i = 0; i < x; ++i)
            /// avoid -O2 optimization
            y = i + 1 - y;
        y = y + 1;
        return y;
    }

#endif
    return 0;
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
				tls_id = cnt;
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
				tls_id = cnt;
				rthread_init_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
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

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int bugcnt = 0;
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            if (p0.read(&j))
                                break;
                            {
                                /// fix-me: a writer notify and a reader wait are parallel,
                                lock_guard<mutex> lgd2(qlock);
                                /// read again, maybe a notify done before.
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
                    payload(j, affine_size, affine_policy);
                }
                if (bugcnt)
                {
                    /// how many time the writers were interrupted before notify.
                    //cerr << "bugs :" << bugcnt << endl;
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
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

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
                            lock_guard<mutex> lgd(rlock);
                            if (p0.read(&j))
                                break;
                            {
                                /// avoid sleeping if a writer is notifying.
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
        })));
        for_each(thrds.begin(), thrds.end(), [](shared_ptr<thread>& thr){ thr->join(); });
    }
}



void BM_ypipe2(benchmark::State& state)
{
    /// this is a bad implement version of BM_ypipe
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    p0.write(i, false);
                    p0.flush();
                    /// a problem would happen up here,
                    /// can_read's notify is not under a lock which can_read wait for.
                    /// wait after notify, and then no notify any more.
                    can_read.notify_one();
                }

                //p0.push_back(i);
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int bugcnt = 0;
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                if (bugcnt)
                {
                    cerr << "bugs :" << bugcnt << endl;
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    //lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }

            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    pw->push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    pw->push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
#if DEPRECATED_USE_SPINLOCK == ON
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
#else
                            lock_guard<mutex> lgd(rlock);
#endif
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        reset_payload_stat();
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
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

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
                    lock_guard<mutex> lgd(wlock);
                    lock_guard<mutex> lgd2(qlock);
                    p0.push_back(i);
                    can_read.notify_one();
                }
            })));

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
#if DEPRECATED_USE_SPINLOCK == ON
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
#else
                            lock_guard<mutex> lgd(rlock);
#endif
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

    int affine_size = state.range(0);
    int affine_policy = state.range(1);

    while (state.KeepRunning())
    {
        vector<shared_ptr<thread> > thrds;
        for (int cnt = 0; cnt < N_WTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                for (int i = 0; i < N_WMSG_PER_THREAD; ++i)
                {
                    mock_affine_write(i, affine_size, affine_policy);
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

        for (int cnt = 0; cnt < N_RTHREADS; ++cnt)
        thrds.push_back(shared_ptr<thread>(
            new thread([&](){
                int j = 0;
				tls_id = cnt;
				rthread_init_local();
                for (int i = 0; i < N_RMSG_PER_THREAD; ++i)
                {
                    while (1)
                    {
                        bool notify = false;
                        {
#if DEPRECATED_USE_SPINLOCK == ON
                            while (!rlock.try_lock());
                            lock_guard<mutex> lgd(rlock, std::adopt_lock);
#else
                            lock_guard<mutex> lgd(rlock);
#endif
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
                    payload(j, affine_size, affine_policy);
                }
                rthread_free_local();
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

#define BENCHMARK_APPLY_ARGS(bm) \
    BENCHMARK(bm)->Args({0,0}) \
            ->Args({100,1}) \
            ->Args({100,2}) \
            ->Args({100,3}) \
            ->Args({100,4}) \
            ->Args({1024,1}) \
            ->Args({1024,2}) \
            ->Args({1024,3}) \
            ->Args({1024,4}) \
            ->Args({8192,1}) \
            ->Args({8192,2}) \
            ->Args({8192,3}) \
            ->Args({8192,4}) \
            ->Args({1<<14,1}) \
            ->Args({1<<14,2}) \
            ->Args({1<<14,3}) \
            ->Args({1<<14,4}) \

BENCHMARK(BM_yield0);
BENCHMARK(BM_cvnotify0);
BENCHMARK(BM_yield);
BENCHMARK(BM_yield2);
BENCHMARK_APPLY_ARGS(BM_deque0);
BENCHMARK_APPLY_ARGS(BM_deque);
BENCHMARK_APPLY_ARGS(BM_deque_lf);
BENCHMARK_APPLY_ARGS(BM_deque_lf_s);
BENCHMARK_APPLY_ARGS(BM_deque2_lf);
BENCHMARK_APPLY_ARGS(BM_deque2_lf_s);
//BENCHMARK_APPLY_ARGS(BM_ypipe2);
BENCHMARK_APPLY_ARGS(BM_ypipe);
BENCHMARK_APPLY_ARGS(BM_ypipe_s);
BENCHMARK_APPLY_ARGS(BM_ypipe_lf);
BENCHMARK_APPLY_ARGS(BM_ypipe_lf_s);

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();
}
