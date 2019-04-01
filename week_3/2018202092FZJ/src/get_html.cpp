#include "Web_Crawler.h"
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

void Web_Crawler::get_html(){
	std::ofstream fout("/home/kevin/RUC_Turing_Homework/url_list", std::ios::app);
	fout << current_url << std::endl;
	fout.close();
	char operation[1000], number_html[1000];
	sprintf(number_html, "%d.html", total_website);
	sprintf(operation, "wget --tries=3 \"%s\" -O %s", current_url.c_str(), number_html);
	int res = system(operation);
	
	exit_status(res);
	
	FILE* read_html = fopen(number_html, "r");
	char temp = fgetc(read_html);
	while (temp != EOF){
		current_html.push_back(temp);
		temp = fgetc(read_html);
	}
	
	fclose(read_html);
}
