#include <iostream>
#include "url_string.h"
#include "others.h"

using namespace std;

extern const string Ahead;
extern const string False;
extern string Root;

string get_url(string &a_string)
{
    for (int i = 0; i < a_string.length(); i++)
    {
        bool flag = 1;
        for (int j = 0; j < Ahead.length(); j++)
        {
            if (a_string[i + j] != Ahead[j] || i + j >= a_string.length())
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            string url;
            for (int j = i + 6; j < a_string.length(); j++)
            {
                if (a_string[j] == '"' || a_string[j] == '#')
                {
                    break;
                }
                url += a_string[j];
            }
            return url;
        }
    }
    return False;
}

bool is_url(string &a_string)
{
    if (a_string.find("http", 0) != string::npos)
    {
        if (!check1(a_string)) return 0;
    }
    for (int i = a_string.length() - 1; i >= 0; i--)
    {
        if (a_string[i] == '.')
        {
            if (a_string[i + 1] == 'c' && a_string[i + 2] == 'n') return 1;
            bool flag1 = 0, flag2 = 0;
            if (a_string[i + 1] == 'h' && a_string[i + 2] == 't' && a_string[i + 3] == 'm' && a_string[i + 4] == 'l') flag1 = 1;
            if (a_string[i + 1] == 'p' && a_string[i + 2] == 'h' && a_string[i + 3] == 'p') flag2 = 1;
            return flag1 | flag2;
        }
    }
    return 1;
}

string get_direction(string &url)
{
    int len = url.length();
    if (url[0] == '/')
    {
        string direction = Root;
        for (int i = 1; i < len ; i++)
        direction += url[i];
        return direction;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        if (url[i] == '.')
        {
            if (url[i + 1] == 'c' && url[i + 2] == 'n')
            {
                if (url[len - 1] != '/') url += "/";
                return url;
            }
            bool flag1 = 0, flag2 = 0;
            if (url[i + 1] == 'h' && url[i + 2] == 't' && url[i + 3] == 'm' && url[i + 4] == 'l') flag1 = 1;
            if (url[i + 1] == 'p' && url[i + 2] == 'h' && url[i + 3] == 'p') flag2 = 1;
            if (flag1 | flag2) 
            {
                string direction;
                int ed;
                for (int j = len - 1; j >=0 ; j--)
                {
                    if (url[j] == '/')
                    {
                        ed = j;
                        break;
                    }
                }
                for (int j = 0; j <= ed; j ++)
                direction += url[j];
                return direction;
            }
            break;
        }
    }            
    if (url[len - 1] != '/') url += "/";
    return url;
}