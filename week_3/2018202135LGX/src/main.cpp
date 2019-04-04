#include"crawler.h"

int main(){
    Crawler mission("econ.ruc.edu.cn", "result"); //result为存url的文件名
    mission.bfs();
}