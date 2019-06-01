#include"HTMLparser.h"
#include<regex>


HTMLparser::HTMLparser(const CMDparser&other):GetContent(other){
    if(m_content.empty()){
        m_htmltype = BAD_HTML;
        m_valid = false;
    }
    else if(m_content.find("<html>") == std::string::npos && m_content.find("</html>")== std::string::npos){
        m_htmltype = NOT_A_HTML;
        m_valid = false;
    }
    else{
        m_htmltype = FINE_HTML;
        m_valid = true;
    }
}

HTMLparser::HTMLparser(const std::string&url):GetContent(url){
    if (m_content.empty()){
        m_htmltype = BAD_HTML;
        m_valid = false;
    }
    else if (m_content.find("<html>") == std::string::npos && m_content.find("</html>") == std::string::npos){
        m_htmltype = NOT_A_HTML;
        m_valid = false;
    }
    else{
        m_htmltype = FINE_HTML;
        m_valid = true;
    }
}



std::string trans(const std::string&str){ //实现href之后路径的获取以及格式化
    std::string temp = str.substr(str.find("href="), str.length() - 1);
    temp = temp.substr(temp.find_first_of("=") + 1, temp.length() - 1);
    // std::cout << temp << std::endl;
    if(temp[0] == '\"'){
        temp = temp.substr(1, temp.length() - 1);
        temp = temp.substr(0, temp.find_last_of("\""));
    }
    if (temp[0] == '\''){
        temp = temp.substr(1, temp.length() - 1);
        temp = temp.substr(0, temp.find_last_of("\'"));
    }
    if(temp.find_last_of("\"") != std::string::npos){
        temp = temp.substr(0, temp.find_last_of("\""));
    }
    if(temp.find_last_of("\'") != std::string::npos){
        temp = temp.substr(0, temp.find_last_of("\'"));
    }
    return temp;
}


std::string urljoin(const std::string&host, const std::string&another){ //实现相对路径的改写
    std::string temp_1 = host;
    std::string temp_2 = another;
    std::string root;
    std::string result;
    if(temp_1.find("http://") != std::string::npos){
        temp_1 = temp_1.substr(temp_1.find("//") + 2, temp_1.length() - 1);
        if(temp_1.find("/") == std::string::npos){
            root = temp_1;
        }
        else{
            root = temp_1.substr(0, temp_1.find_first_of("/") - 1);
        }
    }
    else{
        if (temp_1.find("/") == std::string::npos){
            root = temp_1;
        }
        else{
            root = temp_1.substr(0, temp_1.find_first_of("/") - 1);
        }
    }
    if(temp_2[0] == '/'){
        return "http://" + root + temp_2;
    }
    if(temp_2[0] != '/' && temp_2[0] != '.'){
        std::string temp = temp_1.substr(0, temp_1.find_last_of('/'));
        return "http://" + temp + "/" + temp_2;
    }
    return "";
}

void HTMLparser::urlparser(std::queue<std::string>&aqueue){
    if(m_htmltype != FINE_HTML) return;
    std::regex pattern("<a +[^`>]* *href=[^ >]*");
    std::smatch result;
    std::string temp_result;
    std::string::const_iterator iterStart = m_content.begin();
    std::string::const_iterator iterEnd = m_content.end();
    while(regex_search(iterStart, iterEnd, result, pattern)){
        temp_result = result[0];
        // 
        temp_result = trans(temp_result);
        if(temp_result != "#" && temp_result.find("javascript:") !=0 && temp_result != "" && temp_result.find("http") == 0){
            aqueue.push(temp_result);
            iterStart = result[0].second;
            continue;
        }
        if(temp_result.find("//") == 0){
            aqueue.push("http:" + temp_result);
            iterStart = result[0].second;
            continue;
        }
        if(temp_result.find("http:") || temp_result.find("https:") == std::string::npos){
            temp_result = urljoin(m_url, temp_result);
            aqueue.push(temp_result);
            iterStart = result[0].second;
            continue;
        }
    }
}
