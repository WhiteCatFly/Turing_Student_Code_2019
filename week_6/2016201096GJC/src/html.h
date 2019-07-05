#include "HTMLParser.h"

using std::string;
using std::vector;

class Html{
private:
	int road_;
	int i_;
	HTMLParser parser_;
	string htmlname_;
	string starturl_;
public:
	Html() = default;
	Html(int i, int road, string starturl);
	static vector<string> single_url_set_;
	static vector<string> history_url_set_;
	void HtmlName();
	void HtmlParse();
	void ShowCount() const;
};
