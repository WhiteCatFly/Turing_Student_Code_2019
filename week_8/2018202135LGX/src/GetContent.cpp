#include<sstream>
#include<algorithm>
#include<fstream>
#include<iostream>
#include"GetContent.h"
#include"BuildIndex.h"

int FromStringToInt(const std::string&str){
    int m = 0;
    int k = 1;
    for(int i = str.length() - 1; i >= 0; i --){
        m += k * (str[i] - '0');
        k *= 10;
    }
    return m;
}


GetContent::GetContent(const std::string &url, int _tries=2, int _timeout=2, const std::string &file_name="default"){
    tries = _tries;
    timeout = _timeout;
    filename = file_name;
    m_url = url;
    std::stringstream m1, m2;
    std::string tries_string, timeout_string;
    m1 << tries;
    m2 << timeout;
    m1 >> tries_string;
    m2 >> timeout_string;
    std::string syscmd = "wget -O " + filename + " --tries=" + tries_string + " --timeout=" + timeout_string + " " +url;
    int k = system(syscmd.c_str());
    std::ifstream fin(filename);
    int i = 0;
    while(!fin.eof() && k == 0){
        i ++;
        m_content += fin.get();
        if(i > 1024 * 1024){
            break;
        }
    }
    fin.close();
    // if(k == 0){
    //     syscmd = "rm " + filename;
    //     system(syscmd.c_str());
    // }
}

void GetContent::show(){
    std::cout << m_content << std::endl;
}