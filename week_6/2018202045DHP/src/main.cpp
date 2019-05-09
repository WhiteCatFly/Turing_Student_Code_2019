#include "internetworm.h"
#include "htmlparser.h"
#include <iostream>
#include <regex>
#include <string>
#include <string.h>
#include <fstream>
#include <queue>
#include <set>
#include <sys/time.h>

URL ROOT_URL(EMPTY);
std::regex BANNED(EMPTY);
std::string DOWNLOAD;

int main(int argc, char **argv){
    timeval starttime, endtime;
    gettimeofday(&starttime, NULL);
    int backupcontroller = 0;
//    ROOT_URL = URL("http://econ.ruc.edu.cn/");
//    BANNED = std::regex("(.css )|(@ruc.edu.cn )|(@163.com )|(@126.com )|(.png )|(.pdf )|(.PDF )|(.docx )|(.bmp )|(.ico )|(.doc )|(.xls )|(.mp4 )|(.jpg )|(.xlsx )|(.ppt )|(.zip )|(.rar )|(.JPG )");
    
    if(argc > 2) {
        std::cerr << argc << ' ' << "Invalid Parametres" << std::endl;
        return 0;
    }

    std::queue  <URL>   waitinglist;
    std::set    <URL>   repeatjudge;
    IniLoader();
    if(argc > 1 && strcmp(argv[1], "continue") == 0)
        if(!BreakpointLoader(waitinglist, repeatjudge))
            return 0;
    std::ofstream error;    error.open("fail.log");
    std::ofstream normal;   normal.open("succeed.log");
    std::ofstream result;   result.open("result.out");

    waitinglist.push    (ROOT_URL);
    repeatjudge.insert  (ROOT_URL);

    while(!waitinglist.empty()){
        backupcontroller ++;
        if(backupcontroller % OUT_INTERVAL == 0)
            Backup(waitinglist, repeatjudge);
        URL current = waitinglist.front();
        waitinglist.pop();
        if(!current.Download()){
            current.Write   (error);
            continue;
        } else {
            std::cerr << repeatjudge.size() << ' ' << waitinglist.size() << ' ';
            current.WritePage   (result);
            current.Write       (std::cerr);
            current.Write       (normal);
            HtmlParser temp(current);
            temp.Extract     ();
            while(!temp.emptylink()){
                URL brandnew = Format_Normalizer(current, temp.frontlink());
                if(repeatjudge.count    (brandnew) == 0){
                    waitinglist.push    (brandnew);
                    repeatjudge.insert  (brandnew);
                }temp.poplink();
            }
        }
    }gettimeofday(&endtime, NULL);
    normal << endtime.tv_sec - starttime.tv_sec << " second(s) were consumed.\n" << repeatjudge.size() << " page(s) were detected and tried to download." << std::endl;
    system("rm -rf backup.ini");
    return 0;
}