#ifndef SPIDER_H
#define SPIDER_H
#include <set>
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "Request.h"
#include "Attribute.h"
#include "HTMLParser.h"

using std::string;


class Spider
{
protected:
	std::queue<std::string> q; // queue
	std::mutex              mt; // lock
	std::set<std::string>   urlSet; //visied urls
	std::ofstream runLog;//keep the push and pop of the queue
	Attribute     Config; //keep some configures.
	std::ofstream errFile;// errFile << err_url
	
public:
	Spider() = default;
	Spider(const Attribute& config);
	void run();
	void load();
	string getFront(); //get the first item of the queue, if not exists, return empty string
	virtual void crawlSingle(string url);//crawl a single page and update new links to the queue.
	~Spider() = default;
};
inline void threadWrapper(Spider* s, std::thread* t);

class SSpider: public Spider
{
private:
	bool gziped; //如果采用gzip格式传输，可以大大加快传播速度，同时也需要对Request的命令进行修改,所以设为友元类。
	void addHeader(const string& key, const string& val);
	void addCookies(const string& cookie_file);
	std::map<string, string> creatHeaders(const string& header_file);  //
public:
	SSpider(const Attribute& config, const string& headers = "", const string& cookie = "" ); // you can use headers, cookies to cheat the server
	virtual void crawlSingle(string url);//由于可能采用gzip命令,需要对此进行修改
	~SSpider() = default;
};


#endif