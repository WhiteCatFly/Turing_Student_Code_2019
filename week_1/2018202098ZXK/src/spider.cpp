#include <set>
#include <queue>
#include <regex>
#include <mutex>
#include <cstdio>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


void bfs();
bool inline hasEnding (std::string const &fullString, std::string const &ending);
bool inline hasPrefix(std::string const &fullString, std::string const &prefix); // filter
void crawl(std::string url);
void getUrl(const std::string filename, const std::string url); // download a url and store it by file
std::string getCurrent();
std::string load2text(const std::string filename); //load a file to a string
std::string parseUrl(std::string ori, const std::string url); //convert a url to its absolute url //maybe null

std::mutex mt;
std::queue<std::string> q;
std::set<std::string> urlSet; //visied urls


int main(){
	std::cout << "Start spider\n";
	q.push("http://info.ruc.edu.cn/");
	bfs();
	//std::cout << parseUrl("http://info.ruc.edu.cn/aaads", "bbds");
	return 0;
}

std::string getCurrent(){
	std::string res = "";
	if(q.empty()) return res;
	res = q.front();
	q.pop();
	return res;
}



void bfs(){
	using std::string;
	using std::cout;
	using std::thread;
	const string pattern = "href=\"([^\"]+)\"";
	thread *T;
	while(!q.empty()){
		T = new thread[20];
		for(int i = 0; i < 20; i++){
			T[i] = thread{crawl, getCurrent()};
		}
		for(int i = 0; i < 20; i++){
			T[i].join();
		}
		delete [] T;
	}
}

void crawl(std::string url){
	std::string text;
	std::string filename;
	std::string matchUrl;
	const std::string pattern = "href=\"([^\"]+)\"";


	if(url.length() < 23) return;
	filename = url.length() == 23 ? "index.html" : url.substr(23); 
	std::replace(filename.begin(), filename.end(), '/', '_');

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

 
bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool hasPrefix(std::string const &fullString, std::string const &prefix){
	if(fullString.length() < prefix.length()) return false;
	return fullString.substr(0, prefix.length()) == prefix;
}

std::string parseUrl(std::string ori, const std::string url){
	using std::string;
	string base = "http://info.ruc.edu.cn/";

	//std::cout << "Input to parseUrl " << url << "\n";

	if(hasPrefix(url, "mailto")) return base;
	if(url[0] == ';') return base;

	string suffixs[8] = {".css", ".docx", ".doc", ".xls", ".xlsx", ".pdf", "rar", ".flv"}; // filter by suffix
	for(int i = 0; i < 8; i++){
		if(hasEnding(url, suffixs[i])) return base;
	}
	if(hasPrefix(url, "http")){
		if(hasPrefix(url, "http://info.ruc.edu.cn/")) return url;
		else return base;
	}
	
	if(url[0] == '/') return "http://info.ruc.edu.cn" + url;
	int pos = ori.rfind("/");
	return ori.substr(0, pos+1) + url;
}

std::string load2text(const std::string filename){
	using namespace std;
	ifstream in(filename);
	if(!in) return "";
	ostringstream tmp;
	tmp << in.rdbuf();
	return tmp.str();;
}

void getUrl(const std::string filename, const std::string url){
	using std::string;
	//std::cout << "Downloading " << url << " " << filename << " ";
	string command = "wget --max-redirect=0 --timeout=4 –tries=1 ";
	command += url;
	command += " -O ";
	command += filename;
	std::cout << command << "\n";
	std::system(command.c_str());
	std::cout << "Done\n";
}
