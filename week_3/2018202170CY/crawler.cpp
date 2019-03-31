#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <set>

#include "others.h"
#include "url_string.h"
#include "crawler.h"

using namespace std;

bool Crawler::solve_a_line(string &one_line, string &direction)
{
    string now;
    string url = url_string.get_url(one_line);
    if (url == False_) return false;
    if (url.find("http", 0) != string::npos && url.find(Root_, 0) == string::npos)
    {
        one_line[one_line.find(Ahead_, 0)] = 'X';
        return false;
    }
    if (url.find("../", 0) != string::npos)
    {
        int num = 0;
        for (int i = 0; i < url.length(); i++)
        if (url[i] == '/') num++;
        others.true_url(direction, num + 1);
    }
    else
    {
        if (url_string.is_url(url) == false) return false;
        if (others.check1(url) == true)
        now = url;
        else
        {
            if (url[0] != '/')
            now = direction + url;
            else
            now = Root_ + url;
        }
        if (now.find(".html", 0) == string::npos && now.find(".php", 0) == string::npos && now.find(".asp", 0) == string::npos)
        {
            if (now[now.length() - 1] != '/')
            now += '/';
        }
    }
    for (int i = now.length() - 2; i >= 1; i--)
    {
        if (now[i] == '/' && now[i + 1] == '/' && now[i - 1] != ':')
        now.erase(i, 1);
    }
    if (url_set.find(now) == url_set.end())
    {
        url_set.insert(now);
        url_queue.push(now);
    }
    int pos = one_line.find(Ahead_, 0);
    if(pos == std::string::npos) return true;
    else one_line[pos] = 'X';
    solve_a_line(one_line, direction);
    return true;
}

void Crawler::crawler()
{
    url_set.insert(Root_);
    url_queue.push(Root_);
    int cnt = 0;
    while (!url_queue.empty())
    {
        string now_url = url_queue.front();
        url_queue.pop();
        if (others.check1(now_url) == false) continue;
        cnt ++;
        cout << cnt << " : " << now_url << endl;
        string filename = now_url;
        for (int i = 0; i < filename.length(); i++)
        if (filename[i] == '/') filename[i] = '_';
        others.use_wget(now_url, filename);
        ifstream fin;
        fin.open(Store_direction_ + filename);
        string one_line;
        string direction = url_string.get_direction(now_url);
        while (getline(fin, one_line))
        {
            solve_a_line(one_line, direction);
        }
        fin.close();
    }
}