#include "internetworm.h"
#include <regex>
#include <string>

static std::regex DIRECT("http://|https://");
extern std::regex BANNED;
extern URL ROOT_URL;

bool URL::Scheck(){
    if(_url[0] == SLASH) {
        _url.erase(0,1);
        return true;
    } else return false;
}

bool URL::DScheck(){
    if(_url[0] == DOT && _url[1] == SLASH) {
        _url.erase(0,2);
        return true;
    } else return false;
}

bool URL::DDScheck(){
    if(_url[0] == DOT && _url[1] == DOT && _url[2] == SLASH) {
        _url.erase(0,3);
        return true;
    }
    else return false;
}

void URL::DeletePeriod(){
    if(_url[_url.length() - 1] == '/') _url.pop_back();
    while(_url[_url.length() - 1] != '/') _url.pop_back();
}

inline bool URL::Direct()       {return std::regex_search(_url, DIRECT);}
inline bool URL::ContainRoot()  {return std::regex_search(_url, std::regex(ROOT_URL.OriginLink()));}
inline bool URL::isban()        {return std::regex_search(_url + " ", BANNED);}

URL Format_Normalizer(URL x, URL y){
    if(y.Direct())
        if(y.ContainRoot()) return y;
        else return EMPTY;
    if(y.isban()) return EMPTY;
    if(x.OriginLink() != ROOT_URL.OriginLink()) x.DeletePeriod();
    while(1){
        if(y.Scheck())          ;
        else if(y.DScheck())    ;
        else if(y.DDScheck())   x.DeletePeriod();
        else                    break;
    }return x + y;
}
