#ifndef CRAWL_H_INCLUDE
#define CRAWL_H_INCLUDE

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <regex>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

using namespace std;

#define pss pair<string,string>

const regex ti_str ("<title>.+</title>");
const regex he_str ("<head>.+</head>");
const regex m_str ("href=[\"\']?([^ <>\f\n\r\t\v]+)[\"\']?");
const regex mul_slash ("//+");

const string ti_sl = "<title>";
const string ti_sr = "</title>";
const string he_sl = "<head>";
const string he_sr = "</head>";
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
const int MAXN = 100005;
const int ti_len = 7;
const int he_len = 6;
const int cilen = 2;
const int lilen = 3;
const int headlen = 7;
const int headslen = 8;
const int matchsuf_num = 2;
const int matchhead_num = 1;
const int matchblack_num = 12;
string regex_search_title (const string &s);
string regex_search_head (const string &s);
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
	int html_cnt;
	set <pss > visit;
	queue <pss > que;
	pss Html[MAXN];
	map <pss , int> html_id;
	vector <pss > son[MAXN];
public:
	CRAWL () {
		html_cnt = 0;
		visit.clear ();
	}
	CRAWL (string s = "") {
		html_cnt = 0;
		visit.clear ();
		//bfs (s);
	}
	~CRAWL () {}
	void insert (pss & p1, pss & p2);
	inline void bfs (const string S);
};
void solve ();

#endif
