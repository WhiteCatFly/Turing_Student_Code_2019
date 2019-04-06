#ifndef CRAWLER_H
#define CRAWLER_H

#include<queue>
#include<set>
#include<string>
class crawler
{
	private:
		std::set <std::string> str_set;
		std::pair<std::set<std::string>::iterator,bool>ret;
		std::queue <std::string> str_queue; 
		int ans;
	public:
		crawler()
		{
			str_set.insert(" "); 
   			str_set.insert("http://econ.ruc.edu.cn");
    		str_queue.push("http://econ.ruc.edu.cn");
			ans=0;
		}
		crawler(std::string first_url)
		{
			str_set.insert(" "); 
   			str_set.insert(first_url.c_str());
    		str_queue.push(first_url.c_str());
			ans=0;
		}
		void bfs();
		~crawler()
		{
			
		}
};

#endif
