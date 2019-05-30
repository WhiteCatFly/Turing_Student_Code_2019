#ifndef SEARCH_H_
#define SEARCH_H_

#include<map>
//#include"./THULAC/include/thulac.h"
using namespace std;

void apart();
class Search
{
private:
    map<string,string> mapurl;
    //map<double,pair<string,string>> mapfinal;
    int all_num;
    int num;
    int word_num;
    string* word;
    string* url_;
    int* word_times;
    double* word_times_lg;
    double* word_frequency;
public:
    Search();
    void find_times();
    void find_frequency();
    void word_apart(string& words);
    void sort();
    ~Search();
};



#endif