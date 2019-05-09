#include <iostream>
#include "Spider.h"
#define Debug 0

Spider::Spider(const Attribute& config){
	Config  = config;
	Request::setConfig(Config);
	q.push(Config["url"]);
	errFile = std::ofstream(Config["error"]);
}

string Spider::getFront(){
	std::string res = "";
	if(q.empty()) return res;
	res = q.front();
	q.pop();
	runLog << "pop " << res << std::endl;
	return res;
}


void Spider::crawlSingle(string url){
	if(!url.length()) return;//empty string, do nothing
	Request R(url);
	std::vector<std::string> v{};
	R.crawl();
	if(!R.getStatus()){
		std::cout << "Can not download " << url << std::endl;
		errFile << url << std::endl;
		return;
	}
	R.getUrls(v);
	mt.lock();
	for(auto x: v){
		if(urlSet.find(x) == urlSet.end()){
			urlSet.insert(x);
			q.push(x);
			runLog << "push " <<x << std::endl;
		}
	}
	mt.unlock();
}

void threadWrapper(Spider* s, std::thread* t){
	*t = std::thread(&Spider::crawlSingle, s, s->getFront());
}

void Spider::run(){
	using std::string;
	using std::stoi;

	std::thread *T;
	int t_num = stoi(Config["thread"]);
	int sleep_time = stoi(Config["sleep"]);
	runLog = std::ofstream(Config["runlog"], std::ios::app);

	while(!q.empty()){
		T = new std::thread[t_num];
		for(int i = 0; i < t_num; i++){
			threadWrapper(this, T+i);
			usleep(sleep_time);
		}
		for(int i = 0; i < t_num; i++){
			T[i].join();
		}
		delete [] T;
	}

	std::cout << "We have finished!\n";
	runLog.close();
	errFile.close();
}

void Spider::load(){
	std::set<std::string> popUrl;
	std::string line;
	std::ifstream infile(Config["reload"],std::ios::in);

	if(!infile){
		std::string fileError = "your run log does not exists";
		throw std::invalid_argument(fileError);
	}

	while (infile)
	{
		std::getline(infile, line);
		if(!line.length()) continue;
		if(hasPrefix(line, "pop") && line.length() > 4) popUrl.insert(line.substr(4));
		else if (hasPrefix(line, "push") &&  line.length() > 5) urlSet.insert(line.substr(5));
	}
	infile.close();

	for(auto url: urlSet){
		if(popUrl.find(url) == popUrl.end()){
			q.push(url);
		}
	}
	run();
}

void SSpider::addHeader(const string& key, const string& val){
	Request::common_command += ("  --header=\""  + key + ":"  + val + "\" ");
}

void SSpider::addCookies(const string& cookie_file){
	Request::common_command += ("--load-cookies= "+cookie_file + " ");
}

std::map<string, string> SSpider::creatHeaders(const string& header_file){
	std::map<string, string> res;
	std::string line;
	std::pair <string, string> pa;
	std::ifstream ifile(header_file);

	if(!ifile){
		string error = "Unable to open " + header_file;
		throw std::invalid_argument(error);
	}
	while (ifile)
	{
		std::getline(ifile, line);
		pa = splitKeyVal(line, ':');
		res[pa.first] = pa.second;
	}

	return res;
}

SSpider::SSpider(const Attribute& config, const string& header, const string& cookie ):Spider(config), gziped(false){
	if(header.length()){
		std::map<string, string> headers = creatHeaders(header);
		if(headers.count("Accept-Encoding")){
			if(headers["Accept-Encoding"].find("gzip") != std::string::npos){
				gziped = true;
			}
		}
		for(auto item: headers){
			addHeader(item.first, item.second);
		}
	}
	if(cookie.length()){
		 addCookies(cookie);
	}
}

void SSpider::crawlSingle(string url){
	if(!gziped){
		Spider::crawlSingle(url);
		return;
	}

	if(!url.length()) return;//empty string, do nothing
	Request R(url);
	std::vector<std::string> v{};
	R.crawl();
	if(!R.getStatus()){
		std::cout << "Can not download " << url << std::endl;
		errFile << url << std::endl;
		return;
	}

	//overload Part
	if(Debug) std::cout << "in crawl gziped is true\n";
	string command = "mv ";
	string filename = R.filename;
	command += filename;
	command += " ";
	command += filename;
	command += ".gz";
	if(system(command.c_str())){
		// depress the file, but when it fails, log the error and return!
		errFile << url << std::endl;
		return;
	}
	//if(Debug) std::cout << command << std::endl;
	command = "gzip -d ";
	command += filename;
	command += ".gz"; 
	if(system(command.c_str())){
		// depress the file, but when it fails, log the error and return!
		errFile << url << std::endl;
		return;
	}
	//if(Debug) std::cout << command << std::endl;
	//

	R.getUrls(v);
	mt.lock();
	for(auto x: v){
		if(urlSet.find(x) == urlSet.end()){
			urlSet.insert(x);
			q.push(x);
			runLog << "push " <<x << std::endl;
		}
	}
	mt.unlock();
}


