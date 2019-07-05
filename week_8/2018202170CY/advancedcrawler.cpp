#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <queue>
#include <set>
#include <cstring>
#include <cstdio>

#include "parser.h"
#include "basecrawler.h"
#include "advancedcrawler.h"

using std::string;
using std::cout;
using std::endl;
void AdvancedCrawler::use_wget(string url, string directory)
{
    std::ofstream log;
    log.open("log.txt", std::ios::out | std::ios::app);
    log << url << ":";
    for (int i = url.length() - 1; i >= 0; i--)
    {
        if (url[i] == '&' || url[i] == '(' || url[i] == ')')
        {
            url.insert(i, "\\");
        } 
    }
    for (int i = directory.length() - 1; i >= 0; i--)
    {
        if (directory[i] == '&' || directory[i] == '(' || directory[i] == ')')
        {
            directory.insert(i, "\\");
        } 
    }
    string wget = Wget_ + Store_directory_ + directory + " " + url;
    system(wget.c_str());
    std::ifstream in;
    in.open(directory + " " + url);
    char a_char;
    in.get(a_char);
    if (a_char != EOF)
    {
        log << "succeess" << std::endl;
    }
    else
    {
        log << "fail" << std::endl;
    }
};

void seperate_word(string filename)
{
    string directory_of_fin = "before_seperation/", directory_of_fout = "after_seperation/";
    string seperate = "./thulac -seg_only <" + filename + " " + ">after_seperation.txt";
    system(seperate.c_str());
}

void AdvancedCrawler::crawler(int cnt)
{
    std::ofstream all_url, solved_url, Chinese;
    all_url.open("all_url.txt", std::ios::out | std::ios::app);
    solved_url.open("solved_url.txt", std::ios::out | std::ios::app);
    Chinese.open("Chinese.txt");
    std::set<string> Chinese_string;
    if (url_set.empty() == true)
    {
        all_url << Root_ << endl;
        url_set.insert(Root_);
        url_queue.push(Root_);
    }
    string diretory_of_fout = "before_seperation/";
    std::ofstream fout;
    fout.open("before_seperation.txt");

    while (!url_queue.empty())
    {
        string now_url = url_queue.front();
        string filename = now_url;
        url_queue.pop();
        if (belong_to_Root(now_url) == false) continue;
        cnt ++;
        // cout << cnt << ":" << now_url << "\n";

        for (int i = 0; i < filename.length(); i++)
        if (filename[i] == '/') filename[i] = '_';
        std::ifstream fin;
        fin.open(Store_directory_ + filename, std::ios::in);
        if (!fin)
        {
            fin.close();
            use_wget(now_url, filename);
            fin.open(Store_directory_ + filename);
        }
        parser_root = build_from_stream(fin);
        if (parser_root == NULL) continue;
        std::ofstream store_link;
        store_link.open("store_link.txt");
        string directory = get_directory(now_url);
        (*parser_root).parser_link(store_link);
        fout << "belong to " << filename << '\n';
        (*parser_root).put_body_to_file(fout);
        // seperate_word(filename);
        fin.close();
        store_link.close();

        std::ifstream putin_link;
        putin_link.open("store_link.txt");
        string new_url;
        while(getline(putin_link, new_url))
        {
            if(is_url(new_url) == true && belong_to_Root(new_url) == true)
            {   
                if (is_absolute_address(new_url) == true)
                {
                    int place = new_url.find("#");
                    if (place != string::npos)
                    {
                        new_url.erase(place, new_url.length() - 1);
                    }
                    if (url_set.find(new_url) == url_set.end())
                    {
                        all_url << new_url << endl;
                        url_queue.push(new_url);
                        url_set.insert(new_url);
                    }
                }
                else
                {
                    if (new_url[0] == '/')
                    {
                        new_url.erase(0, 1);
                    }
                    new_url = directory + new_url;
                    int place = new_url.find("#");
                    if (place != string::npos)
                    {
                        new_url.erase(place, new_url.length() - 1);
                    }
                    if (url_set.find(new_url) == url_set.end())
                    {
                        all_url << new_url << endl;
                        url_queue.push(new_url);
                        url_set.insert(new_url);
                    }
                }
            }
        }
        solved_url << now_url << endl;
        free(parser_root);
    }

    seperate_word("before_seperation.txt");
}