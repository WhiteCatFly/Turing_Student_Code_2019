#include "crawl.h"

#define cf curp.first
#define cs curp.second
#define pss pair<string,string>
#define mp(x,y) make_pair(x,y)

ifstream fin;
ofstream fout;

string regex_search_title (const string &s) {
	smatch res;
	if (!regex_search (s, res, ti_str) ) return "";
	string ext = res[0].str ();
	int p1 = ext.find (ti_sl);
	int p2 = ext.find (ti_sr);
	stringstream ostr;
	ostr << ext.substr (p1+ti_len, p2-(p1+ti_len));
	return ostr.str ();
}

string regex_search_head (const string &s) {
	smatch res;
	if (!regex_search (s, res, he_str) ) return "";
	string ext = res[0].str ();
	int p1 = ext.find (he_sl);
	int p2 = ext.find (he_sr);
	stringstream ostr;
	ostr << ext.substr (p1+he_len, p2-(p1+he_len));
	return ostr.str ();
}

string extract (const string & s) {
	int pl, pr;
	pl = s.find ("\"");
	if (pl != string::npos) {
		pr = s.rfind ("\"");
		//fout<<pr<<" "<<s.substr (pl+1, pr-pl-1)<<endl;
		if (pr != string::npos)
			return s.substr (pl+1, pr-pl-1);
	}
	pl = s.find ("\'");
	if (pl != string::npos) {
		pr = s.rfind ("\'");
		//fout<<pr<<" "<<s.substr (pl+1, pr-pl-1)<<endl;
		if (pr != string::npos)
			return s.substr (pl+1, pr-pl-1);
	}
	pl = s.find ("=");
	if (pl != string::npos)
		return s.substr (pl+1);
	return "";
}

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

string ch_form (const string &s) {
	//fout<<s<<endl;
	string t = s;
	while (true) {
		int pos = t.find (slash);
		if (pos == string::npos) break;
		t.replace (pos, 1, udl);
	}
	//fout<<t<<endl;
	return t;
}

bool invalid (const string &s) {
	return s.find (dot) != string::npos && !checksuf (s);
}

int calc_last (string & p) {
	int num = 0, pos;
	while (true) {
		pos = p.find (last_index);
		if (pos == string::npos) break;
		num++;
		p.replace (pos, lilen, "");
	}
	return num;
}

void rem_cur (string & p) {
	int pos;
	while (true) {
		pos = p.find (cur_index);
		if (pos == string::npos) break;
		p.replace (pos, cilen, "");
	}
	return;
}

void cuts (string & s, const int & len) {
	s = s.substr (len);
}

void cuthead (string & s) {
	int pos = s.find (head);
	if (pos != string::npos)
		cuts (s, headlen);
	pos = s.find (heads);
	if (pos != string::npos)
		cuts (s, headslen);
}

void modify_slash (pss & p) {
	smatch ms;
	while (regex_search (p.first, ms, mul_slash)) {
		string ss = ms[0].str ();
		int pos = p.first.find (ss);
		p.first.replace (pos, ss.size (), slash);
		p.second.replace (pos, ss.size (), udl);
	}
}

void find_last (string & fi, string & se, int &num) {
	int pos;
	while (num--) {
		pos = fi.rfind (slash);
		if (pos == string::npos) break;
		if (fi.substr (pos) == slash) num++;
		fi = fi.substr (0, pos);
		se = se.substr (0, pos);
	}
	return;
}

pss to_link (const pss & curp, const string & link, bool &flag, int &num) {
	pss nep;
	if (flag == true) {
		nep = mp (link, ch_form(link));
	}
	else {
		string fi, se;
		if (checksuf (cf)) {
			int pos = cf.rfind (slash);
			fi = cf.substr (0, pos);
			se = cs.substr (0, pos);
		}
		else {
			fi = cf;
			se = cs;
		}
		find_last (fi, se, num);
		nep = mp (fi+slash+link, se+udl+ch_form(link));
	}
	modify_slash (nep);
	return nep;
}

void inque (queue <pss> &que, set <pss> &visit, const pss & s) {
	//fout <<"inque:" << s.first <<" " <<s.second<<endl;
	que.push (s);
	visit.insert (s);
}

CRAWL::CRAWL () {
	html_cnt = 0;
	visit.clear ();
	que = queue<pss> ();
}

CRAWL::CRAWL (string s) {
	html_cnt = 0;
	visit.clear ();
	S = s;
	que = queue<pss> ();
}

CRAWL::~CRAWL () {
	html_cnt = 0;
	S = "";
	visit.clear ();
	que = queue<pss> ();
}

void CRAWL::insert (pss &p1, pss &p2) {
	html_cnt++;
	html[html_cnt] = p2;
	html_id[p2] = html_cnt;
	son[html_id[p1]].push_back (p2);
	//fout << "cnt=" << html_cnt << endl;
}

inline void CRAWL::bfs () {
	
	extern const regex m_str;
	extern const string store;
	extern const string wg;
	extern const string rem;
	inque (que, visit, mp(S, ch_form(S)));
	//cout<<ch_form(S)<<endl;
	while (!que.empty ()) {
		pair <string, string> curp = que.front ();
		que.pop ();
		string p1 = cf;
		string p2 = cs;
		fout << p1 << endl;
		system ((wg +  p1 +  " -O " + store + slash + p2).c_str());
		fin.open ((store + slash + p2).c_str ());
		string s;
		while (getline (fin,s)) {
			smatch res;
			while (regex_search (s,res,m_str)) {
				string link = extract (res[0].str ());
				//fout<<res[0].str()<<" "<<link<<endl;
				if (checkblack (link)) {
					s = res.suffix ();
					continue;
				}
				cuthead (link);
				bool flag = checkhead (link);
				pair <string, string> nep;
				if (flag == false && invalid (link)) {
					s = res.suffix ();
					continue;
				}
				int num = calc_last (link);
				rem_cur (link);
				nep = to_link (curp, link, flag, num);
				//fout << nep.first<<endl;
				if (!visit.count (nep)) {
					insert (curp, nep);
					inque (que, visit, nep);
				}
				s = res.suffix ();
			}
		}
		system ((rem + blank + store + slash + p2).c_str ());
		fin.close();
	}
	//fout << "total_html = " << html_cnt << endl;
}

/*
CRAWL_TREE::CRAWL_TREE () {
	html_cnt = 0;
	visit.clear ();
	que = queue<pss> ();
}

CRAWL_TREE::CRAWL_TREE (string s) {
	html_cnt = 0;
	visit.clear ();
	S = s;
	que = queue<pss> ();
}

CRAWL_TREE::~CRAWL_TREE () {
	html_cnt = 0;
	S = "";
	visit.clear ();
	que = queue<pss> ();
}

void CRAWL_TREE::insert (pss &p1, pss &p2) {
	html_cnt++;
	html[html_cnt] = p2;
	html_id[p2] = html_cnt;
	son[html_id[p1]].push_back (p2);
	//fout << "cnt=" << html_cnt << endl;
}

inline void CRAWL_TREE::bfs () {
	
	extern const regex m_str;
	extern const string store;
	extern const string wg;
	extern const string rem;
	inque (que, visit, mp(S, ch_form(S)));
	//cout<<ch_form(S)<<endl;
	while (!que.empty ()) {
		pair <string, string> curp = que.front ();
		que.pop ();
		string p1 = cf;
		string p2 = cs;
		fout << p1 << endl;
		system ((wg +  p1 +  " -O " + store + slash + p2).c_str());
		fin.open ((store + slash + p2).c_str ());
		string s;
		while (getline (fin,s)) {
			smatch res;
			while (regex_search (s,res,m_str)) {
				string link = extract (res[0].str ());
				//fout<<res[0].str()<<" "<<link<<endl;
				if (checkblack (link)) {
					s = res.suffix ();
					continue;
				}
				cuthead (link);
				bool flag = checkhead (link);
				pair <string, string> nep;
				if (flag == false && invalid (link)) {
					s = res.suffix ();
					continue;
				}
				int num = calc_last (link);
				rem_cur (link);
				nep = to_link (curp, link, flag, num);
				//fout << nep.first<<endl;
				if (!visit.count (nep)) {
					insert (curp, nep);
					inque (que, visit, nep);
				}
				s = res.suffix ();
			}
		}
		system ((rem + blank + store + slash + p2).c_str ());
		fin.close();
	}
	//fout << "total_html = " << html_cnt << endl;
}
*/

void solve () {
	int init_time = clock ();
	fout.open ("crawl3.txt");
	//cout << "aaa" << endl;
	const string S = tag + "/";
	//cerr << S << endl;
	CRAWL url_crawl (S);
	url_crawl.bfs ();
	int last_time = clock ();
	//fout << CLOCKS_PER_SEC << endl;
	fout << "time = " << (double)(last_time - init_time) / CLOCKS_PER_SEC << endl;
}
