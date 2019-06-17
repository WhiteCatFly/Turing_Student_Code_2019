#include "search_engine.h"
#include "THULAC_lite_c++_v1/include/thulac.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <regex>

SearchEngine::SearchEngine(){;}
SearchEngine::~SearchEngine(){;}
static THULAC_result result;
static THULAC master_LAC;

void SearchEngine::Initialize(){
    master_LAC.init("THULAC_lite_c++_v1/models/", NULL, 1, 0, 1);
}

void SearchEngine::LoadData(FILE *fp){
    
    fprintf(stderr, "Loading ...\n");
    std::vector<std::pair<int, int>> EMPTY1; 
    std::vector<std::string>        EMPTY2;

    int preid = 0;
    int idofpage = 0, idofword = 0;
    char temp_ch[999999];
    std::string tmp;
    
    while(fscanf(fp, "%s", temp_ch) != EOF){    
        
        if(idofpage != preid && idofpage % 100 == 0){
            fprintf(stderr, "%d pages loaded.\n", idofpage);
            preid = idofpage;
        }

        tmp = std::string(temp_ch);
        if(tmp == "|*****"){
            
            std::string URL;
            while(1){
                fscanf(fp, "%s", temp_ch);
                tmp = std::string(temp_ch);
                if(tmp == "*****|") break;
                else URL += tmp;
            }
            
            
            idtopage[++idofpage]    = URL;
            pagetoid[URL]           = idofpage;
            sizeofpage[idofpage]    = 0;

            int n;
            fscanf(fp, "%d", &n);
            
            while(n--){
                fscanf(fp, "%s", temp_ch);
                tmp = std::string(temp_ch);
                int num;
                fscanf(fp, "%d", &num);
                if(num < 0) continue;
                if(wordtoid.find(tmp) == wordtoid.end()){
                    idtoword[++idofword]    = tmp;
                    wordtoid[tmp]           = idofword;  
                }int wordid = wordtoid[tmp];
                
                wordtopages[wordid].push_back(std::make_pair(idofpage, num));
                sizeofpage[idofpage] += num; 
            }
        }else{
            if(content.size() < idofpage) content.push_back(EMPTY2);
            content[idofpage - 1].push_back(tmp);
        }
    }
    fprintf(stderr, "Loading finished\n");
}

//void Evaluate(){}
void SearchEngine::Search(std::string x){
    master_LAC.cut(x, result);
    std::vector<std::pair<double,int> > evaluate;
    for(int i = 0; i <= pagetoid.size(); i++){
        evaluate.push_back(std::make_pair(0.0, i));
    }

    for(auto keyword = result.begin(); keyword != result.end(); keyword ++){
        std::string y = (*keyword).first;
        if(wordtoid.find(y) == wordtoid.end())
            continue;
        int wordid = wordtoid[y];
        double idfi = log10(1.0 * pagetoid.size() / (wordtopages[wordid].size() + 1));
        for(int i = 0; i < wordtopages[wordid].size(); i++){
            int pageid = wordtopages[wordid][i].first;
            int num = wordtopages[wordid][i].second;
            evaluate[pageid].first -= idfi * num / sizeofpage[pageid];
        }
    }

    std::sort(evaluate.begin(), evaluate.end());

    int cut = 0;
    for(auto i = evaluate.begin(); cut < 10 && (*i).first != 0.0; i++, cut++){
        fprintf(stderr, "tf-idf index:%.20lf %s\n", i -> first, idtopage[i -> second].c_str());
        int cnt_ = 0;
        for(auto j = content[i -> second - 1].begin(); cnt_ < 3 && j != content[i -> second - 1].end(); j++){
            for(auto k = result.begin(); k != result.end(); k++){
                if((*j).find((*k).first) != std::string::npos){
                    fprintf(stderr, "%s\n", (*j).c_str());
                    cnt_++;
                    break;
                }
            }
        }
    }

/*
    if(wordtoid.find(x) == wordtoid.end()){
        fprintf(stderr, "nope\n");
        return;
    }
    int wordid = wordtoid[x];
    double idfi = log10(1.0 * pagetoid.size() / (wordtopages[wordid].size() + 1));
    for(int i = 0; i < wordtopages[wordid].size(); i++){
        int pageid = wordtopages[wordid][i].first;
        int num = wordtopages[wordid][i].second;
        evaluate.push_back(std::make_pair( - idfi * num / sizeofpage[pageid], pageid));
    }
    std::sort(evaluate.begin(), evaluate.end());

    int cnt = 0;
    for(auto i = evaluate.begin();cnt < 10 && i != evaluate.end(); i++, cnt++){
        fprintf(stderr, "tf-idf index:%.20lf %s\n",i -> first, idtopage[i -> second].c_str());
        int cnt_ = 0;
        for(auto j = content[i -> second - 1].begin(); cnt_ < 3 && j != content[i -> second - 1].end(); j++){
            if((*j).find(x) != std::string::npos){
                fprintf(stderr, "%s\n", (*j).c_str());
                cnt_ ++;
            }
        }
    }
*/
}

void SearchEngine::TEST(){
    for(auto i = wordtopages.begin(); i != wordtopages.end(); i++){
        std::cerr << idtoword[i -> first] << std::endl;
        for(auto j = (i -> second).begin(); j != (i -> second).end(); j++){
            std::cerr << j -> first << ' ' << j -> second << std::endl;
        }
    }
}