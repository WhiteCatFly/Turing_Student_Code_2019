#ifndef _UTILITY_H_INCLUDED
#define _UTILITY_H_INCLUDED

bool has_chinese(std::string str);
std::vector<std::string> extract_chinese(std::vector<std::string> text);
void escape_html(std::vector<std::string> &text);

typedef std::vector<std::pair<std::string, std::string> > THULAC_result;
THULAC_result split(std::vector<std::string> text);

#endif