#ifndef  TEXTQUERY_H
#define  TEXTQUERY_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cin;
using std::cout;
using std::endl;

bool judge_meaning(std::string word);
class textquery
{
    public:
    textquery(){}
    textquery(int num);
    void add_new_word(int &file_no, std::string &word);
    void add_new_file(int &file_no, std::string &word);

    int get_num(){return file_num;}
    std::map <std::string, std::vector<std::vector<int>> > get_map(){return wordmap;}
    std::set <std::string> get_words(){return word_in_map;}

    ~textquery(){}
    private:
    int file_num;
    std::map <std::string, std::vector<std::vector<int>> > wordmap;
    std::set <std::string> word_in_map;
    std::ifstream fin;

};
#endif