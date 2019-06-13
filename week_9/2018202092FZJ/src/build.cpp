#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "searchengine.h"
using namespace std;

bool SearchEngine::build(){
	ifstream databs(DATABS_NAME);
	if(!databs) return 1;
	int dict_sz, voc_num, doc_id;
	ULL en;
	double val;
	string voc_name;
	Item* p, *nowp;
	databs >> dict_sz;
	for(int i = 1; i <= dict_sz; ++i){
		databs >> en >> voc_name >> voc_num;
		for(int j = 1; j <= voc_num; ++j){
			databs >> val >> doc_id;
			p = new Item; p->val = val; p->doc_id = doc_id;
			p->voc_name = voc_name;
			if(j == 1) dict[en] = nowp = p;
			else nowp->next = p, p->pre = nowp, nowp = p;
		}
		dict_num[en] = voc_num;
	}

	databs >> doc_num;
	for(int i = 1; i <= doc_num; ++i){
		databs >> docs[i].tit >> docs[i].body >> docs[i].htm;
	}
	databs.close();
	return 0;
}
