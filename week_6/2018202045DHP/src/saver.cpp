#include "internetworm.h"
#include <set>
#include <queue>
#include <regex>
#include <fstream>
#include <iostream>

void Backup(std::queue <URL> waitinglist, std::set <URL> repeatjudge){
    std::ofstream ini;
    ini.open("backup.ini");
    ini << waitinglist.size() << std::endl;
    while(!waitinglist.empty()){
        ini << waitinglist.front() << std::endl;
        waitinglist.pop();
    }
    ini << repeatjudge.size() << std::endl;
    for(auto it = repeatjudge.begin(); it != repeatjudge.end(); it++)
        ini << *it << std::endl; 
}