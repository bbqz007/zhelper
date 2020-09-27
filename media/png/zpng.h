#ifndef __ZHELPER_LIBPNG_H__
#define __ZHELPER_LIBPNG_H__
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
 *    The above copyright notice and this permission notice shall be included in all 
 *    copies or substantial portions of the Software. 
 *     
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 *     SOFTWARE.
 *     */

#include <png.h>
#include <vector>
#include <functional>
#include <atomic>

namespace zhelper
{
namespace zpng
{

class zpng_context;
class zpng_reader;
class zpng_writer;
class zpng_header;
class zpng_trycatch;

typedef png_infop zpng_headerp;

class zpng_trycatch
{
public:
    zpng_trycatch(png_structp ctx) : ctx_(ctx),
            lasterror_(0), executing_(false)
    {

    }
    typedef std::function<void(void)> tryF;
    typedef std::function<void(int)> catchF;
    int _catch(std::function<void(int)> catch_)
    {
        executing_ = true;
        lasterror_ = setjmp(png_jmpbuf(ctx_));
        if (0 == lasterror_)
            try_();
        else
            catch_(lasterror_);
        executing_ = false;
        return lasterror_;
    }
    bool on() { return executing_; }
private:
    friend class zpng_context;
    std::function<void(void)> try_;
    png_structp ctx_;
    int lasterror_;
    bool executing_;
};

class zpng_context
{
public:
    ~zpng_context()
    {
        if (memio_)
            memio_ = NULL;  // not managed
        if (filedesc_)
            fclose(filedesc_);
        filedesc_ = NULL;
    }
    zpng_context() : ctx_(0), hdr_(0)
        , lasterror_(0), filedesc_(0)
        , memio_(0), pos_(0)
        , trycatch_(ctx_) {}
    bool ok () { return ctx_ != NULL; }
    zpng_trycatch& _try(const zpng_trycatch::tryF& F)
    {
        trycatch_.ctx_ = ctx_;
        trycatch_.try_ = F;
        return trycatch_;
    }
    int get_lasterror() { return trycatch_.lasterror_; }

    // getter
    png_uint_32 image_height() { return png_get_image_height(ctx_, hdr_); }
    png_uint_32 image_width() { return png_get_image_width(ctx_, hdr_); }
    png_uint_32 rowbytes() { return png_get_rowbytes(ctx_, hdr_); }
    png_byte color_type() { return png_get_color_type(ctx_, hdr_); }
    png_byte bit_depth() { return png_get_bit_depth(ctx_, hdr_); }
    // setter
    void sig_bytes(int bytes) { png_set_sig_bytes(ctx_, bytes); }
    void set_IHDR (png_uint_32 width, png_uint_32 height,
                   int bit_depth, int  color_type,
                   int  interlace_type = PNG_INTERLACE_NONE,
                   int compression_type = PNG_COMPRESSION_TYPE_DEFAULT,
                   int filter_type = PNG_FILTER_TYPE_BASE)
                   {
                       png_set_IHDR(ctx_, hdr_, width, height, bit_depth, color_type,
                                    interlace_type, compression_type, filter_type);
                   }
    void set_compression_level(int level) { png_set_compression_level(ctx_, level); }
    void set_compression_mem_level(int level) { png_set_compression_mem_level(ctx_, level); }
    void set_compression_method(int method) { png_set_compression_method(ctx_, method); }
    void set_compression_strategy(int strategy) { png_set_compression_strategy(ctx_, strategy); }
    void set_filter(int method, int filter) { png_set_filter(ctx_, method, filter); }
    void set_interlace_handling() { png_set_interlace_handling(ctx_); }
    void set_lendian() { png_set_swap(ctx_); }
    void set_bgr() { png_set_bgr(ctx_); }
protected:
    bool open()
    {
        if (filedesc_ == NULL)
            return false;
        if (trycatch_.on())
        {
            png_init_io(ctx_, filedesc_);
            return true;
        }
        bool ok = true;
        _try([this]() { png_init_io(ctx_, filedesc_); })._catch([&](int) { ok = false; } );
        return ok;
    }
    png_structp ctx_;
    png_infop hdr_;
    zpng_trycatch trycatch_;
    int lasterror_;
    FILE* filedesc_;
    std::vector<png_byte>* memio_;          // not managed
    std::vector<png_byte>::difference_type pos_;
private:
    zpng_context(const zpng_context&); // delete
    zpng_context& operator =(const zpng_context&); //delete
};

class zpng_reader : public zpng_context
{
public:
    ~zpng_reader()
    {
        if (ctx_)
            png_destroy_read_struct(&ctx_, &hdr_, (png_infopp)NULL);
    }
    zpng_reader()
    {
        ctx_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (ctx_)
            hdr_ = png_create_info_struct(ctx_);
    }
    // bool open(std::reference<std::vector<png_byte> > mem);
    // lambda implement void user_read_data(png_structp png_ptr, png_bytep data, png_size_t length);
    static void adapter_read(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        zpng_reader* reader = (zpng_reader*) png_get_io_ptr(png_ptr);
        std::vector<png_byte>& memio = *reader->memio_;
        std::vector<png_byte>::difference_type& pos = reader->pos_;
        if (pos + length > memio.size())
        {
            fprintf(stderr, "unbounded reading %d bytes at pos %d end %d\n", length, pos, memio.size());
            png_longjmp(png_ptr, 0xbad001);
        }
        else
        {
            //fprintf(stderr, "reading %d bytes at pos %d\n", length, pos);
            std::copy(memio.begin() + pos, memio.begin() + pos + length, data);
            pos += length;
        }
    }
    bool open(std::vector<png_byte>& mem)
    {
        if (filedesc_ || memio_)
            return false;
        memio_ = &mem;
        pos_ = 0;
        png_set_read_fn(ctx_, (void*)this, adapter_read);
    }
    bool open(const char* name)
    {
        if (memio_ || filedesc_)
            return false;
        filedesc_ = fopen(name, "rb");
        return zpng_context::open();
    }
    bool read_header()
    {
        if (trycatch_.on())
        {
            png_read_info(ctx_, hdr_);
            return true;
        }
        bool ok = true;
        _try([this]() { png_read_info(ctx_, hdr_); })._catch([&](int) { ok = false; });
        return ok;
    }
    bool read_image(std::vector<png_byte>& rgb)
    {
        if (trycatch_.on())
        {
            read_image_(rgb);
            return true;
        }
        bool ok = true;
        _try([this, &rgb]() { read_image_(rgb); })._catch([&](int) { ok = false; });
        return ok;
    }
    bool read_tailer()
    {
        if (trycatch_.on())
        {
            png_read_end(ctx_, NULL);
            return true;
        }
        bool ok = true;
        _try([this]() { png_read_end(ctx_, NULL); })._catch([&](int) { ok = false; });
        return ok;
    }
private:
    bool read_image_(std::vector<png_byte>& rgb)
    {
        png_uint_32 height = image_height();
        png_uint_32 rowbs = rowbytes();
        rgb.resize(rowbs * height);
        std::vector<png_bytep> rows;
        rows.reserve(height);
        for (int i = 0; i < height; ++i)
            rows.push_back(&rgb[0] + i*rowbs);
        png_read_image(ctx_, &rows[0]);
    }
};

class zpng_writer : public zpng_context
{
public:
    class mem_root;
    ~zpng_writer()
    {
        if (ctx_)
            png_destroy_write_struct(&ctx_, &hdr_);
    }
    zpng_writer(mem_root* mr = NULL)
    {
        if (NULL == mr)
            ctx_ = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        else
            ctx_ = png_create_write_struct_2(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL,
                                             (png_voidp)mr, adapter_malloc, adapter_free);
        if (ctx_)
            hdr_ = png_create_info_struct(ctx_);
    }
    // memory alloc strategy
    // reference to mysql's mem_root
    // 128x128
    //    need to malloc 1328 bytes @ 319445e0
    //    need to malloc 8192 bytes @ 31962850
    //    need to malloc 312 bytes @ 31944b20
    //    need to malloc 385 bytes @ 31945070
    //    need to malloc 385 bytes @ 31945200
    //    need to malloc 5936 bytes @ 31964860
    //    need to malloc 65536 bytes @ 31965fa0
    //    need to malloc 65536 bytes @ 31975fb0
    //    need to malloc 65536 bytes @ 31985fc0
    //    need to malloc 65536 bytes @ 31995fd0
    // 2560x1600
    //    need to malloc 1328 bytes @ 23a755f0
    //    need to malloc 8192 bytes @ 23a75b30
    //    need to malloc 312 bytes @ 23a77b40
    //    need to malloc 7681 bytes @ 23a7ae90
    //    need to malloc 7681 bytes @ 23a7cca0
    //    need to malloc 5936 bytes @ 23a7eab0
    //    need to malloc 65536 bytes @ 23a801f0
    //    need to malloc 65536 bytes @ 23a90200
    //    need to malloc 65536 bytes @ 23aa0210
    //    need to malloc 65536 bytes @ 23ab0220
    class mem_root
    {
    public:
        std::vector<png_byte> mem_root_;
        int ref_count_;     // thread-safe un-necessary, atomic<int> reduce half performance.
        size_t mem_root_pos_;
        const size_t mem_root_capacity_;
        mem_root() : mem_root_pos_(0), mem_root_capacity_(5*(1<<16)), ref_count_(0) {}
        png_voidp mem_root_malloc(png_alloc_size_t size)
        {
            png_voidp p = NULL;
            size_t capacity = mem_root_capacity_;
            if (mem_root_.capacity() < capacity)
            {
                mem_root_.reserve(capacity);
                mem_root_.push_back(0);
                mem_root_pos_ = 0;
            }
            if (mem_root_pos_ + size < capacity)
            {
                p = &mem_root_[0] + mem_root_pos_;
                mem_root_pos_ += size;

#ifdef BAD_PERFORMANCE
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
                // it costs 2ns cpu cycle, 10 times takes 20ns
                // when encode a 128x128 png, the whole produce just takes 1000ns.
                // it reduces about 2% performance.
                // although it can be ignore in case of big png.
                if (unlikely(mem_root_pos_ & ((size_t)sizeof(long) - 1)))
                {
                    mem_root_pos_ &= ~(size_t)sizeof(long);
                    mem_root_pos_ += sizeof(long);
                }
#else
                mem_root_pos_ += (sizeof(long) - 1);
                mem_root_pos_ &= ~((size_t)sizeof(long) - 1);
#endif
                ++ref_count_;
            }
            else
            {
                p = malloc(size);
            }
            return p;
        }
        void mem_root_free(png_voidp ptr)
        {
            size_t capacity = mem_root_capacity_;
            if ((png_bytep)ptr < &mem_root_[0]
                 && (png_bytep)ptr >= &mem_root_[0] + capacity)
            {
                free(ptr);
            }
            else if (--ref_count_ == 0)
            {
                mem_root_pos_ = 0;
            }
        }
    };

    static png_voidp adapter_malloc(png_structp png_ptr, png_alloc_size_t size)
    {
        mem_root* mr = (mem_root*)png_get_mem_ptr(png_ptr);
        png_voidp mem = mr->mem_root_malloc(size);
        //fprintf(stderr, "need to malloc %d bytes @ %x\n", size, (uintptr_t)mem);
        return mem;
    }
    static void adapter_free(png_structp png_ptr, png_voidp ptr)
    {
        mem_root* mr = (mem_root*)png_get_mem_ptr(png_ptr);
        //fprintf(stderr, "need to free ptr : %x\n", (uintptr_t)ptr);
        mr->mem_root_free(ptr);
    }
    // bool open(std::reference<std::vector<png_byte> > mem);
    static void adapter_write(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        zpng_writer* writer = (zpng_writer*) png_get_io_ptr(png_ptr);
        std::vector<png_byte>& memio = *writer->memio_;
        //fprintf(stderr, "writing %d bytes at pos %d\n", length, memio.size());
        memio.insert(memio.end(), data, data + length);
    }
    static void adapter_flush(png_structp png_ptr)
    {

    }
    bool open(std::vector<png_byte>& mem)
    {
        if (filedesc_ || memio_)
            return false;
        memio_ = &mem;
        png_set_write_fn(ctx_, (void*)this, adapter_write, adapter_flush);
    }

    bool open(const char* name)
    {
        if (memio_ || filedesc_)
            return false;
        filedesc_ = fopen(name, "wb");
        return zpng_context::open();
    }

    void select_fastest_args()
    {
        // opencv default argument settings
        set_compression_level(1);
        set_compression_strategy(3);
        set_filter(0, 16);
    }
    // plan a: write_header, write_image/write_rows, write_tailer
    // lambda implement void user_write_data(png_structp png_ptr, png_bytep data, png_size_t length);
    //                  void user_flush_data(png_structp png_ptr);

    bool write_header()
    {
        if (trycatch_.on())
        {
            png_write_info(ctx_, hdr_);
            return true;
        }
        bool ok = true;
        _try([this]() { png_write_info(ctx_, hdr_); })._catch([&](int) { ok = false; });
        return ok;
    }
    bool write_image(std::vector<png_byte>& rgb)
    {
        if (trycatch_.on())
        {
            write_image_(rgb);
            return true;
        }
        bool ok = true;
        _try([this, &rgb]() { write_image_(rgb); })._catch([&](int) { ok = false; });
        return ok;
    }
    bool write_tailer()
    {
        if (trycatch_.on())
        {
            png_write_end(ctx_, NULL);
            return true;
        }
        bool ok = true;
        _try([this]() { png_write_end(ctx_, NULL); })._catch([&](int) { ok = false; });
        return ok;
    }
    // plan b: set_rows, write_png
    // bool set_rows()
    // bool write_png()
private:
    bool write_image_(std::vector<png_byte>& rgb)
    {
        png_uint_32 height = image_height();
        png_uint_32 rowbs = rowbytes();
        std::vector<png_bytep> rows;
        rows.reserve(height);
        for (int i = 0; i < height && (1+i)*rowbs <= rgb.size(); ++i)
            rows.push_back(&rgb[0] + i*rowbs);
        png_write_image(ctx_, &rows[0]);
    }
};

/**
* // usages:
* reader.open("/path/to/png");
* reader._try([&]() {
*               })._catch([&](int) {
*                  });
*/

namespace zpng_enum
{
    namespace color_type { enum
    {
        gray = 0,
        palette = PNG_COLOR_TYPE_PALETTE,
        rgb = PNG_COLOR_TYPE_RGB,
        rgba = PNG_COLOR_TYPE_RGB_ALPHA,
        ga = PNG_COLOR_TYPE_GRAY_ALPHA
    };};
    namespace compression_type { enum
    {
        base = 0,
        Default = PNG_COMPRESSION_TYPE_DEFAULT
    };};
    namespace filter_type { enum
    {
        base = 0,
        intrapixel_differencing = PNG_INTRAPIXEL_DIFFERENCING,
        Default = base
    };};
    namespace interlace { enum
    {
        none = PNG_INTERLACE_NONE,
        adam7 = PNG_INTERLACE_ADAM7,
        last = PNG_INTERLACE_LAST
    };};
    namespace offset { enum
    {
        pixel = PNG_OFFSET_PIXEL,
        micrometer = PNG_OFFSET_MICROMETER,
        last = PNG_OFFSET_LAST
    };};
    namespace equation { enum
    {
        linear = PNG_EQUATION_LINEAR,
        base_e = PNG_EQUATION_BASE_E,
        arbitrary = PNG_EQUATION_ARBITRARY,
        hyperbolic = PNG_EQUATION_HYPERBOLIC,
        last = PNG_EQUATION_LAST
    };};
    namespace resolution { enum
    {
        unknown = PNG_RESOLUTION_UNKNOWN,
        meter = PNG_RESOLUTION_METER,
        last = PNG_RESOLUTION_LAST
    };};
    namespace sRGB { enum
    {
        perceptual = PNG_sRGB_INTENT_PERCEPTUAL,
        relative = PNG_sRGB_INTENT_RELATIVE,
        saturation = PNG_sRGB_INTENT_SATURATION,
        absolute = PNG_sRGB_INTENT_ABSOLUTE,
        last = PNG_sRGB_INTENT_LAST
    };};
};


}; // end ns zpng
}; // end ns zhelper

#endif // __ZHELPER_LIBPNG_H__
