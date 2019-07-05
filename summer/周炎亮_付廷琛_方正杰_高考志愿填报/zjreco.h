#ifndef ZJRECO_H_
#define ZJRECO_H_

#include<iostream>
#include<string>
#include<cstdlib>
#include<set>
#include<vector>
using namespace std;

struct zjinfo
{
    double rank_17=0.0;
    double rank_18=0.0;
    double percent_17=0.0;
    double percent_18=0.0;
    //int num=1;
};
struct RANK
{
    int score;
    int rank;
};
struct FINAL
{
    string final_profession="";
    double final_rank=0.0;
    int final_score=0;
};
class zjreco
{
private:
    set <string> abled_profession;
    vector <string> scored_profession;
    vector <zjinfo> scored_profession_rank;
    vector <RANK> rank;
    double max_rank;
    double min_rank;
    double* model;
    int curr_score;
    int profession_num;
    int rank_num;
    FINAL last[10];
public:
    zjreco(string sub[],int score);
    void get_profession();
    void get_final_profession();
    void get_model();
    void test();
    void unite();
    int score_to_rank(int SCORE);
    int rank_to_score(int RANK);
    ~zjreco();
};
bool find_repeat(FINAL a[],double b);

#endif