#include <vector>
#include <string>
#include <iostream>
#include "searchengine.h"

std::string find[8] = {"刘德明" , "男" , "34" , "北京 海淀" , "浙江 杭州" , "2019 2 2" , "180" , "wdnmd闸总"};

int main(int argc, char **argv){
    SearchEngine excellent;
    excellent.Initialize();
    std::cerr << "Loading complete" << std::endl;
    excellent.Search(find);
    std::cerr << "StageFinished" << std::endl;
    return 0;
}