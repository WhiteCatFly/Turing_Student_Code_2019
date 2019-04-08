#include"HTMLparser.h"

std::string GetContent(std::string url){
    std::string temp1;
    std::string syscmd = "wget -c " + url + " -O temp";
    system(syscmd.c_str());
    std::ifstream fin;
    fin.open("temp");
    while(!fin.eof()){
        temp1 += fin.get();
    }
    syscmd = "rm temp";
    system(syscmd.c_str());
    return temp1;
}


std::string HTMLparser::trans_URLs(std::string aurl){
    std::regex pattern("<a +[^ >]* *href *= *'*\"*[^ >]*'*\"*");

    std::string::const_iterator iterStart = aurl.begin();

    std::string::const_iterator iterEnd = aurl.end();

    std::smatch result;

    regex_search(iterStart, iterEnd, result, pattern);

    aurl = result[0];

    bool if_ = false;

    if(aurl.find("'") == -1 && aurl.find("\"") == -1){   //如果网址两端未加引号的处理

        int temp = aurl.find_first_of("=");

        aurl = aurl.substr(temp + 1, aurl.size() - 1);

        if_ = true;

    }

    std::regex pattern_1("'[^ >]*'");  //单引号匹配

    std::regex pattern_2("\"[^ >]*\"");  //双引号匹配

    iterStart = aurl.begin();

    iterEnd = aurl.end();

    std::string url_result;

    std::string root = host;

    //std::smatch result;

    while(regex_search(iterStart, iterEnd, result, pattern_1)){

        url_result = result[0];

        iterStart = result[0].second;

    }
    while(regex_search(iterStart, iterEnd, result, pattern_2)){

        url_result = result[0];

        iterStart = result[0].second;

    }

    if(if_) url_result = aurl; 



    if(url_result.back() =='\'' || url_result.back() == '\"'){

        url_result.pop_back();

    }

    if(url_result.front() =='\'' || url_result.front() == '\"'){

        url_result = url_result.substr(1, url_result.size() - 1);

    }

    if(url_result.find("http")  != -1){

        return url_result;
    }

    if(url_result.front() =='/'){   //相对路径前加/的，回到主页
        
        if(host.find("http") != std::string::npos)
        return host + url_result;
        else return "http://" + host +url_result;

    }

    if(root == host && url_result.front() != '/'){  

        if(host.find("http") != std::string::npos)
        return host + "/" + url_result;
        else return "http://" + host + "/" + url_result;

    }

    if(root != host && url_result.front() != '/'){  //相对路径不加 / 的，回退一次

        int temp = root.find_last_of('/');

        root = root.substr(0, temp + 1);
        
        if(root.find("http") == std::string::npos){
            root = "http://" + root;
        }
        return root + url_result;
    }

    return url_result;
}

std::string HTMLparser::trans_URLs_for_Img(std::string aurl){
    bool if_ = false;

    if(aurl.find("'") == -1 && aurl.find("\"") == -1){   //如果网址两端未加引号的处理

        int temp = aurl.find_first_of("=");

        aurl = aurl.substr(temp + 1, aurl.size() - 1);

        if_ = true;

    }

    std::regex pattern_1("'[^ >]*'");  //单引号匹配

    std::regex pattern_2("\"[^ >]*\"");  //双引号匹配

    std::string::const_iterator iterStart = aurl.begin();

    std::string::const_iterator iterEnd = aurl.end();

    std::string url_result;

    std::string root = host;

    std::smatch result;

    //std::smatch result;

    while(regex_search(iterStart, iterEnd, result, pattern_1)){

        url_result = result[0];

        iterStart = result[0].second;

    }
    while(regex_search(iterStart, iterEnd, result, pattern_2)){

        url_result = result[0];

        iterStart = result[0].second;

    }

    if(if_) url_result = aurl; 



    if(url_result.back() =='\'' || url_result.back() == '\"'){

        url_result.pop_back();

    }

    if(url_result.front() =='\'' || url_result.front() == '\"'){

        url_result = url_result.substr(1, url_result.size() - 1);

    }

    if(url_result.find("http")  != -1){

        return url_result;
    }

    if(url_result.front() =='/'){   //相对路径前加/的，回到主页
        
        if(host.find("http") != std::string::npos)
        return host + url_result;
        else return "http://" + host +url_result;

    }

    if(root == host && url_result.front() != '/'){  

        if(host.find("http") != std::string::npos)
        return host + "/" + url_result;
        else return "http://" + host + "/" + url_result;

    }

    if(root != host && url_result.front() != '/'){  //相对路径不加 / 的，回退一次

        int temp = root.find_last_of('/');

        root = root.substr(0, temp + 1);
        
        if(root.find("http") == std::string::npos){
            root = "http://" + root;
        }
        return root + url_result;
    }

    return url_result;
}


std::string RemoveTag(std::string str){
    /*std::string temp;
    char temp_char;
    bool if_ = false;
    std::istringstream sin(str);
    while(!sin.eof()){
        temp_char = sin.get();
        if(temp_char == '<'){
            if_ = true;
        }
        if(!if_){
        temp += temp_char;
        }
        if(temp_char == '>'){
            if_ = false;
        }
    }
    temp.pop_back();
    return temp;*/
    const std::regex pattern("<[^ >]*>");
    std::regex  replace("&lt;|&gt;|&le;|&ge;|&quot;|&ldquo;|&rdquo;|&lsquo;|&rsquo;");
    str = regex_replace(str, pattern, "");
    return str;
}

std::string get_title(std::string str){
    std::string temp;
    std::regex pattern("\"[^`]*\"");
    std::string::const_iterator iterStart = str.begin();
    std::string::const_iterator iterEnd = str.end();
    std::smatch result;
    while(regex_search(iterStart, iterEnd, result, pattern)){
        temp = result[0];
        iterStart = result[0].second;
    }
    temp.pop_back();
    temp = temp.substr(1, temp.length() - 1);
    return temp;
}

std::string get_title_1(std::string str){
    std::string::const_iterator iterStart = str.begin();
    std::string::const_iterator iterEnd = str.end();
    std::regex pattern(">[^`]*<");
    std::smatch result;
    regex_search(iterStart, iterEnd, result, pattern);
    std::string temp = result[0];
    temp.pop_back();
    temp = temp.substr(1, temp.length() - 1);
    return temp;
}

HTMLparser::HTMLparser(std::string url){
    web_content = GetContent(url);
    host = url;
}

HTMLparser::HTMLparser(std::ifstream fin){
    while(!fin.eof()){
        web_content += fin.get();
    }

}

void HTMLparser::GetTitle(){
    std::regex pattern("<title[^ >]*>([^<>]*)</title>");
    //std::regex pattern("(\\w).*?(?=\\1)");
    std::string::const_iterator iterStart = web_content.begin();
    std::string::const_iterator iterEnd = web_content.end();
    std::smatch result;
    //regex_match(web_content, result, pattern);
    while(regex_search(iterStart, iterEnd, result, pattern)){
        title = result[0];
        iterStart = result[0].second;
    }
    std::cout << title << std::endl;
    title = RemoveTag(title);
    std::cout << title << std::endl;
}

void HTMLparser::GetBody(){
    std::regex pattern_start("<body *[^ >]*>");
    web_content = regex_replace(web_content, pattern_start, "_body_start");
    std::regex pattern_end("</body>");
    web_content = regex_replace(web_content, pattern_end, "_body_end");
    int BodyStart = web_content.find("_body_start");
    int BodyEnd = web_content.find("_body_end");
    web_content = web_content.substr(BodyStart, BodyEnd);
    std::regex pattern("<a +[^ >]* *href *=[^<]*</a>");
    std::string::const_iterator iterStart = web_content.begin();
    std::string::const_iterator iterEnd = web_content.end();
    std::smatch result;
    std::string temp;
    while(regex_search(iterStart, iterEnd, result, pattern)){
        temp = result[0];
        int point = temp.find("title=");
        if(point != std::string::npos){
            std::cout << get_title(temp.substr(point, temp.length() - 1))
                      << " "
                      << trans_URLs(temp)
                      << std::endl;

        }
        else{
            std::cout << get_title_1(temp) 
                      << " "
                      << trans_URLs(temp)
                      << std::endl;
        }
        //std::cout << result[0] << std::endl;
        iterStart = result[0].second;
    }


    //std::cout << web_content << std::endl;
}


void HTMLparser::GetImg(){
    std::string temp;
    std::regex pattern("<img *[^>]* *src=[^ >]*");
    std::string::const_iterator iterStart = web_content.begin();
    std::string::const_iterator iterEnd = web_content.end();
    std::smatch result;
    while(regex_search(iterStart, iterEnd, result, pattern)){
        temp = result[0];
        temp = temp.substr(temp.find("src"), temp.length() - 1);
        std::cout << trans_URLs_for_Img(temp) << std::endl;
        iterStart = result[0].second;
    }
}
