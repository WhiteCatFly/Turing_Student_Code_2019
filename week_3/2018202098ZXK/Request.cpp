#include "Request.h"
#define Debugger 0
#include <cassert>
#include <sstream>
#include <fstream>

string Request::BASE = "";
int Request::time_out = 0;
int Request::tries_num = 0;

string getKey(std::ifstream& in, string& key){
	string line;
	string val;
	size_t pos;
	std::getline(in, line);
	pos = line.find("=");
	assert(pos != string::npos);
	assert(key == line.substr(0, pos));
	return line.substr(pos+1);
}

Config iniConfig(const string& iniFile){
	using std::stoi;
	Config conf;
	conf.loaded = false;
	const int key_size = 6;
	string keys[key_size] = {"Web_Base", "Num_Thread", "Time_Sleep", "Num_Tries", 
							"Time_Out", "Error_File"};
	std::ifstream configFile;
	configFile.open(iniFile, std::ios::in);
	if(!configFile){
		std::cout << "unable to load configFile "<< iniFile << std::endl;
		return conf;
	}
	//逐步加载conf
	conf.BASE = getKey(configFile, keys[0]);
	conf.thread_num = stoi(getKey(configFile, keys[1]));
	conf.sleep_time = stoi(getKey(configFile, keys[2]));
	conf.tries_num = stoi(getKey(configFile, keys[3]));
	conf.time_out = stoi(getKey(configFile, keys[4]));
	conf.err_file = getKey(configFile, keys[5]);
	conf.loaded = true;
	return conf;
}

void Request::crawl(){
	using std::system;
	using std::to_string;
	if(url.length() + 1 < BASE.length()) return;
	string command = "wget -q --max-redirect=0";
	command += " --timeout=";
	command += to_string(time_out);
	command += " -tries=";
	command += to_string(tries_num);
	command += " \"";
	command += url;
	command += "\" -O \"";
	command += filename;
	command += "\"";
	crawled = system(command.c_str()) == 0;
	if(Debugger && !crawled){
		std::cout << "Command is " << command << std::endl;
	}
	if(Debugger && crawled){
		std::cout << "Scommand is " << command << std::endl;
	}
}

Request::Request(string url_):url(url_), crawled(false)
{
	//set filename
	if(url.length() == BASE.length()){
		filename = "index.html";
	}
	else{
		filename = url_.substr(BASE.length());
		strReplace(filename, '/', '_');
	}

	//set cur_dir
	size_t pos = url.rfind('/');
	if(pos < 7) cur_dir = BASE + '/'; // if that url is http://www.xxxx.com, use BASE+/
	else cur_dir = url.substr(0, pos+1);
}

bool Request::parseUrl(string &s_url){
	//input:an url select from the file
	//output:true:parsed and s_url is the result
	//       false:wrong url, ignored
	if(Debugger){
		std::cout << "\t" << s_url << std::endl;
	}
	const string prefixs[] = {"mailto", "#", ";"};
	const string suffixs[] = {".css", ".docx", ".doc", ".xls", ".xlsx", ".pdf", ".ppt",".JPG",
								"rar", ".flv", ".png", ".zip", ".gif", ".jpg", ".bmp",".jpeg"}; // filter by suffix
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

	while(hasPrefix(s_url, "./")){
		s_url = s_url.substr(2);
	}


	int pos = cur_dir.length()-1;
	while(hasPrefix(s_url,"../")){
		s_url = s_url.substr(3);
		pos = cur_dir.rfind('/', pos-1);
	}
	s_url = cur_dir.substr(0, pos+1) + s_url;

	return true;
}


void Request::getUrls(std::vector<string> &v){
	if(!crawled) return; // fail to crawl url. so do nothing

	const string pattern = "href=[\"|\']([^\"\']+)[\"|\']";

	std::regex word_regex(pattern);
	string text = load2text(filename);
	if(!text.length()) return;//fail to open file, so do nothing

    auto words_begin = 
    std::sregex_iterator(text.begin(), text.end(), word_regex);
    auto words_end = std::sregex_iterator();

    //use pattern
    for(std::sregex_iterator i = words_begin; i != words_end; ++i){
    	std::smatch match = *i;
    	string s_url = match.str(1);
    	if(parseUrl(s_url)){
    		v.push_back(s_url);
    	}
    }

    //use pattern2
    std::regex word_regex2("href=([^\"\'>]+)>");
    auto words_begin2 = std::sregex_iterator(text.begin(), text.end(), word_regex2);
    auto words_end2 = std::sregex_iterator();
    for(std::sregex_iterator i = words_begin2; i != words_end2; ++i){
    	std::smatch match = *i;
    	string s_url = match.str(1);
    	if(parseUrl(s_url)){
    		v.push_back(s_url);
    	}
    }


}

void Request::set_config(Config &conf){
	BASE = conf.BASE;
	time_out = conf.time_out;
	tries_num = conf.tries_num;
}

