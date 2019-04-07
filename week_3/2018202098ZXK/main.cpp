#include <set>
#include <queue>
#include <mutex>
#include <thread>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "Request.h"

void bfs(int t_num = 20, int sleep_time = 0); // t_num stands for the number of threads
std::string getCurrent(); // get the current url in queue
void crawl(std::string url); // given an url, crawl it and push its urls into queue

std::mutex mt; // lock
std::queue<std::string> q; // queue
std::set<std::string> urlSet; //visied urls
std::ofstream errFile;// errFile << err_url



int main(int argc, char const *argv[])
{
	using std::cout;
	using std::endl;

	Config conf;//configs

	if(argc > 1){
		cout << "Using given config" << endl;
		conf = iniConfig(argv[1]);
	}
	else{
		cout << "Using default config" << endl;
		conf = iniConfig("default.ini");
	}
	
	if(!conf.loaded){
		cout << "can not load config file, please check again" << endl;
		return 1;
	}
	//set errFile
	errFile.open(conf.err_file);
	//set Request
	Request::set_config(conf);
	//start bfs
	q.push(conf.BASE);
	bfs(conf.thread_num, conf.sleep_time);
	//close
	errFile.close();
	return 0;
}


void bfs(int t_num, int sleep_time){
	using std::string;
	using std::cout;
	std::thread *T;
	while(!q.empty()){
		T = new std::thread[t_num];
		for(int i = 0; i < t_num; i++){
			T[i] = std::thread {crawl, getCurrent()};
			usleep(sleep_time);
		}
		for(int i = 0; i < t_num; i++){
			T[i].join();
		}
		delete [] T;
	}
}

std::string getCurrent(){
	std::string res = "";
	if(q.empty()) return res;
	res = q.front();
	q.pop();
	return res;
}


void crawl(std::string url){
	if(!url.length()) return;//empty string, do nothing
	Request R(url);
	std::vector<std::string> v;
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
		}
	}
	mt.unlock();
}