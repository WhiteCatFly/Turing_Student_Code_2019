#include <iostream>

#include "others.h"
#include "url_string.h"

using namespace std;

string Url_string::get_url(string &a_string)
{
    int pos = a_string.find(Ahead_, 0);
    if (pos == string::npos) return False_;
    string url;
    int begin = pos + 5;
    if (a_string[begin] == '"' || a_string[begin] == '\'') begin++;
    if (a_string[begin] == '"' || a_string[begin] == '\'') return False_;
    for (int j = begin; j < a_string.length(); j++)
    {
        if (a_string[j] == '"' || a_string[j] == '#' || a_string[j] == '\'' 
        || a_string[j] == '>' || a_string[j] == ' ' || a_string[j] == '\n')
        {
            break;
        }
        url += a_string[j];
    }
    while (url[0] == '.' && url[1] == '/')
    {
        std::cout << url << " ";
        url.erase(0, 2);
        std::cout << url << "\n";
    }
    return url;
}

bool Url_string::is_url(string &a_string)
{
    if (a_string.find("script", 0) != string::npos || a_string.find("@", 0) != string::npos) return false;
    if (a_string.find("http", 0) != string::npos)
    {
        if (!others.check1(a_string)) return false;
    }
    if (a_string.find(".html", 0) != string::npos || a_string.find(".php", 0) != string::npos 
    || a_string.find(".asp", 0) != string::npos) return true;
    for (int i = a_string.length() - 1; i >= 0; i--)
    {
        if (a_string[i] == '.')
        {
            if (a_string[i + 1] == 'c' && a_string[i + 2] == 'n') return true;
            else return false;
        }
    }
    return true;
}

string Url_string::get_direction(string &url)
{
    int len = url.length();
    if (url[0] == '/')
    {
        string direction = Root_;
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
            bool flag1 = 0, flag2 = 0, flag3 = 0;
            if (url[i + 1] == 'h' && url[i + 2] == 't' && url[i + 3] == 'm' && url[i + 4] == 'l') flag1 = 1;
            if (url[i + 1] == 'p' && url[i + 2] == 'h' && url[i + 3] == 'p') flag2 = 1;
            if (url[i + 1] == 'a' && url[i + 2] == 's' && url[i + 3] == 'p') flag3 = 1;
            if (flag1 | flag2 | flag3) 
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