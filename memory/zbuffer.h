#ifndef __ZHELPER_ZBUFFER_H__
#define __ZHELPER_ZBUFFER_H__
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
#include <memory>
#include <deque>
#include <vector>
#include <mutex>
#include <atomic>
#include <map>
#include <iostream>
#include <iterator>
//http://anki3d.org/spinlock/
namespace anki3d
{

class SpinLock
{
public:
    void lock()
    {
        while(lck.test_and_set(std::memory_order_acquire))
        {}
    }

    void unlock()
    {
        lck.clear(std::memory_order_release);
    }

private:
    std::atomic_flag lck = ATOMIC_FLAG_INIT;
};

} // namespace anki3d

namespace zhelper
{

#define ZHELPER_SLAB_USE_DEQUE 0
#if 0
#define ftracef fprintf
#else
#define ftracef(...)
#endif // 0

struct bulk_free_list
{
    int magic;
    int next;
};

typedef void* (*ztd_malloc_fn)(size_t);
typedef void* (*ztd_realloc_fn)(void*, size_t);
typedef void (*ztd_free_fn)(void*);

struct ztd_mem_methods
{
    static void* malloc(size_t sz) { return ::malloc(sz); }
    static void* realloc(void* p, size_t sz) { return ::realloc(p, sz); }
    static void free(void* p) { ::free(p); }
};

struct zlab_allocator_size_checker
{
    std::vector<uint32_t> checker;
};

template<typename MemMethods = ztd_mem_methods,
    size_t b16 = (1<<20)/16,
    size_t b32 = (1<<20)/32,
    size_t b64 = (1<<20)/64,
    size_t b128 = (1<<20)/128,
    size_t b256 = (1<<20)/256,
    size_t b512 = (1<<20)/512,
    size_t k1 = (1<<20)/(1<<10),
    size_t k4 = (1<<20)/(1<<12),
    size_t k8 = (1<<20)/(1<<13),
    size_t k64 = (1<<20)/(1<<16),
    class Lock = anki3d::SpinLock,
    class LockGuard = std::lock_guard<Lock> >

// zhelper slab allocator
struct zlab_allocator
{
#define kCOUNT 10
#define FREEMAIGC 0xfee0dead
    typedef std::pair<char*, char*> bulk_type;
    std::vector<char> buffer_;
    std::map<char*, int> upper_boundaries_; // lowerb : (...], upperb: [...)
    // zip all the things
    bulk_type bulks_[kCOUNT];
    bulk_free_list freelist_[kCOUNT];
    std::deque<void*> free_[kCOUNT];
    size_t levels_[kCOUNT];
    size_t quotas_[kCOUNT];
    Lock locks_[kCOUNT];
    std::vector<uint16_t> checker_;
    uint16_t* checkers_[kCOUNT];
    char* checker_boundaries_[kCOUNT];
    size_t lacks_[kCOUNT];
    size_t stats_[kCOUNT];
    size_t actxs_[kCOUNT];
    size_t peaks_[kCOUNT];

    ~zlab_allocator()
    {
        for (int i = 0; i < kCOUNT; ++i)
        {
            LockGuard lck(locks_[i]);
            {
                bulk_type& bulk = bulks_[i];
                bulk.second = bulk.first;
                free_[i].clear();
            }
        }
    }
    zlab_allocator()
    : levels_({16, 32, 64, 128, 256, 512, 1024, 4096, 8192, 1<<16})
        , quotas_({b16, b32, b64, b128, b256, b512, k1, k4, k8, k64})
        , lacks_({0})
        , peaks_({0}), stats_({0})
    {
        size_t total_size = 0;
        for (int i = 0; i < kCOUNT; ++i)
            total_size += levels_[i]*quotas_[i];
        buffer_.reserve(total_size);
        buffer_.push_back('\0');
        char* cursor = &buffer_[0];
        upper_boundaries_[cursor] = -1;
        for (int i = 0; i < kCOUNT; ++i)
        {
            freelist_[i].magic = FREEMAIGC | (1 << 16);
            freelist_[i].next = freelist_[i].magic;
            bulks_[i] = bulk_type(cursor, cursor + levels_[i]*quotas_[i]);
            checker_boundaries_[i] = cursor;
            cursor += levels_[i]*quotas_[i];
            upper_boundaries_[cursor] = i;
        }
        size_t total = 0;
        for (int i = 0; i < kCOUNT; ++i)
            total += quotas_[i];
        checker_.resize(total);
        uint16_t* cur = &checker_[0];
        for (int i = 0; i < kCOUNT; ++i)
        {
            checkers_[i] = cur;
            cur += quotas_[i];
        }
    }
    int levels_to_index(size_t level)
    {
        int index = kCOUNT;
        switch (level)
        {
        case 1: case (2): case (4): case(8):case(16):
            index = 0; break;
        case 32:
            index = 1; break;
        case 64:
            index = 2; break;
        case 128:
            index = 3; break;
        case 256:
            index = 4; break;
        case 512:
            index = 5; break;
        case (1<<10):
            index = 6; break;
        case (1<<11): case(1<<12):
            index = 7; break;
        case (1<<13):
            index = 8; break;
        case (1<<14): case (1<<15): case(1<<16): case(1<<17): case(1<<18):
        case (1<<19): case (1<<20):
            index = 9; break;
        }
        return index;
    }
    int size_to_index(size_t sz)
    {
        size_t* found = std::lower_bound(levels_, levels_ + kCOUNT, sz);
        if (found && found < levels_ + kCOUNT)
        {
            //return std::distance(levels_, found);
            return found - (size_t*)levels_;
        }
        return kCOUNT;
    }
    int address_to_index(void* p)
    {
        std::map<char*, int>::iterator it = upper_boundaries_.upper_bound((char*)p);
        if (it == upper_boundaries_.end()
            || it->second == -1)
        {
            return -1;
        }
        return it->second;
    }
    size_t align_to_cpu_long(size_t sz)
    {
        return (sz + ((size_t)sizeof(void*) - 1)) & ~((size_t)sizeof(void*) - 1);
    }
    void* realloc(void* p, size_t sz)
    {
        size_t chk_sz = check_size(p);
        if (chk_sz == 0)
            return MemMethods::realloc(p, sz);
        int idx = address_to_index(p);
        void* newp = p;
        if (sz > levels_[idx])
            newp = allocate(sz);
        if (newp && newp != p)
        {
            std::copy((char*)p, (char*)p + chk_sz, (char*)newp);
        }
        if (newp != p)
            deallocate(p);
        int i = intptr_t((char*)p - checker_boundaries_[idx]) / levels_[idx];
        if (i < quotas_[idx])
            checkers_[idx][i] = sz;
        ftracef(stderr, "Realloc %d -> %d bytes (%p -> %p).\n",
                    chk_sz, sz, p, newp);

        return newp;
    }
    void* allocate(size_t sz, const void *hint = 0)
    {
        ftracef(stderr, "Alloc %d bytes.\n", sz);

        if (sz == 0)
            return NULL;
        if (sz > (1<<16))
            return MemMethods::malloc(align_to_cpu_long(sz));

            // int level = size_to_level(sz);
        int idx = size_to_index(sz);
        const int limit = 2;
        for (int j = 0; j < limit && idx < kCOUNT; ++j, ++idx)
        {
            //if (idx > 8)
                //fprintf(stderr, "*%d\n", sz);
            LockGuard lck(locks_[idx]);
            {
                bulk_type& bulk = bulks_[idx];
                if (bulk.second > bulk.first)
                {
                    bulk.second -= levels_[idx];
                    checkers_[idx][(intptr_t(bulk.second - bulk.first) / levels_[idx])] = sz;
                    ++stats_[idx];
                    peaks_[idx] = std::max(++actxs_[idx], peaks_[idx]);
                    return bulk.second;
                }
                else
                {
                    void* p = __dequeue_free_list(idx);
                    if (p)
                    {
                        checkers_[idx][(intptr_t(bulk.second - bulk.first) / levels_[idx])] = sz;
                        ++stats_[idx];
                        peaks_[idx] = std::max(++actxs_[idx], peaks_[idx]);
                        return p;
                    }
                }
                if (j == 0)
                    ++lacks_[idx];
            }
        }
        return MemMethods::malloc(align_to_cpu_long(sz));
    }
    void deallocate(void* p)
    {
        if (!p)
            return;
        std::map<char*, int>::iterator it = upper_boundaries_.upper_bound((char*)p);
        if (it == upper_boundaries_.end()
            || it->second == -1)
        {
            MemMethods::free(p);
        }
        else
        {
            LockGuard lck(locks_[it->second]);
            __enqueue_free_list(it->second, p);
        }
    }
    void __enqueue_free_list(int index, void* p)
    {
        --actxs_[index];
        bulk_free_list* bfl = (bulk_free_list*)((char*)p + levels_[index]);
        --bfl;
        bfl->magic = FREEMAIGC | (index << 16);
        bfl->next = freelist_[index].next;
        freelist_[index].next = (char*) p - &buffer_[0];
        if (ZHELPER_SLAB_USE_DEQUE)
        {
            free_[index].push_back(p);
        }
    }
    void* __dequeue_free_list(int index)
    {
        void* p = NULL;
        if (ZHELPER_SLAB_USE_DEQUE)
        {
            std::deque<void*>& free = free_[index];
            if (free.empty())
                return NULL;
            p = free.back();
            free.pop_back();
            return p;
        }
        else
        {
            bulk_free_list* head = &freelist_[index];
            if (head->magic == head->next)
                return NULL;
            p = head->next + &buffer_[0];
            bulk_free_list* bfl = (bulk_free_list*)((char*)p + levels_[index]);
            --bfl;
            head->next = bfl->next;
        }
        return p;
    }
    size_t check_size(void* p)
    {
        int idx = address_to_index(p);
        size_t xsz = 0;
        if (idx != -1)
        {
            //xsz = levels_[idx];
            size_t i = intptr_t((char*)p - checker_boundaries_[idx]) / levels_[idx];
            if (i < quotas_[idx])
                xsz = checkers_[idx][i];
        }
        ftracef(stderr, "chksize %d bytes (%p).\n", xsz, p);
        return xsz;
    }
    bool check_pointer(void* p)
    {
        return &buffer_[0] <= (char*) p
                && p < (&buffer_[0] + buffer_.capacity());
    }
    static zlab_allocator& inst()
    {
        static zlab_allocator inst_;
        return inst_;
    }
    static void* adapt_malloc(size_t sz)
    {
        return inst().allocate(sz);
    }
    static void adapt_free(void* p)
    {
        inst().deallocate(p);
    }
    static void* adapt_realloc(void* p, size_t sz)
    {
        return inst().realloc(p, sz);
    }
    static size_t adapt_check_size(void* p)
    {
        return inst().check_size(p);
    }
    void dumpinfo(std::ostream& os)
    {
        os << "zhelper allocator\n";
        os << "levels:\n";
        std::copy(levels_, levels_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\nquotas:\n";
        std::copy(quotas_, quotas_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\nlacks:\n";
        std::copy(lacks_, lacks_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\npeaks:\n";
        std::copy(peaks_, peaks_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\nstats:\n";
        std::copy(stats_, stats_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\nactives:\n";
        std::copy(actxs_, actxs_ + kCOUNT, std::ostream_iterator<size_t>(os, ", "));
        os << "\nbulks begins at:" << (void*)&buffer_[0];
        os << " size of " << buffer_.capacity();
        os << " end at:" << (void*)(&buffer_[0] + buffer_.capacity());
        os << std::endl;
    }
};

template<typename T>
struct myallocator : std::allocator<T>
{
public:
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;

    template<typename _Tp1>
    struct rebind
    {
        typedef myallocator<_Tp1> other;
    };

    pointer allocate(size_type n, const void *hint = 0)
    {
        pointer p = (pointer)zlab_allocator<>::adapt_malloc(n * sizeof(T));
        ftracef(stderr, "Alloc %d bytes (%p).\n", n*sizeof(T), p);
        return p;
    }

    void deallocate(pointer p, size_type n = 1)
    {
        ftracef(stderr, "Dealloc %d bytes (%p).\n", n*sizeof(T), p);
        return zlab_allocator<>::adapt_free((void*)p);
    }
};

} // namespace zhelper

#endif // __ZHELPER_ZBUFFER_H__
