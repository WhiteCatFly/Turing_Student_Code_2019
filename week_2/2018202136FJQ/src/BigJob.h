
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
extern int number ;
extern string root ;
extern string current_url ;
extern queue<string> url_to_be_crawled;
extern set<string> url_already_be_crawled;
void getContent(string);
void deep_search(void);

