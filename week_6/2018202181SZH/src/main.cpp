#ifndef unit
#define unit
#include "unit.h"

string root_url ;

int main(int argc,char* argv[]){
    if(argc==2){
    //读入根目录 argv[1] is root_url
    root_url = argv[1];
    website run;
    run.Bfs();  
    }
    
    if(argc==4){
    //argv[1] is root_url
    root_url = argv[1];
    //argv[2] is "diary_to_be_crawled.txt"(里面包含了将要爬取的，和已经爬取了但是没有pop掉)
    //argv[3] is "diary_already_crawled.txt"
    string to_be_txt = argv[2];
    string already_txt = argv[3];
    
    website run;
    run.restart(to_be_txt,already_txt);
    run.Bfs();
    }
    
   

    //在crawler爬取完全部网站以后选择网页用htmlParser编辑
    cout<<"Please input the website which can be a url or a file name"<<endl;
    string name;
    cin>>name;
    html website11;
    judge_url_or_file(name,website11);
    website11.inter_face();
    return 0;
}
#endif // !unit
