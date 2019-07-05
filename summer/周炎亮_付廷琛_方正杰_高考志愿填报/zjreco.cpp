#include"zjreco.h"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

string SUBJECT[8]={"生物","化学","地理","历史","物理","思想政治","技术"};
string SUBJECT_[8]={"biology","chemistry","geography","history","physics","politics","tech"};

zjreco::zjreco(string sub[],int score):curr_score(score)
{
    string location,line;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(sub[i]==SUBJECT[j])
            {
                location="./zhejiang/"+SUBJECT_[j]+".txt";
                ifstream fin(location);
                while(getline(fin,line))
                    abled_profession.insert(line);
                fin.close();
                break;
            }
        }
    }
    ifstream hin("G:\\untitled\\zhejiang\\2019_rank.txt");
    string l;
    int i=-1;
    while(getline(hin,line))
    {
        i++;
        RANK Rank;
        size_t position=line.find(",");
        l=line.substr(0,position);
        //cout<<l<<endl;
        Rank.score=atoi(l.c_str());
        line=line.substr(position+1,line.length());
        Rank.rank=atoi(line.c_str());
        rank.push_back(Rank);
        
    }
    rank_num=i;
    hin.close();
}
int zjreco::score_to_rank(int SCORE)
{
    int k=0;
    while(SCORE<rank[k].score&&k<rank_num)
        k++;
    return rank[k].rank;
}
int zjreco::rank_to_score(int RANK)
{
    int k=0;
    while(RANK>rank[k].rank)
        k++;
    return rank[k].score;
}
void zjreco::get_profession()
{
    pair <set <string>::iterator,bool> ret;
    ifstream fin("G:\\untitled\\zhejiang\\2017_new.csv");
    string line,school,profession;
    double rank;
    while(getline(fin,line))
    {
        size_t position=line.find(",");
        school=line.substr(0,position);
        line=line.substr(position+1,line.length());
        position=line.find(",");
        profession=line.substr(0,position);
        line=line.substr(position+1,line.length());
        /*position=line.find(",");
        string l=line.substr(0,position);*/
        rank=atof(line.c_str());
        string whole=school+","+profession;
        ret=abled_profession.insert(whole);
        if(!ret.second)
        {
            scored_profession.push_back(whole);
            zjinfo a;
            a.rank_17=rank;
            a.percent_17=0.35;
            scored_profession_rank.push_back(a);
        }
    }
    fin.close();
    ifstream hin("G:\\untitled\\zhejiang\\2018_new.csv");
    while(getline(hin,line))
    {
        size_t position=line.find(",");
        school=line.substr(0,position);
        line=line.substr(position+1,line.length());
        position=line.find(",");
        profession=line.substr(0,position);
        line=line.substr(position+1,line.length());
        /*position=line.find(",");
        string l=line.substr(0,position);*/
        rank=atof(line.c_str());
        string whole=school+","+profession;
        ret=abled_profession.insert(whole);
        if(!ret.second)
        {
            vector <string>::iterator iter=find(scored_profession.begin(),scored_profession.end(),whole);
            if(iter!=scored_profession.end())
            {
                int nposition=distance(scored_profession.begin(),iter);
                scored_profession_rank[nposition].rank_18=rank;
                scored_profession_rank[nposition].percent_18=0.65;
            }
            else
            {
                scored_profession.push_back(whole);
                zjinfo a;
                a.rank_18=rank;
                a.percent_18=0.65;
                scored_profession_rank.push_back(a);
            }
        }
    }
    hin.close();
    profession_num=distance(scored_profession.begin(),scored_profession.end());
    model=new double[profession_num];
}
void zjreco::get_model()
{
    //cout<<profession_num;
    double average,variance,value;
    for(int i=0;i<=profession_num;i++)
    {
        //cout<<'1';
        average=(scored_profession_rank[i].rank_17*scored_profession_rank[i].percent_17+scored_profession_rank[i].rank_18*scored_profession_rank[i].percent_18)
            /(scored_profession_rank[i].percent_17+scored_profession_rank[i].percent_18);
        variance=(average-scored_profession_rank[i].rank_17)*(average-scored_profession_rank[i].rank_17)*scored_profession_rank[i].percent_17
            +(average-scored_profession_rank[i].rank_18)*(average-scored_profession_rank[i].rank_18)*scored_profession_rank[i].percent_18;
        if((scored_profession_rank[i].rank_17-scored_profession_rank[i].rank_18)>0.0)
        {
            value=average-sqrt(variance);
            model[i]=value;
            //cout<<value<<endl;
        }
        else
        {
            value=average+sqrt(variance);
            model[i]=value;
            //cout<<value<<endl;
        }
    }
}

void zjreco::get_final_profession()
{
    max_rank=score_to_rank(curr_score+1)/53225.0;
    min_rank=score_to_rank(curr_score-4)/53225.0;
    for(int i=0;i<5;i++)
    {
        int k=0;
        for(int j=0;j<=profession_num;j++)
        {
            if(fabs(model[k]-min_rank)>fabs(model[j]-min_rank)&&find_repeat(last,model[j]))
                k=j;
        }
        last[i+5].final_profession=scored_profession[k].c_str();
        last[i+5].final_rank=model[k];
        last[i+5].final_score=rank_to_score(last[i+5].final_rank*53225);
    }
    for(int i=0;i<5;i++)
    {
        int k=0;
        for(int j=0;j<=profession_num;j++)
        {
            if(fabs(model[k]-max_rank)>fabs(model[j]-max_rank)&&find_repeat(last,model[j]))
                k=j;
        }
        last[i].final_profession=scored_profession[k].c_str();
        last[i].final_rank=model[k];
        last[i].final_score=rank_to_score(last[i].final_rank*53225);
    }
    for(int i=0;i<5;i++)
    {
        for(int j=4;j>i;j--)
        {
            if((last[j].final_rank-last[j-1].final_rank)<0)
            {
                FINAL a=last[j];
                last[j]=last[j-1];
                last[j-1]=a;
            }
        }
    }
    for(int i=5;i<10;i++)
    {
        for(int j=9;j>i;j--)
        {
            if((last[j].final_rank-last[j-1].final_rank)<0)
            {
                FINAL a=last[j];
                last[j]=last[j-1];
                last[j-1]=a;
            }
        }
    }
    for(int i=0;i<5;i++)
    {
        if(last[i].final_score<=last[5].final_score)
        {
            FINAL a;
            last[i]=a;    
        }
    }
}

zjreco::~zjreco()
{
    delete [] model;
}

void zjreco::test()
{
    //for(int i=0;i<=profession_num;i++)
    //    cout<<scored_profession[i].c_str()<<' '<<scored_profession_rank[i].rank_17<<' '<<scored_profession_rank[i].rank_18
    //        <<' '<<model[i]<<endl;
    ofstream fout("C:\\Users\\Administrator\\Documents\\build-untitled-Desktop_Qt_5_6_1_MinGW_32bit-Debug\\ans.txt");
    for(int i=0;i<10;i++)
        fout<<last[i].final_profession<<' '<<"预测分数为："<<last[i].final_score<<endl;
    fout.close();
    //cout<<curr_score<<' '<<max_rank<<' '<<min_rank<<endl;      
    //for(int i=0;i<rank_num;i++)
    //    cout<<rank[i].score<<' '<<rank[i].rank<<endl;
}

void zjreco::unite()
{
    get_profession();
    get_model();
    get_final_profession();
    test();
}
bool find_repeat(FINAL a[],double b)
{
    for(int i=0;i<10;i++)
    {
        if((a[i].final_rank-b)==0)
            return false;
    }
    return true;
}
