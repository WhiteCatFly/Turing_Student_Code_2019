#include <iostream>
#include <algorithm>
#include <cstring>
using std::string;

#include "others.h"
const string Wget_ = "wget -o a.out -t3 -T3 -O ";

bool Others::check1(string &str)// check Root
{
    return str.find(Root_, 0) != string::npos;
}

void Others::use_wget(string url, string direction)
{
    for (int i = url.length() - 1; i >= 0; i--)
    {
        if ((url[i] == '&' || url[i] == '(' || url[i] == ')') && url[i - 1] != '\\')
        {
            url.insert(i, "\\");
        } 
    }
    for (int i = direction.length() - 1; i >= 0; i--)
    {
        if ((direction[i] == '&' || direction[i] == '(' || direction[i] == ')') && direction[i - 1] != '\\')
        {
            direction.insert(i, "\\");
        } 
    }
    string wget = Wget_ + Store_direction_ + direction + " " + url;
    system(wget.c_str());
}

void Others::true_url(string &direction, int num)
{
    const int end = std::strlen("http://");
    for (int i = direction.length() - 1; i >= end; i--)
    {
        if (direction[i] == '/')
        {
            num--;
            if (num == 0)
            {
                break;
            }
        }
        direction.erase(i, 1);
    }
}