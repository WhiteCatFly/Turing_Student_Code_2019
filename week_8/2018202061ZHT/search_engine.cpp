#include "search.h"

using namespace std;


ifstream fin;
ofstream fout;

Search::Search () {
	for (int i = 1; i <= N; i++) v[i].clear ();
	mod.clear ();
	id.clear ();
	pos.clear ();
}

Search::~Search () {}

double Search::cal_tf (int cnt) {
	if (cnt == 0) return 0;
	return 1.0 + (log10(cnt));
}

double Search::cal_idf (int cnt) {
	return log (N/cnt);
}

void Search::divide (string s, vector <string> &vec) {
	vec.clear ();
	int pos;
	pos = s.find ("/");
	if (pos == string::npos) {
		vec.push_back (s);
		return;
	}
	if (pos > 0)
		vec.push_back (s.substr (0, pos));
	s = s.substr (pos + 1);
	while (1) {
		pos = s.find ("/");
		if (pos == string::npos) {
			if (s != " ")
				vec.push_back (s);
			break;
		}
		if (s.substr (0, pos) != " ")
			vec.push_back (s.substr (0, pos));
		s = s.substr (pos + 1);
	}
}

void Search::pre_deal () {
	fin.open ("splite.txt");
	string s;
	while (getline (fin, s)) {
		int doce_num = 0;
		for (int i = 0; i < s.size() && isdigit(s.at(i)); i++)
			doce_num = doce_num * 10 + s.at(i) - '0';
		divide (s, v[doce_num]);
		string tmp;
		for (int i = 0; i < v[doce_num].size(); i++) {
			tmp = v[doce_num][i];
			if (pos[tmp].empty()) {
				pos[tmp].push_back(make_pair(doce_num, 1));
				id[make_pair(tmp, doce_num)] = pos[tmp].size()-1;
			}
			else if (pos[tmp].back().first != doce_num) {
				pos[tmp].push_back(make_pair(doce_num, 1));
				id[make_pair(tmp, doce_num)] = pos[tmp].size()-1;
			}
			else
				pos[tmp].back().second++;
		}
	}
	fin.close ();
}

void Search::query () {
	fin.open ("search.txt");
	string s;
	while (getline (fin, s)) {
		divide (s, mod);
		m = mod.size();
		for (int i = 1; i <= N; i++) {
			value[i] = 0.0;
			for (int j = 0; j < m; j++)
				if (id.count(make_pair (mod[j], i)))
					value[i] += cal_tf (pos[mod[j]][id[make_pair (mod[j], i)]].second)
					* cal_idf (mod[j].size ());
			if (value[i] > eps) 
				Q.push (make_pair (value[i], i));
		}
		while (!Q.empty ()) {
			fout << Q.top().first << " " << Q.top().second << endl;
			vector <string> tmp = v[Q.top().second];
			for (int i = 1; i < tmp.size (); i++)
				fout << tmp[i] ;
			fout << endl;
			Q.pop();
		}
	}
	fin.close ();
}

void solve () {
	fout.open ("output.txt");
	Search A;
	A.pre_deal();
	A.query();
	fout.close();
}
