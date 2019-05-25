#define Debug 0
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "TermLog.h" //保存出现网页的ID， 在网页中的pos
#include "vec_uti.h" //用于交集 并集

using namespace std;




//保存数据
unordered_map<string, TermLog > InvertedIndex; // inverted index
std::vector<string> titles; //标题
std::vector<int> docWordLength; //docId对应的文章的长度

//return parameters
double getTermFrequency(const string& term, int docId); //return TF
double getDocFrequency(const string& term); //return DF
inline double getTitleWeigh(int docId, const string& term); //return the weigh of title.


//构造inverted index
void initial(const char* namelist);
inline void addDocument(int docId, const string& filename); 
inline void addWordIdPos(const string& word, int docId, int pos);

// parse the query line eg "web xml" -> vector<string> {web, xml} and run the query
inline int parseQueryLine(const string& queryline, std::vector<string>& v); 
void query(); //interface 



int main(int argc, char const *argv[])
{

	initial(argv[1]);

	while(cin){
		query();
	}

	return 0;
}

void addDocument(int docId, const string& filename){
	int pos = 0;
	string word;
	ifstream ifile(filename);
	while(ifile >> word){
		addWordIdPos(word, docId, pos++);
	}
	docWordLength.push_back(pos);
}

void addWordIdPos(const string& word, int docId, int pos){

	if(InvertedIndex.find(word) == InvertedIndex.end()){
		InvertedIndex[word] = TermLog();
	}
	InvertedIndex[word].addIdPos(docId, pos);
}




double getDocFrequency(const string& term){
	if(InvertedIndex.count(term)) 
		return InvertedIndex[term].size()/(double)InvertedIndex.size(); 
	else 
		return -1.0;
}

double getTermFrequency(const string& term, int docId){
	if(InvertedIndex.count(term)){
		size_t term_size = InvertedIndex[term].getPos(docId).size();
		size_t doc_size = docWordLength[docId];
		return (double) term_size / log(log(doc_size+1)+1);
	}
	else{
		return 0.0;
	}
}

double getTitleWeigh(int docId, const string& term){
	if(titles[docId].find(term) == string::npos) return 1.0;
	else return 100.0 / (titles[docId].find(term)+1) + 1.0;
}



int parseQueryLine(const string& queryline, std::vector<string>& v){
	int size = 0;
	string word;
	istringstream ss(queryline);
	while(ss >> word){
		if(!InvertedIndex.count(word)) continue;
		++size;
		v.push_back(word);
	}
	return size;
}

void initial(const char* namelist){
	int docId = 0;
	clock_t startTime, endTime;
	string queryTerm;
	string filename;
	string fileList = namelist;
	ifstream flist(fileList);
	startTime = clock();
	while(flist){
		getline(flist, filename);
		addDocument(docId++, filename);
		titles.push_back(filename);
	}
	endTime = clock();//计时结束
	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	cout << "WordNum: " << InvertedIndex.size() << endl;
}


void query(){
	string queryline;
	vector<int> common_docs;
	vector<string> terms;
	vector<double> IDFs;
	vector<pair<int, double>> ranks;

	cout << "Please input what you want to search, if one term not exists, the prog will ignore\n";

	//parse the queryline into terms
	getline(cin, queryline);
	if(!parseQueryLine(queryline, terms)){
		cout << "sorry, we don't have what you want" << endl;
		return;
	}

	//update IDFs
	for_each(terms.begin(), terms.end(), [&](const string& term){IDFs.push_back(1.0 / getDocFrequency(term));});

	//update common_docs
	common_docs = InvertedIndex[terms[0]].getDocIds(); 
	for(auto it = terms.begin()+1; it != terms.end(); ++it){
		common_docs = intersection(common_docs, InvertedIndex[*it].getDocIds());
	}

	//creat raw rank of the common_docs
	for(auto docId: common_docs){
		double rank = 0.0;
		for(std::vector<int>::size_type i = 0; i < terms.size(); ++i){
			rank += getTermFrequency(terms[i], docId) * IDFs[i] * getTitleWeigh(docId, terms[i]);
		}
		ranks.push_back(make_pair(docId, rank));
	}

	//sort the ranks
	sort(ranks.begin(), ranks.end(), [](pair<int, double>& lhs, pair<int, double>& rhs){return lhs.second > rhs.second;});

	//output the ranks
	for(auto &r: ranks){
		cout << r.second << " " << titles[r.first] << endl;
	}

}
