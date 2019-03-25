#include<iostream>
#include<cstring>
#include<string>
int format_bool(std::string &url)
{
	std::string word[7]={".png",".jpg",".css",".doc",".ppt",".xls",".mp4"};
	for(int i = 0;i<7;i++)
	{
		if(url.find(word[i])!=std::string::npos)
			return 0;
	}
	return 1;
}
