#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "searchengine.h"
using namespace std;

ULL SearchEngine::encode(const string& str){
	const char* ch = str.c_str();
	ULL t = 0;
	while((*ch) != '\0'){
		t = (t << 8) + (ULL)(*ch);
		ch++;
	}
	return t;
}

int SearchEngine::InitWork(ifstream& f, vector<ULL> &v, int id, int op){//op == 0: title, otherwise body
	string str;
	ULL en;
	Item* p, * q;
	int maxtf = 0;
	while(f >> str){
		if(!op) docs[id].tit += str;
		else{
			if((docs[id].body + str).length() <= BODY_MAXLEN) docs[id].body += str;
		}			
		en = encode(str);
		if(!dict.count(en) || (dict[en]->doc_id != id)){
			p = new Item; p->tf = 1, p->val = !op ? TIT_VALUE : BODY_VALUE;
			p->doc_id = id, p->voc_name = str;		
			q = dict[en], p->next = q;
			if(q != NULL) q->pre = p;
			dict[en] = p;
			v.push_back(en);
			if(dict_num.count(en)) dict_num[en]++;
			else dict_num[en] = 1;
		}
		else dict[en]->tf += 1;
		maxtf = max(maxtf, (int)dict[en]->tf);
	}

	return maxtf;
}

inline static const string& trans(const string& str){
	if(str == "") return NULL_STRING;
	else return str;
}

bool SearchEngine::init(){
	ifstream file_list("./data/file_list.txt");
	if(!file_list) return 1;
	string str;
	char tmpstr[READ_MAXLEN + 1];
	int tf1, tf2;
	memset(tmpstr, 0, sizeof(tmpstr));
	while(file_list.getline(tmpstr, READ_MAXLEN)){
		str = tmpstr;
		doc_num++;
		docs[doc_num].htm = str; //11
		ifstream doc_tit("./data/" + str + "_title.txt"), doc_body("./data/" + str + ".txt");
		vector<ULL> v;
		tf1 = InitWork(doc_tit, v, doc_num, 0);
		tf2 = InitWork(doc_body, v, doc_num, 1);
		tf1 = max(tf1, tf2);
		int vlen = v.size();
		for(int i = 0;i < vlen; ++i){
			dict[v[i]]->tf = RetTf(dict[v[i]]->tf, tf1);
		}
	}
	
	int voc_num;
	double voc_idf;
	ofstream databs(DATABS_NAME);
	databs << dict.size() << endl;
	for(auto i = dict.begin(); i != dict.end(); ++i){
		voc_num = dict_num[i->first];
		voc_idf = RetIdf(doc_num, voc_num);
		databs << i->first << " " << i->second->voc_name << " " << voc_num;
		for(Item* p = i -> second; p != NULL; p = p->next){
			p->idf = voc_idf;
			p->val *= p->tf * p->idf;
			databs << " " << p->val << " " << p->doc_id;
		}
		databs << endl;
	}
	databs << doc_num << endl;
	for(int i = 1; i <= doc_num; ++i) databs << trans(docs[i].tit) << " " << trans(docs[i].body) << " " << trans(docs[i].htm) << endl;
	databs.close();
	
	return 0;
}
