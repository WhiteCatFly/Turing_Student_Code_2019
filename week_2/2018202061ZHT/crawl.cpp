#include "crawl.h"

#define cf curp.first
#define cs curp.second

ifstream fin;
ofstream fout;
bool checkblack (const string &s) {
	extern const int matchblack_num;
	extern const string blacklist[];
	for (int i = 0; i < matchblack_num; i++)
		if (s.find (blacklist[i]) != string::npos)
			return 1;
	return 0;
}
bool checksuf (const string &s) {
	extern const int matchsuf_num;
	extern const string suflist[];
	if ((*s.begin ()) == '/') return 1;
	for (int i = 0; i < matchsuf_num; i++)
		if (s.find (suflist[i]) != string::npos) {
			return 1;
		}
	return 0;
}
bool checkhead (const string &s) {
	extern const int matchhead_num;
	extern const string headlist[];
	for (int i = 0; i < matchhead_num; i++)
		if (s.find (headlist[i]) != string::npos) {
			return 1;
		}
	return 0;
}
string chu (int x) {
	string s = "";
	while (x) {
		s = char((x%10) + '0') + s;
		x /= 10;
	}
	return s;
}
inline void bfs (const string S) {
	extern const regex m_str;
	extern const string store;
	extern const string wg;
	extern const string rem;
	set <pair <string, string> > visit;
	visit.clear ();
	queue <pair <string, string> > que;
	que.push (make_pair (S, S));
	visit.insert (make_pair (S, S));
	//int Cnt = 0;
	while (!que.empty ()) {
		pair <string, string> curp = que.front ();
		que.pop ();
		//Cnt++;
		string p1 = cf;
		string p2 = cs;
		system ((wg + p1 + " -O ./scrawl/" + p2).c_str());
		fin.open ((store + "/" + p2).c_str ());
		//if (curp == S) fin.open ("index.html");
		//else fin.open (curp.c_str ());
		fout << p1 << endl;
		string s;
		while (getline (fin,s)) {
			smatch res;
			while (regex_search (s,res,m_str)) {
				string link = res[1].str ();
				if (checkblack (link)) {
					s = res.suffix ();
					continue;
				}
				//string::size_type idx, idx2;
				//idx = link.find (suf);
				bool flag = checkhead (link);
				pair <string, string> nep;
				if (flag == 1) {
					nep = make_pair (link, link);
				}
				else {
					if (link.find (".") == string::npos || checksuf (link)) {
						if (checksuf (cf)) {
							int pos = cf.rfind ("/");
							nep = make_pair (cf.substr (0, pos) + "/" + link, cs.substr (0, pos) + "_" + link);
						}
						else
							nep = make_pair (cf + "/" + link, cs + "_" + link);
					}
					else{
						s = res.suffix ();
						continue;
					}
				}
				if (!visit.count (nep)) {
					que.push (nep);
					visit.insert (nep);
				}
				s = res.suffix ();
			}
		}
		system ((rem + " " + store + "/" + p2).c_str ());
		fin.close();
	}
}
void solve () {
	fout.open ("crawl.txt");
	string S = "info.ruc.edu.cn";
	bfs (S);
}
