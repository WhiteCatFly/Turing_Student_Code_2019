#include "web_crawler.h"
#include <fstream>
#include <cstdio>
#include <string>

void get_html(const std::string &present_url, std::string &present_html,const int total){
	std::ofstream fout("/home/kevin/RUC_Turing_Homework/url_list", std::ios::app);
	fout << present_url << std::endl;
	fout.close();
	char operation[1000], number_html[1000]; 
	sprintf(number_html, "%d.html", total);
	sprintf(operation, "wget \"%s\" -O %s", present_url.c_str(), number_html);
	system(operation);
	FILE* read_html = fopen(number_html, "r");
	char temp = fgetc(read_html);
	while (temp != EOF){
		present_html.push_back(temp);
		temp = fgetc(read_html);
	}
	fclose(read_html);
}