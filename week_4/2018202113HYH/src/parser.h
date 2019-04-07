#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

class parser
{
    public:

    
    parser(){}
    parser(std::string root_)
    {
        root = root_;
    }
    parser(char* file)
    {
        fout.open(file);
    }
  
    void set_root(std::string root_)
    {
        root = root_;

    }
    void set_fout(std::string file = "okkk.txt")
    {
        fout.open(file);
    }
    void get_content(std::string storage_path = "/home/halcyon/index.html" )
    {
        std::ifstream fin;
        std::string line;
        std::string order = "wget --timeout=3 --waitretry=0 --tries=5 \"";
        std::string opn   = "\" -O ";

        opn   += storage_path;
        order += root;
        order += opn;

        system (order.c_str());

        fin.open(storage_path);
        while (getline(fin,line))
        content += line;

        fin.close();
    }
    void get_title();
    void get_urls();
    void get_body();
    void judge(std::string str);
    void judge_mark(std::string str);
    void judge_slash(std::string str);
    ~parser(){}

    private:

    std::string root;
    std::string content;
    std::string title;
    std::string body;
    std::vector <std::string> urls;
    //std::vector <std::string> body;
    std::ofstream fout;

};
