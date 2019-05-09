#include "HTMLParserBase.h"

class HTMLParser: public HTMLParserBase{
public:
	HTMLParser() = default;
	HTMLParser(string url, string starturl);
	HTMLParser(std::ifstream &file, string starturl);
	void GenerateVector(string strurl, vector<string>& single_url_set_, vector<string>& history_url_set_);
	void AddEscapeCharacter(string& strurl);
	void GetSubLinks(vector<string>& single_url_set_, vector<string>& history_url_set_);
};
