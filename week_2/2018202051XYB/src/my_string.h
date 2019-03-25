#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <string>
#include <regex>

const std::string black_sub_list[] = {
    ".css", ".js", ".png", ".jpg", ".jpeg", ".ico", ".mp4", ".mp3", ".flv",
    ".xls", ".xlsx", ".doc", ".ppt", ".docx", ".pptx", ".rar", ".zip", ".7z", ".pdf",
    "mailto", //"javascript",
    //"download.php", // file download
};

std::string normalize_url(std::string str, std::string &f_url);

const std::regex re_href("href=\"(.*?)\"");
void parse_html(std::string *content, std::string &f_url);



#endif