#include"QueryResult.h"

void QueryResult::show(Base &base)
{
    if(result.size() < max_result) max_result = result.size();
    for (int i = 0; i < result.size(); i++)
    {
        base.People[result[i]].showall();
        if (i > max_result)
            break;
    }
}