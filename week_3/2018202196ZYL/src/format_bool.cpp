#include<iostream>
#include<cstring>
#include<string>
int format_bool(std::string &url)
{
	std::string word[]={".png",".jpg",".css",".doc",".rar",".ppt",".xls","pdf",".mp4","last"};
	int i=0;
	while(word[i]!="last")
	{
		if(url.find(word[i])!=std::string::npos)
			return 0;
		i++;
	}
	return 1;
}
