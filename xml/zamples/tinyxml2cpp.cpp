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
#include <tinyxml2.h>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLAttribute;
using tinyxml2::XMLComment;
using tinyxml2::XMLText;
using tinyxml2::XMLDeclaration;
using tinyxml2::XMLNode;
using tinyxml2::XMLUnknown;
using tinyxml2::XMLPrinter;     // construct or modify a doc, and print(/output) it to file or memory
using tinyxml2::XMLVisitor;

struct walker_ctx
{
	int depth;
	template<typename T>
	void collect_node(T&) {}
	template<typename T>
	void collect_attribute(T&) {}
	void reset() { depth = 0; }
};

void collect_one_node(const XMLElement* node, walker_ctx& ctx)
{
	std::cout << ctx.depth << " "
				<< "node: name = \"" << node->Name()
				<< "\" value = \"" << node->Value()
				<< "\"\n";
	ctx.collect_node(node);

	const XMLAttribute* ita = node->FirstAttribute(),
							*itea = NULL;
	for(; ita != itea; ita = ita->Next())
	{
		std::cout << ctx.depth << " "
					<< "attr: name = \"" << ita->Name()
					<< "\" value = \"" << ita->Value()
					<< "\"\n";
		ctx.collect_attribute(*ita);
	}
}


void scan(const XMLElement* ele, walker_ctx& ctx);
void scan(const XMLNode* node, walker_ctx& ctx);
void scan(const XMLDocument* doc, walker_ctx& ctx)
{
    const XMLElement* root = doc->RootElement();
    collect_one_node(root, ctx);
    ++ctx.depth;
    scan(root,  ctx);
    --ctx.depth;
}

void scan(const XMLElement* ele, walker_ctx& ctx)
{
    const XMLNode* child = ele->FirstChild();
    while(child)
    {
        scan(child, ctx);
        child = child->NextSibling();
    }
}

void scan(const XMLNode* node, walker_ctx& ctx)
{
    const XMLElement* ele = node->ToElement();
    if (ele)
    {
        collect_one_node(ele, ctx);
        ++ctx.depth;
        scan(ele, ctx);
        --ctx.depth;
    }

    const XMLText* txt = node->ToText();
    if (txt)
    {
        std::cout << ctx.depth << " value = \""
                    << txt->Value() << "\"\n";
    }
}

typedef void (*hook_whilevisit)();
class visitor : public XMLVisitor
{
private:
	walker_ctx& ctx;
public:
	visitor(walker_ctx& _) : ctx(_) {}
	virtual bool for_each(const XMLElement* node)
	{
		//ctx.depth = depth();
		collect_one_node(node, ctx);
		return true;	// true then continue, other or false then stop walking.
	}
	const bool return_continue = true;
    const bool return_stop_while_you_found_target = false;
	virtual bool VisitEnter(const tinyxml2::XMLDocument & )
    {
        return return_continue;
    }
    virtual bool VisitExit(const tinyxml2::XMLDocument & )
    {
        return return_continue;
    }
    virtual bool VisitEnter(const tinyxml2::XMLElement & elem, const tinyxml2::XMLAttribute * attrs)
    {
        collect_one_node(&elem, ctx);
        ++ctx.depth;
        return return_continue;
    }
    virtual bool VisitExit(const tinyxml2::XMLElement & )
    {
        --ctx.depth;
        return return_continue;
    }
    virtual bool Visit(const tinyxml2::XMLText & txt)
    {
        std::cout << ctx.depth << " value = \""
                    << txt.Value() << "\"\n";
        return return_continue;
    }
    void traverse(XMLDocument& doc)
    {
        // doc begin to traverse, and call back to visitor every where needed.
        doc.Accept(this);
    }
};

void visit(XMLDocument& doc, walker_ctx& ctx)
{
    visitor walker(ctx);
    ctx.reset();
    walker.traverse(doc);
}

void load(XMLDocument& doc, const std::string& content)
{
	std::cout << "container is xml_document" << "\n";
	doc.Parse(content.c_str(), content.size());
}

void save(XMLDocument& doc)
{
	doc.SaveFile("./utf8_tinyxml2_save.xml");
    doc.SaveFile(stdout);
	//doc.save(std::cout);
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

	XMLDocument doc;

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
		scan(&doc, wc);
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
