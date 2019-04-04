#include<iostream>
#include<cstring>
#include<string>
std::string minitofull(std::string &mini_url)
{
	std::string full_url;
	if(mini_url.find("http://info")!=std::string::npos)
  		full_url=mini_url;
  	else
	{
  		if(mini_url[0]=='/')
  			full_url="http://info.ruc.edu.cn"+mini_url;
  		else
  			full_url="http://info.ruc.edu.cn/"+mini_url;
	} 
	return full_url;
}
