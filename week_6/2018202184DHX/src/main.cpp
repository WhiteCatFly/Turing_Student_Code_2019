#include "Crawler.h"
#include "HTMLParser.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <regex>

//主函数参数0 ： 程序名字 参数1：路径 参数2：根url 参数3：Set的日志 参数4：Queue的日志
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
    else if (argc == 5)
    {
        std::string root_url = argv[2];
        std::string root_path = argv[1];
        Crawler test(root_url, root_path);
        test.REset(argv[3],argv[4]);
        test.Core();
    }
    else
    {
        Crawler test("http://econ.ruc.edu.cn/");
        test.Core();
    }
    for(;1;)
    {
        std::cout << "Input 'q' to exit or input the website to get more detail" << std::endl;
        char temp[MaxWebUrl];
        std::cin >> temp;
        if(temp == "q")
        {
            break;
        }
        else
        {
            std::string url = temp;
            std::string instruction_name = "wget -q -O Detail.html \"" + url + "\"";
            const char* key = instruction_name.c_str();
            system(key);
            Parser detail("Detail.html",url);
            detail.Title();
            detail.Body();
            detail.Url();
        }
    }
    return 0;
}