#include"crawler.h"

int main(){
    system("touch results.txt");
    std::set<std::string> urls;
    std::set<std::string> &turls = urls;
    std::queue<std::string> results;
    std::queue<std::string> &tresults = results;
    std::set<std::string> labels;
    std::set<std::string> &tlabels = labels;
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