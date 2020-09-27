#ifndef __ZHELPER_FFMPEG_H__
#define __ZHELPER_FFMPEG_H__
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

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/pixfmt.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
};
#include <stdlib.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

namespace zhelper
{

namespace zff
{

class zff_options;
class zff_reader;
class zff_writer;

enum AVPixelFormat choose_pixel_fmt(AVStream *st, AVCodecContext *avctx, AVCodec *codec, enum AVPixelFormat target)
{
    if (codec && codec->pix_fmts)
    {
        const enum AVPixelFormat *p = codec->pix_fmts;
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(target);
        int has_alpha = desc ? desc->nb_components % 2 == 0 : 0;

        enum AVPixelFormat best= AV_PIX_FMT_NONE;

        for (; *p != AV_PIX_FMT_NONE; p++)
        {
            best= avcodec_find_best_pix_fmt_of_2(best, *p, target, has_alpha, NULL);
            if (*p == target)
                break;
        }

        if (*p == AV_PIX_FMT_NONE) {
            if (target != AV_PIX_FMT_NONE)
                av_log(NULL, AV_LOG_WARNING,
                       "Incompatible pixel format '%s' for codec '%s', auto-selecting format '%s'\n",
                       av_get_pix_fmt_name(target),
                       codec->name,
                       av_get_pix_fmt_name(best));
            return best;
        }
    }
    return target;
}

class zff_options
{
public:
    ~zff_options()
    {
        av_dict_free(&dict_);
    }
    zff_options()
    : dict_(0)
    {

    }
    zff_options& set(const char* name, const char* val, int flag = 0)
    {
        av_dict_set(&dict_, name, val, flag);
        return *this;
    }
    zff_options& set(const char* name, int val, int flag = 0)
    {
        sprintf(buf_, "%d", val);
        av_dict_set(&dict_, name, buf_, flag);
        return *this;
    }
    zff_options& copy(AVDictionary* src)
    {
        av_dict_copy(&dict_, src, 0);
        return *this;
    }
    AVDictionary** options() { return &dict_; }
private:
    AVDictionary* dict_;
    char buf_[72];
};

class zff_reader
{
public:
    ~zff_reader()
    {
        codecs_.clear();
        ctx_.reset();
    }
    zff_reader()
    {

    }
    void dump()
    {
        av_dump_format(ctx_.get(),  0, path_.c_str(), 0);
    }
    int open(const char* name,
             AVInputFormat* fmt = NULL,
             AVDictionary** options = NULL)
    {
        int ret = 0;
        if (!ctx_)
        {
            AVFormatContext* ctx = NULL;
            ret = avformat_open_input(&ctx, name, fmt, options);
            if (ret < 0)
                return ret;
            ctx_.reset(ctx, [](AVFormatContext*& p) { avformat_close_input(&p); });
        }
        return 0;
    }
    int read_header(AVDictionary** options = NULL)
    {
        return avformat_find_stream_info(ctx_.get(), options);
    }
    int read_ffm()
    {
        for (int i = 0; i < ctx_->nb_streams; ++i)
        {
            open_ffm_stream(ctx_->streams[i]);
        }
    }
    int open_vedio_stream(AVDictionary** options = NULL)
    {
        AVStream* vstream = NULL;
        for (int i = 0; i < ctx_->nb_streams; ++i)
        {
            if (AVMEDIA_TYPE_VIDEO == ctx_->streams[i]->codecpar->codec_type)
            {
                vstream = ctx_->streams[i];
                break;
            }
        }
        zff_options zoptions;
        if (options)
            zoptions.copy(*options);
        AVRational rate = av_guess_frame_rate(ctx_.get(), vstream, NULL);
        zoptions.set("r", rate.num /rate.den);
        return open_stream(vstream, zoptions.options(),
                           [this](AVStream* s, AVCodecContext* c) {
                                c->framerate = av_guess_frame_rate(ctx_.get(), s, NULL);
                           });
    }
    int open_audio_stream(AVDictionary** options = NULL)
    {
        AVStream* astream = NULL;
        for (int i = 0; i < ctx_->nb_streams; ++i)
        {
            if (AVMEDIA_TYPE_AUDIO == ctx_->streams[i]->codecpar->codec_type)
            {
                astream = ctx_->streams[i];
                break;
            }
        }
        return open_stream(astream, options);
    }
    int open_streams(AVDictionary** options = NULL)
    {
        for (int i = 0; i < ctx_->nb_streams; ++i)
        {
            switch(ctx_->streams[i]->codecpar->codec_type)
            {
            case AVMEDIA_TYPE_AUDIO: open_audio_stream(options); break;
            case AVMEDIA_TYPE_VIDEO: open_vedio_stream(options); break;
            default: open_stream(ctx_->streams[i], options); break;
            }
        }
        return 0;
    }
    int poll(AVFrame** dec_frame_pp, AVPacket* raw_frame_p = NULL)
    {
        int ret = 0;
        AVPacket packet;
        std::shared_ptr<AVPacket> pcktp;
        if (raw_frame_p)
            pcktp.reset(raw_frame_p, [](AVPacket*){});
        else
            pcktp.reset(&packet, av_packet_unref);
        ret = av_read_frame(ctx_.get(), pcktp.get());
        if (ret < 0)
            return ret;
        if (!dec_frame_pp)
            return 0;
        *dec_frame_pp = NULL;
        ret = decode(dec_frame_pp, pcktp.get());
        copy_side_data_to_first_packet(pcktp.get());
        ++pktcnt_[pcktp->stream_index];
        return ret;
    }

    // just for test program to use this decoder for benchmark
    friend class explorer;
    struct explorer
    {
        static int decode(zff_reader& reader, AVFrame** framepp, AVPacket* packet)
        {
            return reader.decode(framepp, packet);
        }
    };
private:
    friend class zff_writer;
    int open_stream(AVStream* avstrm, AVDictionary** options = NULL,
                    std::function<void(AVStream*, AVCodecContext*)> preconfig = [](AVStream*, AVCodecContext*){})
    {
        int ret = 0;
        if (!avstrm)
            return -1;
        AVCodec* dec = avcodec_find_decoder(avstrm->codecpar->codec_id);
        if (!dec)
            return AVERROR_DECODER_NOT_FOUND;
        AVCodecContext* dectx = NULL;
        dectx = avcodec_alloc_context3(dec);
        if (!dectx)
            return AVERROR(ENOMEM);
        ret = avcodec_parameters_to_context(dectx, avstrm->codecpar);
        if (ret < 0)
            return ret;

        std::shared_ptr<AVCodecContext> ptr(dectx, [](AVCodecContext*& p){
                                        avcodec_close(p);
                                        avcodec_free_context(&p);
                                     });
        preconfig(avstrm, dectx);
        ret = avcodec_open2(dectx, dec, options);
        if (ret < 0)
            return ret;
        codecs_[avstrm->index].swap(ptr);
        return ret;
    }
    int open_ffm_stream(AVStream* avstrm)
    {
        int ret = 0;
        if (!avstrm)
            return -1;
        AVCodec* enc = avcodec_find_encoder(avstrm->codecpar->codec_id);
        if (!enc)
            return AVERROR_DECODER_NOT_FOUND;
        // close the encode context
        //avcodec_get_context_default3(avstrm->codec, enc);
        char* enc_config = av_stream_get_recommended_encoder_configuration(avstrm);
        if (enc_config)
        {
            AVDictionary *opts = NULL;
            av_dict_parse_string(&opts, enc_config, "=", ",", 0);
            av_opt_set_dict2(avstrm->codec, &opts, AV_OPT_SEARCH_CHILDREN);
            av_dict_free(&opts);
        }

        std::shared_ptr<AVCodecContext> ptr(avstrm->codec, [](AVCodecContext*& p){

                                        // managed by avformatcontext
                                     });
//        ret = avcodec_open2(avstrm->codec, enc, NULL);
//        if (ret < 0)
//            return ret;
        codecs_[avstrm->index].swap(ptr);
        return ret;
    }
    int copy_side_data_to_first_packet(AVPacket* pkt)
    {
        if (pktcnt_[pkt->stream_index] != 0)
            return 0;
        AVStream* ist = ctx_->streams[pkt->stream_index];
        for (int i = 0; i < ist->nb_side_data; i++) {
            AVPacketSideData *src_sd = &ist->side_data[i];
            uint8_t *dst_data;

            if (src_sd->type == AV_PKT_DATA_DISPLAYMATRIX)
                continue;

            if (av_packet_get_side_data(pkt, src_sd->type, NULL))
                continue;

            dst_data = av_packet_new_side_data(pkt, src_sd->type, src_sd->size);
            if (!dst_data)
                break;

            memcpy(dst_data, src_sd->data, src_sd->size);
        }
    }
    int decode(AVFrame** framepp, AVPacket* packet)
    {
        int got = 0;
        int ret = 0;
        *framepp = NULL;
        if (codecs_.end() == codecs_.find(packet->stream_index))
            return 0;
        AVFrame* frame = av_frame_alloc();
        AVCodecContext* dectx = codecs_[packet->stream_index].get();
        av_packet_rescale_ts(packet,
                             ctx_->streams[packet->stream_index]->time_base,
                             dectx->time_base);
        switch (ctx_->streams[packet->stream_index]->codecpar->codec_type)
        {
        case AVMEDIA_TYPE_AUDIO: ret = avcodec_decode_audio4(dectx, frame, &got, packet); break;
        case AVMEDIA_TYPE_VIDEO: ret = avcodec_decode_video2(dectx, frame, &got, packet); break;
        default: break;
        }
        if (ret >= 0 && got > 0)
        {
            frame->pts = frame->best_effort_timestamp;
            *framepp = frame;
        }
        else
            av_frame_free(&frame);

        return ret;
    }
    std::shared_ptr<AVFormatContext> ctx_;
    std::unordered_map<int, std::shared_ptr<AVCodecContext> > codecs_;
    std::unordered_map<int, int> pktcnt_;
    std::string path_;
};

class zff_writer
{
public:
    ~zff_writer()
    {
        clear_sw();
        codecs_.clear();
        ctx_.reset();
    }
    zff_writer()
    {
        is_header_written_ = false;
        is_nofile_io_opened_ = false;
    }
    void dump()
    {
        av_dump_format(ctx_.get(),  0, path_.c_str(), 1);
    }
    AVIOContext* select_io(AVIOContext* pb)
    {
        AVIOContext* ret = NULL;
        if (!(ctx_->oformat->flags & AVFMT_NOFILE)
            || !(ctx_->oformat->flags & AVFMT_NOTIMESTAMPS))
            return pb; // not accepted
        ret = ctx_->pb;
        ctx_->pb = pb;
        is_nofile_io_opened_ = !!pb;
        return ret;
    }
    int open(const char* filename, const char* fmtname = NULL)
    {
        int ret = 0;
        if (!ctx_)
        {
            AVFormatContext* ctx = NULL;
            ret = avformat_alloc_output_context2(&ctx, NULL, fmtname, filename);
            if (ret < 0)
                return ret;
            path_ = filename;
            ctx_.reset(ctx, avformat_free_context);
            av_opt_set(ctx, "loglevel", "trace", AV_OPT_SEARCH_CHILDREN);
        }
        return ret;
    }
    int copy_side_data(zff_reader& reader, AVStream* ost)
    {
        AVMediaType type = ost->codecpar->codec_type;
        AVStream* ist = NULL;
        AVFormatContext* infmt_ctx = reader.ctx_.get();
        for (int i = 0; i < infmt_ctx->nb_streams; ++i)
        {
            if (infmt_ctx->streams[i]->codecpar->codec_type == type)
            {
                ist = infmt_ctx->streams[i];
                break;
            }
        }
        if (ist) {
            int i;
            for (i = 0; i < ist->nb_side_data; i++) {
                AVPacketSideData *sd = &ist->side_data[i];
                uint8_t *dst = av_stream_new_side_data(ost, sd->type, sd->size);
                if (!dst)
                    return AVERROR(ENOMEM);
                memcpy(dst, sd->data, sd->size);
            }
        }
        return 0;
    }
    int clone_stream(AVStream* src)
    {
        AVStream* newstrm = avformat_new_stream(ctx_.get(), NULL);
        int ret = avcodec_parameters_copy(newstrm->codecpar, src->codecpar);
        newstrm->time_base = src->time_base;
        return ret;
    }
    int clone_stream(AVCodecContext* dectx, const char* specified_enc = NULL,
                     std::function<void(AVCodecContext*)> preconfig = [](AVCodecContext*) {},
                     std::function<void(AVStream*, AVCodecContext*)> postconfig = [](AVStream*, AVCodecContext*) {})
    {
        int ret = 0;
        AVCodec* enc = NULL;
        if (specified_enc)
            enc = avcodec_find_encoder_by_name(specified_enc);
        else
            enc = avcodec_find_encoder(dectx->codec_id);
        if (!enc)
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enctx = avcodec_alloc_context3(enc);
        if (!enctx)
            return AVERROR(ENOMEM);
        std::shared_ptr<AVCodecContext> enctxp(enctx,
                                               [](AVCodecContext*& p) {
                                                    avcodec_close(p);
                                                    avcodec_free_context(&p);
                                               });
        if (dectx->codec_type == AVMEDIA_TYPE_VIDEO)
            clone_video_stream(enctx, enc, dectx, preconfig);
        if (dectx->codec_type == AVMEDIA_TYPE_AUDIO)
            clone_audio_stream(enctx, enc, dectx, preconfig);
        ret = avcodec_open2(enctx, enc, NULL);
        if (ret < 0)
            return ret;
        AVStream* newstrm = avformat_new_stream(ctx_.get(), NULL);
        ret = avcodec_parameters_from_context(newstrm->codecpar, enctx);
        for (int i = 0; enctx->coded_side_data && i < enctx->nb_coded_side_data; ++i)
        {
            const AVPacketSideData* sd_src = &enctx->coded_side_data[i];
            uint8_t* dst_data = av_stream_new_side_data(newstrm, sd_src->type, sd_src->size);
            if (dst_data)
                memcpy(dst_data, sd_src, sd_src->size);
        }
        codecs_[newstrm->index].swap(enctxp);
        newstrm->time_base = enctx->time_base;
        enctx->bit_rate = dectx->bit_rate;
        postconfig(newstrm, enctx);
        return ret;
    }
    int clone_video_stream(zff_reader& reader, const char* specified_enc = NULL,
                           std::function<void(AVCodecContext*)> preconfig = [](AVCodecContext*) {},
                           std::function<void(AVStream*, AVCodecContext*)> postconfig = [](AVStream*, AVCodecContext*) {})
    {
        AVFormatContext* infmt_ctx = reader.ctx_.get();
        AVStream* vstream = NULL;
        for (int i = 0; i < infmt_ctx->nb_streams; ++i)
        {
            if(infmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                vstream = infmt_ctx->streams[i];
                break;
            }
        }
        if (!vstream)
            return -1;
        if (reader.codecs_.find(vstream->index) != reader.codecs_.end())
            clone_stream(reader.codecs_[vstream->index].get(), specified_enc, preconfig, postconfig);
        else
            clone_stream(vstream);
        return ctx_->nb_streams;
    }

    int add_stream(AVCodecID id, std::function<void(AVFormatContext* outfmt_ctx,
                                                    AVCodecContext* enc_ctx,
                                                    AVCodec* enc)> config = [](AVFormatContext* outfmt_ctx,
                                                                                AVCodecContext* enc_ctx,
                                                                                AVCodec* enc) {})
    {
        AVCodec* enc = avcodec_find_encoder(id);
        if (!enc)
            return AVERROR_ENCODER_NOT_FOUND;
        return add_stream(enc, config);
    }
    int add_stream(const char* name, std::function<void(AVFormatContext* outfmt_ctx,
                                                    AVCodecContext* enc_ctx,
                                                    AVCodec* enc)> config = [](AVFormatContext* outfmt_ctx,
                                                                                AVCodecContext* enc_ctx,
                                                                                AVCodec* enc) {})
    {
        AVCodec* enc = avcodec_find_encoder_by_name(name);
        if (!enc)
            return AVERROR_ENCODER_NOT_FOUND;
        return add_stream(enc, config);
    }
    int read_ffm_before_write_header()
    {
        int ret = 0;
        AVFormatContext* ic = avformat_alloc_context();
        ic->flags |= AVFMT_FLAG_KEEP_SIDE_DATA;
        ret = avformat_open_input(&ic, path_.c_str(), NULL, NULL);
        avformat_close_input(&ic);
        return ret;
    }
    int write_header()
    {
        ensure_io();
        // write_header will do things to AVStreams
        // if not, st->xxxx would be NULL.
        return avformat_write_header(ctx_.get(), NULL);
    }
    int write2(int stream_index, AVFrame* pix_frame_p)
    {
        int ret = 0;
        ret = ensure_header();
        if (ret < 0)
            return ret;
        if (codecs_.find(stream_index) == codecs_.end())
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enc_ctx = codecs_[stream_index].get();
        AVFrame* swframe = pix_frame_p;
        if (AVMEDIA_TYPE_VIDEO == enc_ctx->codec_type)
            swframe = swscale(stream_index, pix_frame_p, enc_ctx);
        ret = avcodec_send_frame(enc_ctx, swframe);
        if (ret < 0)
            return ret;
        AVPacket enc_pkt = {0};
        while(1)
        {
            ret = avcodec_receive_packet(enc_ctx, &enc_pkt);
            if (ret == AVERROR(EAGAIN))
                break;
            if (ret < 0)
                break;
            int64_t dura = 0;
            int64_t& lastpts = lastpts_[enc_pkt.stream_index];

#error "you should implement how to rescale pts here, and remove this statment."

            av_log(NULL, AV_LOG_DEBUG,
                       "pkt = pts:%10lld dts:%10lld dura:%10lld\n",
                       enc_pkt.pts, enc_pkt.dts, enc_pkt.duration);
            if(!memcmp(enc_pkt.data, "\x00\x00\x00\x01\x67", 5)) {
                enc_pkt.flags |= AV_PKT_FLAG_KEY;
            }
            ret = av_interleaved_write_frame(ctx_.get(), &enc_pkt);
            av_packet_unref(&enc_pkt);
        }
        av_packet_unref(&enc_pkt);
        return ret;
    }
    int write(int stream_index, AVFrame* pix_frame_p,
              const AVRational* input_time_base = NULL)
    {
        int ret = 0;
        ret = ensure_header();
        if (ret < 0)
            return ret;
        if (codecs_.find(stream_index) == codecs_.end())
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enc_ctx = codecs_[stream_index].get();
        AVPacket enc_pkt;
        AVFrame* swframe = pix_frame_p;
        if (AVMEDIA_TYPE_VIDEO == enc_ctx->codec_type)
            swframe = swscale(stream_index, pix_frame_p, enc_ctx);
        encode(enc_pkt, stream_index, swframe, input_time_base);
        ret = av_interleaved_write_frame(ctx_.get(), &enc_pkt);
        return ret;
    }
    void rescale_packet_ts(AVPacket* enc_frame_p, const AVRational& input_time_base)
    {
        av_packet_rescale_ts(enc_frame_p, input_time_base,
                             ctx_->streams[enc_frame_p->stream_index]->time_base);
    }
    int write(AVPacket* enc_frame_p, const AVRational* input_time_base = NULL)
    {
        int ret = 0;
        ret = ensure_header();
        if (ret < 0)
            return ret;
        if (input_time_base)
            rescale_packet_ts(enc_frame_p, *input_time_base);
        return av_interleaved_write_frame(ctx_.get(), enc_frame_p);
    }
    int write_trailer()
    {
        int ret = 0;
        flush();
        return av_write_trailer(ctx_.get());
    }
    // just for test program to use this decoder for benchmark
    friend class explorer;
    struct explorer
    {
        static int encode(zff_writer& writer, AVPacket& enc_pkt,
                        int stream_index, AVFrame* pix_frame_p,
                        const AVRational* input_time_base = NULL)
        {
            return writer.encode(enc_pkt, stream_index, pix_frame_p, input_time_base);
        }
    };
protected:
    void clone_video_stream(AVCodecContext* enc_ctx, AVCodec* encoder, AVCodecContext* dec_ctx,
                            std::function<void(AVCodecContext*)> preconfig = [](AVCodecContext*) {})
    {
        if (!dec_ctx->codec || !dec_ctx->codec->decode)
        {
            avcodec_copy_context(enc_ctx, dec_ctx);
            enc_ctx->chroma_sample_location = dec_ctx->chroma_sample_location;
            preconfig(enc_ctx);
            //choose_pixel_fmt(,0,0,(AVPixelFormat)encoder->pix_fmts[0]);
        }
        else
        {
            enc_ctx->height = dec_ctx->height;
            enc_ctx->width = dec_ctx->width;
            enc_ctx->sample_aspect_ratio = dec_ctx->sample_aspect_ratio;
            /* video time_base can be set to whatever is handy and supported by encoder */
            enc_ctx->time_base = av_inv_q(dec_ctx->framerate);
        }
        /* take first format from list of supported formats */
        if (enc_ctx->pix_fmt == AV_PIX_FMT_NONE)
        {
            if (encoder->pix_fmts)
                enc_ctx->pix_fmt = encoder->pix_fmts[0];
            else
                enc_ctx->pix_fmt = dec_ctx->pix_fmt;
        }
        if (ctx_->oformat->flags & AVFMT_GLOBALHEADER)
            enc_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    void clone_audio_stream(AVCodecContext* enc_ctx, AVCodec* encoder, AVCodecContext* dec_ctx,
                            std::function<void(AVCodecContext*)> preconfig = [](AVCodecContext*) {})
    {
        if (!dec_ctx->codec || !dec_ctx->codec->decode)
        {
            avcodec_copy_context(enc_ctx, dec_ctx);
            preconfig(enc_ctx);
        }
        else
        {
            enc_ctx->sample_rate = dec_ctx->sample_rate;
            enc_ctx->channel_layout = dec_ctx->channel_layout;
            enc_ctx->channels = av_get_channel_layout_nb_channels(enc_ctx->channel_layout);
            enc_ctx->time_base = (AVRational){1, enc_ctx->sample_rate};
        }
        /* take first format from list of supported formats*/
        if (enc_ctx->sample_fmt == AV_SAMPLE_FMT_NONE)
            enc_ctx->sample_fmt = encoder->sample_fmts[0];
        if (ctx_->oformat->flags & AVFMT_GLOBALHEADER)
            enc_ctx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    int add_stream(AVCodec* enc, std::function<void(AVFormatContext* outfmt_ctx,
                                                    AVCodecContext* enc_ctx,
                                                    AVCodec* enc)> config)
    {
        int ret = 0;
        if (!enc)
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enctx = avcodec_alloc_context3(enc);
        if (!enctx)
            return AVERROR(ENOMEM);
        std::shared_ptr<AVCodecContext> enctxp(enctx,
                                               [](AVCodecContext*& p) {
                                                    avcodec_close(p);
                                                    avcodec_free_context(&p);
                                               });

        config(ctx_.get(), enctx, enc);
        if (enctx->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            // height, width, pix_fmt, time_base should be set.
            if (enctx->pix_fmt == AV_PIX_FMT_NONE)
                enctx->pix_fmt = choose_pixel_fmt(NULL, enctx, enc, AV_PIX_FMT_YUV420P);
            if (enctx->time_base.den == 0)
                enctx->time_base = {1, 25};
        }
        ret = avcodec_open2(enctx, enc, NULL);
        if (ret < 0)
            return ret;
        AVStream* newstrm = avformat_new_stream(ctx_.get(), NULL);
        newstrm->time_base = enctx->time_base;
        ret = avcodec_parameters_from_context(newstrm->codecpar, enctx);
        codecs_[newstrm->index].swap(enctxp);
        return ret;
    }
    int ensure_io()
    {
        int ret = 0;
        if (ctx_->pb)
            return ret;
        if (!(ctx_->oformat->flags & AVFMT_NOFILE) && !is_nofile_io_opened_)
        {
            ret = avio_open(&ctx_->pb, path_.c_str(), AVIO_FLAG_WRITE);
            if (ret < 0)
            {
                av_log(NULL, AV_LOG_ERROR, "Could not open output file '%s'", path_.c_str());
                return ret;
            }
            is_nofile_io_opened_ = true;
        }
        else if (ctx_->oformat->flags & AVFMT_NOFILE)
        {
            ret = avio_open(&ctx_->pb, path_.c_str(), AVIO_FLAG_READ_WRITE);
            if (ret < 0)
            {
                av_log(NULL, AV_LOG_ERROR, "Could not open output file '%s'", path_.c_str());
                return ret;
            }
        }
        return ret;
    }
    int ensure_header()
    {
        int ret = 0;
        if (!is_header_written_)
            if ((ret = write_header()) >= 0)
                is_header_written_ = true;
        return ret;
    }
    int encode(AVPacket& enc_pkt,
               int stream_index, AVFrame* pix_frame_p,
              const AVRational* input_time_base)
    {
        int ret;
        int got_frame;
        if (codecs_.find(stream_index) == codecs_.end())
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enc_ctx = codecs_[stream_index].get();
        int (*enc_func)(AVCodecContext *, AVPacket *, const AVFrame *, int *) =
            (ctx_->streams[stream_index]->codecpar->codec_type ==
             AVMEDIA_TYPE_VIDEO) ? avcodec_encode_video2 : avcodec_encode_audio2;
        enc_pkt.data = NULL;
        enc_pkt.size = 0;
        av_init_packet(&enc_pkt);
        ret = enc_func(enc_ctx, &enc_pkt, pix_frame_p, &got_frame);
        if (ret < 0)
            return ret;
        if (got_frame <= 0)
        {
            av_packet_unref(&enc_pkt);
            return 0;
        }
        /* prepare packet for muxing */
        enc_pkt.stream_index = stream_index;
        if (input_time_base)
        {
            av_packet_rescale_ts(&enc_pkt,
                             *input_time_base,
                             ctx_->streams[stream_index]->time_base);
            enc_pkt.duration = av_rescale_q(pix_frame_p->pkt_duration,
                                            *input_time_base,
                                            ctx_->streams[stream_index]->time_base);
        }
        else
        {
            av_packet_rescale_ts(&enc_pkt,
                             enc_ctx->time_base,
                             ctx_->streams[stream_index]->time_base);
            enc_pkt.duration = av_rescale_q(pix_frame_p->pkt_duration,
                                             enc_ctx->time_base,
                                             ctx_->streams[stream_index]->time_base);
        }
        av_log(NULL, AV_LOG_INFO,
               "pts:%10lld dts:%10lld dura:%10lld\n",
               enc_pkt.pts, enc_pkt.dts, enc_pkt.duration);
        return ret;
    }
    int flush()
    {
        for (int i = 0; i < ctx_->nb_streams; ++i)
        {
            flush_stream(i);
        }
    }
    int flush_stream(int stream_index)
    {
        if (codecs_.find(stream_index) == codecs_.end())
            return AVERROR_ENCODER_NOT_FOUND;
        AVCodecContext* enc_ctx = codecs_[stream_index].get();
        AVStream* st = ctx_->streams[stream_index];
        int ret = 0;
        AVPacket enc_pkt = {0};
        for (;;)
        {
            while((ret = avcodec_receive_packet(enc_ctx, &enc_pkt)) == AVERROR(EAGAIN))
            {
                ret = avcodec_send_frame(enc_ctx, NULL);
                if (ret < 0)
                    break;
            }
            if (ret < 0)
                break;
            av_packet_rescale_ts(&enc_pkt, enc_ctx->time_base,
                                 ctx_->streams[stream_index]->time_base);
            enc_pkt.duration = av_rescale_q(1,
                                             enc_ctx->time_base,
                                             ctx_->streams[stream_index]->time_base);
            av_log(NULL, AV_LOG_DEBUG,
                       "flush pts:%10lld dts:%10lld dura:%10lld\n",
                       enc_pkt.pts, enc_pkt.dts, enc_pkt.duration);
            ret = av_interleaved_write_frame(ctx_.get(), &enc_pkt);
            av_packet_unref(&enc_pkt);
        }
        av_packet_unref(&enc_pkt);
        return ret;
    }
    AVFrame* swscale(int stream_index, AVFrame* frame, AVCodecContext* enc_ctx)
    {
        if (AVMEDIA_TYPE_VIDEO != enc_ctx->codec_type)
            return frame;
        if (frame->width == enc_ctx->width
            && frame->height == enc_ctx->height
            && frame->format == (int)enc_ctx->pix_fmt)
                return frame;
        SwsContext* sws = cachedswses_[stream_index];
        AVFrame* swsframe = swframes_[stream_index];
        if (swsframe == 0)
        {
            swframes_[stream_index] = av_frame_alloc();
            swsframe = swframes_[stream_index];
            // av_frame_unref wont manage these data, but will zero data
            av_image_alloc(swsframe->data, swsframe->linesize,
                           enc_ctx->width, enc_ctx->height,
                           enc_ctx->pix_fmt, 32);
        }
        // ugly clear side data.
        if (swsframe->nb_side_data)
        {
            AVFrame clrframe = {0};
            std::swap(clrframe.side_data, swsframe->side_data);
            std::swap(clrframe.nb_side_data, swsframe->nb_side_data);
            av_frame_unref(&clrframe);
        }
        av_dict_free(&swsframe->metadata);
        swsframe->format = enc_ctx->pix_fmt;
        swsframe->width = enc_ctx->width;
        swsframe->height = enc_ctx->height;
        sws = sws_getCachedContext(sws, frame->width, frame->height, (AVPixelFormat)frame->format,
                             swsframe->width, swsframe->height, (AVPixelFormat)swsframe->format,
                             SWS_BICUBIC, 0, 0, 0);
        sws_scale(sws, frame->data, frame->linesize, 0, frame->height,
                  swsframe->data, swsframe->linesize);
        av_frame_copy_props(swsframe, frame);
        return swsframe;
    }
    void clear_sw()
    {
        std::for_each(swframes_.begin(), swframes_.end(),
                      [](std::pair<const int, AVFrame*>& el) {
                        av_freep(&el.second->data[0]);
                        av_frame_free(&el.second);
                      });
        std::for_each(cachedswses_.begin(), cachedswses_.end(),
                      [](std::pair<const int, SwsContext*>& el) {
                        sws_freeContext(el.second);
                      });
    }
    std::shared_ptr<AVFormatContext> ctx_;
    std::unordered_map<int, std::shared_ptr<AVCodecContext> > codecs_;
    std::unordered_map<int, int64_t> lastpts_;
    std::unordered_map<int, int> pktcnt_;
    std::unordered_map<int, AVFrame*> swframes_;
    std::unordered_map<int, SwsContext*> cachedswses_;
    std::string path_;
    bool is_header_written_;
    bool is_nofile_io_opened_;
};

// the following 2 io context are just for benchmark
class zff_nullio
{
public:
    zff_nullio()
    {
        AVIOContext* avio_ctx = NULL;
        // opaque can not be NULL, reference to av_close()
        // opaque, buffer should be malloc by av_malloc.
        avio_ctx = avio_alloc_context(dummy_, 64, 1, NULL, NULL, &write_packet, &seek);
        if (avio_ctx) {
            ctx_.reset(avio_ctx, [](AVIOContext* p) { avio_context_free(&p); });
        }
    }
    operator bool ()
    {
        return (bool)ctx_;
    }
    operator AVIOContext* ()
    {
        return ctx_.get();
    }
    static int write_packet(void *opaque, uint8_t *buf, int buf_size)
    {
        return buf_size;
    }
    static int64_t seek (void *opaque, int64_t offset, int whence)
    {
        return 1;
    }
private:
    uint8_t dummy_[64];
    std::shared_ptr<AVIOContext> ctx_;
};
class zff_memio
{
// implement code from https://gist.github.com/AlexVestin/15b90d72f51ff7521cd7ce4b70056dff
// just a wrapper
public:
    ~zff_memio()
    {
        ctx_.reset();
        if (bd_.buf)
            av_freep(&bd_.buf);
    }
    zff_memio(size_t bd_buf_size = 4096)
    {
        bd_.ptr  = bd_.buf = (uint8_t*)av_malloc(bd_buf_size);

        if (!bd_.buf) {
            return;
        }
        bd_.size = bd_.room = bd_buf_size;

        uint8_t* avio_ctx_buffer = NULL;
        const size_t avio_ctx_buffer_size = 4096;
        AVIOContext* avio_ctx = NULL;

        avio_ctx_buffer = (uint8_t*)av_malloc(avio_ctx_buffer_size);
        if (avio_ctx_buffer) {
            avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size, 1, &bd_, NULL, &write_packet, &seek);
            if (avio_ctx) {
                ctx_.reset(avio_ctx, [](AVIOContext* p) { avio_context_free(&p); });
            }
        }
    }
    operator bool ()
    {
        return (bool)ctx_;
    }
    operator AVIOContext* ()
    {
        return ctx_.get();
    }
    static int write_packet(void *opaque, uint8_t *buf, int buf_size)
    {
        struct buffer_data *bd = (struct buffer_data *)opaque;
        while (buf_size > bd->room) {
            int64_t offset = bd->ptr - bd->buf;
            bd->buf = (uint8_t*)av_realloc_f(bd->buf, 2, bd->size);
            if (!bd->buf)
                return AVERROR(ENOMEM);
            bd->size *= 2;
            bd->ptr = bd->buf + offset;
            bd->room = bd->size - offset;
        }
        //printf("write packet pkt_size:%d used_buf_size:%zu buf_size:%zu buf_room:%zu\n", buf_size, bd->ptr-bd->buf, bd->size, bd->room);

        memcpy(bd->ptr, buf, buf_size);
        bd->ptr  += buf_size;
        bd->room -= buf_size;

        //free(buf);
        return buf_size;
    }
    static int64_t seek (void *opaque, int64_t offset, int whence)
    {
        struct buffer_data *bd = (struct buffer_data *)opaque;
        switch(whence){
            case SEEK_SET:
                bd->ptr = bd->buf + offset;
                return (int64_t)bd->ptr;
                break;
            case SEEK_CUR:
                bd->ptr += offset;
                break;
            case SEEK_END:
                bd->ptr = (bd->buf + bd->size) + offset;
                return (int64_t)bd->ptr;
                break;
            case AVSEEK_SIZE:
                return bd->size;
                break;
            default:
               return -1;
        }
        return 1;
    }
private:
    struct buffer_data
    {
        uint8_t *buf;
        int size;
        uint8_t *ptr;
        size_t room; ///< size left in the buffer
    };
    buffer_data bd_;
    std::shared_ptr<AVIOContext> ctx_;
};

};

};
#endif //__ZHELPER_FFMPEG_H__
