#include <iostream>
#include "crawler.h"
#include "url_string.h"
#include "others.h"

std::string Root = "http://info.ruc.edu.cn";
std::string Store_direction = "/home/cy/Desktop/big_homework/crawler/data/";
extern const std::string Ahead = "href=\"";
extern const std::string False = "0";
extern const std::string Wget = "wget -o a.out -t5 -T5 -O ";

int main(int argv, char *argc[])
{
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
    
    crawler();
    return 0;
}
