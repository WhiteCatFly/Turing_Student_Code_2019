#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include "searchengine.h"
using namespace std;

SearchEngine::~SearchEngine(){
	Item* q;
	for(auto i = dict.begin(); i != dict.end(); ++i){
		for(Item* p = i -> second; p != NULL;){
			q = p; p = p->next; delete q;
		}
	}
}
