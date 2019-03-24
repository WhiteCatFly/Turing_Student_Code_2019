// regex_search example
#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<ios>
#include<set>
#include<queue>
#include<stdlib.h>

std::set <std::string> str_set;
std::pair<std::set<std::string>::iterator,bool>ret;
std::queue <std::string> str_queue; 
std::string word[13]={".png",".jpg",".png",".bmp",".css",".doc",".docx",".ppt",".pptx",".xls",".xlsx",".mp4",".avi"};
//int url_num=0;
void BFS ()
{
	int ans = 0;
	while(!str_queue.empty())
	{
		char wget_str[500];
		char str[500];
		ans++;
		//char num[500];
		const char* str_que=str_queue.front().data();
		sprintf(wget_str,"wget %s -O ./home1/%d.html -T 20 -q",str_que,ans);
		//wget_str="wget "+str_queue.front()+" -O ./home/"+num+".html";
		system(wget_str);
		std::cout<<ans<<' '<<str_queue.front()<<std::endl;
		str_queue.pop();
		sprintf(str,"./home1/%d.html",ans);
		std::ifstream cur_url (str);
    	std::string col;
    	std::string full_url;
   		std::string mini_url;
		while(getline(cur_url,col))
    	{
			std::regex url_regex("(%*href=\")([^\"]*)");
	   		std::smatch res;
  			while(std::regex_search(col,res,url_regex))
    		{
    			full_url=""; 
    			mini_url=res[2].str();
				int Bool=1;
				for(int i = 0;i<13;i++)
				{
					if(mini_url.find(word[i])!=std::string::npos)
						Bool=0;
				}
    			if(Bool==1&&(mini_url.find("http://info")!=std::string::npos||mini_url.find("http://info")==std::string::npos&&mini_url.find(".html")!=std::string::npos
		  		||mini_url.find(".php")!=std::string::npos))
    			{
  	    			if(mini_url.find("http://info")!=std::string::npos)
  	    				full_url=mini_url;
  		    		else
	  	    		{
  				   		if(mini_url[0]=='/')
  				    		full_url="http://info.ruc.edu.cn"+mini_url;
  				    	else
  					    	full_url="http://info.ruc.edu.cn/"+mini_url;
		    		}  
	    		}
	    		ret=str_set.insert(full_url);
	    		if(ret.second!=false)
		    		str_queue.push(full_url);
  				//std::cout<<full_url<<std::endl;
  	    		col=res.suffix();
    		}
    	}  	
	}
	std::cout<<ans<<std::endl;
}
int main ()
{
    system ("wget info.ruc.edu.cn -O ./home1/1.html -T 20 -q");
    /*std::ifstream cur_url ("./home1/1.html");
    std::string col;
    std::string full_url;
    std::string mini_url;
    while(getline(cur_url,col))
    {
		std::regex url_regex("(%*href=\")([^\"]*)");
   		std::smatch res;
  		while(std::regex_search(col,res,url_regex))
    	{
    		full_url="";
    		mini_url=res[2].str();
		int Bool=1;
		for(int i = 0;i<13;i++)
		{
			if(mini_url.find(word[i])!=std::string::npos)
				Bool=0;
		}
    		if(Bool==1&&(mini_url.find("http://info")!=std::string::npos||mini_url.find("http://info")==std::string::npos&&mini_url.find(".html")!=std::string::npos
	  		||mini_url.find(".php")!=std::string::npos))
    		{
  	    		if(mini_url.find("http://info")!=std::string::npos)
  	    			full_url=mini_url;
  		    	else
  	    		{
  			   		if(mini_url[0]=='/')
  			    		full_url="http://info.ruc.edu.cn"+mini_url;
  			    	else
  				    	full_url="http://info.ruc.edu.cn/"+mini_url;
		    	}  
	    	}
	    	ret=str_set.insert(full_url);
	    	if(ret.second!=false)
				str_queue.push(full_url);
  			//std::cout<<full_url<<std::endl;
  	    	col=res.suffix();
    	}
    }  */
    str_set.insert("http://info.ruc.edu.cn");
    str_queue.push("http://info.ruc.edu.cn");
    BFS();
    return 0;
}
