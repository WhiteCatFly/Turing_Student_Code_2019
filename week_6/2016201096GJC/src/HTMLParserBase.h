#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>
#include "CmdOrder.h"

using std::string;
using std::vector;

class HTMLParserBase{
private:
	string url_;
	string location_;
public:
	string html_;
	string starturl_;
	HTMLParserBase() = default;
    HTMLParserBase(string url, string starturl);
	string replace(string str, string pattern, string repattern);
	void DownloadFromUrl();
	string GetTitle();
	void DeleteLabel(string& body);
	string GetBody();
	~HTMLParserBase();
};
