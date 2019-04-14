#include <iostream>
#include <string>
#include <regex>
#include <set>

using std::string;
using std::set;

void parseURLs(const string & page_content,const string & current_url, set <string> &urls_current_page);
