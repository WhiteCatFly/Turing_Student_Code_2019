#include"crawler.h"

std::string Get_Source_Code(std::string url){
    std::string filename = "temp";
    std::string syscmd = "ulimit -f 200; wget -O " + filename + " --tries=2 --timeout=2 " + url;//不允许下载超过200k的网页
    system(syscmd.c_str());
    std::ifstream fin;
    fin.open(filename);
    std::string whole;
    int k = 0;
    while(!fin.eof()){
        whole += fin.get();
        k ++;
        if(k >= 1024 * 1024) break;
    }
    fin.close();
    syscmd = "rm " + filename;
    system(syscmd.c_str());
    return whole;
}

void insert_URLs(std::string url, std::string source_code, std::set<std::string>& temp, std::queue<std::string>& tempqueue, std::set<std::string> &label){
    std::regex standard("<a +href *= *[\"][^ >]*");
    std::string::const_iterator iterStart = source_code.begin();
    std::string::const_iterator iterEnd = source_code.end();
    std::string temp_result;
    std::string temp_result_copy;
    std::smatch result;
    int k = 0;
    while(regex_search(iterStart, iterEnd, result, standard)){
        temp_result = result[0];
        temp_result_copy = trans_URLs(url, temp_result, label);
        if(!temp.count(temp_result_copy) && temp_result_copy.find("info") != -1 && temp_result_copy.find("ruc") != -1){
            temp.insert(temp_result_copy);
            tempqueue.push(temp_result_copy);
            std::cout << "Inserting " << temp_result_copy << std::endl;
            k ++;
        }
        //std::cout << trans_URLs(url, temp_result) << std::endl;
        iterStart = result[0].second;
    }
}

std::string trans_URLs(std::string root, std::string url, std::set<std::string>& label){
    std::regex standard("\"[^ >]*\"");
    std::string::const_iterator iterStart = url.begin();
    std::string::const_iterator iterEnd = url.end();
    std::string temp_result;
    std::smatch result;
    while(regex_search(iterStart, iterEnd, result, standard)){
        temp_result = result[0];
        iterStart = result[0].second;
        temp_result = temp_result.substr(1, temp_result.size() - 2);
        if(label.count(temp_result)){
            break;
        }
        if(temp_result.find("//") == -1 && temp_result.front() != '/'){
            root +="/" + temp_result;
            label.insert(temp_result);
            return root;
        }
        if(temp_result.find("//") == -1 && temp_result.front() == '/'){
            root += temp_result;
            label.insert(temp_result);
            return root;
        }
        return temp_result;
    }
    return "";
}

