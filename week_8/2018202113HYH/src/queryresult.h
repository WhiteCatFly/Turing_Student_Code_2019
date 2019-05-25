#ifndef  QUERYRESULT_H
#define  QUERYRESULT_H
#include "textquery.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>

class textquery;

void run_query(int &file_num);
bool cmp(std::pair <int, double> a, std::pair<int, double> b);
int int_cmp(int a, int b);

class queryresult
{
    public:
    friend class textquery;
    queryresult(textquery &tq);
    void get_result(std::vector<std::string> &words);
    void print_result();

    ~queryresult(){};
    private:
    int file_available;
    int num ;//= tq.get_num();
    std::map <std::string, std::vector<std::vector<int>> > wordmap ;//= tq.get_map();
    std::set <std::string> word_in_map ;//= tq.get_words();
    std::vector<std::pair<int, double>> file_score;
    //std::vector<std::string> words;

};

#endif