#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "searchengine.h"
#include "./THULAC/include/thulac.h"

#define DEBUG 0
using namespace std;

int main(int argc, char* argv[]){
	SearchEngine se;
	if(DEBUG || (argc > 1 && strcmp(argv[1], "init") == 0)){
		if(se.init()){
			cout << "init error" << endl; 
			return 0;
		}
		else cout << "init completed" << endl;
	}
	else{
		if(se.build()){
			cout << "build error" << endl;
			return 0;
		}
		else cout << "build completed" << endl;
	}
	string str, s0;
	int len = 0;
	THULAC lac;
	lac.init("./THULAC/models/", NULL, 0, 0, 0, '_');
	THULAC_result res;
	SearchResult qr;
	while(1){
	    cout << "find:";
		getline(cin, str);
		//str = "校长";
		lac.cut(str, res);
		len = 0;
		vector<string> qv;
		for(auto i = res.begin(); i != res.end(); ++i){
			if(i -> first == " " || i -> first == "\n" || i -> first == "\r") continue;
			qv.push_back(i -> first), len++;
			if(len >= QUERY_SIZE) break;
		}
		qr = se.query(qv);
		len = 0;
	    for(auto i = qr.begin(); i != qr.end(); ++i){
			++len;
			if(len > QRES_SIZE) break;
			cout <<  (*i).tit << "\n" << (*i).htm << "\n" << endl;
		}
		cout << endl;
	}

	return 0;
}
