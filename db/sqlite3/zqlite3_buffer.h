#ifndef __ZHELPER_SQLITE3_BUFFER_H__
#define __ZHELPER_SQLITE3_BUFFER_H__

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
#include "zbuffer.h"
#include <sqlite3.h>

namespace zhelper
{

struct ori_sqlite3_mem_methods
{
    static void* xMalloc(int sz)
    {
        ftracef(stderr, "xMalloc %d bytes.\n", sz);
        return methods_.xMalloc(sz);
    }
    static void xFree(void* p)
    {
        methods_.xFree(p);
    }
    static void* xRealloc(void*p, int sz)
    {
        ftracef(stderr, "xRealloc %d bytes (%p) .\n", sz, p);
        return methods_.xRealloc(p, sz);
    }
    static int xSize(void* p)
    {
        int sz = methods_.xSize(p);
        ftracef(stderr, "xSize %d bytes (%p) .\n", sz, p);
        return sz;
    }
    static int xRoundup(int sz)
    {
        int rsz = methods_.xRoundup(sz);
        ftracef(stderr, "xRoundup %d -> %d bytes.\n", sz, rsz);
        return rsz;
    }
    static int xInit(void* p)
    {
        return methods_.xInit(p);
    }
    static void xShutdown(void* p)
    {
        return methods_.xShutdown(p);
    }
    static void initialize()
    {
        methods_2.xMalloc = xMalloc;
        methods_2.xFree = xFree;
        methods_2.xRealloc = xRealloc;
        methods_2.xSize = xSize;
        methods_2.xRoundup = xRoundup;
        methods_2.xInit = xInit;
        methods_2.xShutdown = xShutdown;
        methods_2.pAppData = ori_sqlite3_mem_methods::methods_.pAppData;
    }

    static sqlite3_mem_methods methods_;
    static sqlite3_mem_methods methods_2;
};

sqlite3_mem_methods ori_sqlite3_mem_methods::methods_;
sqlite3_mem_methods ori_sqlite3_mem_methods::methods_2;

#if 1
struct zqlite3_mem_methods_imp
{
    typedef zlab_allocator<zqlite3_mem_methods_imp> zqlite3_allocator;
    static void* xMalloc(int sz)         /* Memory allocation function */
    {
        if (sz < 0)
            return NULL;
        void* p = zqlite3_allocator::adapt_malloc(sz + sizeof(sqlite3_int64));
        if (!p)
            return ori_sqlite3_mem_methods::methods_.xMalloc(sz);
        *(sqlite3_int64*)p = sz;
        ftracef(stderr, "xMalloc %d bytes (%p).\n", sz, p);
        return (sqlite3_int64*)p + 1;
    }
    static void xFree(void* p)          /* Free a prior allocation */
    {
        if (!zqlite3_allocator::inst().check_pointer((sqlite3_int64*)p - 1))
        {
            ori_sqlite3_mem_methods::methods_.xFree(p);
            return;
        }
        ftracef(stderr, "xFree %p \n", (void*)((sqlite3_int64*)p - 1));
        zqlite3_allocator::adapt_free((sqlite3_int64*)p - 1);
    }
    static void* xRealloc(void* p,int sz)  /* Resize an allocation */
    {
        if (sz < 0)
            return p;
        void* newp = NULL;
        if (zqlite3_allocator::inst().check_pointer((sqlite3_int64*)p - 1))
        {
            newp = zqlite3_allocator::adapt_realloc((void*)((sqlite3_int64*)p - 1), sz);
        }
        if (!newp)
        {
            return ori_sqlite3_mem_methods::methods_.xRealloc(p, sz);
        }
        *(sqlite3_int64*)newp = sz;
        return (sqlite3_int64*)newp + 1;
    }
    static int xSize(void* p)           /* Return the size of an allocation */
    {
        if (!p)
            return 0;
        int sz = *((sqlite3_int64*)p - 1);
        ftracef(stderr, "xSize %d bytes (%p) .\n", sz, p);
        return sz;
    }
    static int xRoundup(int sz)          /* Round up request size to allocation size */
    {
        return ori_sqlite3_mem_methods::methods_.xRoundup(sz);
    }
    static int xInit(void* p)           /* Initialize the memory allocator */
    {
        (void)zqlite3_allocator::inst();
        return ori_sqlite3_mem_methods::methods_.xInit(p);
    }
    static void xShutdown(void* p)      /* Deinitialize the memory allocator */
    {
        ori_sqlite3_mem_methods::methods_.xShutdown(p);
    }
    static void initialize()
    {
        methods_.xMalloc = xMalloc;
        methods_.xFree = xFree;
        methods_.xRealloc = xRealloc;
        methods_.xSize = xSize;
        methods_.xRoundup = xRoundup;
        methods_.xInit = xInit;
        methods_.xShutdown = xShutdown;
        methods_.pAppData = ori_sqlite3_mem_methods::methods_.pAppData;
    }
    static void* malloc(size_t sz) { return NULL; }
    static void* realloc(void* p, size_t sz) { return NULL; }
    static void free(void* p) {  }
    static sqlite3_mem_methods methods_;
};
#else
struct zqlite3_mem_methods_imp
{
    typedef zlab_allocator<zqlite3_mem_methods_imp> zqlite3_allocator;
    static void* xMalloc(int sz)         /* Memory allocation function */
    {
        if (sz < 0)
            return NULL;
        void* p = zqlite3_allocator::adapt_malloc(sz);
        ftracef(stderr, "xMalloc %d bytes (%p).\n", sz, p);
        return p;
    }
    static void xFree(void* p)          /* Free a prior allocation */
    {
        ftracef(stderr, "xFree %p \n", p);
        zqlite3_allocator::adapt_free(p);
    }
    static void* xRealloc(void* p,int sz)  /* Resize an allocation */
    {
        if (sz < 0)
            return p;
        void* newp = zqlite3_allocator::adapt_realloc(p, sz);
        ftracef(stderr, "xRealloc %d bytes (%p -> %p). \n", sz, p, newp);
        return newp;
    }
    static int xSize(void* p)           /* Return the size of an allocation */
    {
        int xsz = zqlite3_allocator::adapt_check_size(p);
        if (0 == xsz)
            xsz = ori_sqlite3_mem_methods::methods_.xSize(p);
        return xsz;
    }
    static int xRoundup(int sz)          /* Round up request size to allocation size */
    {
        return ori_sqlite3_mem_methods::methods_.xRoundup(sz);
    }
    static int xInit(void*)           /* Initialize the memory allocator */
    {
        (void)zqlite3_allocator::inst();
        return ori_sqlite3_mem_methods::methods_.xInit(
                    ori_sqlite3_mem_methods::methods_.pAppData);
    }
    static void xShutdown(void*)      /* Deinitialize the memory allocator */
    {
        ori_sqlite3_mem_methods::methods_.xShutdown(
                    ori_sqlite3_mem_methods::methods_.pAppData);
    }
    static void initialize()
    {
        methods_.xMalloc = xMalloc;
        methods_.xFree = xFree;
        methods_.xRealloc = xRealloc;
        methods_.xSize = xSize;
        methods_.xRoundup = xRoundup;
        methods_.xInit = xInit;
        methods_.xShutdown = xShutdown;
        methods_.pAppData = ori_sqlite3_mem_methods::methods_.pAppData;
    }
    static void* malloc(size_t sz) { return ori_sqlite3_mem_methods::methods_.xMalloc(sz); }
    static void* realloc(void* p, size_t sz) { return ori_sqlite3_mem_methods::methods_.xRealloc(p, sz); }
    static void free(void* p) { ori_sqlite3_mem_methods::methods_.xFree(p); }

    static sqlite3_mem_methods methods_;
};
#endif
sqlite3_mem_methods zqlite3_mem_methods_imp::methods_;

typedef zqlite3_mem_methods_imp::zqlite3_allocator zqlite3_allocator;
} // namespace zhelper

#endif // __ZHELPER_SQLITE3_BUFFER_H__
