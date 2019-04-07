#ifndef UNIT_H
#define UNIT_H
#include<iostream>
#include<string>
#include<set>
#include<queue>
 
void input_first_url(std::string &url);
class website {
    private:
        std::queue<std::string>url_to_be_crawled;
        std::set<std::string>url_already_be_crawled;
        int n;
        std::string current_url;
        
        void parseUrls(std::string &src,std::set<std::string> &store);

        std:: string getContent(int times);

    public:
        website();
        ~website();
        void Bfs( );

};
#endif // UNIT_H
