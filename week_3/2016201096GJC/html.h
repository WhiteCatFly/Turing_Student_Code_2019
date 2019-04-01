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
public:
	Html() = default;
	Html(int i, int road);
	static vector<string> _single_url_set;
	static vector<string> _history_url_set;
	static int count;
	void HtmlName();
	void GenerateVector(string strurl);
	void ReduplictionRemoving();
	void HtmlParse(string RegularExperssion);
	void ShowCount() const;
};
