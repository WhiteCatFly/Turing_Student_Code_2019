#include "vec_uti.h"

std::vector<int> intersection(const std::vector<int>& v1, const std::vector<int>& v2){
	std::vector<int> res;
	auto p = v1.begin();
	auto q = v2.begin();
	while(p!=v1.end() && q!=v2.end()){
		if(*p < *q) ++p;
		else if(*p > *q) ++q;
		else{
			res.push_back(*p);
			++p;
			++q;
		}
	}
	return res;
}


std::vector<int> unionsection(const std::vector<int>& v1, const std::vector<int>& v2){
	std::vector<int> res;
	auto p = v1.begin();
	auto q = v2.begin();
	while(p!=v1.end() && q!=v2.end()){
		if(*p < *q){
			res.push_back(*p);
			++p;
		}
		else if(*p > *q){
			res.push_back(*q);
			++q;
		}
		else{
			res.push_back(*p);
			++p;
			++q;
		}
	}
	while(p!=v1.end()){
		res.push_back(*p);
		++p;
	}
	while(q!=v2.end()){
		res.push_back(*q);
		++q;
	}
	return res;
}
