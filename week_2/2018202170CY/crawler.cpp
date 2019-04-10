#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>

#include "crawler.h"
#include "url_string.h"
#include "others.h"

using namespace std;

extern string Root;
extern string Store_direction;
extern const string Ahead;
extern const string False;
extern const string Wget;
set<string> url_set;
queue<string> url_queue;

bool solve_a_line(string &one_line, string &direction)
{
    string url = get_url(one_line);
    if (url == False) return 0;
    if (is_url(url) == 0) return 0;
    string now;
    if (check1(url))
    now = url;
    else 
    now = direction + url;
    if (url_set.find(now) == url_set.end())
    {
        url_set.insert(now);
        url_queue.push(now);
    }
    int pos = one_line.find(Ahead, 0);
    if(pos == std::string::npos) return 1;
    else one_line[pos] = 'X';
    solve_a_line(one_line, direction);
    return 1;
}

void crawler()
{
    url_set.insert(Root);
    url_queue.push(Root);
    int cnt = 0;
    while (!url_queue.empty())
    {
        string now_url = url_queue.front();
        url_queue.pop();
        cnt ++;
        cout << cnt << " : " << now_url << endl;
        string filename = now_url;
        for (int i = 0; i < filename.length(); i++)
        if (filename[i] == '/') filename[i] = '_';
        use_wget(now_url, filename);
        ifstream fin;
        fin.open(Store_direction + filename);
        string one_line;
        string direction = get_direction(now_url);
        while (getline(fin, one_line))
        {
            solve_a_line(one_line, direction);
        }
        fin.close();
    }
}