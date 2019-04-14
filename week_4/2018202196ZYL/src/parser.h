#ifndef PARSER_H_
#define PARSER_H_

#include<fstream>
#include<string>
#include<queue>
#include<set>
using namespace std;
class parser
{
private:
    string target_url;
    ifstream file_url;
    queue<string> get_url;
    queue<string> get_text;
    set<string> get_text_bool;
    pair<std::set<std::string>::iterator,bool>ret;
public:
    parser(string& url);
    ~parser()
    {
        
    }
    //void PARSE_ALL();
    void parse_title();
    void parse_text();
    void parse_url();
    
};



#endif