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
#include"unistd.h"
#include"crawler.h"
#include"parser.h"
//#include"thulac.h"
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
		cout<<url<<endl;
	}
	fin.close();
	ifstream gin("faileddata");
	//cout<<'1';
	string failed_url;
	getline(gin,failed_url);
	while(getline(gin,failed_url))
	{
		failed_crawler.push(failed_url);
		failed_ans++;
	}
	gin.close();
	ifstream hin("data");
	string succ_url;
	int n=ans+failed_ans;
	str_set.insert(" "); 
	getline(hin,succ_url);
	cmd_str=succ_url;
	getline(hin,succ_url);
	first_url=succ_url;
	str_set.insert(first_url);
	getline(hin,succ_url);
	int i=1;
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
	if(access("home",0)==-1)
		system("mkdir home");
	cmd=strstr(origin_url.c_str()," ");
	if(cmd)
	{
		size_t space=origin_url.find_first_of(' ');
		first_url=origin_url.substr(0,space);
		cmd_str=origin_url.substr(space+1);
	}
	else
	{
		first_url=origin_url;
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
	//ofstream iout("text.txt");
	//iout.close();
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
		wget_str="wget \""+str_queue.front()+"\" --output-document=./home/"+to_string(ans+1)+".html "+cmd_str;
		bool a=system(wget_str.c_str());
		if(a)													//判断网页是否爬取成功
		{
			failed_ans++;
			failed_crawler.push(str_queue.front());
			ofstream ffout("faileddata",ios::app);
			ffout<<str_queue.front()<<endl;
			str_queue.pop();
			ffout.close();
		}
		else
		{
			ans++;
			cout<<ans<<' '<<str_queue.front()<<endl;
			ofstream fout("result.txt",ios::app);
			fout<<ans<<' '<<str_queue.front()<<endl;
			
			//sprintf(str,"./home/%d.html",ans);
			addr_str="./home/"+to_string(ans)+".html";
			ifstream cur_url (addr_str.c_str());
			parser Parser(&cur_url);							//利用HTMLparser解析url
			Parser.parse_url();
			unite_url(Parser);		
			Parser.parse_text();
			unite_text(Parser,str_queue.front());
			str_queue.pop();							
			fout.close();
		}
	}
	finish=clock();
	cout<<"本次共爬取网页"<<ans<<"个,用时"<<(finish-start)/CLOCKS_PER_SEC<<"秒。具体信息及异常情况见日志"<<endl;
	ofstream fout("result.txt",ios::app);
	fout<<"finished"<<endl;
	fout<<"本次共爬取网页"<<ans<<"个,用时"<<(finish-start)/CLOCKS_PER_SEC<<"秒。"<<endl;
	fout<<"爬取失败的网页共"<<failed_ans<<"个："<<endl;
	for(int i=1;i<=failed_ans;i++)
	{
		fout<<i<<' '<<failed_crawler.front()<<endl;
		failed_crawler.pop();
	}
	fout.close();
}
void crawler::unite_text(parser& Parser,string& url)
{
	string addr_str="text.txt";
	ofstream fout(addr_str,ios::app);
	fout<<url<<endl;
	while(!Parser.get_text.empty())
	{
		fout<<Parser.get_text.front()<<' ';
		Parser.get_text.pop();
	}
	fout<<endl;
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
			ofstream ffout("data",ios::app);
			ffout<<full_url<<endl;
			ffout.close();
		}
		Parser.get_url.pop();
    }
}
bool crawler::url_bool(string &url)
{
	if(url.find(first_url.c_str())!=string::npos)
		return true;
	/*if(url.find("http://econ")==string::npos&&url.find(".html")!=string::npos)
		return 1; */
	if(url.find("http://")==string::npos&&url.find("https://")==string::npos&&(url[0]<48||url[0]>57))
		return true;
	return false;
}
bool crawler::format_bool(string &url)
{
	string word[]={".js","javascript",".css",".asp",".xml",".mso",".thmx",".shtml","@",".png",".jpeg",".JPEG",".JPG",".jpg",".gif",".doc",".rar",".ppt",".xls",".pdf",".PDF",".mp4","last"};
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
	//string a=first_url.substr(0,first_url.size());	
	string full_url=" ";
	if(mini_url.find(first_url.c_str())!=string::npos)
  		full_url=mini_url;
  	else
	{
  		if(mini_url[0]=='/')
  			full_url=first_url+mini_url;
  		else
  			full_url=first_url+"/"+mini_url;
	} 
	//cout<<full_url;
	return full_url;
}
