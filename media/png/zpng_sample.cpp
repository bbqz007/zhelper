#include "zpng.h"
#include <fstream>

using namespace std;

vector<png_byte> loadfile(const char* name)
{
	vector<png_byte> raw;
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

void savefile(const char* name, const vector<png_byte>& bytes)
{
	ofstream ofs(name, ios_base::binary|ios_base::out);
	if (ofs.is_open())
	{
		ofs.write((char*)&bytes[0], bytes.size());
	}
}

int main()
{
    using namespace zhelper::zpng;
    png_uint_32 width, height;
    png_byte color_type, bit_depth;
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

    zpng_writer writer;
    writer.open("images/zpng.png");
    writer._try(
        [&]() {
            writer.set_IHDR(width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
            writer.set_compression_level(6);
        })._catch([](int) {});
    writer.write_header();
    writer.write_image(rgb);
    writer.write_tailer();

    std::vector<png_byte> readbuf = loadfile("images/out.png");
    std::vector<png_byte> writebuf;

    rgb.clear();

    zpng_reader mem_reader;
    mem_reader.open(readbuf);
    mem_reader.read_header();
    mem_reader._try(
        [&]() {
            width = mem_reader.image_width();
            height = mem_reader.image_height();
            color_type = mem_reader.color_type();
            bit_depth = mem_reader.bit_depth();
        })._catch([](int) {});
    mem_reader.read_image(rgb);
    mem_reader.read_tailer();

    zpng_writer mem_writer;
    mem_writer.open(writebuf);
    mem_writer._try(
        [&]() {
            mem_writer.set_IHDR(width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        })._catch([](int) {});
    mem_writer.write_header();
    mem_writer.write_image(rgb);
    mem_writer.write_tailer();

    savefile("images/zpng_mem.png", writebuf);

    return 0;
}
