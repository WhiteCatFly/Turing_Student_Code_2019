#include "Query.h" 

bool cmp1(pair<string,double> a,pair<string,double> b)
{
    if(a.second - b.second < 0)
    {
        return true;
    }
    else return false;
}

TextQuery::TextQuery(){ 
    string text; 
    Count = N;
    for(int i = 0;i < Count;i ++)
    {
        int wordcount = 0;
        string filename = "./textsource/" + to_string(i+1) + "_cut.txt";
        ifstream is(filename);
        while(getline(is,text)){
            istringstream line(text);
            string word;
            while(line >> word){ //从每行中读取单个单词 
                wordcount ++;                                   
                if(!wm[word].empty()){
                    for(int j = 0;j < i + 1;j ++)
                    {
                        wm[word].push_back(0);
                    }
                }
            (wm[word])[i] = (wm[word])[i] + 1;
        } 
        filecount.push_back(wordcount);
    } 
    }
}

TextQuery::TextQuery(int M){ 
    string text; 
    Count = M;
    for(int i = 0;i < Count;i ++)
    {
        int wordcount = 0;
        string filename = "./textsource/" + to_string(i+1) + "_cut.txt";
        ifstream is(filename);
        while(getline(is,text)){
            istringstream line(text);
            string word;
            while(line >> word){ //从每行中读取单个单词 
                wordcount ++;                                   
                if(!wm[word].empty()){
                    for(int j = 0;j < i + 1;j ++)
                    {
                        wm[word].push_back(0);
                    }
                }
            (wm[word])[i] = (wm[word])[i] + 1;
        } 
        filecount.push_back(wordcount);
    } 
    }
}

void TextQuery::query(const string &sought) { 
    auto loc = wm.find(sought); 
    if(loc==wm.end()){ 
        cout << "there is no this word" << endl; //如果没找到
    } 
    else{ 
        vector<pair<string,double>> tf;
        for(int i = 0;i < Count;i ++)
        {
            string key = to_string(i) + "_cut.txt";
            double temp = ((wm[sought])[i] *1.0) / (filecount[i] * 1.0);
            pair <string,double> temp1 (key,temp); 
            tf.push_back(temp1);
        }
        sort(tf.begin(),tf.end(),cmp1);
        for(int i = 0;i < K;i ++)
        {
            cout << tf[i].first << endl;
        }
    }
    return; 
}