#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <regex>
#include <time.h>
using namespace std;
class Crawled
{
   private:
	int number ;
	string _root ;
	string current_url ;
	queue<string> url_to_be_Crawled;
	set<string> url_already_be_Crawled;
   public:
	void getContent(string);
	void deep_search(void);
	Crawled()
	{
		number = 0;
	}
	Crawled(string root)
	{
		number = 0;
		_root = root;
	}
};
class Parser
{
   private:
	int number ;
	set<string> title_already_be_parser;
	set<string> url_already_be_parser;
	set<string> text_already_be_parser;
	set<string> a_way_already_be_parser;
	void getcontent(ifstream &io);
	string _content;
	void get_title(string content);
 	void get_text(string content);
	void get_url(string content);
	void get_in_a_certain_way(string content);
public:
	Parser()
	{
		number = 0;
	}
	Parser(string root,char select);
	Parser(ifstream &io,char select);
};
class Crawled_parser : public Crawled 
{
private:
    char _command;
    Parser _parser;
public:
    Crawled_parser(){}
    Crawled_parser(string root);
    ~Crawled_parser(){}
};
