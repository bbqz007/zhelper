#include <zffmpeg.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include <math.h>

using namespace std;


void traverse_packets(const char* name)
{
    AVFormatContext* ifmt = NULL;
    AVPacket packet = {0}; packet.data = NULL, packet.size = 0;
    int err = 0;
    err = avformat_open_input(&ifmt, name, NULL, NULL);
    map<int, int> count;
    do
    {
        err = av_read_frame(ifmt, &packet);
        fprintf(stdout, "pts:%lld dts:%lld pos:%lld dura:%lld idx:%d size:%d flags:%x\n",
                packet.pts, packet.dts,
                packet.pos, packet.duration,
                packet.stream_index, packet.size, packet.flags);
        ++count[packet.stream_index];
        av_packet_unref(&packet);
    } while (0 == err);
    fprintf(stdout, "total 0:%d 1:%d packets\n", count[0], count[1]);
    avformat_close_input(&ifmt);
}

void zff_traverse_packets(const char* name)
{
    using namespace zhelper::zff;
    using namespace cv;
    zff_options opts;
        //opts.set("rtsp_flags", "listen");
    zff_reader reader;
    reader.open(name, NULL, opts.options());
    reader.read_header();
    reader.open_vedio_stream();
    AVPacket inpkt;
    AVFrame* frame = NULL;

    av_init_packet(&inpkt);
    for(; reader.poll(&frame, &inpkt) >= 0;
            av_packet_unref(&inpkt))
    {
        if (!frame || !frame->pict_type)
            continue;
        fprintf(stdout, "ptk = pts:%lld dts:%lld pos:%lld dura:%lld idx:%d size:%d flags:%x\n",
                inpkt.pts, inpkt.dts,
                inpkt.pos, inpkt.duration,
                inpkt.stream_index, inpkt.size, inpkt.flags);
        fprintf(stdout, "frm = pts:%lld dts:%lld pos:%lld dura:%lld flags:%x type:(%d) repeat:%d\n",
                frame->pts, frame->pkt_dts,
                frame->pkt_pos, frame->pkt_duration,
                frame->flags, frame->pict_type,
                frame->repeat_pict);
    }
}


int main(int argc, const char** argv)
{
    avformat_network_init();
    av_log_set_level(AV_LOG_QUIET);
    av_register_all();

    if (argc == 2)
    {
        if (argv[1][0] == '1')
            traverse_packets("images/sample.mp4");
        else
            traverse_packets("rtsp://localhost:1235/test1.sdp");
        return 0;
    }
    else if (argc == 3)
    {
        if (argv[2][0] == '1')
            zff_traverse_packets("images/sample.mp4");
        else
            zff_traverse_packets("rtsp://localhost:1235/test1.sdp");
        return 0;
    }

    using namespace zhelper::zff;
    zff_reader reader;
    reader.open("images/sample.mp4");
    reader.read_header();
    reader.open_vedio_stream();

    zff_writer writer;
#if 1
    writer.open("images/out.mp4");
    writer.clone_video_stream(reader, "libx264",
                              [](AVCodecContext* cc) {
                                    cc->time_base = (AVRational){1, 15};
                                  });
#endif
    AVFrame* frame = 0;
    reader.dump();
    writer.dump();
    AVPacket inpkt;
#if 1
    av_init_packet(&inpkt);
    for(; reader.poll(&frame, &inpkt) >= 0;
            av_packet_unref(&inpkt))
#else
    while(reader.poll(&frame) >= 0)
#endif
    {
        if (!frame || !frame->pict_type)
            continue;
        fprintf(stdout, "frm = pts:%lld dts:%lld pos:%lld dura:%lld flags:%x type:(%d) repeat:%d\n",
                frame->pts, frame->pkt_dts,
                frame->pkt_pos, frame->pkt_duration,
                frame->flags, frame->pict_type,
                frame->repeat_pict);
#if 0
	// todo: correct the pts
 #endif
        //frame->pict_type = AV_PICTURE_TYPE_NONE;
        static int count = 0;
        if (frame->pkt_dts == frame->pts)
            frame->pkt_dts -= frame->pkt_duration;
        frame->pts /= frame->pkt_duration;
        frame->pkt_dts /= frame->pkt_duration;
        frame->pkt_duration = 1;
#if 1
	// todo: do filtering on this frame
#endif
        fprintf(stdout, "fRm = pts:%lld dts:%lld pos:%lld dura:%lld flags:%x type:(%d) repeat:%d\n",
                frame->pts, frame->pkt_dts,
                frame->pkt_pos, frame->pkt_duration,
                frame->flags, frame->pict_type,
                frame->repeat_pict);
        writer.write2(0, frame);
        //writer.write(0, frame);
        av_frame_free(&frame);
    }
    writer.write_trailer();

    avformat_network_deinit();

    return 0;
}
