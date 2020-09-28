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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/smart_ptr.hpp>
#include "expat.h"

struct walker_ctx
{
	int depth;
	std::string name;
	template<typename T>
	void collect_node(T&) {}
	template<typename T>
	void collect_attribute(T&, T&) {}
	void reset() { depth = 0; }
};

void collect_one_node(const char* name,
						const char** attributes,
						 walker_ctx& ctx)
{
	std::cout << ctx.depth << " "
				<< "node: name = \"" << name
				//<< "\" value = \"" << ""
				<< "\"\n";
    ctx.name = name;
	ctx.collect_node(name);

	for(int i = 0; attributes[i]; i += 2)
	{
		std::cout << ctx.depth << " "
					<< "attr: name = \"" << attributes[i]
					<< "\" value = \"" << attributes[i+1]
					<< "\"\n";
		ctx.collect_attribute(attributes[i], attributes[i+1]);
	}
}

void collect_one_node_text(const char* s, int len, walker_ctx& ctx)
{
    const char* p = s;
    const char* ep = p + len;
    while (p < ep)
    {
        if (*p != ' ' && *p != '\n')
            break;
        ++p;
    }
    if (p == ep)
        return;
    std::cout << ctx.depth
				<< " value = \"" << std::string(s, len - 1)
				<< "\"\n";
}

void end_collect_one_node_text(walker_ctx& ctx)
{

}

void scan(const XML_Parser, walker_ctx& ctx)
{
	std::cout << "does not provide for scan parttern\n";
}

typedef void (*hook_whilevisit)();
static void XMLCALL
hook_startElement(void *userData, const char *name, const char **atts)
{
	walker_ctx* ctx = (walker_ctx*) userData;
	++ctx->depth;
    collect_one_node(name, atts, *ctx);
}

static void XMLCALL
hook_endElement(void *userData, const char *name)
{
	walker_ctx* ctx = (walker_ctx*) userData;
	--ctx->depth;
	end_collect_one_node_text(*ctx);
}

static void XMLCALL
hook_textCharacterData (void *userData, const XML_Char *s, int len)
{
    walker_ctx* ctx = (walker_ctx*) userData;
    collect_one_node_text(s, len, *ctx);
}

struct visitor
{
    visitor(walker_ctx& ctx) : ctx_(ctx) {}
    walker_ctx& ctx_;
    void traverse(XML_Parser parser)
    {
        XML_SetUserData(parser, &ctx_);
        XML_SetElementHandler(parser, hook_startElement, hook_endElement);
        XML_SetCharacterDataHandler(parser, hook_textCharacterData);
        char buf[BUFSIZ];
        FILE* io = fopen("utf8.xml","rb");
        int done = !io;
        do {
            int len = (int)fread(buf, 1, sizeof(buf), io);
            done = len < sizeof(buf);
            if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
              fprintf(stderr,
                      "%s at line %d\n",
                      XML_ErrorString(XML_GetErrorCode(parser)),
                      (int)XML_GetCurrentLineNumber(parser));
              return;
            }
        } while (!done);
        fclose(io);
    }
};
void visit(XML_Parser parser, walker_ctx& ctx)
{
	visitor walker(ctx);
	ctx.reset();
	walker.traverse(parser);
}

void load(XML_Parser, const std::string& content)
{
	std::cout << "does not provide for loading" << "\n";
}

void save(XML_Parser)
{
	std::cout << "does not provide for writing" << "\n";
}

void load_file(
    std::stringstream& outstr,
    const std::string& path)
{
    std::ifstream ifs(path.c_str());
    outstr << ifs.rdbuf();
}

int main()
{
    std::stringstream sscontent;
    std::stringstream ssregex;

    load_file(sscontent, "./utf8.xml");

    const std::string& content = sscontent.str();

	boost::shared_ptr<XML_ParserStruct> parser(XML_ParserCreate(NULL),
												XML_ParserFree);


	walker_ctx wc;
	wc.depth = 0;

	struct scoper
	{
		std::string str;
		scoper(const std::string& sth) : str(sth)
		{
			std::cout << "====== BEGIN "
					<< str << " =====\n";
		}
		~scoper()
		{
			std::cout << "====== END "
					<< str << " -----\n";
		}
	};

	{
		scoper scpr("load");
		load(parser.get(), content);
	}

	{
		scoper scpr("scan");
		scan(parser.get(), wc);
	}

	{
		scoper scpr("visitor");
		visit(parser.get(), wc);
	}

	{
		scoper scpr("save");
		save(parser.get());
	}

	return 0;
}
