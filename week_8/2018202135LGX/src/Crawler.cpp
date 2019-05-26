#include"Crawler.h"
#include<fstream>
Crawler::Crawler(const HTMLparser&other){
    to_be_crawled.push(other.m_url);
    index = 0;
}



void Crawler::Run(){
    std::ofstream fout;
    while(!to_be_crawled.empty()){
        Current_url = to_be_crawled.front();
        if(whole_result.count(Current_url) == 0 && Current_url.find("info.ruc.edu.cn") != std::string::npos){
            HTMLparser temp(Current_url);
            if(temp.Valid()){
                this->Add(Current_url);
                system("rm default");
            }
            temp.urlparser(to_be_crawled);
            whole_result.insert(Current_url);
            pairs.push_back(std::make_pair(Current_url, temp));
            index ++;
        }
        to_be_crawled.pop();
    }
}

void Crawler::Check(){
    int k1 = 0;
    int i;
    for(i = index - 1; i >= 0; i --){
        if(pairs[i].second.m_htmltype == HTMLparser::BAD_HTML){
            k1++;
        }
        if(pairs[i].second.m_htmltype != HTMLparser::BAD_HTML) break;
}
    if(k1 >= 1){
        std::cout << "There seems to be a network problem. Do you want to re-crawl them?(Y/N)" << std::endl;
    }
    char c;
    std::cin >> c;
    if(c == 'y' || c == 'Y'){
        for (int j = i + 1; j < index; j++){
            to_be_crawled.push(pairs[j].first);
        }
        this->Run();
    }
}

void Crawler::Output(const std::string&file_name){
    std::ofstream fout(file_name);
    auto it = whole_result.begin();
    for(auto it:whole_result){
        fout << it << std::endl;
    }
    fout.close();
}