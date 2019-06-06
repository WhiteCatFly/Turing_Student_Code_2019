#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED

#include <fstream> 
#include <iostream> 
#include <vector> 
#include <memory> 
#include <map> 
#include <set> 
#include <string> 
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std; 
const int N = 6200;
const int K = 10;

class TextQuery 
{ 
public:
    TextQuery(); //构造函数，传入要查询的文本 
    TextQuery(int);
    void query(const string&); //查询函数，传入要查询的单词，返回查询结果 
    ~TextQuery(){}; 
private: 
    int Count;
    vector<int> filecount;
    map<string,vector<int>> wm;
};
bool cmp(pair<string,int>&,pair<string,int>&);
#endif