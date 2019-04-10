#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include "CmdOrder.h"

using std::string;

class HTMLParser{
private:
	string url_;
	string location_;
	string html_;
public:
	HTMLParser() = default;
    HTMLParser(string url);
	HTMLParser(std::ifstream &file);
	string replace(string str, string pattern, string repattern);
	void DownloadFromUrl();
	string GetTitle();
	void DeleteLabel(string& body);
	string GetBody();
	string GetSubLinks();
	~HTMLParser();
};
