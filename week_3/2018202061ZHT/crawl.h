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

const regex m_str ("href=[\"\']?([^ <>\f\n\r\t\v]+)[\"\']?");
const regex mul_slash ("//+");
const string store = "./crawl_url";
const string tag = "econ.ruc.edu.cn";
const string wg = "wget ";
const string dot = ".";
const string slash = "/";
const string udl = "_";
const string blank = " ";
const string cur_index = "./";
const string last_index = "../";
const string head = "http://";
const string heads = "https://";
const string suflist[2] = {"php", "html"};
const string headlist[1] = {"econ.ruc.edu.cn"};
const string blacklist[12] = {"@", "www", "doc", "pdf", "xls", "rar", "zip", "#", "script", "jpg", "JPG", "ppt"};
const string rem = "rm ";
const int cilen = 2;
const int lilen = 3;
const int headlen = 7;
const int headslen = 8;
const int matchsuf_num = 2;
const int matchhead_num = 1;
const int matchblack_num = 12;
string extract (const string &s);
bool checkblack (const string &s);
bool checksuf (const string &s);
bool checkhead (const string &s);
void cuts (string & s, const int & len);
void cuthead (string & s);
void modify_slash (pss & p);
string chu (int x);
string ch_form (const string &s);
void inque (queue <pss > &que, set <pss > &visit, const string & s);
pss to_link (const pss & curp, const string & link, bool &flag);
bool invalid (const string &s);
void find_last (string & fi, string & se, int &num);
int calc_last (string & p);
void rem_cur (string & p);
class CRAWL {
private:
	set <pair <string, string> > visit;
	queue <pair <string, string> > que;
public:
	CRAWL () {
		visit.clear ();
	}
	CRAWL (string s = "") {
		visit.clear ();
	}
	~CRAWL () {}
	inline void bfs (const string S);
};
void solve ();

#endif
