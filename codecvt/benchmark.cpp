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
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *     SOFTWARE.
 *
 */
#include <vector>
#include <algorithm>
#include <deque>
#include <iostream>
#include <fstream>
#include <benchmark/benchmark.h>
#include <iconv.h>
#include <unicode/ucnv.h>

#include <utf8.h>

#include <utility>
#include <codecvt>
#include <locale>

#include <errno.h>

void BM_template(benchmark::State& state)
{

}

void BM_iconv_openclose_ascii2unicode(benchmark::State& state)
{
    iconv_t cvt;
    while (state.KeepRunning())
    {
        cvt = iconv_open("ASCII", "UNICODE");
        iconv_close(cvt);
    }
}

void BM_iconv_openclose_utf82unicode(benchmark::State& state)
{
    iconv_t cvt;
    while (state.KeepRunning())
    {
        cvt = iconv_open("UTF8", "UNICODE");
        iconv_close(cvt);
    }
}

void BM_iconv_openclose_gb180302unicode(benchmark::State& state)
{
    iconv_t cvt;
    while (state.KeepRunning())
    {
        cvt = iconv_open("GB18030", "UNICODE");
        iconv_close(cvt);
    }
}

void BM_iconv_openclose_gb180302utf8(benchmark::State& state)
{
    iconv_t cvt;
    while (state.KeepRunning())
    {
        cvt = iconv_open("GB18030", "UTF8");
        iconv_close(cvt);
    }
}

void BM_codecvt_openclose_utf162utf8(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        (void)
        std::wstring_convert<
        std::codecvt_utf8_utf16<char16_t>, char16_t>{};
    }
}

void BM_codecvt_openclose_utf82unicode(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        (void)
        std::wstring_convert<
        std::codecvt_utf8<wchar_t>, wchar_t>{};
    }
}

BENCHMARK(BM_iconv_openclose_ascii2unicode);
BENCHMARK(BM_iconv_openclose_utf82unicode);
BENCHMARK(BM_iconv_openclose_gb180302unicode);
BENCHMARK(BM_iconv_openclose_gb180302utf8);
BENCHMARK(BM_codecvt_openclose_utf162utf8);
BENCHMARK(BM_codecvt_openclose_utf82unicode);

using namespace std;

vector<char> loadfile(const char* name)
{
    vector<char> raw;
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

vector<char> g_us_utf8;
vector<char> g_us_utf16;
vector<char> g_zh_utf8;
vector<char> g_zh_utf16;
vector<char> g_zhs_utf8;
vector<char> g_zhs_utf16;
vector<char> g_zh_gb;
vector<char> g_jp_utf8;
vector<char> g_jp_utf16;
vector<char> g_jp_gb;
vector<char> g_jp_utf8_s;
vector<char> g_jp_utf16_s;

vector<char> g_us_utf32;
vector<char> g_zh_utf32;
vector<char> g_jp_utf32;
void init()
{
    g_us_utf8 = loadfile("text.us.utf8");
    g_us_utf16 = loadfile("text.us.unicode");
    g_zh_utf8 = loadfile("text.zh.utf8");
    g_zh_utf16 = loadfile("text.zh.unicode");
    g_zhs_utf8 = loadfile("text.zh.utf8.s");
    g_zhs_utf16 = loadfile("text.zh.unicode.s");
    g_zh_gb = loadfile("text.zh.gb18030");
    g_jp_utf8 = loadfile("text.jp.utf8");
    g_jp_utf16 = loadfile("text.jp.unicode");
    g_jp_gb = loadfile("text.jp.gb18030");
    g_jp_utf8_s = loadfile("text.jp.utf8.s");
    g_jp_utf16_s = loadfile("text.jp.unicode.s");
    if (sizeof(wchar_t) == 4)
    {
        g_us_utf32 = loadfile("text.us.utf32");
        g_zh_utf32 = loadfile("text.zh.utf32");
        g_jp_utf32 = loadfile("text.jp.utf32");
    }
}
void BM_iconv_utf82unicode1(benchmark::State& state, vector<char>& in,
                           char* incode, char* outcode);
void BM_iconv_utf82unicode2(benchmark::State& state, vector<char>& in,
                           char* incode, char* outcode);
void BM_iconv_utf82unicode(benchmark::State& state, vector<char>& in,
                           char* incode, char* outcode)
{
    if (state.range(1) == 1)
    {
        BM_iconv_utf82unicode1(state, in, incode, outcode);
        return;
    }
    if (state.range(1) == 2)
    {
        BM_iconv_utf82unicode2(state, in, incode, outcode);
        return;
    }
    iconv_t cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        cvt = iconv_open(outcode, incode);
        char* inp = &in[0];
        size_t inb = in.size();
        char* outp = buf;
        size_t outb = sz;
        while (inb)
        {
            if (-1 == iconv(cvt, &inp, &inb, &outp, &outb)
                 && errno != E2BIG)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", errno, inb, in.size());
                     exit(0);
                 }

            outp = buf;
            outb = sz;
        }

        iconv_close(cvt);
    }
}

void BM_iconv_utf82unicode1(benchmark::State& state, vector<char>& in,
                           char* incode, char* outcode)
{
    iconv_t cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        string outstr;
        outstr.resize(sz);
        char* buf = (char*)outstr.c_str();
        cvt = iconv_open(outcode, incode);
        char* inp = &in[0];
        size_t inb = in.size();
        char* outp = buf;
        size_t outb = sz;
        while (inb)
        {
            if (-1 == iconv(cvt, &inp, &inb, &outp, &outb)
                 && errno != E2BIG)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", errno, inb, in.size());
                     exit(0);
                 }
            if (inb == 0)
            {
                outstr.resize(outstr.size() - outb);
                break;
            }
            outstr.resize(outstr.size() + sz);
            buf = (char*)outstr.c_str() + outstr.size() - sz - outb;
            outp = buf;
            outb += sz;
        }

        iconv_close(cvt);
    }
}

void BM_iconv_utf82unicode2(benchmark::State& state, vector<char>& in,
                           char* incode, char* outcode)
{
    iconv_t cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    cvt = iconv_open(outcode, incode);
    while (state.KeepRunning())
    {
        string outstr;
        outstr.resize(sz);
        char* buf = (char*)outstr.c_str();

        char* inp = &in[0];
        size_t inb = in.size();
        char* outp = buf;
        size_t outb = sz;
        while (inb)
        {
            if (-1 == iconv(cvt, &inp, &inb, &outp, &outb)
                 && errno != E2BIG)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", errno, inb, in.size());
                     exit(0);
                 }
            if (inb == 0)
            {
                outstr.resize(outstr.size() - outb);
                break;
            }
            outstr.resize(outstr.size() + sz);
            buf = (char*)outstr.c_str() + outstr.size() - sz - outb;
            outp = buf;
            outb += sz;
        }


    }
    iconv_close(cvt);
}


void BM_iconv_us_utf82unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf8, "UTF8", "UNICODE");
}

void BM_iconv_zh_utf82unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_utf8, "UTF8", "UNICODE");
}

void BM_iconv_zhs_utf82unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zhs_utf8, "UTF8", "UNICODE");
}

void BM_iconv_jp_utf82unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_jp_utf8, "UTF8", "UNICODE");
}

void BM_iconv_jps_utf82unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_jp_utf8_s, "UTF8", "UNICODE");
}

void BM_iconv_us_unicode2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf16, "UNICODE", "UTF8");
}

void BM_iconv_zh_unicode2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_utf16, "UNICODE", "UTF8");
}

void BM_iconv_zhs_unicode2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zhs_utf16, "UNICODE", "UTF8");
}

void BM_iconv_jp_unicode2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_jp_utf16, "UNICODE", "UTF8");
}

void BM_iconv_jps_unicode2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_jp_utf16_s, "UNICODE", "UTF8");
}

/////////////////

void BM_iconv_us_gb2unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf8, "GB18030", "UNICODE");
}

void BM_iconv_us_unicode2gb(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf16, "UNICODE", "GB18030");
}

void BM_iconv_us_gb2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf8, "GB18030", "UTF8");
}

void BM_iconv_us_utf82gb(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_us_utf8, "UTF8", "GB18030");
}

void BM_iconv_zh_gb2unicode(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_gb, "GB18030", "UNICODE");
}

void BM_iconv_zh_unicode2gb(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_utf16, "UNICODE", "GB18030");
}

void BM_iconv_zh_gb2utf8(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_gb, "GB18030", "UTF8");
}

void BM_iconv_zh_utf82gb(benchmark::State& state)
{
    BM_iconv_utf82unicode(state, g_zh_utf8, "UTF8", "GB18030");
}


void BM_codecvt_utf82unicode_1(benchmark::State& state, vector<char>& in);
void BM_codecvt_utf82unicode_2(benchmark::State& state, vector<char>& in);
void BM_codecvt_utf82unicode(benchmark::State& state, vector<char>& in)
{
    if (state.range(0) == 1)
    {
        BM_codecvt_utf82unicode_1(state, in);
        return;
    }
    else if (state.range(0) == 2)
    {
        BM_codecvt_utf82unicode_2(state, in);
        return;
    }
    while (state.KeepRunning())
    {
        char* inp = &in[0];
        char* inep = &in[0] + in.size();
        std::u16string wstr =
        std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t>{}.from_bytes(inp, inep);
        (void)wstr.begin();
    }
}

void BM_codecvt_utf82unicode_1(benchmark::State& state, vector<char>& in)
{

    while (state.KeepRunning())
    {
        char* inp = &in[0];
        char* inep = &in[0] + in.size();
        std::wstring_convert<
            std::codecvt_utf8<char16_t>, char16_t> cvt;
        try
        {
            std::u16string wstr =
            cvt.from_bytes(inp, inep);
            (void)wstr.begin();
        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}

void BM_codecvt_utf82unicode_2(benchmark::State& state, vector<char>& in)
{
    std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t> cvt;
    try
    {
        while (state.KeepRunning())
        {
            char* inp = &in[0];
            char* inep = &in[0] + in.size();
            std::u16string wstr =
            cvt.from_bytes(inp, inep);
            (void)wstr.begin();
        }
    }
    catch(std::range_error& err)
    {
        fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                     exit(0);
    }
}

void BM_codecvt_unicode2utf8_1(benchmark::State& state, vector<char>& in);
void BM_codecvt_unicode2utf8_2(benchmark::State& state, vector<char>& in);
void BM_codecvt_unicode2utf8(benchmark::State& state, vector<char>& in)
{
    if (state.range(0) == 1)
    {
        BM_codecvt_unicode2utf8_1(state, in);
        return;
    }
    else if (state.range(0) == 2)
    {
        BM_codecvt_unicode2utf8_2(state, in);
        return;
    }
    while (state.KeepRunning())
    {
        char16_t* inp = (char16_t*)&in[0];
        char16_t* inep = (char16_t*)(&in[0] + in.size());

        std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t> cvt;
        try
        {
            std::string str = cvt.to_bytes(inp, inep);
            (void)str.begin();
        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}

void BM_codecvt_unicode2utf8_1(benchmark::State& state, vector<char>& in)
{
    while (state.KeepRunning())
    {
        char16_t* inp = (char16_t*)&in[0];
        char16_t* inep = (char16_t*)(&in[0] + in.size());
        std::string str =
        std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t>{}.to_bytes(inp, inep);
        (void)str.begin();
    }
}

void BM_codecvt_unicode2utf8_2(benchmark::State& state, vector<char>& in)
{
    std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t> cvt;
    try
    {
        while (state.KeepRunning())
        {
            char16_t* inp = (char16_t*)&in[0];
            char16_t* inep = (char16_t*)(&in[0] + in.size());
            std::string str =
            cvt.to_bytes(inp, inep);
            (void)str.begin();
        }
    }
    catch(std::range_error& err)
    {
        fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                     exit(0);
    }
}

void BM_codecvt_us_utf82unicode(benchmark::State& state)
{
    BM_codecvt_utf82unicode(state, g_us_utf8);
}

void BM_codecvt_zh_utf82unicode(benchmark::State& state)
{
    BM_codecvt_utf82unicode(state, g_zh_utf8);
}

void BM_codecvt_zhs_utf82unicode(benchmark::State& state)
{
    BM_codecvt_utf82unicode(state, g_zhs_utf8);
}

void BM_codecvt_jp_utf82unicode(benchmark::State& state)
{
    BM_codecvt_utf82unicode(state, g_jp_utf8);
}

void BM_codecvt_jps_utf82unicode(benchmark::State& state)
{
    BM_codecvt_utf82unicode(state, g_jp_utf8_s);
}

void BM_codecvt_us_unicode2utf8(benchmark::State& state)
{
    BM_codecvt_unicode2utf8(state, g_us_utf16);
}

void BM_codecvt_zh_unicode2utf8(benchmark::State& state)
{
    BM_codecvt_unicode2utf8(state, g_zh_utf16);
}

void BM_codecvt_zhs_unicode2utf8(benchmark::State& state)
{
    BM_codecvt_unicode2utf8(state, g_zhs_utf16);
}

void BM_codecvt_jp_unicode2utf8(benchmark::State& state)
{
    BM_codecvt_unicode2utf8(state, g_jp_utf16);
}

void BM_codecvt_jps_unicode2utf8(benchmark::State& state)
{
    BM_codecvt_unicode2utf8(state, g_jp_utf16_s);
}

////////////////
// std::wstring_convert code sample from https://en.cppreference.com/w/cpp/locale/wstring_convert/~wstring_convert
template<class Facet>
struct deletable_facet : Facet
{
    template<class ...Args>
    deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    ~deletable_facet() {}
};
typedef deletable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>> gbfacet_t;

void BM_codecvt_unicode2x(benchmark::State& state, vector<char>& in, const char* cvtcode)
{
    //cout << std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(std::locale(cvtcode)).encoding() << endl;
    while (state.KeepRunning())
    {
        wchar_t* inp = (wchar_t*)&in[0];
        wchar_t* inep = (wchar_t*)(&in[0] + in.size());

        std::wstring_convert<gbfacet_t, wchar_t> cvt(new gbfacet_t(cvtcode));
        try
        {
            std::string str = cvt.to_bytes(inp, inep);
            (void)str.begin();
        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}

void BM_codecvt_x2unicode(benchmark::State& state, vector<char>& in, const char* cvtcode)
{

    while (state.KeepRunning())
    {
        char* inp = &in[0];
        char* inep = &in[0] + in.size();
        std::wstring_convert<gbfacet_t, wchar_t> cvt(new gbfacet_t(cvtcode));
        try
        {
            std::wstring wstr =
            cvt.from_bytes(inp, inep);
            (void)wstr.begin();
        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}
void BM_codecvt_us_unicode2gb(benchmark::State& state)
{
    BM_codecvt_unicode2x(state,
                         (sizeof(wchar_t) == 4) ? g_us_utf32 : g_us_utf16, "zh_CN.gb18030");
}

void BM_codecvt_zh_unicode2gb(benchmark::State& state)
{
    BM_codecvt_unicode2x(state,
                         (sizeof(wchar_t) == 4) ? g_zh_utf32 : g_zh_utf16, "zh_CN.gb18030");
}

void BM_codecvt_jp_unicode2gb(benchmark::State& state)
{
    BM_codecvt_unicode2x(state,
                         (sizeof(wchar_t) == 4) ? g_jp_utf32 : g_jp_utf16, "zh_CN.gb18030");
}

void BM_codecvt_us_gb2unicode(benchmark::State& state)
{
    BM_codecvt_x2unicode(state, g_us_utf8, "zh_CN.gb18030");
}

void BM_codecvt_zh_gb2unicode(benchmark::State& state)
{
    BM_codecvt_x2unicode(state, g_zh_gb, "zh_CN.gb18030");
}

void BM_codecvt_jp_gb2unicode(benchmark::State& state)
{
    BM_codecvt_x2unicode(state, g_jp_gb, "zh_CN.gb18030");
}

////////////////

void BM_icu1_x2unicode(benchmark::State& state, vector<char>& in,
                           char* cvtcode);
void BM_icu2_x2unicode(benchmark::State& state, vector<char>& in,
                           char* cvtcode);
void BM_icu_x2unicode(benchmark::State& state, vector<char>& in,
                           char* cvtcode)
{
    if (state.range(1) == 1)
    {
        BM_icu1_x2unicode(state, in, cvtcode);
        return;
    }
    if (state.range(1) == 2)
    {
        //BM_icu2_x2unicode(state, in, cvtcode);
        return;
    }
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        cvt = ucnv_open(cvtcode, &err);
        const char* inp = &in[0];
        const char* inep = inp + in.size();
        UChar* outp = (UChar*)buf;
        UChar* outep = (UChar*)(buf + sz);
        while (inp != inep)
        {
            err = U_ZERO_ERROR;
            ucnv_toUnicode(cvt, &outp, outep, &inp, inep, 0, FALSE, &err);
            if (err
                 && err != U_BUFFER_OVERFLOW_ERROR)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", (int)err, inep - inp, in.size());
                     exit(0);
                 }
            outp = (UChar*)buf;
            outep = (UChar*)(buf + sz);
        }

        ucnv_close(cvt);
    }
}

void BM_icu1_x2unicode(benchmark::State& state, vector<char>& in,
                           char* cvtcode)
{
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        cvt = ucnv_open(cvtcode, &err);
        const char* inp = &in[0];
        const char* inep = inp + in.size();
        string outstr;
        outstr.resize(sz);
        buf = (char*)outstr.c_str();
        UChar* outp = (UChar*)buf;
        UChar* outep = (UChar*)(buf + sz);
        while (inp != inep)
        {
            err = U_ZERO_ERROR;
            ucnv_toUnicode(cvt, &outp, outep, &inp, inep, 0, FALSE, &err);
            if (err
                 && err != U_BUFFER_OVERFLOW_ERROR)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", (int)err, inep - inp, in.size());
                     exit(0);
                 }
            int distance = (char*)outp - (char*)buf;
            outstr.resize(outstr.size() + sz);
            buf = (char*)outstr.c_str();
            outp = (UChar*)(buf + distance);
            outep = (UChar*)(buf + outstr.size());
        }
        outstr.resize((char*)outp - (char*)buf);
        ucnv_close(cvt);
    }
}

void BM_icu_us_utf82unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_us_utf8, "UTF8");
}

void BM_icu_zh_utf82unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_zh_utf8, "UTF8");
}

void BM_icu_zhs_utf82unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_zhs_utf8, "UTF8");
}

void BM_icu_jp_utf82unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_jp_utf8, "UTF8");
}

void BM_icu_jps_utf82unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_jp_utf8_s, "UTF8");
}

void BM_icu_us_gb2unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_us_utf8, "GB18030");
}

void BM_icu_zh_gb2unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_zh_gb, "GB18030");
}

void BM_icu_jp_gb2unicode(benchmark::State& state)
{
    BM_icu_x2unicode(state, g_jp_gb, "GB18030");
}

void BM_icu1_unicode2x(benchmark::State& state, vector<char>& in,
                           char* cvtcode);
void BM_icu2_unicode2x(benchmark::State& state, vector<char>& in,
                           char* cvtcode);
void BM_icu_unicode2x(benchmark::State& state, vector<char>& in,
                           char* cvtcode)
{
    if (state.range(1) == 1)
    {
        BM_icu1_unicode2x(state, in, cvtcode);
        return;
    }
    if (state.range(1) == 2)
    {
        //BM_icu2_unicode2x(state, in, cvtcode);
        return;
    }
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        cvt = ucnv_open(cvtcode, &err);
        const UChar* inp = (const UChar*)&in[0];
        const UChar* inep = (const UChar*)(inp + in.size());
        char* outp = buf;
        char* outep = buf + sz;
        while (inp != inep)
        {
            err = U_ZERO_ERROR;
            ucnv_fromUnicode(cvt, &outp, outep, &inp, inep, 0, FALSE, &err);
            if (err
                 && err != U_BUFFER_OVERFLOW_ERROR)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", (int)err, inep - inp, in.size());
                     exit(0);
                 }
            outp = buf;
            outep = buf + sz;
        }

        ucnv_close(cvt);
    }
}

void BM_icu1_unicode2x(benchmark::State& state, vector<char>& in,
                           char* cvtcode)
{
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cvt;
    const size_t sz = state.range(0);
    string s;
    s.resize(sz);
    char* buf = (char*)s.c_str();
    while (state.KeepRunning())
    {
        cvt = ucnv_open(cvtcode, &err);
        const UChar* inp = (const UChar*)&in[0];
        const UChar* inep = (const UChar*)(inp + in.size());
        string outstr;
        outstr.resize(sz);
        buf = (char*)outstr.c_str();
        char* outp = buf;
        char* outep = buf + sz;
        while (inp != inep)
        {
            err = U_ZERO_ERROR;
            ucnv_fromUnicode(cvt, &outp, outep, &inp, inep, 0, FALSE, &err);
            if (err
                 && err != U_BUFFER_OVERFLOW_ERROR)
                 {
                     fprintf(stderr, "errno: %2d, inleft:%d/%d\n", (int)err, inep - inp, in.size());
                     exit(0);
                 }
            int distance = outp - buf;
            outstr.resize(outstr.size() + sz);
            buf = (char*)outstr.c_str();
            outp = buf + distance;
            outep = buf + outstr.size();
        }
        outstr.resize(outp - buf);
        ucnv_close(cvt);
    }
}

void BM_icu_us_unicode2utf8(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_us_utf16, "UTF8");
}

void BM_icu_zh_unicode2utf8(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_zh_utf16, "UTF8");
}

void BM_icu_zhs_unicode2utf8(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_zhs_utf16, "UTF8");
}

void BM_icu_jp_unicode2utf8(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_jp_utf16, "UTF8");
}

void BM_icu_jps_unicode2utf8(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_jp_utf16_s, "UTF8");
}

void BM_icu_us_unicode2gb(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_us_utf16, "GB18030");
}

void BM_icu_zh_unicode2gb(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_zh_utf16, "GB18030");
}

void BM_icu_jp_unicode2gb(benchmark::State& state)
{
    BM_icu_unicode2x(state, g_jp_utf16, "GB18030");
}

////////////////////


void BM_utf8cpp_iterator(benchmark::State& state, vector<char>& in)
{
    {
        char16_t* inp = (char16_t*)&in[0];
        char16_t* inep = (char16_t*)(&in[0] + in.size());

        std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t> cvt;
        try
        {
            std::string str = cvt.to_bytes(inp, inep);
            if (state.range(0) == 1)
            {
                while (state.KeepRunning())
                {
                    string::iterator it = str.begin();
                    string::iterator ite = str.end();
                    while (it < ite)
                    {
                        utf8::next(it, ite);
                    }
                }
            }
            else
            {
                while (state.KeepRunning())
                {
                    string::iterator it = str.begin();
                    string::iterator ite = str.end();
                    while (it < ite)
                    {
                        utf8::unchecked::next(it);
                    }
                }
            }
        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}

void BM_utf8cpp_us_iterator(benchmark::State& state)
{
    BM_utf8cpp_iterator(state, g_us_utf16);
}

void BM_utf8cpp_zh_iterator(benchmark::State& state)
{
    BM_utf8cpp_iterator(state, g_zh_utf16);
}

void BM_utf8cpp_jp_iterator(benchmark::State& state)
{
    BM_utf8cpp_iterator(state, g_jp_utf16);
}

void BM_icu_iterator(benchmark::State& state, vector<char>& in)
{
    {
        char16_t* inp = (char16_t*)&in[0];
        char16_t* inep = (char16_t*)(&in[0] + in.size());

        std::wstring_convert<
        std::codecvt_utf8<char16_t>, char16_t> cvt;
        try
        {
            std::string str = cvt.to_bytes(inp, inep);

            while (state.KeepRunning())
            {
                const char* it = str.c_str();
                const char* ite = it + str.size();
                UErrorCode err = U_ZERO_ERROR;
                UConverter* cvt = ucnv_open("utf8", &err);
                while (it < ite)
                {
                    err = U_ZERO_ERROR;
                    ucnv_getNextUChar(cvt, &it, ite, &err);
                    if (err
                         && err != U_BUFFER_OVERFLOW_ERROR)
                         {
                             fprintf(stderr, "errno: %2d, inleft:%d/%d\n", (int)err, inep - inp, in.size());
                             exit(0);
                         }
                }
                ucnv_close(cvt);
            }

        }
        catch(std::range_error& err)
        {
            fprintf(stderr, "range_error converted:%d/%d\n", (int)cvt.converted(), in.size());
                         exit(0);
        }
    }
}

void BM_icu_us_iterator(benchmark::State& state)
{
    BM_icu_iterator(state, g_us_utf16);
}

void BM_icu_zh_iterator(benchmark::State& state)
{
    BM_icu_iterator(state, g_zh_utf16);
}

void BM_icu_jp_iterator(benchmark::State& state)
{
    BM_icu_iterator(state, g_jp_utf16);
}


////////////////////

static void BM_iconv_CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 9; i <= 16; ++i)
    for (int j = 0; j <= 2; ++j)
      b->Args({1<<i, j});
}

static void BM_icu_CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 9; i <= 16; ++i)
    for (int j = 0; j <= 1; ++j)
      b->Args({1<<i, j});
}


BENCHMARK(BM_iconv_us_utf82unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_utf82unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_jp_utf82unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_us_unicode2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_unicode2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_jp_unicode2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});

BENCHMARK(BM_iconv_us_gb2unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_us_unicode2gb)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_us_gb2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_us_utf82gb)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_gb2unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_unicode2gb)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_gb2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zh_utf82gb)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});

BENCHMARK(BM_codecvt_us_utf82unicode)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_zh_utf82unicode)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_jp_utf82unicode)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_us_unicode2utf8)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_zh_unicode2utf8)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_jp_unicode2utf8)->Arg(0)->Arg(1)->Arg(2);

BENCHMARK(BM_codecvt_us_gb2unicode);
BENCHMARK(BM_codecvt_zh_gb2unicode);
BENCHMARK(BM_codecvt_jp_gb2unicode);
BENCHMARK(BM_codecvt_us_unicode2gb);
BENCHMARK(BM_codecvt_zh_unicode2gb);
BENCHMARK(BM_codecvt_jp_unicode2gb);


BENCHMARK(BM_iconv_jps_utf82unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_jps_unicode2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_codecvt_jps_utf82unicode)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_jps_unicode2utf8)->Arg(0)->Arg(1)->Arg(2);

BENCHMARK(BM_iconv_zhs_utf82unicode)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_iconv_zhs_unicode2utf8)->Apply(BM_iconv_CustomArguments);//->Ranges({{1<<9, 1<<16}, {0,1}})->Ranges({{1<<13, 1<<14}, {0,1}});
BENCHMARK(BM_codecvt_zhs_utf82unicode)->Arg(0)->Arg(1)->Arg(2);
BENCHMARK(BM_codecvt_zhs_unicode2utf8)->Arg(0)->Arg(1)->Arg(2);

BENCHMARK(BM_icu_us_utf82unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_zh_utf82unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jp_utf82unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_us_gb2unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_zh_gb2unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jp_gb2unicode)->Apply(BM_icu_CustomArguments);

BENCHMARK(BM_icu_us_unicode2utf8)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_zh_unicode2utf8)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jp_unicode2utf8)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_us_unicode2gb)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_zh_unicode2gb)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jp_unicode2gb)->Apply(BM_icu_CustomArguments);

BENCHMARK(BM_icu_zhs_utf82unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jps_utf82unicode)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_zhs_unicode2utf8)->Apply(BM_icu_CustomArguments);
BENCHMARK(BM_icu_jps_unicode2utf8)->Apply(BM_icu_CustomArguments);

BENCHMARK(BM_utf8cpp_us_iterator)->Arg(0)->Arg(1);
BENCHMARK(BM_utf8cpp_zh_iterator)->Arg(0)->Arg(1);
BENCHMARK(BM_utf8cpp_jp_iterator)->Arg(0)->Arg(1);
BENCHMARK(BM_icu_us_iterator);
BENCHMARK(BM_icu_zh_iterator);
BENCHMARK(BM_icu_jp_iterator);

int main(int argc, char** argv)
{
    cout << "be careful, wchar_t is 4 bytes wide in gcc platform\n"
            "Unlike Windows UTF-16 2-byte wide chars, wchar_t on Linux and OS X is 4 bytes UTF-32 (gcc/g++ and XCode).\n";
    init();

    ::benchmark::Initialize(&argc, argv);                               \
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; \
    ::benchmark::RunSpecifiedBenchmarks();
}
