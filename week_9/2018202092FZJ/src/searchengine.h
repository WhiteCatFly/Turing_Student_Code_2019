#ifndef SEARCHENGINE_H_
#define SEARCHENGINE_H_

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include "const.h"

#define db double
#define LL long long
#define ULL unsigned long long

class Document{
	friend class SearchEngine;
public:
	std::string tit, body, htm;
	Document() {tit = body = htm = ""; }
	~Document() {}
};

class Item{
	friend class SearchEngine;
private:
	double tf, idf, val;
	int doc_id;
	std::string voc_name;
	Item* next, *pre;
public:
	Item() {tf = idf = val = doc_id = 0; voc_name = ""; next = pre = NULL; }
	~Item() {}	
};

typedef std::vector<Document> SearchResult;

class SearchEngine{
private:
	std::map<ULL, Item*> dict;
	std::map<ULL, int> dict_num;
	Document docs[DOC_SIZE];	
	int doc_num;
	
	ULL encode(const std::string&);
	int InitWork(std::ifstream&, std::vector<ULL>&, int, int);
	std::vector<db> QWork(const std::vector<std::string>&);
	std::vector<std::string> DelMul(const std::vector<std::string>&);
	
public:
	SearchEngine() {doc_num = 0; }
	~SearchEngine();
	bool init(); //no error return 0,else return 1
	bool build();
	SearchResult query(const std::vector<std::string>&);
};

//inline double RetTf(int x) {return x ? 1 + log10(x) : 0; }
inline double RetTf(int x, int y) {return 0.5 + (0.5 * (db)x) / (db)y; }
inline double RetIdf(double N, double x) {return x ? log10(N / x) : 0; }

#endif
