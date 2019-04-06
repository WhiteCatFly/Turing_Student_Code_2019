#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <algorithm>

using std::string;
using std::vector;

class Html{
private:
	int _road;
	int _i;
	string _htmlname;
	string _starturl;
public:
	Html() = default;
	Html(int i, int road, string starturl);
	static vector<string> _single_url_set;
	static vector<string> _history_url_set;
	void HtmlName();
	void GenerateVector(string strurl);
	void HtmlParse(string RegularExperssion);
	inline void AddEscapeCharacter(string& strurl){
		if (strurl.find("page=") != string::npos){
			int position = strurl.find("page=");
            strurl = strurl.insert(position-2, "\\");
			strurl = strurl.insert(position, "\\");
		}
	}
	void ShowCount() const;
};
