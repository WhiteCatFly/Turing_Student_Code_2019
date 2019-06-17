#include"crawler.h"
#include"parser.h"
#include"search.h"
//#include<thulac.h>
#include"THULAC_lite_c++_v1/include/thulac.h"
#include<iostream>
using namespace std;
/*void Thulac(string& input,string& output)
{
	THULAC lac;
    THULAC_result result;
    string raw;   
    lac.init("models/",NULL,true,false,false);
	ifstream gin;
	gin.open(input,ios::in);
	gin.clear();
	gin.seekg(0);
	ofstream gout(output);
	//if(gin) cout<<"1"<<endl;
	while(getline(gin,raw))
    {
            //cout<<raw<<endl;
        lac.cut(raw,result);
            //cout<<k<<endl;
        for(int j = 0; j < result.size() - 1; j++) 
        {
            if(j!=0) gout<<" ";
            gout<<result[j].first;
			//cout<<result[j].first;
        }
		cout<<endl;
    }
	gin.close();
    gout.close();
}
void apart()
{
    //cout<<"1";
    int i=1;
    ifstream fin("result.txt");
    string url;
    string loc,locout;
    //cout<<"2";
    getline(fin,url);    
    //cout<<"3";
     
    while(url!="finished")
    {
        
        loc="./home/"+to_string(i)+".txt";
        //ifstream gin(loc);
        locout="./home/"+to_string(i);
        //ofstream gout(locout);
        //cin.rdbuf(gin.rdbuf);
        //string str="";
        //cout.rdbuf(gout.rdbuf);   
        //cout<<endl;
        //gout<<endl;
		
		
		//string aa;
		//gin>>aa;
		//cout<<aa<<endl;
		Thulac(loc,locout);
        
        if(i%100==0)
            cout<<i<<endl;
        i++;
        getline(fin,url);
    }
    fin.close();
}*/
void apart()
{
	//string loc="text.txt";
	THULAC lac;
    THULAC_result result;
	string raw="";
	//cout<<"1";
	ifstream fin("text.txt");
	
	ofstream fout("text_apart");
	while(getline(fin,raw))
	{
		fout<<raw<<endl;
		getline(fin,raw);
		lac.cut(raw, result);
		for(int j = 0; j < result.size() - 1; j++) 
        {
            if(j!=0) fout<<" ";
            fout<<result[j].first;
			//cout<<result[j].first;
        }
		fout<<endl;
	}
	fin.close();
	fout.close();
}
/*string word_apart(string& words)
{
	//cout<<"d";
	THULAC lac;
    THULAC_result result;
	//cout<<"q";
	string raw="";
	lac.cut(words,result);
	for(int j = 0; j < result.size() - 1; j++) 
    {
        if(j!=0) raw=raw+" ";
        raw=raw+result[j].first;
    }
	return raw;
}*/
int main ()
{
	char a;
	string origin_url;
	cout<<"是否继续上次的任务？(y/n)"<<endl;
	cin>>a;
	while(a!='y'&&a!='n')
	{
		cout<<"输入错误，请重新输入。"<<endl;
		cin>>a;
	}
	if(a=='y')
	{
		ifstream fin("result.txt");
		bool b=fin.is_open();
		fin.close();
		if(b)
		{
			crawler Crawler(true);
			Crawler.bfs();
		}
		else
		{
			cout<<"上次无任务，读取失败。"<<endl;
			return 0;
		}
	}
	else
	{	
		cout<<"是否重新开始爬取？（y/n）"<<endl;
		char c;
		cin>>c;
		while(c!='y'&&c!='n')
		{
			cout<<"输入错误，请重新输入。"<<endl;
			cin>>c;
		}
		if(c=='y')
		{
			cout<<"请输入一个完整的URL(如http://info.ruc.edu.cn) (以及命令(可选，默认为-t 3 -T 15 -q)):"<<endl;
			cin>>origin_url; 
			crawler Crawler(origin_url,false);
			Crawler.bfs();
		}
	}
//	THULAC aaa;
	cout<<"是否开始查找？（y/n）"<<endl;
	cin>>a;
	while(a!='y'&&a!='n')
	{
		cout<<"输入错误，请重新输入。"<<endl;
		cin>>a;
	}
	if(a=='y')
	{
		cout<<"是否对已有文件进行分词？（y/n）"<<endl;
		char c;
		cin>>c;
		while(c!='y'&&c!='n')
		{
			cout<<"输入错误，请重新输入。"<<endl;
			cin>>c;
		}
		if(c=='y')
			apart();
		cout<<"请输入需要查找的内容："<<endl;
		string words;
		cin>>words;
		//word_apart(words);
		//cout<<words;
		Search SEARCH;
		SEARCH.word_apart(words);
		SEARCH.find_times();
		SEARCH.find_frequency();
	}
    return 0;
}
