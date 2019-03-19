#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <set>
#include <queue>

using namespace std;

const string forbidden_words[200]={".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", ".js", ".7z", ".rar", ".zip", "end"};

void get_html(string &present_url, string &present_html, int &total){
	ofstream fout("/home/kevin/RUC_Turing_Homework/url_list", ios::app);
	fout << present_url << endl;
	fout.close();
	char operation[1000], number_html[1000]; 
	sprintf(number_html, "%d.html", total++);
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

void find_next_url(string &present_url, string &present_html, queue<string> &url_queue, set<string> &url_set){
	int url_begin = present_html.find("href=");
	while (url_begin != -1){
		int url_end = present_html.find(present_html[url_begin + 5] == '\"' ? '\"' : '\'', url_begin + 6);
		string new_url = present_html.substr(url_begin + 6, url_end - url_begin - 6);
		url_begin = present_html.find("href=", url_end);
		if (new_url.find("info.ruc") != new_url.npos){
			if (new_url.find("http:") != new_url.npos)
				new_url.erase(0,7);
		}
		else if (new_url.find("http") == new_url.npos){
				new_url = present_url.substr(0, present_url.find_last_of('/') + 1) + new_url;
			}
		if (new_url.find("info.ruc") != new_url.npos){
			int flag = 0;
			for (int i = 0; forbidden_words[i] != "end"; ++i){
				if (new_url.find(forbidden_words[i]) != new_url.npos){
					flag = 1;
					break;
				}
			}
			if (flag)
				continue;
			if (!url_set.count(new_url)){
				url_set.insert(new_url);
				url_queue.push(new_url);
			}
		}
	}
}

void web_crawler(){
	queue<string> url_queue;
	while (!url_queue.empty())
		url_queue.pop();
	set<string> url_set;
	url_set.clear();
	
	int total = 0;
	string origin = "info.ruc.edu.cn/";
	url_queue.push(origin);
	url_set.insert(origin);
	while (!url_queue.empty()){
		string present_url = url_queue.front(), present_html = "";
		url_queue.pop();
		get_html(present_url, present_html, total);
		find_next_url(present_url, present_html, url_queue, url_set);
	}
	printf("There are %d websites in http://info.ruc.edu.cn.\n", total);	
}

int main(){
	clock_t now = clock();
	web_crawler();
	int times = (clock() - now) / 1000;
	cout << times / 60"m"times % 60 << endl;
	return 0;
}