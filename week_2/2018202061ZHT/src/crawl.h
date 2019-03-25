#ifndef CRAWL_H_INCLUDE
#define CRAWL_H_INCLUDE

#include <iostream>
#include <cstdio>
#include <fstream>
#include <regex>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

#define pss pair<string,string>

const regex m_str ("href=\"(.+?)\"");
const string store = "./crawl_url";
const string wg = "wget ";
const string dot = ".";
const string slash = "/";
const string udl = "_";
const string blank = " ";
const string suflist[2] = {"php", "html"};
const string headlist[2] = {"http", "info.ruc.edu.cn"};
const string blacklist[6] = {"@", "doc", "pdf", "xls", "rar", "zip"};
const string rem = "rm ";
const int matchsuf_num = 2;
const int matchhead_num = 2;
const int matchblack_num = 6;
bool checkblack (const string &s);
bool checksuf (const string &s);
bool checkhead (const string &s);
string chu (int x);
void inque (queue <pss > &que, set <pss > &visit, const string & s);
pss to_link (const pss & curp, const string & link, bool &flag);
bool invalid (const string &s);
inline void bfs (const string S);
void solve ();

#endif
