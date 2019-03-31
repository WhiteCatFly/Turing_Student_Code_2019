#include "crawl.h"

#define cf curp.first
#define cs curp.second
#define pss pair<string,string>
#define mp(x,y) make_pair(x,y)

ifstream fin;
ofstream fout;

bool checkblack (const string &s) {
	extern const int matchblack_num;
	extern const string blacklist[];
	for (int i = 0; i < matchblack_num; i++)
		if (s.find (blacklist[i]) != string::npos)
			return true;
	return false;
}

bool checksuf (const string &s) {
	extern const int matchsuf_num;
	extern const string suflist[];
	if ((*s.begin ()) == slash[0]) return true;
	for (int i = 0; i < matchsuf_num; i++)
		if (s.find (suflist[i]) != string::npos) {
			return true;
		}
	return false;
}

bool checkhead (const string &s) {
	extern const int matchhead_num;
	extern const string headlist[];
	for (int i = 0; i < matchhead_num; i++)
		if (s.find (headlist[i]) != string::npos) {
			return true;
		}
	return false;
}

string chu (int x) {
	string s = "";
	while (x) {
		s = char((x%10) + '0') + s;
		x /= 10;
	}
	return s;
}

void inque (queue <pss> &que, set <pss> &visit, const pss & s) {
	if (visit.count (s)) return;
	que.push (s);
	visit.insert (s);
}

bool invalid (const string &s) {
	return s.find (dot) != string::npos && !checksuf (s);
}

pss to_link (const pss & curp, const string & link, bool &flag) {
	pss nep;
	if (flag == true) {
		nep = mp (link, link);
	}
	else {
		if (checksuf (cf)) {
			int pos = cf.rfind (slash);
			nep = mp (cf.substr (0, pos)+slash+link, cs.substr (0, pos)+udl+link);
		}
		else
			nep = mp (cf+slash+link, cs+udl+link);
	}
	return nep;
}

inline void bfs (const string S) {
	extern const regex m_str;
	extern const string store;
	extern const string wg;
	extern const string rem;
	set <pair <string, string> > visit;
	visit.clear ();
	queue <pair <string, string> > que;
	inque (que, visit, mp(S,S));
	while (!que.empty ()) {
		pair <string, string> curp = que.front ();
		que.pop ();
		string p1 = cf;
		string p2 = cs;
		fout << p1 << endl;
		system ((wg + p1 + " -O " + store + slash + p2).c_str());
		fin.open ((store + slash + p2).c_str ());
		string s;
		while (getline (fin,s)) {
			smatch res;
			while (regex_search (s,res,m_str)) {
				string link = res[1].str ();
				if (checkblack (link)) {
					s = res.suffix ();
					continue;
				}
				bool flag = checkhead (link);
				pair <string, string> nep;
				if (flag == false && invalid (link)) {
					s = res.suffix ();
					continue;
				}
				nep = to_link (curp, link, flag);
				inque (que, visit, nep);
				s = res.suffix ();
			}
		}
		system ((rem + blank + store + slash + p2).c_str ());
		fin.close();
	}
}
void solve () {
	fout.open ("crawl.txt");
	string S = "info.ruc.edu.cn";
	//cerr << "fuck" << endl;
	bfs (S);
}
