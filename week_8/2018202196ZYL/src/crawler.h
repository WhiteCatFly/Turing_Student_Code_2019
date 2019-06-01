#ifndef CRAWLER_H
#define CRAWLER_H

#include<queue>
#include<set>
#include<string>
#include"parser.h"
class parser;
class crawler
{
	private:
		std::set <std::string> str_set;
		std::pair <std::set <std::string>::iterator,bool> ret;
		std::queue <std::string> str_queue; 
		std::queue <std::string> failed_crawler;
		bool reload;
		int ans;
		int failed_ans;
		bool cmd;
		std::string wget_str;
		std::string addr_str;
		std::string cmd_str;
		std::string first_url;
	public:
		/*crawler()
		{
			str_set.insert(" "); 
   			str_set.insert("http://econ.ruc.edu.cn");
    		str_queue.push("http://econ.ruc.edu.cn");
			ans=0;
		}*/
		crawler(std::string origin_url,bool a);
		crawler(bool a);
		void bfs();
		bool url_bool(std::string &url);
		bool format_bool(std::string &url);
		std::string minitofull(std::string &mini_url);
		~crawler(){};
		void unite_url(parser& Parser);
		void unite_text(parser& Parser,std::string& url);
	friend class parser;
};
#endif
