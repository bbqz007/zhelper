#include <stdio.h>
#include <jconfig.h>
#include <jerror.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <setjmp.h>

#include <vector>



namespace zhelper
{

namespace zjpeg
{

class zjpeg_reader;
class zjpeg_writer;
typedef unsigned char jpeg_byte;
// component equals to channel

// jpeg_stdio_src : read enc-data from io, then decode
// jpeg_mem_src : read enc-data from memory buffer
// you need support another buffer for receiving decoded data
// jpeg_stdio_dest : write enc-data to io
// jpeg_mem_dest : write enc-data to memory buffer
// you need support another buffer to encode.
// while using jpeg_mem_dest, do not access output buffer until jpeg_finish_(de)compress or
//          jpeg_abort_(de)compress

#define JPEG_TRY \
    jmp_buf jb;             \
    int jbv = setjmp(jb);   \
    if (0 == jbv)
    // {
    //      todo:
    // }
#define JPEG_CATCH_DEFAULT  \
    if (jbv)    \
        fprintf(stderr, ctx_.err->msg_parm.s);
#define JPEG_CATCH  \
    JPEG_CATCH_DEFAULT  \
    if (jbv)
    // {
    //      todo:
    // }


class zjpeg_reader
{
public:
    ~zjpeg_reader()
    {
        jpeg_destroy_decompress(&ctx_);
    }
    zjpeg_reader()
    {
        ctx_.err = jpeg_std_error(&errmgr_);    // miss this step, SEGV when read/write op
        jpeg_create_decompress(&ctx_);
    }
    int image_width() { return ctx_.image_width; }
    int image_height() { return ctx_.image_height; }
    int out_color_space() { return ctx_.out_color_space; }
    int out_color_components() { return ctx_.out_color_components; }
    int read(const char* name, std::vector<jpeg_byte>& rgb)
    {
        FILE* io = fopen(name, "rb");
        if (!io)
            return -1;
        int ret = read(io, rgb);
        fclose(io);
        return ret;
    }
    int read(FILE* io, std::vector<jpeg_byte>& rgb)
    {
        if (!io)
            return -1;
        JPEG_TRY
        {
            jpeg_stdio_src(&ctx_, io);
            read_header();
            decode(rgb);
        }
        JPEG_CATCH_DEFAULT
        return 0;
    }
    int read(const std::vector<jpeg_byte>& mem, std::vector<jpeg_byte>& rgb)
    {
        if (mem.empty())
            return -1;
        return read(&mem[0], mem.size(), rgb);
    }
    int read(const jpeg_byte* mem, size_t size, std::vector<jpeg_byte>& rgb)
    {
        JPEG_TRY
        {
            jpeg_mem_src(&ctx_, (jpeg_byte*)mem, size);
            read_header();
            decode(rgb);
        }
        JPEG_CATCH_DEFAULT
        return 0;
    }
protected:
    int read_header()
    {
        jpeg_read_header(&ctx_, TRUE);
        return 0;
    }
    int decode(std::vector<jpeg_byte>& rgb)
    {
        ctx_.out_color_space = JCS_RGB;
        ctx_.out_color_components = 3;

        jpeg_start_decompress(&ctx_);
        int row_stride = ctx_.output_width * ctx_.output_components;
        rgb.resize(row_stride * ctx_.output_height);
        jpeg_byte* p = &rgb[0];
        while (ctx_.output_scanline < ctx_.output_height)
        {
            JSAMPROW lines[] = {p};
            jpeg_read_scanlines(&ctx_, lines, 1);
            p += row_stride;
        }
        jpeg_finish_decompress(&ctx_);
        return 0;
    }
    jpeg_decompress_struct ctx_;
    jpeg_error_mgr errmgr_;
};


class zjpeg_writer
{
public:
    ~zjpeg_writer()
    {
        jpeg_destroy_compress(&ctx_);
    }
    zjpeg_writer()
        : quality_(95), progressive_(0),
            optimize_(0), rst_interval_(0)
    {
        ctx_.err = jpeg_std_error(&errmgr_);
        jpeg_create_compress(&ctx_);
    }
    void set_quality(int val) { quality_ = std::min(std::max(val, 0), 100); }
    void set_progressive(int val) { progressive_ = val; }
    void set_optimize(int val) { optimize_ = val; }
    void set_rst_interval(int val) { rst_interval_ = val; }
    void set_WxH(int w, int h) { ctx_.image_width = w; ctx_.image_height = h; }
    void set_gray() { ctx_.input_components = 1; ctx_.in_color_space = JCS_GRAYSCALE; }
    void set_color() { ctx_.input_components = 3; ctx_.in_color_space = JCS_RGB; }
    int write(const char* name, const jpeg_byte* rgb, size_t size)
    {
        FILE* io = fopen(name, "wb");
        if (!io)
            return -1;
        int ret = write(io, rgb, size);
        fclose(io);
        return ret;
    }
    int write(const char* name, const std::vector<jpeg_byte>& rgb)
    {
        if (rgb.empty())
            return -1;
        return write(name, &rgb[0], rgb.size());
    }
    int write(FILE* io, const jpeg_byte* rgb, size_t size)
    {
        if (!io)
            return -1;
        JPEG_TRY
        {
            jpeg_stdio_dest(&ctx_, io);
            encode(rgb, size);
        }
        JPEG_CATCH_DEFAULT
        return ctx_.err->msg_code;
    }
    int write(std::vector<jpeg_byte>& mem, const jpeg_byte* rgb, size_t size)
    {
        jpeg_byte* frame = 0;
        unsigned long frame_size = 0;
        zjpeg_dest_mgr dstmgr;
        ctx_.dest = &dstmgr;
        JPEG_TRY
        {
            // default dest mgr only has 4k free bytes?
            // jpeg_mem_dest(&ctx_, &frame, &frame_size);
            encode(rgb, size);
            frame = &dstmgr.zjpeg_buffer[0];
            frame_size = dstmgr.zjpeg_buffer.size();
        }
        JPEG_CATCH_DEFAULT
        if (frame)
        {
            mem.clear();
            mem.insert(mem.end(), frame, frame + frame_size);
        }
        return ctx_.err->msg_code;
    }
    int write(std::vector<jpeg_byte>& mem, const std::vector<jpeg_byte>& rgb)
    {
        if (rgb.empty())
            return -1;
        return write(mem, &rgb[0], rgb.size());
    }
protected:
    int quality_;
    int progressive_;
    int optimize_;
    int rst_interval_;
    class zjpeg_dest_mgr : public jpeg_destination_mgr
    {
    public:
        std::vector<jpeg_byte> zjpeg_buffer;
        const size_t BLOCK_SIZE;
        zjpeg_dest_mgr() : BLOCK_SIZE(8<<10)
        {
            init_destination = _init_destination;
            empty_output_buffer = _empty_output_buffer;
            term_destination = _term_destination;
        }
        static void _init_destination(j_compress_ptr cinfo)
        {
            zjpeg_dest_mgr* mgr = (zjpeg_dest_mgr*)cinfo->dest;
            mgr->zjpeg_init_destination(cinfo);
        }
        void zjpeg_init_destination(j_compress_ptr cinfo)
        {
            zjpeg_buffer.resize(BLOCK_SIZE);
            cinfo->dest->next_output_byte = &zjpeg_buffer[0];
            cinfo->dest->free_in_buffer = zjpeg_buffer.size();
        }

        static boolean _empty_output_buffer(j_compress_ptr cinfo)
        {
            zjpeg_dest_mgr* mgr = (zjpeg_dest_mgr*)cinfo->dest;
            return mgr->zjpeg_empty_output_buffer(cinfo);
        }
        boolean zjpeg_empty_output_buffer(j_compress_ptr cinfo)
        {
            size_t oldsize = zjpeg_buffer.size();
            zjpeg_buffer.resize(oldsize + BLOCK_SIZE);
            cinfo->dest->next_output_byte = &zjpeg_buffer[oldsize];
            cinfo->dest->free_in_buffer = zjpeg_buffer.size() - oldsize;
            return true;
        }

        static void _term_destination(j_compress_ptr cinfo)
        {
            zjpeg_dest_mgr* mgr = (zjpeg_dest_mgr*)cinfo->dest;
            mgr->zjpeg_term_destination(cinfo);
        }
        void zjpeg_term_destination(j_compress_ptr cinfo)
        {
            zjpeg_buffer.resize(zjpeg_buffer.size() - cinfo->dest->free_in_buffer);
        }
    };
    int encode(const jpeg_byte* rgb, size_t size)
    {
        jpeg_set_defaults(&ctx_);
        ctx_.restart_interval = rst_interval_;
        jpeg_set_quality(&ctx_, quality_, TRUE);
        if(progressive_)
            jpeg_simple_progression( &ctx_ );
        if(optimize_)
            ctx_.optimize_coding = TRUE;

        jpeg_start_compress(&ctx_, TRUE);
        int row_stride = ctx_.image_width * ctx_.input_components;
        int scanline = 0;
        jpeg_byte* p = (jpeg_byte*)rgb;
        while (scanline++ < ctx_.image_height)
        {
            JSAMPROW lines[] = {p};
            jpeg_write_scanlines(&ctx_, lines, 1);
            p += row_stride;
        }
        jpeg_finish_compress(&ctx_);
        return ctx_.err->msg_code;
    }
    jpeg_compress_struct ctx_;
    jpeg_error_mgr errmgr_;
};

};

};
