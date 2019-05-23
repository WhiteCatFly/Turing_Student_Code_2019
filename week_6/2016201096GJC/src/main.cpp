#include "html.h"
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <fstream>
#include "easylogging++.h"
#include <typeinfo>
#include <exception>

INITIALIZE_EASYLOGGINGPP

vector<string>Html::history_url_set_;
vector<string>Html::single_url_set_;

int main(int argc, char*argv[]){
	LOG(INFO) << "My first info log using default logger";
	string starturl = argv[1];
    DownloadStartHtml(starturl);
	int road = 0;
	int StartSize = 0;
	int EndSize = 1;
	while (StartSize != EndSize){
    	StartSize = Html::history_url_set_.size();
		MakeDir(road+1);
		string ordercount = CountFiles(road);
		//std::cout << "ordercount " << ordercount << std::endl;
		int number = stoi( GetCmdResult(ordercount) );
		try{

			for (int i = 0; i < number; ++i){
				Html html(i, road, starturl);
				html.HtmlName();
				html.HtmlParse();
			}
		}catch(std::exception &e){
			std::cerr << "Caught: " << e.what() << std::endl;
			std::cerr << "Type: " << typeid(e).name() << std::endl;
		}
		try{
			while(!Html::single_url_set_.empty()){
				int j = Html::single_url_set_.size() - 1;
				string url = Html::single_url_set_[j];
				string order;
				string strroadadd = std::to_string(road + 1);
				order = DownloadHtml(strroadadd, j, url);
				std::cout << order << std::endl;
				std::vector<string> urls;
				string tmp;
				std::ifstream urlsets_read;
				urlsets_read.open("urlset.txt");
				while(getline(urlsets_read,tmp)){
					urls.push_back(tmp);
				}
				urlsets_read.close();
				std::vector<string>::iterator it = find(urls.begin(), urls.end(), url);
				if (it == urls.end()){
					system(order.c_str());
				}
				std::ofstream urlsets;
				urlsets.open("urlset.txt", std::ios::app | std::ios::out);
				urlsets << url << std::endl;
				urlsets.close();
				Html::single_url_set_.pop_back();
			}
		}catch(std::exception &e){
			std::cerr << "Caught: " << e.what() << std::endl;
			std::cerr << "Type: " << typeid(e).name() << std::endl;
		}
		EndSize = Html::history_url_set_.size();
		road += 1;
	}
	Html last;
	last.ShowCount();
	return 0;
}
