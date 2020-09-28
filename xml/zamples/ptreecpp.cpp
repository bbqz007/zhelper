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
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define ATTR_SET ".<xmlattr>"
using namespace boost;
using boost::property_tree::read_xml;
using boost::property_tree::write_xml;
using boost::property_tree::ptree;

struct walker_ctx
{
	int depth;
	template<typename T>
	void collect_node(T&) {}
	template<typename T>
	void collect_attribute(T&) {}
	void reset() { depth = 0; }
};

void collect_one_node(const ptree::value_type& node, walker_ctx& ctx)
{
	std::cout << ctx.depth << " "
				<< "node: name = \"" << node.first.data()
				<< "\" value = \"" << ((node.second.empty())?node.second.data():"")
				<< "\"\n";
	ctx.collect_node(node);
	ptree attributes;
	try
	{
		attributes = node.second.get_child("<xmlattr>");
	}
	catch(...)
	{
		return;
	}

	BOOST_FOREACH(const ptree::value_type & attr, attributes)
	{
		std::cout << ctx.depth << " "
                    << "attr: name = \"" << attr.first.data()
                    << "\" value = \"" << attr.second.data()
                    << "\"\n";
        ctx.collect_attribute(attr);
	}
}

void scan(const ptree::value_type& node, walker_ctx& ctx);
void scan(const ptree& node, walker_ctx& ctx)
{
	ptree::const_iterator xmlattr = node.to_iterator(node.find("<xmlattr>"));
	BOOST_FOREACH(const ptree::value_type & child, node)
	{
		// value_type is pair<key, ptree>,
		// the kv you known is value_type.first and value_type.second.data()
		if (child.first == "<xmlattr>")
		{
			continue;
		}
		scan(child, ctx);
	}
}

void scan(const ptree::value_type& node, walker_ctx& ctx)
{
	collect_one_node(node, ctx);

	++ctx.depth;
	scan(node.second, ctx);
	--ctx.depth;
}

typedef void (*hook_whilevisit)();
class visitor /** : public xml_tree_walker*/
{
private:
	walker_ctx& ctx;
public:
	visitor(walker_ctx _) : ctx(_) {}
	virtual bool for_each(ptree::value_type& node)
	{
		//ctx.depth = depth();
		collect_one_node(node, ctx);
		return true;	// true then continue, other or false then stop walking.
	}
};

void visit(ptree& doc, walker_ctx& ctx)
{
	std::cout << "does not provide for visit-parttern\n";
}

void load(ptree& doc, std::istream& is)
{
	std::cout << "container is ptree" << "\n";
	read_xml(is, doc);
}

void save(ptree& doc)
{
	write_xml("./utf8_ptree_save.xml", doc);
	write_xml(std::cout, doc);
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

	ptree doc;

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
		load(doc, sscontent);
	}

	{
		scoper scpr("scan");
		scan(doc, wc);
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
