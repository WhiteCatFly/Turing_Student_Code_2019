#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <numeric>

using std::string;

int countstr(const std::string& str, const std::string& sub){
	int num = 0;
	for (size_t i = 0; (i = str.find(sub, i)) != std::string::npos; num++, i++);
	return num;
}

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {
	std::vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});
	return idx;
}

int main(int argc, char*argv[]){
	int n;
	std::cout << "the number of words to query: ";
	std::cin >> n;
	std::vector<string>words;
	for (int j=0; j<n; j++){
		std::cout << "please enter the word you'd like to search: ";
		string word;
		std::cin >> word;
		words.push_back(word);
	}
	string txt = argv[1];
	std::ifstream pagestxt(txt);
	string page;
	std::vector<string> pages; 
	while(getline(pagestxt, page)){
		pages.push_back(page);
	}
	pagestxt.close();
	std::vector<double>idfs;
	for(int m=0; m<n; m++){
		double idfe = count(pages.begin(), pages.end(), words[m]);
		double idf = log10(pages.size()/(1+idfe));
		idfs.push_back(idf);
	}
	
	std::vector<double> tfidfs;
	for(int i=0; i<pages.size(); i++){
		double tfidf = 0;
		for(int z=0; z<n; z++){
		double tfo = countstr(pages[i], words[z]);
		double tfe = countstr(pages[i], " ");
		tfidf = tfidf+ tfo/tfe*idfs[z];
		}
		tfidfs.push_back(tfidf);
	}
	std::vector<int> indexs(tfidfs.size(), 0);
	for(int p=0; p<indexs.size(); p++){
		indexs[p] = p;
	}
	sort(indexs.begin(), indexs.end(), [&](const int& a, const int& b){
				return (tfidfs[a] > tfidfs[b]);
			});
	for(int k=0; k<tfidfs.size(); k++){
		std::cout << indexs[k] << " " << tfidfs[indexs[k]] << std::endl;
	}
	return 0;
}
