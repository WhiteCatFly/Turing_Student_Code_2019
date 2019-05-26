#include "crawler.h"
#include "parser.h"

string crawler::get_content()
{
    std::ifstream fin;

    total_urls++;
    if(total_urls % 100 == 0)
    fout << total_urls << " urls crawled"<< std::endl;
    std::cout << total_urls << std::endl;
    
    string content;
    string line;

    string order = "wget --timeout=3 --waitretry=0 --tries=5 \"";
    string opn   = "\" -O ";
    //string file  = "/home/halcyon/index.html";
    
    opn   += storage_path;
    order += current;
     
    order += opn;
    //cout<< order <<endl;
    system (order.c_str());

    fin.open(storage_path);
    //cout<<fin.is_open(opn)<<endl;
    while (getline(fin,line))
        content += line;

    fin.close();

    return content;

}
void crawler::worker(string content)
{
    std::regex  pattern("href=[\'\"]?([\u4e00-\u9fa5a-z0-9_:\\/.\\?=&]+)[\'\"]?",std::regex_constants::icase);
    std::smatch res;
   
    while(regex_search(content,res,pattern))
   {   
       
        //cout<< a[0].str() <<endl;
        int judge_url = my_parser.if_get_urls(res[1].str(),current,root,record_str);
        //cout<< a[1].str() <<endl;
        if(judge_url)
        judge_slash(record_str);

        content = res.suffix();
        
   }
}
inline void crawler::judge_slash(string &str)          //删除多余的slash并且将结果insert
{
    char slash = '/'; 
    string::iterator it;             
	for (it = str.begin(); it != str.end() + 1; it++)
	{
		if (*it == slash && *(it+1) == slash)
        {
            str.erase(it);       
            break;
        
        }		
	}
    if(str[str.length() - 1] == slash)
        str.erase(str.end() - 1);

    urls_tobe_judged.insert(str);

    return;
}

void if_find(crawler &crawler)        //判重
{

    for(auto it : crawler.urls_tobe_judged )
    {
        if(crawler.urls_clawed.find(it) == crawler.urls_clawed.end())
        {
            crawler.urls_tobe_clawed.push(it);
            crawler.fout_tobe << it << std::endl;

            crawler.urls_clawed.insert(it);
        }       
    }

}
void run_bfs(crawler &crawler)
{

   
    while (!crawler.urls_tobe_clawed.empty())
    {
        string current = crawler.urls_tobe_clawed.front();
        crawler.fout_crawled << current << std::endl;

        crawler.set_current(current);
        string content = crawler.get_content();

        crawler.urls_tobe_clawed.pop();
        crawler.urls_clawed.insert(current);
       
        crawler.worker(content);
        if_find(crawler);

    }

    crawler.fout_crawled.close();
    crawler.fout_tobe.close();
    
    if(remove("record_.txt") == 0)
    {
        crawler.fout << "mission completed" << std::endl;
        crawler.fout << "---------------------------"  << std::endl;
        crawler.fout << "total urls : " << crawler.total_urls << std::endl;
    }
   
}