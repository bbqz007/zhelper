#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct walker_ctx
{
	int depth;
}

void scan()
{
}

typedef void (*hook_whilevisit)();

void visit()
{
}

void load()
{
}

void load_file(
    std::stringstream& outstr,
    const std::string& path)
{
    std::ifstream ifs(path);
    outstr << ifs.rdbuf();
}

int main()
{
    std::stringstream sscontent;
    std::stringstream ssregex;

    load_file(sscontent, "./utf8.txt");
    load_file(ssregex, "./utf8-word.txt");

    const std::string& content = sscontent.str();
    const std::string& regexes = ssregex.str();

	return 0;
}
