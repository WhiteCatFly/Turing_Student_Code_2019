#ifndef SEARCH_H_INCLUDE
#define SEARCH_H_INCLUDE

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <map>

using namespace std;
/*
ifstream fin;
ofstream fout;
*/
const int N = 1000;
const int M = 1000;
const double eps = 1e-7;

class Search {
private:
	int m, tf_cnt[M+5], idf_cnt[M+5];
	double value[N+5], w[M+5];
	vector<string> v[N+5], mod;
	map< pair <string, int> , int> id;
	map<string, vector <pair <int, int> > > pos;
	struct val {
		double v;
		int id;
		val () {}
		val (double _v, int _id) {
			v = _v; id = _id;
		}
		bool operator <(const val &t) const{return v > t.v;}
	};
	priority_queue< pair<double, int> > Q;
public:
	Search ();
	~Search ();
	double cal_tf (int cnt);
	double cal_idf (int cnt);
	void divide (string s, vector <string> &vec);
	void pre_deal ();
	void query ();
};


void solve ();

#endif
