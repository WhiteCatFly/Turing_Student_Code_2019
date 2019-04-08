#include<regex>
#include"HTMLparser.h"

std::string get_title(std::string str, std::string p){

    std::string::const_iterator itStart = str.begin();

    std::string::const_iterator itEnd = str.end();

    std::regex pattern(p);

    std::smatch result;

    regex_search(itStart, itEnd, result, pattern);

    std::string temp = result[0];

    temp.pop_back();

    temp = temp.substr(1, temp.length() - 1);

    return temp;


}

void HTMLparser::Ini(){

    std::regex pattern("&nbsp");

    web_content = regex_replace(web_content, pattern, " ");

}



void HTMLparser::GetTitle(){

    std::regex pattern("<title[^ >]*>([^<>]*)</title>");

    std::smatch result;

    tempiter = web_content.begin();

    iterEnd = web_content.end();

    while(regex_search(tempiter, iterEnd, result, pattern)){

        title = result[0];

        tempiter = result[0].second;

    }

    pattern = "<[^ >]*>";

    title = regex_replace(title, pattern, "");

    std::cout << title << std::endl;

}

void HTMLparser::GetBody(){

    std::regex pattern_start("<body *[^ >]*>");

    std::regex pattern_end("</body>");

    std::string web_copy =  regex_replace(web_content, pattern_start, "_body_start");

    web_copy = regex_replace(web_copy, pattern_end, "_body_end");

    web_copy = web_copy.substr(web_copy.find("_body_start"), web_copy.find("_body_end"));

    std::regex pattern("<a +[^ >]* *href *=[^<]*</a>");

    std::smatch result;

    tempiter = web_copy.begin();

    std::string::const_iterator tempiter_1 = web_copy.end();

    while(regex_search(tempiter, tempiter_1, result, pattern)){

        std::string temp = result[0];

        int point = temp.find("title=");

        if(point != std::string::npos){

            std::cout << get_title(temp.substr(point ,temp.length() - 1), "\"[^`]*\"")
                      << " "
                      << trans_URLs(temp, 0)
                      << std::endl;

        }
        else{

            std::cout << get_title(temp, ">[^`]*<")
                      << " "
                      << trans_URLs(temp, 0)
                      << std::endl;
        }

        tempiter = result[0].second;

    }

}

void HTMLparser::GetImg(){

    std::string temp;

    std::regex pattern("<img *[^>]* *src=[^ >]*");

    tempiter = web_content.begin();

    iterEnd = web_content.end();

    std::smatch result;

    while(regex_search(tempiter, iterEnd, result, pattern)){

        temp = result[0];

        temp = temp.substr(temp.find("src"), temp.length() - 1);

        std::string temp_1 = trans_URLs(temp, 1);

        if(Img.count(temp_1) == 0){

            Img.insert(temp_1);

            std::cout << temp_1 << std::endl;

        }

        

        tempiter = result[0].second;

    }
}