#include <fstream>
#include<algorithm>
#include "Request.h"
#define DEBUG 0

using std::string;

//定义static变量
string Request::common_command = "";
string Request::BASE = "";
Attribute Request::Config = Attribute();

void Request::setConfig(const Attribute& config){
	Config = config;
	BASE = Config["url"];
	common_command = "wget --max-redirect=0 ";
	common_command += " --timeout=";
	common_command += Config["timeout"];
	common_command += " -tries=";
	common_command += Config["tries"];
}

Request::Request(const string& url_):crawled(false), url(url_) 
{
	//set filename
	if(url.length() == BASE.length()){
		filename = "index.html";
	}
	else if(url.length() > BASE.length()){
		filename = url_.substr(BASE.length());
		std::replace(filename.begin(), filename.end(), '/', '_');
	}

	//set cur_dir
	size_t pos = url.rfind('/');
	if(pos < BASE.rfind('/')) cur_dir = BASE; // if that url is http://www.xxxx.com, use BASE
	else cur_dir = url.substr(0, pos+1);
}

void Request::crawl(){
	using std::system;
	if(url.length() < BASE.length()) return;
	string command = common_command;
	command += " \"";
	command += url;
	command += "\" -O \"";
	command += filename;
	command += "\"";
	crawled = system(command.c_str()) == 0;
}

bool Request::parseUrl(string &s_url, size_t pos){
	//input:an url select from the file
	//output:true:parsed and s_url is the result
	//       false:wrong url, ignored
	
	const string prefixs[] = {"mailto", "#", ";", "javas"};
	const string suffixs[] = {".css", ".docx", ".doc", ".xls", ".xlsx", ".pdf", ".ppt",".JPG", ".ico",
								"rar", ".flv", ".png", ".zip", ".gif", ".jpg", ".bmp",".jpeg"}; // filter by suffix
	if(!s_url.length()) return false;
	for(auto x: prefixs){
		if(hasPrefix(s_url, x)) return false;
	}

	for(auto x: suffixs){
		if(hasEnding(s_url, x)) return false;
	}

	if(hasPrefix(s_url, "http")){
		if(hasPrefix(s_url, BASE)) return true;
		else return false;
	}


	if (s_url[0] == '/')
	{
		s_url = BASE + s_url.substr(1);
		return true;
	}

	//遇到./ ../ 递归parseUrl
	if(hasPrefix(s_url, "./")){
		s_url = s_url.substr(2);
		return parseUrl(s_url, pos);
	}

	if(hasPrefix(s_url,"../")){
		s_url = s_url.substr(3);
		pos = cur_dir.rfind('/', pos-1);
		if(pos == string::npos) return false;
		return parseUrl(s_url, pos);
	}

	s_url = cur_dir.substr(0, pos+1) + s_url;
	return true;
}


void Request::getUrls(std::vector<string> &v){
	if(!crawled) return; // fail to crawl url. so do nothing.
	std::ifstream ifile(filename);
	if(!ifile) return; // fail to open the file, so return.
	if(DEBUG) std::cout << "Try to parser the " << filename << std::endl;
	HTMLParser parser = HTMLParser(ifile);
	std::vector<string> RAWURLS;
	parser.getLinks(RAWURLS);
	for(auto raw_url : RAWURLS){
		if(parseUrl(raw_url, cur_dir.length()-1)){
			v.push_back(raw_url);
		}
	}
	ifile.close();
}