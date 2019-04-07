#include"crawler.h"

inline std::string restrict_(std::string url){  //url格式化小函数
    while(url.back()> 'z'|| url.back() < '0'){
        url.pop_back();
    }
    return url;
}

void Crawler::ParseURLs(){  

    std::string temp_2;

    int point = web_content.find("location.href"); //处理跳转

    bool if_ = false;

    if(point != std::string::npos){

        for(int k = 0; k < 2; point ++){

            if(web_content[point] == '\"'){

                if_ = !if_;

                k ++;

            }

            if(if_){

                temp_2 += web_content[point];

            }

        }

        temp_2 += '\"';

        if(temp_2.find("http") != std::string::npos){

            point = temp_2.find("http");

            temp_2 = temp_2.substr(point, temp_2.size() - 1);

        }

    }

    std::regex pattern("<a +[^ >]* *href *= *'*\"*[^ >]*'*\"*");

    std::string::const_iterator iterStart = web_content.begin();

    std::string::const_iterator iterEnd = web_content.end();

    std::string temp;

    std::string temp_copy;

    std::smatch result;

    if(!temp_2.empty()){

        if(current_url.back() != '/')

        current_url += '/';

        temp_copy = trans_URLs(temp_2);

        if(current_url.back() == '/')

        current_url = current_url.substr(0, current_url.size() - 2);

        temp_copy = restrict_(temp_copy);

        if(final_results.count(temp_copy) == 0 && temp_copy.find(".css") == std::string::npos){

            final_results.insert(temp_copy);

            temp_results.push(temp_copy);

        }

        std::cout << "Inserting " << temp_copy << std::endl;

    }

    while(regex_search(iterStart, iterEnd, result, pattern)){

        temp = result[0];

        temp_copy = trans_URLs(temp);

        if(!final_results.count(temp_copy) && !temp_copy.find("econ") && temp_copy.find(";")){
            
            final_results.insert(temp_copy);

            temp_results.push(temp_copy);

            std::cout << "Inserting " << temp_copy << std::endl;

        }

        iterStart = result[0].second;
    }

}