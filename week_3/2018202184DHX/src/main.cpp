#include "Crawler.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <regex>

int main(int argc, char *argv[])
{
    if(argc == 3)
    {
        std::string root_url = argv[2];
        std::string root_path = argv[1];
        Crawler test(root_url, root_path);
        test.Core();
    }
    else if(argc == 2)
    {
        std::string root_url = argv[1];
        Crawler test(root_url);
        test.Core();
    }
    else
    {
        Crawler test("http://econ.ruc.edu.cn/");
        test.Core();
    }
    return 0;
}