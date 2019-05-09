#include<iostream>
#include<cstring>
#include<string>
#include<regex>
#include<fstream>
#include<sstream>
#include<ios>
#include<set>
#include<queue>
#include<ctime>
#include"crawler.h"
#include"parser.h"
using namespace std;
crawler::crawler(bool a):reload(a)								//读入断点之前的数据
{
	ans=0;
	failed_ans=0;
	ifstream fin("result.txt");
	string url;
	while(getline(fin,url))
	{
		ans++;
		cout<<ans<<' '<<url<<endl;
	}
	fin.close();
	ifstream gin("faileddata");
	string failed_url;
	while(getline(gin,failed_url))
	{
		failed_crawler.push(failed_url);
		failed_ans++;
	}
	gin.close();
	ifstream hin("data");
	string succ_url;
	int n=ans+failed_ans;
	int i=0;
	str_set.insert(" "); 
	getline(hin,succ_url);
	cmd_str=succ_url;
	while (getline(hin,succ_url))
	{
		i++;
		if(i<=n)
			str_set.insert(succ_url);
		else
		{
			str_set.insert(succ_url);
			str_queue.push(succ_url);
		}
	}
	hin.close();
}
crawler::crawler(string origin_url,bool a):reload(a)
{
	cmd=strstr(origin_url.c_str()," ");
	if(cmd)
	{
		size_t space=origin_url.find_first_of(' ');
		first_url="http://"+origin_url.substr(0,space);
		cmd_str=origin_url.substr(space+1);
	}
	else
	{
		first_url="http://"+origin_url;
		cmd_str="-t 3 -T 15 -q";
	}
	str_set.insert(" "); 
   	str_set.insert(first_url.c_str());
    str_queue.push(first_url.c_str());
	ans=0;
	failed_ans=0;	
	ofstream fout("result.txt");								//把三个文件清空
	fout.close();
	ofstream gout("faileddata");
	gout.close();
	ofstream hout("data");
	hout<<cmd_str<<endl<<first_url<<endl;
	hout.close();
}
void crawler::bfs()
{
	clock_t start,finish;
	start=clock();
	while(!str_queue.empty())
	{
		
		//ans++;
		//const char* str_que=str_queue.front().data();
		//sprintf(wget_str,"wget %s -O ./home/%d.html -T 20 -q",str_que,ans);
		wget_str="wget \""+str_queue.front()+"\" --output-document="+to_string(ans)+".html "+cmd_str;
		bool a=system(wget_str.c_str());
		if(a)													//判断网页是否爬取成功
		{
			failed_ans++;
			failed_crawler.push(str_queue.front());
			ofstream ffout("faileddata",ios_base::ate);
			ffout<<str_queue.front()<<endl;
			str_queue.pop();
			ffout.close();
		}
		else
		{
			ans++;
			cout<<ans<<' '<<str_queue.front()<<endl;
			ofstream fout("result.txt",ios_base::ate);
			fout<<ans<<' '<<str_queue.front()<<endl;
			str_queue.pop();
			//sprintf(str,"./home/%d.html",ans);
			addr_str=to_string(ans)+".html";
			ifstream cur_url (addr_str.c_str());
			parser Parser(&cur_url);							//利用HTMLparser解析url
			Parser.parse_url();
			unite_url(Parser);									
			fout.close();
		}
	}
	finish=clock();
	cout<<"本次共爬取网页"<<ans<<"个,用时"<<(finish-start)/CLOCKS_PER_SEC<<"秒。具体异常情况见日志"<<endl;
	ofstream fout("result.txt",ios_base::ate);
	fout<<"本次共爬取网页"<<ans<<"个,用时"<<(finish-start)/CLOCKS_PER_SEC<<"秒。"<<endl;
	fout<<"爬取失败的网页共"<<failed_ans<<"个："<<endl;
	for(int i=1;i<=failed_ans;i++)
	{
		fout<<i<<' '<<failed_crawler.front()<<endl;
		failed_crawler.pop();
	}
	fout.close();
}
void crawler::unite_url(parser& Parser)							//分析url是否符合爬取要求
{
    string full_url;
    while(!Parser.get_url.empty())
    {
        if(format_bool(Parser.get_url.front())&&url_bool(Parser.get_url.front()))
		    full_url=minitofull(Parser.get_url.front());
	    ret=str_set.insert(full_url);
	    if(ret.second!=false)
		{
		    str_queue.push(full_url);
			ofstream ffout("data",ios_base::ate);
			ffout<<full_url<<endl;
			ffout.close();
		}
		Parser.get_url.pop();
    }
}
bool crawler::url_bool(string &url)
{
	if(url.find("http://")!=string::npos&&url.find(first_url.c_str())!=string::npos)
		return true;
	/*if(url.find("http://econ")==string::npos&&url.find(".html")!=string::npos)
		return 1; */
	if(url.find(url.find("http://")==string::npos))
		return true;
	return false;
}
bool crawler::format_bool(string &url)
{
	string word[]={"@",".png",".js","javascript",".jpg",".css",".doc",".rar",".ppt",".xls","pdf",".mp4","last"};
	int i=0;
	while(word[i]!="last")
	{
		if(url.find(word[i])!=string::npos)
			return false;
		i++;
	}
	return true;
}
string crawler::minitofull(string &mini_url)
{
	string full_url=" ";
	if(mini_url.find(first_url.c_str())!=string::npos)
  		full_url=mini_url;
  	else
	{
  		if(mini_url[0]=='/')
  			full_url="http://"+first_url+mini_url;
  		else
  			full_url="http://"+first_url+"/"+mini_url;
	} 
	return full_url;
}
