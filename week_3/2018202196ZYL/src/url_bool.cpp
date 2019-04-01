#include<iostream>
#include<cstring>
#include<string>
int url_bool(std::string &url)
{
	if(url.find("http://econ")!=std::string::npos)
		return 1;
	/*if(url.find("http://econ")==std::string::npos&&url.find(".html")!=std::string::npos)
		return 1; */
	if(url.find(".php")!=std::string::npos&&url.find("http://")==std::string::npos)
		return 1;
	return 0;
}
