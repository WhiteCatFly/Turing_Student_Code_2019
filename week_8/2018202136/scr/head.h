#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <ctime>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <regex>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
struct havenapart{
	map<string,int> file;
	int total_number;
	string url_name;
	int ID;
	double dft;
};
extern int nsize;
extern string word[100];
extern havenapart all[10000];  
void getdft(int n,string *p,int size);
void fromitoa(int i,string & s);
void store(int n);

class HtmlParser{
private:
	int number ;
    string _content;
	string _root ;
	string current_url ;
	set<string> title_already_be_HtmlParser;
	set<string> url_already_be_HtmlParser;
	queue<string> url_to_be_HtmlParser;
	set<string> text_already_be_HtmlParser;
	set<string> a_way_already_be_HtmlParser;
public:
    HtmlParser()
	{
		number = 0;
	}
	HtmlParser(string root)
	{
		number = 0;
		current_url = root;
		_root = root;
	}
	HtmlParser(string root,char select);
    HtmlParser(ifstream &io,char select);
    void getcontent(ifstream &io);
	void get_title(string content);
 	void get_text(string content);
	void get_url(string content);
	void get_in_a_certain_way(string content);
	void getContent(string url);
	void deep_search(void);
	int getnumber(void) const{
		return number;
	}
	~HtmlParser(){}
};