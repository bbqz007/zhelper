#include "zbuffer.h"
#include <string>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <algorithm>

using namespace zhelper;


struct dummy
{
    dummy(size_t sz = sizeof(void*))
    {
        p = zlab_allocator<>::adapt_malloc(sz);
    }
    ~dummy()
    {
        zlab_allocator<>::adapt_free(p);
    }
    void* p;
};

struct dummy2
{
    dummy2(size_t sz = sizeof(void*))
    {
        p = malloc(sz);
    }
    ~dummy2()
    {
        free(p);
    }
    void* p;
};

struct dummy3
{
    dummy3(size_t sz = sizeof(void*))
    {
        p = new char[sz];
    }
    ~dummy3()
    {
        delete p;
    }
    char* p;
};

int main()
{
#if 0
    typedef std::basic_string<char,
                std::char_traits<char>,
                myallocator<char> > zlab_string;
    zlab_string str;
    for (int i = 0; i < 10000; ++i)
        str += "abc";
    //std::cout << str << std::endl;
    zlab_allocator<>::inst().dumpinfo(std::cout);
#endif

    anki3d::SpinLock dummy_queue_spinlock;
#if 1   // using zbuffer
    typedef dummy dummy_type;
    const int kcount = 100000;
#elif 1 // using malloc/free
    typedef dummy2 dummy_type;
    const int kcount = 10000;
#else   // using std::new/std::delete
    typedef dummy3 dummy_type;
    const int kcount = 10000;
#endif // 1

    std::deque<std::shared_ptr<dummy_type> > dummy_queue;
    std::vector<std::thread> threads;
    const int nr = 10;
    threads.reserve(2*nr);
    for (int i = 0; i < nr; ++i)
    {
        threads.push_back(
            std::thread(
                [&](){
                    for (int i = 0; i < kcount; ++i)
                    {
                        std::shared_ptr<dummy_type> dmmy(new dummy_type(std::abs(std::rand()) % (1<<16)));
                        std::lock_guard<anki3d::SpinLock> lck(dummy_queue_spinlock);
                        dummy_queue.push_back(dmmy);
                    }
                }));
    }
    for (int i = 0; i < nr; ++i)
    {
        threads.push_back(
            std::thread(
                [&](){
                    for (int i = 0; i < kcount; ++i)
                    {
                        std::lock_guard<anki3d::SpinLock> lck(dummy_queue_spinlock);
                        if (!dummy_queue.empty())
                            dummy_queue.pop_front();
                    }
                }));
    }
    std::for_each(threads.begin(), threads.end(),
             [](std::thread& thrd)
             {
                 thrd.join();
             });
    return 0;
}
