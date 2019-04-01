#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "getCmdResult.h"
#include "htmlParse.h"
#include "cmdOrder.h"
int main(){
	std::string starturl = "http://info.ruc.edu.cn";
	std::string downloadstartorder = downloadurllink(starturl);
	downloadstartorder = downloadstartorder.append("0");
	system(downloadstartorder.c_str());
	std::vector<std::string> history_url_set;
	for(int m=0; m<100; ++m){
	    int road, number;
		std::vector<std::string> single_url_set;
		road = m;
		std::string ordercount = countFiles(road);
	    number = stoi(getCmdResult(ordercount));	
		for (int i=0; i<number; ++i){
			std::string htmlname;
			htmlname = htmlName(i, road);
            htmlParse(htmlname, single_url_set, history_url_set);
		}

		std::string strroadadd = mkDir(road);
        system(strroadadd.c_str());
		while(!single_url_set.empty()){
			int j = single_url_set.size()-1;
			std::string url = single_url_set[j];
			std::string order;
			order = downloadHtml(strroadadd, j, url);
			system(order.c_str());
			single_url_set.pop_back();
		}
	}
	return 0;
}
