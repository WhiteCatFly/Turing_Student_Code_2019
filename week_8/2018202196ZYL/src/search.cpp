#include"search.h"
#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include<cmath>
#include<sstream>
//#include"THULAC/include/thulac.h"
#include"THULAC_lite_c++_v1/include/thulac.h"

using namespace std;


Search::Search()
{
    all_num=0;
    ifstream fin("text.txt");
    string url;
    string text;
    while(getline(fin,url))
    {
        url_=new string;
        url_[all_num]=url;
        getline(fin,text);
        mapurl.insert(pair<string,string>(url,text));
        all_num++;
    }
    fin.close();
    cout<<"load succesfull"<<endl;
}
void Search::word_apart(string& words)
{
	//cout<<"d";
    word_num=0;
	THULAC lac;
    THULAC_result result;
	//cout<<"q";
	//string raw="";
	lac.cut(words,result);
	for(int j = 0; j < result.size() - 1; j++) 
    {
        word=new string;
        word[j]=result[j].first;
        word_num++;
    }
}
void Search::find_times()
{
    word_times=new int[word_num];
    map<string, string>::iterator iter;  
    for(iter=mapurl.begin();iter!=mapurl.end();iter++) 
    {
        for(int i=0;i<word_num;i++)
        {
            if(iter->second.find(word[i])!=string::npos)
                word_times[i]++;
        }
    }
    word_times_lg=new double[word_num];
    for(int i=0;i<word_num;i++)
        word_times_lg[i]=log10((double)(all_num/word_times[i]));
}
void Search::find_frequency()
{
    word_frequency=new double[all_num];
    string a;
    int frequency,all;
    int j=0;
    for(int i=0;i<word_num;i++)
    {
        map<string, string>::iterator iter;  
        for(iter=mapurl.begin();iter!=mapurl.end();iter++)
        {
            frequency=0;
            all=0;
            stringstream os(iter->second);
            while(os>>a)
            {
                if(word[i]==a)
                    frequency++;
                all++;
            }
            word_frequency[j]=word_frequency[j]+1.0*frequency/all*word_times_lg[i];
            j++;
        }
    }
}
void Search::sort()
{
    int i,j,k;
    /*map<string, string>::iterator iter;  
    for(iter=mapurl.begin();iter!=mapurl.end();iter++)
    {
        pair<string,string> a;
        a=make_pair(iter->first,iter->second);
        mapfinal.insert(pair<double,pair<string,string>>(word_frequency[i],a));
        i++;
    }*/
    for(i=0;i<all_num;i++)
    {
        //if(word_frequency[i]==0)
            //continue;
        k=i;
        for(j=i;j<all_num;j++)
        {
            if(word_frequency[j]!=0&&word_frequency[j]>word_frequency[k])
                k=j;
        }
        if(k!=i)
        {
            int n;
            n=word_frequency[i];
            word_frequency[i]=word_frequency[k];
            word_frequency[k]=n;
            string p;
            p=url_[i];
            url_[i]=url_[k];
            url_[k]=p;
        }
    }
    i=0;
    while(word_frequency[i]!=0)
    {
        cout<<url_[i];
        i++;
    }
}
Search::~Search()
{
    delete [] word;
    delete [] url_;
    delete [] word_times;
    delete [] word_times_lg;
    delete [] word_frequency;
}