#include"crawler.h"

int main(){
    //std::string filter_true[] = {"ruc", "info"};
    //std::string filter_false[] = {"doc", "docx", "pdf", "mp3", "mp4", "xls", "xlsx", "pptx"};
    system("touch results.txt");
    std::set<std::string> urls;
    std::set<std::string> &turls = urls; //引用
    std::queue<std::string> results;
    std::queue<std::string> &tresults = results;  //引用
    std::set<std::string> labels;
    std::set<std::string> &tlabels = labels;  //引用
    std::ofstream fout("results.txt");
    results.push("http://info.ruc.edu.cn");
    while(!results.empty()){
        insert_URLs(results.front(), Get_Source_Code(results.front()), turls, tresults, tlabels);
        fout << results.front() << std::endl;
        results.pop();
        std::cout << "---------------------------------" <<std::endl;
    }
    labels.clear();

}