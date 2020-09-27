#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "benchmark/benchmark.h"
#include "zpng.h"
#include "zjpg.h"

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
};
#include "zffmpeg.h"
#include <zlib.h>

#include <iostream>
#include <fstream>
#include <vector>

#include <thread>

using namespace std;
using namespace cv;

vector<uint8_t> loadfile(const char* name)
{
	vector<uint8_t> raw;
	ifstream ifs(name, ios_base::binary|ios_base::in);
	if (ifs.is_open())
	{
		ifs.seekg(0, ios_base::end);
		raw.resize(ifs.tellg());
		ifs.seekg(0, ios_base::beg);
		ifs.read((char*)&raw[0], raw.size());
	}
	return std::move(raw);
}

void BM_rgb2bgr(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.rgb");
    for (auto _ : state)
    {
        Mat rgb(128, 128, CV_8UC3, &content[0]);
        Mat bgr;
        cvtColor(rgb, bgr, CV_RGB2BGR);
    }
}

BENCHMARK(BM_rgb2bgr);

void BM_yuv2bgr(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out420p.yuv");
    for (auto _ : state)
    {
        Mat yuv420p(128*1.5, 128, CV_8UC1, &content[0]);
        Mat bgr;
        cvtColor(yuv420p, bgr, CV_YUV420p2BGR);
    }
}

BENCHMARK(BM_yuv2bgr);

void BM_ffyuv2bgr(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out420p.yuv");
    AVFrame* frame = av_frame_alloc();
    AVFrame* swsframe = av_frame_alloc();
    av_image_fill_arrays(frame->data, frame->linesize, &content[0],
                         AV_PIX_FMT_YUV420P, 128, 128, 8);
    av_image_alloc(swsframe->data, swsframe->linesize, 128, 128, AV_PIX_FMT_BGR24, 32);
    frame->height = 128; frame->width = 128; frame->format = AV_PIX_FMT_YUV420P;
    swsframe->height = 128; swsframe->width = 128; swsframe->format = AV_PIX_FMT_BGR24;
    SwsContext* sws = NULL;
    for (auto _ : state)
    {
        sws = sws_getCachedContext(sws, frame->width, frame->height, (AVPixelFormat)frame->format,
                             swsframe->width, swsframe->height, (AVPixelFormat)swsframe->format,
                             SWS_BICUBIC, 0, 0, 0);
        sws_scale(sws, frame->data, frame->linesize, 0, frame->height,
                  swsframe->data, swsframe->linesize);
    }
    sws_freeContext(sws);
    av_frame_free(&frame);
    av_frame_free(&swsframe);
}

BENCHMARK(BM_ffyuv2bgr);

void BM_ffyuv2bgr_alloc(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out420p.yuv");
    AVFrame* frame = av_frame_alloc();
    av_image_fill_arrays(frame->data, frame->linesize, &content[0],
                         AV_PIX_FMT_YUV420P, 128, 128, 8);
    frame->height = 128; frame->width = 128; frame->format = AV_PIX_FMT_YUV420P;
    SwsContext* sws = NULL;
    for (auto _ : state)
    {
        AVFrame* swsframe = av_frame_alloc();
        av_image_alloc(swsframe->data, swsframe->linesize, 128, 128, AV_PIX_FMT_BGR24, 32);
        swsframe->height = 128; swsframe->width = 128; swsframe->format = AV_PIX_FMT_BGR24;
        sws = sws_getCachedContext(sws, frame->width, frame->height, (AVPixelFormat)frame->format,
                             swsframe->width, swsframe->height, (AVPixelFormat)swsframe->format,
                             SWS_BICUBIC, 0, 0, 0);
        sws_scale(sws, frame->data, frame->linesize, 0, frame->height,
                  swsframe->data, swsframe->linesize);
        av_frame_free(&swsframe);
    }
    sws_freeContext(sws);
    av_frame_free(&frame);
}

BENCHMARK(BM_ffyuv2bgr_alloc);

////// Encode //////////
void BM_encpng(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.rgb");
    vector<uint8_t> result;
    Mat rgb(128, 128, CV_8UC3, &content[0]);
    for (auto _ : state)
    {
        imencode(".png", rgb, result);
    }
    //cout << this_thread::get_id() << ":" << result.size() << endl;
}

BENCHMARK(BM_encpng);

void BM_enczpng(benchmark::State& state)
{
    using namespace zhelper::zpng;
    png_uint_32 width = 128, height = 128;
    png_byte color_type = zpng_enum::color_type::rgb, bit_depth = 8;
//    std::vector<png_byte> readbuf = loadfile("images/out.png");
//    std::vector<png_byte> rgb;
//    zpng_reader reader;
//    reader.open(readbuf);
//    reader.read_header();
//    reader._try(
//        [&]() {
//            width = reader.image_width();
//            height = reader.image_height();
//            color_type = reader.color_type();
//            bit_depth = reader.bit_depth();
//        })._catch([](int) {});
//    reader.read_image(rgb);
//    reader.read_tailer();

    // arguments
    // 0: bool : prealloc
    // 1: int(0-4) : compression strategy
    // 2: int(1-9) : compression level
    // 3: int : filter
    vector<uint8_t> rgb = loadfile("images/out.rgb");
    size_t szt = 0;
    std::vector<png_byte> writebuf;
        if (state.range(0))
            writebuf.reserve(1 << 16);
    zpng_writer::mem_root mem_root;
    for (auto _ : state)
    {
        writebuf.clear();
        zpng_writer writer(&mem_root);
        writer.open(writebuf);
        writer._try(
            [&]() {
                writer.set_IHDR(width, height,
                         bit_depth, color_type, PNG_INTERLACE_NONE,
                         PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_BASE);
                writer.set_compression_level(state.range(1));
                //writer.set_compression_mem_level(9);
                //writer.set_compression_method(8);
                writer.set_filter(0, state.range(3)*8); //PNG_FILTER_SUB 16
                writer.set_compression_strategy(state.range(2));
                writer.set_lendian();
                writer.set_bgr();
                //writer.set_interlace_handling();
            })._catch([](int) {});
        writer.write_header();
        writer.write_image(rgb);
        writer.write_tailer();
        szt = writebuf.size();
    }
    //cout << szt << endl;
}
void BM_enczpng_args(benchmark::internal::Benchmark* bmrk)
{
    for (int a = 1; a <= 1; ++a)
        for (int b = 1; b <= 9; ++b)
            for (int c = 0; c <= 4; ++c)
                for (int d = 0; d <= 15; ++d)
                    bmrk->Args({a, b, c, d});
}
BENCHMARK(BM_enczpng)->Args({1, 1, 3, 2});//->Apply(BM_enczpng_args);

void BM_enczffpng(benchmark::State& state)
{

    av_log_set_level(AV_LOG_QUIET);
    using namespace zhelper::zff;
    vector<uint8_t> content = loadfile("images/out.rgb");
    vector<uint8_t> result;
    AVFrame* frame = av_frame_alloc();
    av_image_fill_arrays(frame->data, frame->linesize, &content[0],
                         AV_PIX_FMT_RGB24, 128, 128, 24);
    frame->height = 128; frame->width = 128; frame->format = AV_PIX_FMT_RGB24;
    frame->pts = 0; frame->pkt_dts = 0; frame->pkt_duration = 1;
    for (auto _ : state)
    {
        zff_writer writer;
        writer.open("images/nothing", "image2");
        writer.add_stream("png",
                          [frame](AVFormatContext* outfmt_ctx,
                            AVCodecContext* enc_ctx,
                            AVCodec* enc) {
                            enc_ctx->height = frame->height;
                            enc_ctx->width = frame->width;
                            enc_ctx->pix_fmt = (AVPixelFormat)frame->format;
                            enc_ctx->time_base = {1,25};
                          });
        zff_nullio nullio;
        AVIOContext* pb = writer.select_io((AVIOContext*)nullio);
        writer.write(0, frame);
        writer.select_io(pb);
    }
    av_frame_free(&frame);
    //cout << this_thread::get_id() << ":" << result.size() << endl;
}

BENCHMARK(BM_enczffpng);

void BM_encjpg(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.rgb");
    vector<uint8_t> result;
    Mat rgb(128, 128, CV_8UC3, &content[0]);
    for (auto _ : state)
    {
        imencode(".jpg", rgb, result);
    }
    //cout << this_thread::get_id() << ":" << result.size() << endl;
}

BENCHMARK(BM_encjpg);

void BM_enczjpg(benchmark::State& state)
{
    using namespace zhelper::zjpeg;
    vector<uint8_t> rgb = loadfile("images/out.rgb");
    vector<uint8_t> content;
    std::unique_ptr<zjpeg_writer> writerp;
    if (state.range(0) > 0)
        writerp.reset(new zjpeg_writer);
    for (auto _ : state)
    {
        if (!writerp)
            writerp.reset(new zjpeg_writer);
        zjpeg_writer& writer = *writerp.get();
        content.clear();
        writer.set_WxH(128, 128);
        writer.set_color();
        writer.write(content, rgb);
        if (state.range(0) == 0)
            writerp.reset();
    }
}

BENCHMARK(BM_enczjpg)->Range(0, 1);

void BM_enczffjpg(benchmark::State& state)
{

    av_log_set_level(AV_LOG_QUIET);
    using namespace zhelper::zff;
    vector<uint8_t> content = loadfile("images/out.rgb");
    vector<uint8_t> result;
    AVFrame* frame = av_frame_alloc();
    av_image_fill_arrays(frame->data, frame->linesize, &content[0],
                         AV_PIX_FMT_RGB24, 128, 128, 24);
    frame->height = 128; frame->width = 128; frame->format = AV_PIX_FMT_RGB24;
    frame->pts = 0; frame->pkt_dts = 0; frame->pkt_duration = 1;
    for (auto _ : state)
    {
        zff_writer writer;
        writer.open("images/nothing", "image2");
        writer.add_stream("mjpeg",
                          [frame](AVFormatContext* outfmt_ctx,
                            AVCodecContext* enc_ctx,
                            AVCodec* enc) {
                            enc_ctx->height = frame->height;
                            enc_ctx->width = frame->width;
                            enc_ctx->time_base = {1,25};
                          });
        zff_nullio nullio;
        AVIOContext* pb = writer.select_io((AVIOContext*)nullio);
        writer.write(0, frame);
        writer.select_io(pb);
    }
    av_frame_free(&frame);
    //cout << this_thread::get_id() << ":" << result.size() << endl;
}

BENCHMARK(BM_enczffjpg);


////// Decode //////////
void BM_decpng(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.png");
    for (auto _ : state)
    {
        Mat m = imdecode(content, 1);
    }
}

BENCHMARK(BM_decpng);

void BM_deczpng(benchmark::State& state)
{
    using namespace zhelper::zpng;
    png_uint_32 width, height;
    png_byte color_type, bit_depth;
    std::vector<png_byte> readbuf = loadfile("images/out.png");

    for (auto _ : state)
    {
        std::vector<png_byte> rgb;
        zpng_reader reader;
        reader.open(readbuf);
        reader.read_header();
        reader._try(
            [&]() {
                width = reader.image_width();
                height = reader.image_height();
                color_type = reader.color_type();
                bit_depth = reader.bit_depth();
            })._catch([](int) {});
        reader.read_image(rgb);
        reader.read_tailer();
    }
}

BENCHMARK(BM_deczpng);

void BM_decjpg(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.jpg");
    for (auto _ : state)
    {
        Mat m = imdecode(content, 1);
    }
}

BENCHMARK(BM_decjpg);

void BM_deczjpg(benchmark::State& state)
{
    using namespace zhelper::zjpeg;
    std::unique_ptr<zjpeg_reader> readerp;
    std::vector<jpeg_byte> rgb;
    vector<jpeg_byte> content = loadfile("images/out.jpg");
    if (state.range(0) > 0)
        readerp.reset(new zjpeg_reader);
    for (auto _ : state)
    {
        if (!readerp)
            readerp.reset(new zjpeg_reader);
        zjpeg_reader& reader = *readerp.get();
        rgb.clear();
        reader.read(content, rgb);
        if (state.range(0) == 0)
            readerp.reset();
    }
}

BENCHMARK(BM_deczjpg)->Range(0, 1);

void BM_decbmp(benchmark::State& state)
{
    vector<uint8_t> content = loadfile("images/out.bmp");
    for (auto _ : state)
    {
        Mat m = imdecode(content, 1);
    }
}

BENCHMARK(BM_decbmp);

/////// Load encoded frame from io /////////
void BM_loadzpng(benchmark::State& state)
{
    using namespace zhelper::zpng;
    png_uint_32 width, height;
    png_byte color_type, bit_depth;

    for (auto _ : state)
    {
        std::vector<png_byte> rgb;
        zpng_reader reader;
        reader.open("images/out.png");
        reader.read_header();
        reader._try(
            [&]() {
                width = reader.image_width();
                height = reader.image_height();
                color_type = reader.color_type();
                bit_depth = reader.bit_depth();
            })._catch([](int) {});
        reader.read_image(rgb);
        reader.read_tailer();
    }
}

void BM_loadpng(benchmark::State& state)
{
    for (auto _ : state)
    {
        Mat m = imread("images/out.png");
    }
}

void BM_loadzffpng(benchmark::State& state)
{
    using namespace zhelper::zff;
    for (auto _ : state)
    {
        zff_reader reader;
        reader.open("images/out.png");
        reader.open_vedio_stream();
        AVFrame* frame = 0;
        AVPacket inpkt;
        av_init_packet(&inpkt);
        for(; reader.poll(&frame, &inpkt) >= 0;
                av_packet_unref(&inpkt))
        {
            if (!frame)
                continue;
            av_frame_free(&frame);
        }
    }
}

void BM_loadjpg(benchmark::State& state)
{
    for (auto _ : state)
    {
        Mat m = imread("images/out.jpg");
    }
}

void BM_loadzjpg(benchmark::State& state)
{
    using namespace zhelper::zjpeg;
    std::unique_ptr<zjpeg_reader> readerp;
    std::vector<jpeg_byte> rgb;
    if (state.range(0) > 0)
        readerp.reset(new zjpeg_reader);
    for (auto _ : state)
    {
        if (!readerp)
            readerp.reset(new zjpeg_reader);
        zjpeg_reader& reader = *readerp.get();
        rgb.clear();
        reader.read("images/out.jpg", rgb);
        if (state.range(0) == 0)
            readerp.reset();
    }
}

void BM_loadzffjpg(benchmark::State& state)
{
    using namespace zhelper::zff;
    for (auto _ : state)
    {
        zff_reader reader;
        reader.open("images/out.jpg");
        reader.open_vedio_stream();
        AVFrame* frame = 0;
        AVPacket inpkt;
        av_init_packet(&inpkt);
        for(; reader.poll(&frame, &inpkt) >= 0;
                av_packet_unref(&inpkt))
        {
            if (!frame)
                continue;
            av_frame_free(&frame);
        }
    }
}

void BM_loadbmp(benchmark::State& state)
{
    for (auto _ : state)
    {
        Mat m = imread("images/out.bmp");
    }
}

BENCHMARK(BM_loadpng);
BENCHMARK(BM_loadzpng);
BENCHMARK(BM_loadzffpng);
BENCHMARK(BM_loadjpg);
BENCHMARK(BM_loadzjpg)->Range(0, 1);
BENCHMARK(BM_loadzffjpg);
BENCHMARK(BM_loadbmp);

//BENCHMARK_MAIN();
int main(int argc, char** argv) {
    av_register_all();                                  \
    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();                              \
}

