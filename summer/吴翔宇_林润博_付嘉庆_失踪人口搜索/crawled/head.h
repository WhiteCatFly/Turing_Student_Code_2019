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
#include <stdlib.h>
using namespace std;
int datechange(string date);
void dealwith12(string command,string file,int Loc ,int loc);
void dealwith3(string command,string file,int Loc ,int loc);
class crawled
{
   private:
	int number ;
	string _root ;
	string current_url ;
	queue<string> url_to_be_crawled;
	set<string> url_already_be_crawled;
	void getContent(string);
	void deep_search(void);
   public:
	crawled()
	{
		number = 0;
	}
	crawled(string root)
	{
		number = 0;
		_root = root;
		deep_search();
	}
};



