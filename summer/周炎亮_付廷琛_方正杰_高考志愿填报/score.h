#ifndef SCORE_H_
#define SCORE_H_

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

struct info
{
    string major;
    string school;
    double grade;
    double rank;
    double variance;
};


class score//given the specific score and the file storage location
{
private:
    bool score_too_low;
    bool score_too_high;//deal with wrong input
    void judge();
    ifstream fin;
    info* information=NULL;
    int province_code;
    string subject;
    int SCORE;//the score of user
    int RANK;//the rank of user
    int num;//the total number of info
    vector <info> ans;
    int loc_province(string PROVINCE);
    string loc_subject(string SUBJECT);
    int grade_to_rank();

public:
    static  string PRO[31];
    static  string PRO_[31];
    //score(string PROVINCE,string SUBJECT,int GRADE,int Rank);
    score(string PROVINCE,string SUBJECT,string GRADE);
    void search();
    void search_score();
    void search_rank();
    void debugger(){
        cout<<RANK;
    }
    string show();
    ~score();
};





#endif