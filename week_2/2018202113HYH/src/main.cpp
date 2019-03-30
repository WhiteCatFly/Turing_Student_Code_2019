#include "operate.h"


int main()
{    

    //using namespace std;

     std::queue <std::string> urls_tobe_clawed;
     std::set   <std::string> urls_clawed;
     std::set   <std::string> urls_tobe_judged;
    
     std::string storage_path = "/home/halcyon/index.html";
     std::cout << "please enter the storage path: " << std::endl;
     std::cin  >> storage_path ;

     int total_urls = 0;

     clock_t time_start,time_finish;
     time_start = clock();

     urls_tobe_clawed.push(root);

     while (!urls_tobe_clawed.empty())
     {
         std::string current = urls_tobe_clawed.front();
         std::string content = getcontent(current,total_urls,storage_path);

         urls_tobe_clawed.pop();
         urls_clawed.insert(current);

         parse(content,current,urls_tobe_judged);

        for(auto it : urls_tobe_judged )
        {
            if(urls_clawed.find(it) == urls_clawed.end())
            {
                urls_tobe_clawed.push(it);
                urls_clawed.insert(it);
            }       
        }
     }

     time_finish = clock();

     double total_time;
     total_time = (double)(time_finish - time_start) / CLOCKS_PER_SEC;

     std::cout << "total time :" << total_time  << "seconds" << std::endl;
     std::cout << "total urls :" << total_urls  << std::endl;

     return 0;
}