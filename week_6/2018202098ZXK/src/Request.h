#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include "Attribute.h"
#include "HTMLParser.h"
#include "string_tools.h"

using std::string;

class Request
{
	friend class SSpider; //SSpider needs to access common_command to add headers, cookies ..etc
private:
	bool   crawled;
	string url; //given url
	string cur_dir; //current url directory.
	string filename;
	HTMLParser parser;
	static string    BASE; //from where to crawl, like "info.ruc.edu.cn"
	static string    common_command;//all of the commands contain string like "wget --timeout 5 -tries 2"
	static Attribute Config; 
	bool parseUrl(string &s_url, size_t pos); //example: input:".././displaynews.php?id=13562" output:"http://econ.ruc.edu.cn/displaynews.php?id=13562"
public: 
	Request(){}
	Request(const string& url_);
	void crawl();
	void getUrls(std::vector<string> &v);
	bool getStatus(){return crawled;}
	static void setConfig(const Attribute& config);
};

#endif