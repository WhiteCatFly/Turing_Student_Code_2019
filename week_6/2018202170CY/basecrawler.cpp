#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <set>
#include <cstring>

#include "parser.h"
#include "basecrawler.h"

using std::string;
using std::cout;
using std::endl;

// bool BaseCrawler::solve_a_line(string &one_line, string &directory)
// {
//     string now;
//     string url = get_url(one_line);
//     if (url == False_) return false;
//     if (url.find("http", 0) != string::npos && url.find(Root_, 0) == string::npos)
//     {
//         one_line[one_line.find(Ahead_, 0)] = 'X';
//         return false;
//     }
//     if (url.find("../", 0) != string::npos)
//     {
//         int num = 0;
//         for (int i = 0; i < url.length(); i++)
//         if (url[i] == '/') num++;
//         true_url(directory, num + 1);
//     }
//     else
//     {
//         if (is_url(url) == false) return false;
//         if (belong_to_Root(url) == true)
//         now = url;
//         else
//         {
//             if (url[0] != '/')
//             now = directory + url;
//             else
//             now = Root_ + url;
//         }
//         if (now.find(".html", 0) == string::npos && now.find(".php", 0) == string::npos && now.find(".asp", 0) == string::npos)
//         {
//             if (now[now.length() - 1] != '/')
//             now += '/';
//         }
//     }
//     for (int i = now.length() - 2; i >= 1; i--)
//     {
//         if (now[i] == '/' && now[i + 1] == '/' && now[i - 1] != ':')
//         now.erase(i, 1);
//     }
//     if (url_set.find(now) == url_set.end())
//     {
//         url_set.insert(now);
//         url_queue.push(now);
//     }
//     int pos = one_line.find(Ahead_, 0);
//     if(pos == std::string::npos) return true;
//     else one_line[pos] = 'X';
//     solve_a_line(one_line, directory);
//     return true;
// }

void BaseCrawler::crawler()
{
    url_set.insert(Root_);
    url_queue.push(Root_);
    int cnt = 0;
    while (!url_queue.empty())
    {
        // cout << "a" << endl;
        string now_url = url_queue.front();
        url_queue.pop();
        if (belong_to_Root(now_url) == false) continue;
        cnt ++;
        cout << cnt << " : " << now_url << endl;
        string filename = now_url;
        for (int i = 0; i < filename.length(); i++)
        if (filename[i] == '/') filename[i] = '_';
        use_wget(now_url, filename);
        // cout << "d" << endl;
        std::ifstream fin;
        fin.open(Store_directory_ + filename);
        parser_root = build_from_stream(fin);
        if (parser_root == NULL) continue;
        std::ofstream store_link;
        store_link.open("store_link.txt");
        string directory = get_directory(now_url);
        (*parser_root).parser_link(store_link);
        fin.close();
        store_link.close();
        // cout << "b" << endl;
        std::ifstream putin_link;
        putin_link.open("store_link.txt");
        string new_url;
        while(getline(putin_link, new_url))
        {
            if(is_url(new_url) == true && belong_to_Root(new_url) == true)
            {   
                if (is_absolute_address(new_url) == true)
                {
                    int place = new_url.find("#");
                    if (place != string::npos)
                    {
                        new_url.erase(place, new_url.length() - 1);
                    }
                    if (url_set.find(new_url) == url_set.end())
                    {
                        url_queue.push(new_url);
                        url_set.insert(new_url);
                    }
                }
                else
                {
                    if (new_url[0] == '/')
                    {
                        new_url.erase(0, 1);
                    }
                    new_url = directory + new_url;
                    int place = new_url.find("#");
                    if (place != string::npos)
                    {
                        new_url.erase(place, new_url.length() - 1);
                    }
                    if (url_set.find(new_url) == url_set.end())
                    {
                        url_queue.push(new_url);
                        url_set.insert(new_url);
                    }
                }
            }
        }
        // cout << "c" << endl;
        free(parser_root);
    }
}

// string BaseCrawler::get_url(string &a_string)
// {
//     int pos = a_string.find(Ahead_, 0);
//     if (pos == string::npos) return False_;
//     string url;
//     int begin = pos + 5;
//     if (a_string[begin] == '"' || a_string[begin] == '\'') begin++;
//     if (a_string[begin] == '"' || a_string[begin] == '\'') return False_;
//     for (int j = begin; j < a_string.length(); j++)
//     {
//         if (a_string[j] == '"' || a_string[j] == '#' || a_string[j] == '\'' 
//         || a_string[j] == '>' || a_string[j] == ' ' || a_string[j] == '\n')
//         {
//             break;
//         }
//         url += a_string[j];
//     }
//     while (url[0] == '.' && url[1] == '/')
//     {
//         std::cout << url << " ";
//         url.erase(0, 2);
//         std::cout << url << "\n";
//     }
//     return url;
// }

bool BaseCrawler::is_url(string &a_string)
{
    if (a_string.find("script", 0) != string::npos || a_string.find("@", 0) != string::npos) return false;
    if (a_string.find("http", 0) != string::npos)
    {
        if (belong_to_Root(a_string)) return false;
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

string BaseCrawler::get_directory(string &url)
{
    int len = url.length();
    if (url[0] == '/')
    {
        string directory = Root_;
        for (int i = 1; i < len ; i++)
        directory += url[i];
        return directory;
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
                string directory;
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
                directory += url[j];
                return directory;
            }
            break;
        }
    }            
    if (url[len - 1] != '/') url += "/";
    return url;
}

bool BaseCrawler::belong_to_Root(string &str)// check Root
{
    if (str.find("http") != string::npos)
    {
        return str.find(Root_, 0) != string::npos;
    }
    return true;
}

bool is_absolute_address(string &url)
{
    if (url.find("http") != string::npos) return true;
    else return false;
}

void BaseCrawler::use_wget(string url, string directory)
{
    for (int i = url.length() - 1; i >= 0; i--)
    {
        if (url[i] == '&' || url[i] == '(' || url[i] == ')')
        {
            url.insert(i, "\\");
        } 
    }
    for (int i = directory.length() - 1; i >= 0; i--)
    {
        if (directory[i] == '&' || directory[i] == '(' || directory[i] == ')')
        {
            directory.insert(i, "\\");
        } 
    }
    string wget = Wget_ + Store_directory_ + directory + " " + url;
    system(wget.c_str());
}

void BaseCrawler::true_url(string &directory, int num)
{
    const int end = std::strlen("http://");
    for (int i = directory.length() - 1; i >= end; i--)
    {
        if (directory[i] == '/')
        {
            num--;
            if (num == 0)
            {
                break;
            }
        }
        directory.erase(i, 1);
    }
}