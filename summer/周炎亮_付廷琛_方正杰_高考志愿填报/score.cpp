#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>

#include "score.h"

using namespace std;

int score::loc_province(string PROVINCE)
{
    for(int i=0;i<31;i++)
    {
        if(PROVINCE==PRO[i])
        {
            province_code=i;
            return i;
        }
    }
}
string score::loc_subject(string SUBJECT)
{
    if(SUBJECT=="理工")
    {   subject="li";
        return "li";
    }
    if(SUBJECT=="文史")
    {
        subject="wen";
        return "wen";
    }
    
}
void score::judge(){
    if(province_code==8 && SCORE>=480)
    {
        score_too_high=true;
        SCORE=-1;
        RANK=-1;
        return;
    }
    if(province_code==16 && SCORE>=900)
    {
        score_too_high=true;
        SCORE=-1;
        RANK=-1;
        return;
    }
    if(SCORE>=750)
    {
        score_too_high=true;
        SCORE=-1;
        RANK=-1;
        return;
    }
}
score::score(string PROVINCE,string SUBJECT,string GRADE)
{
    SCORE=atoi(GRADE.c_str());
    score_too_high=false;
    score_too_low=false;
    loc_province(PROVINCE);
    judge();
    if(score_too_high)
        return ;
    loc_subject(SUBJECT);
    grade_to_rank();
    
    //return;//here is for debugger
    //string location="./"+PROVINCE+"/"+SUBJECT+"_2018.csv";
    //string location="./school/"+PRO_[province_code]+"/"+subject+"_comprehensive.txt";
    string location = "G:\\untitled\\school\\" + PRO_[province_code] + "\\" + subject + "_comprehensive.txt";
    fin.open(location);
    if(!fin.is_open())
    {
        cout<<"failed opened"<<location<<endl;
    }
    int i=0;
    string line;
    while(getline(fin,line))
        i++;
    num=i;
    fin.clear();
    fin.seekg(0);
    information=new info[num+1];
    i=-1;
    while(getline(fin,line))
    {
        i++;
        information[i].school=line.substr(0,line.find(","));
        line=line.erase(0,line.find(",")+1);
        if(province_code<=24)
        {
        information[i].grade=atof(line.substr(0,line.find(",")).c_str());
        line=line.erase(0,line.find(",")+1);
        information[i].rank=atof(line.substr(0,line.find(",")).c_str());
        information[i].variance=atof(line.erase(0,line.find(",")+1).c_str());
        }
        else
        {
            information[i].grade=atof(line.substr(0,line.find(",")).c_str());
            information[i].variance=atof(line.erase(0,line.find(",")+1).c_str());
            information[i].rank=0;
        }
        

        /*
        i++;
        size_t position;
        position=line.find(",");
        information[i].school=line.substr(0,position);
        line=line.substr(position+1,line.length());
        information[i].grade=atoi(line.c_str());
        */
    }
}

int score::grade_to_rank()
{
    //cout<<"get into grade to rank"<<endl;
    if(province_code>24)
    {
        RANK=0;
        return 0;
    }
    //filename="./school/"+PRO_[province_code]+"/"+subject+"_rank_2019.csv";
    string filename = "G:\\untitled\\school\\" + PRO_[province_code] + "\\" + subject + "_comprehensive.txt";
    cout << filename << endl;
    fstream fin;
    fin.open(filename);
    if(fin.is_open()==false)
    {
        cout<<"failed";
        return 0;
    }
    //else{
    //    cout<<"success opened "<<filename<<endl;
    //}
    string line;
    int flag=0;
    while(getline(fin,line))
    {
        line=line.erase(0,line.find(",")+1);
        int standard_score=atoi(line.substr(0,line.find(",")).c_str());
        int standard_rank=atoi(line.erase(0,line.find(",")+1).c_str());
        //cout<<"my score "<<SCORE<<endl;
        //cout<<standard_score<<"  "<<standard_rank<<endl;
        if(standard_score<=SCORE)
        {
            flag=1;
            RANK=standard_rank;
            return standard_rank;
        }
        line.clear();
    }
    if(flag==0)
    {
        score_too_low=true;
        return 0;//means the uesr's grade is too low to ranked
    }
}
void score::search(){
    if(score_too_high)
    {
        cout<<"error score"<<endl;
        return;
    }
    if(score_too_low)
    {
        cout<<"your score is not high enough to use our predicet system"<<endl;
        return ;
    }
    if(province_code<=24)
        search_rank();
    else
    {
        search_score();
    }
    

}
void score::search_score()
{
    int i,j,k;
    int grantee=0;
    for(i=0;i<num && SCORE<information[i].grade;i++);
    j=i;
    while(information[j].variance==0)
        j++;
    double standard_variance=information[j].variance;
    cout<<"standard_variance"<<standard_variance<<endl;
    for(j=max(0,i-10);j<=i;j++)
        ans.push_back(information[j]);
    for(k=i+1; grantee<10 && k<num;k++)
    {
        if(information[k].variance<=1.25*standard_variance)
        {   grantee++;
            ans.push_back(information[k]);
        }
    }
    /*for  test begin*/
    for( i=0;i<int(ans.size());i++)
    {
        cout<<ans[i].school<<"  "<<ans[i].grade<<"   "<<ans[i].variance<<endl;
    }
    /*for test end*/
     cout<<"size is "<<ans.size()<<endl;
}
void score::search_rank()
{
    int i,j,k;
    int grantee=0;
    for(i=0;i<num && RANK>information[i].rank;i++);
    j=i;
    while(information[j].variance==0)
        j++;
    double standard_variance=information[j].variance;
    cout<<"standard_variance"<<standard_variance<<endl;
    for(j=max(0,i-10);j<=i;j++)
        ans.push_back(information[j]);
    for(k=i+1; grantee<10 && k<num;k++)
    {
        if(information[k].variance<=1.5*standard_variance)
        {   grantee++;
            ans.push_back(information[k]);
        }
    }

    cout<<"size is "<<ans.size()<<endl;
    /*for  test begin*/
    //for( i=0;i<int(ans.size());i++)
    //{
      //  cout<<ans[i].school<<"  "<<ans[i].grade<<"  "<<ans[i].variance<<endl;
    //}
    /*for test end*/
}
string score::show()
{
     cout<<"size is "<<ans.size()<<endl;
    string delete_order="del ans.txt";
    system(delete_order.c_str());
    fstream fout;
    fout.open("ans.txt",std::ios::app);
    for(int i=ans.size()/2-5;i<int(ans.size()/2+5);i++)
    {
        fout<<ans[i].school<<"  "<<ans[i].grade<<endl;
    }
    fout.close();
    return "ans.txt";
}
score::~score()
{
    delete [] information;
}
