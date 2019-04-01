#ifndef URL_PARSER_H_INCLUDED
#define URL_PARSER_H_INCLUDED

std::string normalize(const std::string &domain, const std::string &current_url, std::string pre_url);
void extract_url(const std::string &domain, const std::string &current_url, const std::string &savepath, std::vector<std::string> &target);

#endif