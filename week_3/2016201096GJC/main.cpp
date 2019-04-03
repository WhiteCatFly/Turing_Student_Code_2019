#include "html.h"
#include "CmdOrder.h"
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <fstream>

vector<string>Html::_history_url_set;
vector<string>Html::_single_url_set;

int main(){
	string starturl = "http://econ.ruc.edu.cn";
    DownloadStartHtml(starturl);
	int road = 0;
	int StartSize = 0;
	int EndSize = 1;
	while (StartSize != EndSize){
    	StartSize = Html::_history_url_set.size();
		MakeDir(road);
		string ordercount = CountFiles(road);
		int number = stoi( GetCmdResult(ordercount) );
		for (int i = 0; i < number; ++i){
			Html html(i, road, starturl);
			html.HtmlName();
			html.HtmlParse("href\s*=\s*(?:\"([^\"]*)\"|\'([^\']*)\'|([^\"\'>\s]+))");
		}
		while(!Html::_single_url_set.empty()){
			int j = Html::_single_url_set.size() - 1;
			string url = Html::_single_url_set[j];
			string order;
            string strroadadd = std::to_string(road + 1);
			order = downloadHtml(strroadadd, j, url);
			std::cout << order << std::endl;
			std::ofstream urlsets;
			urlsets.open("urlset.txt", std::ios::app | std::ios::out);
			urlsets << order << std::endl;
			urlsets.close();
			system(order.c_str());
			Html::_single_url_set.pop_back();
		}
		EndSize = Html::_history_url_set.size();
		road += 1;
	}
	Html last;
	last.ShowCount();
	return 0;
}
