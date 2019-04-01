#include "html.h"
#include "CmdOrder.h"
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

vector<string>Html::_history_url_set;
vector<string>Html::_single_url_set;
int Html::count = 1;

int main(){
	int StartSize = 0;
	int EndSize = 1;
    int road = 0;
	string starturl = "http://econ.ruc.edu.cn";
	while(StartSize != EndSize){
		StartSize = Html::_history_url_set.size();
		int number;
		MakeDir(road);
		string ordercount = CountFiles(road);
		number = stoi(getCmdResult(ordercount));
		for (int i=0; i<number; ++i){
			Html html(i, road);
			html.HtmlName();
			html.HtmlParse("a href=\"(.*?)\"");
			html.HtmlParse("a target=\"_blank\" href=\"(.*?)\"");
		}
		while(!Html::_single_url_set.empty()){
			int j = Html::_single_url_set.size()-1;
			string url = Html::_single_url_set[j];
			string order;
            string strroadadd = std::to_string(road + 1);
			order = downloadHtml(strroadadd, j, url);
			system(order.c_str());
			Html::_single_url_set.pop_back();
			Html::count = Html::count + 1;
		}
		EndSize = Html::_history_url_set.size();
		road += 1;
	}
	Html last;
	last.ShowCount();
	return 0;
}
