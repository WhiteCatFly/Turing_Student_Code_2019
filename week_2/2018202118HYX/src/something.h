#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<regex>
#include<set>
using namespace std;

string get_content(string current_url,int &total);

int match(string url);

int ifadjust(string url);

string adjust(string url,string current_url);

void parse(string content,string current_url,set<string>&urls);