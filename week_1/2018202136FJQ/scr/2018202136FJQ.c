#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <regex>
#include <time.h>

using namespace std;
int number = 0;

string root = "info.ruc.edu.cn";

string current_url = "info.ruc.edu.cn";

queue<string> url_to_be_crawled;

set<string> url_already_be_crawled;

void getContent(string url)
{                             
	string command;
	command = "wget -O url_has_been_crawled.txt --tries=1 ";
	command += url;
	system(command.data());
	ifstream fin;
	ofstream fout;
	string  file,file_part;
	int length = 0,len = 0,len1 = 0,location_first = 0,location_end = 0;
	string url_format1 = "<a href=\"";
	string url_format2 = "\"";
	fin.open("url_has_been_crawled.txt");
	fout.open("all_different_urls.txt");
	if(fin.is_open() == false)
	{
		cerr << "Can't open file!\n";
		exit(EXIT_FAILURE);
	}
	while(getline(fin,file_part))
	{
		file += file_part;
	}
	location_first = file.find(url_format1);
	if(location_first == string::npos)
	return;
	else
	{
		while(location_first != string::npos)
		{
			string url_to_be_finded;
			location_end = file.find(url_format2,location_first+9);
			len = location_end-location_first-9;
			url_to_be_finded = file.substr(location_first+9,len);
			if(url_to_be_finded.find("http://info.ruc.edu.cn") != string::npos)
			{
				if(url_already_be_crawled.find(url_to_be_finded) == url_already_be_crawled.end())
				{
					fout << url_to_be_finded << endl;
					url_to_be_crawled.push(url_to_be_finded);
				}
			}
			if(url_to_be_finded.find("http://") == string::npos)
                        {
				int loc = url_to_be_finded.find("/");
				string url_to_be_finded_part;
				if(loc == 0)
				url_to_be_finded = "http://info.ruc.edu.cn"+url_to_be_finded;
				else if(loc == string::npos)
				url_to_be_finded = "http://info.ruc.edu.cn/"+url_to_be_finded;
				else
				{
                                        url_to_be_finded_part = url_to_be_finded.substr(0,loc);
					url_to_be_finded = "http://info.ruc.edu.cn/"+url_to_be_finded_part;
				}
                                if(url_already_be_crawled.find(url_to_be_finded) == url_already_be_crawled.end())
                                {
                                        fout << url_to_be_finded << endl;
                                        url_to_be_crawled.push(url_to_be_finded);
                                }
                        }
			location_first = file.find(url_format1,location_first+1);
			url_to_be_finded.erase(0,200);
		}
	}
	return;
}
void deep_search(void)
{
	while(!url_to_be_crawled.empty())
	{
		current_url = url_to_be_crawled.front();
		url_to_be_crawled.pop();
		if(url_already_be_crawled.find(current_url) == url_already_be_crawled.end())
		{
			number++;
			getContent(current_url);
		}
		url_already_be_crawled.insert(current_url);
	}
	return ;

}
int main()
{
	int time_beg = clock(),time_end,time;
	url_to_be_crawled.push(root);
	deep_search();
	time_end = clock();
	time = time_end-time_beg;
        cout << "Time :"<< time << endl;
        cout << "Number :"<< number << endl;
	return 0;
}

