#ifndef TERM_LOG_H
#define TERM_LOG_H

#include <vector>
#include <iostream>


using std::ostream;
using std::vector;
//保存出现网页的ID， 在网页中的pos
class TermLog
{
	friend ostream& operator<<(ostream& os, TermLog& tlog);
private:
	vector<int> docIds;
	vector<vector<int>> positions;
public:
	int size(){return docIds.size();}
	void addIdPos(int id, int pos); //o(1)
	const vector<int>& getDocIds(){return docIds;} //return the doc_ids o(1)
	const vector<int>& getPos(int docId); // return the pos in the document o(log(n))
	TermLog() = default;
	~TermLog() = default;
};


#endif