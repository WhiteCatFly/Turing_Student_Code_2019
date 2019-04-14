#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <malloc.h>
#include <stack>

#include "parser.h"

using std::string;

int main(int argv, char *argc[])
{
    const string wget = "wget -o a.out -t3 -T3 -O ";
    if (argv < 2)
    {
        std::cerr << "too few argument" << std::endl;
        return 0;
    }
    if (argv > 2)
    {
        std::cerr << "too many argument" << std::endl;
        return 0;
    }
    string url = argc[1];
    const string file_name = "index.html";
    system((wget + file_name + " " + url).c_str());
    std::ifstream fin("index.html");
    Tree* Root = build_from_stream(fin);
    std::ofstream fout("tree.txt");
    (*Root).out(fout);
    Tree* title = Root -> parser_title();
    std::cerr << title -> body() << std::endl;
    fout.close();
    fout.clear();
    fout.open("link.txt");
    (*Root).parser_link(fout);
    fout.close();
    fout.clear();
    fout.open("body.txt");
    (*Root).parser_body(fout);
    return 0;
}
