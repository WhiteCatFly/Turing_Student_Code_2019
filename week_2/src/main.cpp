#include <set>
#include <queue>
#include <regex>
#include <mutex>
#include <thread>
#include <iostream>
#include "spiderString.h"
#include "spiderFile.h"
#include "spiderWeb.h"

void bfs();
std::string getCurrent();
void crawl(std::string url);

std::mutex mt;
std::queue<std::string> q;
std::set<std::string> urlSet; //visied urls


int main(){
	std::cout << "Start spider\n";
	q.push("http://info.ruc.edu.cn/");
	bfs();
	return 0;
}

std::string getCurrent(){
	std::string res = "";
	if(q.empty()) return res;
	res = q.front();
	q.pop();
	return res;
}


void crawl(std::string url){
	std::string text;
	std::string filename;
	std::string matchUrl;
	const std::string pattern = "href=\"([^\"]+)\"";


	if(url.length() < 23) return;
	filename = url.length() == 23 ? "index.html" : url.substr(23); 
	strReplace(filename, '/', '_');

	getUrl(filename, url);
	text = load2text(filename);
	if(!text.length()) return;
	std::regex word_regex(pattern);
    auto words_begin = 
    std::sregex_iterator(text.begin(), text.end(), word_regex);
    auto words_end = std::sregex_iterator();

    mt.lock();
    for(std::sregex_iterator i = words_begin; i != words_end; ++i){
    	std::smatch match = *i;
    	matchUrl = parseUrl(url, match.str(1)); // smath.str(n) return the nth group; 0 presents all of them;
		if(urlSet.find(matchUrl) != urlSet.end()) continue;
		std::cout << "mathchUrl is " << matchUrl << "\n";
		urlSet.insert(matchUrl);
		q.push(matchUrl);
	}
	mt.unlock();
}

void bfs(){
	using std::string;
	using std::cout;
	std::thread *T;
	while(!q.empty()){
		T = new std::thread[20];
		for(int i = 0; i < 20; i++){
			T[i] = std::thread {crawl, getCurrent()};
		}
		for(int i = 0; i < 20; i++){
			T[i].join();
		}
		delete [] T;
	}
}