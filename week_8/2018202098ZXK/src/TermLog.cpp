#include "TermLog.h"

const vector<int>& TermLog::getPos(int docId){
	static std::vector<int> null{};
	int lo = 0, hi = docIds.size(), mid;
	//# [first, last)内第一个不小于value的值的位置
	while(lo < hi){
		mid = lo + (hi - lo) / 2;
		if(docIds[mid] < docId) lo = mid+1;
		else hi = mid;
	}

	if(hi == (int) docIds.size() || docIds[hi] != docId) return null;
	return positions[hi];
}

void TermLog::addIdPos(int id, int pos){
	if(!docIds.size()){
			docIds.push_back(id);
			positions.push_back(std::vector<int>{});
		}
		if(docIds.back() != id){
			docIds.push_back(id);
			positions.push_back(std::vector<int>{});
		}
		positions.back().push_back(pos);
}


ostream& operator<<(ostream& os, TermLog& tlog){
	size_t size = tlog.docIds.size();
	for(size_t i = 0; i < size; ++i){
		for(auto &pos: tlog.positions[i]){
			os << pos << " ";
		}
		os << std::endl;
	}
	return os;
}
