#include"crawler.h"
#include"total.h"
#include<iostream>
int main ()
{
	std::string first_url;
	std::cout<<"please enter the first URL:"<<std::endl;
	std::cin>>first_url; 
	crawler Crawler(first_url);
	Crawler.bfs();
    return 0;
}
