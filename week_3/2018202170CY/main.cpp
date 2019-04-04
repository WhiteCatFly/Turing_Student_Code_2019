#include <iostream>
#include <queue>
#include <set>

#include "others.h"
#include "url_string.h"
#include "crawler.h"

using std::string;

int main(int argv, char *argc[])
{
    string Root, Store_direction;
    const string False = "0", Ahead = "href=";
    if (argv <= 2)
    {
        std::cerr << "arguments are not enough\n";
        return 0;
    }
    else if (argv > 3)
    {
        std::cerr << "there are too many arguments\n";
        return 0;
    }
    else
    {
        Root = argc[1];
        Store_direction = argc[2];
    }
    std::cout << Root << " " << Store_direction << std::endl;
    Crawler crawl(Root, Store_direction, False, Ahead);

    crawl.crawler();
    return 0;
}
