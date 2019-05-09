
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
	Parser(string root,char select)
	{
		number = 0;
		if(select == 'A')
		get_title(_content);
		else if(select == 'B')
		get_text(_content);
		else if(select == 'C')
		get_url(_content);
		else if(select == 'D')
		get_in_a_certain_way(_content);
		else if(select == 'E')
		cout << "good bye" << endl;
		else 
		cout << "wrong command" << endl;	
	}
	Parser(ifstream &io,char select)
	{
		number = 0;
		getcontent(io);
		if(select == 'A')
		get_title(_content);
		else if(select == 'B')
		get_text(_content);
		else if(select == 'C')
		get_url(_content);
		else if(select == 'D')
		get_in_a_certain_way(_content);
		else if(select == 'E')
		cout << "good bye" << endl;
		else 
		cout << "wrong command" << endl;
	}
};


