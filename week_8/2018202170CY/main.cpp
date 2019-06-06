#include <iostream>
#include <queue>
#include <set>
#include <cstring>
#include <fstream>
#include <map>
#include <list>
#include <time.h>

#include "parser.h"
#include "basecrawler.h"
#include "advancedcrawler.h"
#include "search_engine.h"

using std::string;
using std::cout;
using std::endl;

int main(int argv, char *argc[])
{
    string Root, Store_directory, Wget;
    const string False = "0", Ahead = "href=";
    std::ofstream log, solved_url, all_url;
    log.open("log.txt");
    bool method;
    if (argv <= 4)
    {
        std::cerr << "arguments are not enough\n";
        return 0;
    }
    else if (argv > 5)
    {
        std::cerr << "there are too many arguments\n";
        return 0;
    }
    else
    {
        Root = argc[1];
        Store_directory = argc[2];
        Wget = argc[3];
        string putin_method = argc[4];
        if (putin_method == "continue") method = 1;
        else if (putin_method == "restart") method = 0;
        else
        {
            std::cerr << "you putin a wrong method\n";
            return 0;
        }
    }
    if (Wget.find(".out", 0) == string::npos)
    {
        if (Wget.find("-o", 0) == string::npos)
        {
            int place = Wget.find("wget", 0);
            Wget.insert(place + strlen("wget ") - 1, " -o a.out");
        }
        else
        {
            int place = Wget.find("-o", 0);
            Wget.insert(place + 2, " a.out");
        }
    }
    // std::cout << Root << " " << Store_directory << std::endl << Wget << std::endl;
    AdvancedCrawler crawl(Root, Store_directory, Wget);
    int cnt = 0;
    if (method == 1)
    {
        std::ifstream solved, all;
        solved.open("solved_url.txt");
        all.open("all_url.txt");
        string str;
        while(getline(solved, str))
        {
            cnt++;
            crawl.url_set.insert(str);
        }
        while(getline(all, str))
        {
            if (crawl.url_set.find(str) == crawl.url_set.end())
            {
                crawl.url_queue.push(str);
                crawl.url_set.insert(str);
            }
        }
    }
    else
    {
        solved_url.open("solved_url.txt");
        all_url.open("all_url.txt");
    }

    crawl.crawler(cnt);
    Search_engine search_engine;
    search_engine.build_list();
    string target;
    cout << "please putin a string" << endl;
    std::cin >> target;
    time_t T1 = time(NULL);
    search_engine.search(target);
    time_t T2 = time(NULL);
    cout << T2 - T1 << " seconds cost" << endl;
    return 0;
}
