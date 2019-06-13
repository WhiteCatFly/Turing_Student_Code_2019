#include <string>
#include <vector>

#include "THULAC_lite_c++_v1/include/thulac.h"
#include "search.h"

bool isEmptyChar(std::string str)
{
    for(auto s : BLACK_CHARACTER)
        if(s == str)
        return true;
    return false;
}

std::vector<std::string> search(std::string &queryStr)
{
    static THULAC thulac;
    THULAC_result thulacResult;
    static bool initFlag = false;
    if(!initFlag)
    {
        thulac.init("models/", NULL, true);
        initFlag = true;
    }
    thulac.cut(queryStr, thulacResult);
    std::vector<std::string> result;
    for(auto it = thulacResult.begin(); it != thulacResult.end(); it++)
        if(!isEmptyChar(it->first))
            result.push_back(it->first);
    return result;
}
