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
#include "../pugixml/src/pugixml.hpp"

using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_node_iterator;
using pugi::xml_attribute;
using pugi::xml_attribute_iterator;
using pugi::xml_parse_result;
using pugi::xml_tree_walker;

struct walker_ctx
{
	int depth;
	template<typename T>
	void collect_node(T&) {}
	template<typename T>
	void collect_attribute(T&) {}
	void reset() { depth = 0; }
};

void collect_one_node(const xml_node& node, walker_ctx& ctx)
{
	std::cout << ctx.depth << " "
				<< "node: name = \"" << node.name()
				<< "\" value = \"" << node.value()
				<< "\"\n";
	ctx.collect_node(node);

	xml_attribute_iterator ita = node.attributes_begin(),
							itea = node.attributes_end();
	for(; ita != itea; ++ita)
	{
		std::cout << ctx.depth << " "
					<< "attr: name = \"" << ita->name()
					<< "\" value = \"" << ita->value()
					<< "\"\n";
		ctx.collect_attribute(*ita);
	}
}

void scan(const xml_node& node, walker_ctx& ctx)
{
	if(node.empty())
		return;

	collect_one_node(node, ctx);

	xml_node_iterator it = node.begin(),
						ite = node.end();
	for(; it != ite; ++it)
	{
		++ctx.depth;
		scan(*it, ctx);
		--ctx.depth;
	}
}

typedef void (*hook_whilevisit)();
class visitor : public xml_tree_walker
{
private:
	walker_ctx& ctx;
public:
	visitor(walker_ctx _) : ctx(_) {}
	virtual bool for_each(xml_node& node)
	{
		ctx.depth = depth();
		collect_one_node(node, ctx);
		return true;	// true then continue, other or false then stop walking.
	}
};

void visit(xml_document& doc, walker_ctx& ctx)
{
	visitor walker(ctx);
	ctx.reset();
	doc.traverse(walker);
}

void load(xml_document& doc, const std::string& content)
{
	std::cout << "container is xml_document" << "\n";
	doc.load_string(content.c_str());
}

void save(xml_document& doc)
{
	doc.save_file("./utf8_pugi_save.xml");
	doc.save(std::cout);
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

	xml_document doc;

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
		load(doc, content);
	}

	{
		scoper scpr("scan");
		scan(doc.document_element(), wc);
	}

	{
		scoper scpr("visitor");
		visit(doc, wc);
	}

	{
		scoper scpr("save");
		save(doc);
	}

	return 0;
}
