#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include "searchengine.h"
using namespace std;

vector<double> SearchEngine::QWork(const vector<string> &v0){
	map<string, int> vmap;
	vector<db> v;
	int maxtf = 0;
	for(auto i = v0.begin(); i != v0.end(); ++i){
		if(!vmap.count(*i)) vmap[*i] = 1;
		else vmap[*i]++;
		maxtf = max(maxtf, vmap[*i]);
	}
	for(auto i = vmap.begin(); i != vmap.end(); ++i)
		v.push_back(RetTf(i->second, maxtf));
	return v;
}

vector<string> SearchEngine::DelMul(const vector<string> &v0){
	set<string> vset;
	vector<string> v;
	for(auto i = v0.begin(); i != v0.end(); ++i) vset.insert(*i);
	for(auto i = vset.begin(); i != vset.end(); ++i) v.push_back(*i);
	return v;
}

SearchResult SearchEngine::query(const vector<string> &v0){
	vector<db> qval = QWork(v0); // query's tf val vec
	vector<string> vv = DelMul(v0); //query's vocabulary vec
	map<ULL, int> docmap;
	vector<db> qv[QDOC_SIZE]; // store asked document vec
	qv[0].reserve(vv.size() + 1);
	int qh[QDOC_SIZE]; // from pos -> doc_id
	ULL en;
	int minn = 0, qcnt = 0, pos = 0, j = 0, k = -1;
	int vvsiz = vv.size();
	for(auto i = vv.begin(); i != vv.end(); ++i){
		en = encode(*i);
		k++;
		if(dict.count(en) > 0){
			j++;
			qv[0][j] = qval[k] * RetIdf(doc_num, dict_num[en]);
			for(Item* p = dict[en]; p != NULL; p = p->next){				
				if(docmap.size() + 1 >= QDOC_SIZE && !docmap.count(p->doc_id)) {minn = p->doc_id; break; }
				if(p->doc_id < minn) break;
				if(!docmap.count(p->doc_id)){
					docmap[p->doc_id] = pos = ++qcnt;
					qv[pos].resize(vvsiz + 1);
					qv[pos].clear();
				}
				else pos = docmap[p->doc_id];
				qh[pos] = p->doc_id;
				qv[pos][j] = p->val;
			}
		}
	}

	db cos[QDOC_SIZE], tmp = 0;
	memset(cos, 0, sizeof(cos));
	for(int i = 1; i <= qcnt; ++i){
		cos[i] = tmp = 0;
		for(k = 1; k <= j; ++k) cos[i] += qv[0][k] * qv[i][k];
		//for(k = 1; k <= j; ++k) tmp += qv[i][k] * qv[i][k];
		//cos[i] /= sqrt(tmp);
	}
	
	int st[QDOC_SIZE]; //for sort
	memset(st, 0, sizeof(st));
	for(int i = 1; i <= qcnt; ++i) st[i] = i;
	sort(st + 1, st + qcnt + 1, [cos](int _, int __)->bool{return cos[_] > cos[__]; });
	SearchResult res(qcnt);
	for(int i = 0; i < qcnt; ++i) res[i] = docs[qh[st[i + 1]]];
	return res;
}
