#ifndef INTERNETWORM_H
#define INTERNETWORM_H

#include <fstream>
#include <string>
#include <queue>

class URL{
    private:
        std::string _url;
    
    public:
        URL (std::string url);
        URL (){}
        void Show(std::ostream &out);
        bool Download(std::string &page);
/*        void Modify(std::string &url){
            _url = url;
        }*/
       
        std::string Visit() const;
        std::string View();
};

bool operator < (const URL x, const URL y);
bool operator > (const URL x, const URL y);

void LogLoader  ();
//bool Loader   (URL url, std::string &page);
void Extracter  (std::string &page, std::queue <URL> &newurls);
URL Filter      (std::string currenturl, std::string newurl);

#endif

