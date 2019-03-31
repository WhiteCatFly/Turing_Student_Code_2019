#include "tools.h"


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
