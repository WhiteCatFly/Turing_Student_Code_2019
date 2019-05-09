#include"crawler.h"
#include"parser.h"
#include<iostream>
int main ()
{
	char a;
	std::string origin_url;
	std::cout<<"是否继续上次的任务？(y/n)"<<std::endl;
	std::cin>>a;
	while(a!='y'&&a!='n')
	{
		std::cout<<"输入错误，请重新输入。"<<std::endl;
		std::cin>>a;
	}
	if(a=='y')
	{
		ifstream fin("result.txt");
		bool b=fin.is_open();
		fin.close();
		if(b)
			crawler Crawler(true);
		else
		{
			std::cout<<"上次无任务，读取失败。"<<std::endl;
			return 0;
		}
	}
	else
	{		
		std::cout<<"请输入一个完整的URL (以及命令(默认为-t 3 -T 15 -q)):"<<std::endl<<"http://";
		std::cin>>origin_url; 
		crawler Crawler(origin_url,false);
		Crawler.bfs();
	}
    return 0;
}
