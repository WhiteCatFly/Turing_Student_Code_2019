#include"parser.h"
#include"search.h"
bool Searchengine::meaningful(std::string word)
{
    const std::set <std::string> stop {"1","2","3","4","5","6","7","8","9","，","。","年","月","日",". ","&",
    ".",",","、","的","后","共","名","其中","所","了","由","为","在","与","上","于","是","等","人","和",";","将",";",":"
    ,"：","a","the","with","an","by","to","of","and","it","about","-","(",")","on","in","we","is","for","!","！"};
    std::set<std::string>::iterator it;
    for(it=stop.begin();it!=stop.end();it++)
        if(word.find(*it)!=std::string::npos)
            return false;
    return true;
}

void Searchengine::search(std::string query,int require_number)
{
    int i,j,k;
    
    std::fstream fin;
    std::string word;
    for(i=1;i<=url_number;i++)
    { 
        std::stringstream ss;
        ss<<i;
        std::string textname="/home/lucas/textsource/";
        std::string digit;
        ss>>digit;
        textname+=digit;
        textname+="_cut.txt";
        fin.open(textname);
        while(fin>>word)
        {
            if(meaningful(word)==false)
                continue;
            if(word_inmap.find(word)==word_inmap.end())
            {
                std::vector< std::vector<int> > v2d;
                v2d.push_back(std::vector<int> (2));
                v2d[0][0]=i;
                v2d[0][1]=1;
                //std::cout<<word<<' '<<v2d[0][0]<<' '<<v2d[0][1]<<std::endl;
                wordmap.insert(std::map<std::string,std::vector< std::vector<int> >>::value_type(word,v2d));
                word_inmap.insert(word);

            }
            else
            {
                if(wordmap[word].size()==0)
                {
                    wordmap[word].push_back(std::vector<int> (2));
                    wordmap[word][0][0]=i;
                    wordmap[word][0][1]=1;
                }
                else if(wordmap[word][wordmap[word].size()-1][0]==i)
                    wordmap[word][wordmap[word].size()-1][1]++;
                else
                {
                    wordmap[word].push_back(std::vector<int> (2));
                    wordmap[word][wordmap[word].size()-1][0]=i;
                    wordmap[word][wordmap[word].size()-1][1]=1;
                    //std::cout<<word<<' '<<wordmap[word][j][0]<<' '<<wordmap[word][j][1]<<std::endl;
                }
            }   
        }
        fin.close();
    }
    // the index is over;

    if(query.find(" ")==std::string::npos)
        singleword(query,require_number);
    else
        mutipleword(query,require_number);
}
void Searchengine::singleword(std::string query,int require_number)
{
    int i,j,k;
    if(word_inmap.find(query)==word_inmap.end())
    {
        std::cout<<"not found";
        return;
    }
    std::cout<<"the whole site are"<<wordmap[query].size()<<std::endl;
    std::vector<std::pair<double,int>> rank;
    for(k=0;k<wordmap[query].size();k++)
    {
        double tf=1+log10(wordmap[query][k][1]);
        double idf=log10((double)url_number/(double)wordmap[query].size());
        //std::cout<<tf*idf<<" "<<wordmap[query][k][0]<<std::endl;
        rank.push_back(std::pair<double,int>(tf*idf,wordmap[query][k][0]));
    }
    sort(rank.begin(),rank.end());
    //std::cout<<"k=="<<k<<std::endl;
    if(k>require_number)
        k=require_number;
    for(i=k-1;i>=0;i--)
    {
        std::cout<<rank[i].first<<' ';
        Htmlparser webparser=Htmlparser(rank[i].second);
        
        webparser.current_url();
        std::cout<<webparser.gettitle()<<std::endl;
    }
}
void Searchengine::mutipleword(std::string query,int require_number)
{
    int word_inquery=1;
    int i,j,k;
    std::set<int> appear_infirst;
    std::vector<std::pair<int,int>> judge;
    std::vector<std::pair<double,int>> rank;
    std::stringstream ss(query);
    std::string word;
    ss>>word;
    for(j=0;j<wordmap[word].size();j++)
    {
        appear_infirst.insert(wordmap[word][j][0]);
        judge.push_back(std::pair<int,int>(wordmap[word][j][0],1));
    }
    while (ss>>word)
    {
        word_inquery++;
        //std::cout<<word;
        //for(i=0;i<wordmap[word].size();i++)
        //    std::cout<<wordmap[word][i][0]<<word<<std::endl;
        for(j=0;j<wordmap[word].size();j++)
            if(appear_infirst.find(wordmap[word][j][0])!=appear_infirst.end())
            {
                for(i=0;i<judge.size();i++)
                    if(judge[i].first==wordmap[word][j][0])
                    {
                        judge[i].second++;
                    }
                
            }
    }
    for(j=0;j<judge.size();j++)
        if(judge[j].second==word_inquery)
        {
            //std::cout<<judge[j].first<<' '<<judge[j].second<<std::endl;
           rank.push_back(std::pair<double,int>(0,judge[j].first));
        }
    std::stringstream s(query);
    while(s>>word)
    {
        for(i=0;i<rank.size();i++)
        {
            double tf;
            for(j=0;j<wordmap[word].size();j++)
                if(wordmap[word][j][0]==rank[i].second)
                {
                    tf=1+log10(wordmap[word][j][1]);
                    //std::cout<<wordmap[word][j][1]<<std::endl;
                    break;
                }
            double idf=log10((double)url_number/(double)wordmap[word].size());
            rank[i].first+=tf*idf;
        }
    }
    sort(rank.begin(),rank.end());
    if(require_number>=rank.size())
        require_number=rank.size();
    for(i=require_number-1;i>=0;i--)
    {
        std::cout<<rank[i].first<<' '<<rank[i].second<<std::endl;
        Htmlparser webparser=Htmlparser(rank[i].second);
        
        webparser.current_url();
        std::cout<<webparser.gettitle()<<std::endl;
    }
    

}
