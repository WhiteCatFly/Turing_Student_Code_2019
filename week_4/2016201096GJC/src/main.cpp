#include "HTMLParser.h"

int main(){
	string url = "http://econ.ruc.edu.cn/displaynews.php?id=15359";
	HTMLParser html(url);
	string title = html.GetTitle();
	string body = html.GetBody();
    string subLinks = html.GetSubLinks();
	std::cout << title << std::endl;
	std::cout << body << std::endl;
	std::cout << subLinks << std::endl;
	return 0;
}
