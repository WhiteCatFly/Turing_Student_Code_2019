
#include "search.h"
#include "work.h"
#include "get.h"


void if_find(work & work, search & search)        //判重
{

    for(auto it : work.urls_tobe_judged )
    {
        if(search.urls_clawed.find(it) == search.urls_clawed.end())
        {
            search.urls_tobe_clawed.push(it);
            search.urls_clawed.insert(it);
        }       
    }

}


void search::bfs(get & get , work & operate, search & search)    //bfsbfsbfs
{ 
    fout.open("okk.txt");
    //urls_tobe_clawed.push(root);
     while (!urls_tobe_clawed.empty())
     {
         std::string current = urls_tobe_clawed.front();
        
         fout << current << std::endl;

         get.set_current(current);
         std::string content = get.get_content();

         urls_tobe_clawed.pop();
         urls_clawed.insert(current);
        
         operate.set(current, content, root);
         operate.parse();
         if_find(operate , search);

     }
      fout.close();



}


