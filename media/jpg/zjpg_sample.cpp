#include "zjpg.h"
#include <fstream>

using namespace std;
using namespace zhelper::zjpeg;

vector<jpeg_byte> loadfile(const char* name)
{
	vector<jpeg_byte> raw;
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

void savefile(const char* name, const vector<jpeg_byte>& bytes)
{
	ofstream ofs(name, ios_base::binary|ios_base::out);
	if (ofs.is_open())
	{
		ofs.write((char*)&bytes[0], bytes.size());
	}
}

int main()
{
    using namespace zhelper::zjpeg;
    std::vector<jpeg_byte> rgb;

    zjpeg_reader reader;
    reader.read("images/out.jpg", rgb);

    zjpeg_writer writer;
    writer.set_WxH(reader.image_width(), reader.image_height());
    writer.set_color();
    writer.write("images/out_zjpeg.jpg", rgb);

    rgb.clear();
    std::vector<jpeg_byte> jpg = loadfile("images/out.jpg");
    reader.read(jpg, rgb);
    jpg.clear();
    writer.set_WxH(reader.image_width(), reader.image_height());
    writer.set_color();
    writer.write(jpg, rgb);

    savefile("images/out_zjpeg_mem.jpg", jpg);
    return 0;
}
