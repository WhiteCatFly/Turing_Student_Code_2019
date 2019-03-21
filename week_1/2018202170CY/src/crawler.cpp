#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>

using namespace std;

#include "crawler.h"

const string Root = "http://info.ruc.edu.cn";
const string Ahead = "href=\"";
const string False = "0";
const string Wget = "wget -o a.out -t5 -T5 -O ";
const string Store_direction = "/home/cy/Desktop/big_homework/pachong/data/";

bool check1(string s)// check info.ruc.edu.cn
{
    string s0 = Root;
    for (int i = 0; i < s.length(); i++)
    {
        bool flag = 1;
        for (int j = 0; j < s0.length(); j++)
        {
            if (s[i + j] != s0[j] || i + j >= s.length())
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

string get_url(string s)
{
    string s0 = Ahead;
    for (int i = 0; i < s.length(); i++)
    {
        bool flag = 1;
        for (int j = 0; j < s0.length(); j++)
        {
            if (s[i + j] != s0[j] || i + j >= s.length())
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            string s1;
            for (int j = i + 6; j < s.length(); j++)
            {
                if (s[j] == '"' || s[j] == '#')
                {
                    break;
                }
                s1 += s[j];
            }
            return s1;
        }
    }
    return False;
}

bool is_url(string s)
{
    if (s[0] == 'h' && s[1] == 't' && s[2] == 't' && s[3] == 'p')
    {
        if (!check1(s)) return 0;
    }
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] == '.')
        {
            if (s[i + 1] == 'c' && s[i + 2] == 'n') return 1;
            bool flag1 = 0, flag2 = 0;
            if (s[i + 1] == 'h' && s[i + 2] == 't' && s[i + 3] == 'm' && s[i + 4] == 'l') flag1 = 1;
            if (s[i + 1] == 'p' && s[i + 2] == 'h' && s[i + 3] == 'p') flag2 = 1;
            return flag1 | flag2;
        }
    }
    return 1;
}

char system_char[1000];
void use_wget(string s, string s1)
{
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if ((s[i] == '&' || s[i] == '(' || s[i] == ')') && s[i - 1] != '\\')
        {
            s.insert(i, "\\");
        } 
    }
    for (int i = s1.length() - 1; i >= 0; i--)
    {
        if ((s1[i] == '&' || s1[i] == '(' || s1[i] == ')') && s1[i - 1] != '\\')
        {
            s1.insert(i, "\\");
        } 
    }
    string system_string = Wget + Store_direction + s1 + " " + s;
    for (int i = 0; i < system_string.length(); i++)
    system_char[i] = system_string[i];
    system_char[system_string.length()] = 0;
    system(system_char);
}
string get_direction(string s)
{
    int len = s.length();
    if (s[0] == '/')
    {
        string s1 = Root;
        for (int i = 1; i < len ; i++)
        s1 += s[i];
        return s1;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        if (s[i] == '.')
        {
            if (s[i + 1] == 'c' && s[i + 2] == 'n')
            {
                if (s[len - 1] != '/') s += "/";
                return s;
            }
            bool flag1 = 0, flag2 = 0;
            if (s[i + 1] == 'h' && s[i + 2] == 't' && s[i + 3] == 'm' && s[i + 4] == 'l') flag1 = 1;
            if (s[i + 1] == 'p' && s[i + 2] == 'h' && s[i + 3] == 'p') flag2 = 1;
            if (flag1 | flag2) 
            {
                string s1;
                int ed;
                for (int j = len - 1; j >=0 ; j--)
                {
                    if (s[j] == '/')
                    {
                        ed = j;
                        break;
                    }
                }
                for (int j = 0; j <= ed; j ++)
                s1 += s[j];
                return s1;
            }
            break;
        }
    }            
    if (s[len - 1] != '/') s += "/";
    return s;
}

set<string> st;
queue<string> q;
bool solve_a_line(char* one_line, string direction)
{
    string url = get_url(one_line);
    if (url == False) return 0;
    if (is_url(url) == 0) return 0;
    string now;
    if (check1(url))
    now = url;
    else 
    now = direction + url;
    if (st.find(now) == st.end())
    {
        st.insert(now);
        q.push(now);
    }
    for (int i = 0; i < strlen(one_line); i++)
    {
        if (one_line[i] == 'h' && one_line[i + 1] == 'r' && one_line[i + 2] == 'e'
        && one_line[i + 3] == 'f' && one_line[i + 4] == '=' && one_line[i + 5] == '"')
        {
            one_line[i] = 'X';
            break;
        }
    }
    solve_a_line(one_line, direction);
    return 1;
}

void bfs(string s)
{
    st.insert(s);
    q.push(s);
    int cnt = 0;
    while (!q.empty())
    {
        s = q.front();
        q.pop();
        cnt ++;
        cout << cnt << " : " << s << endl;
        string s1 = s;
        for (int i = 0; i < s1.length(); i++)
        if (s1[i] == '/') s1[i] = '_';
        use_wget(s, s1);
        ifstream fin;
        fin.open(Store_direction + s1);
        char one_line[10000];
        string direction = get_direction(s);
        while (fin.getline(one_line, 10000))
        {
            solve_a_line(one_line, direction);
        }
        fin.close();
    }
}