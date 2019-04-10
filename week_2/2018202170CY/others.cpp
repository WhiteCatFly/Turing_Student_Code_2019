#include <iostream>
#include <algorithm>
using std::string;

#include "others.h"

extern string Root;
extern const string Wget;
extern string Store_direction;

bool check1(string &str)// check info.ruc.edu.cn
{
    for (int i = 0; i < str.length(); i++)
    {
        bool flag = 1;
        for (int j = 0; j < Root.length(); j++)
        {
            if (str[i + j] != Root[j] || i + j >= str.length())
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        return 1;
    }
    return 0;
}

void use_wget(string url, string direction)
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
    string wget = Wget + Store_direction + direction + " " + url;
    system(wget.c_str());
}