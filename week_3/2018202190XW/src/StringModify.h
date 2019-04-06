#ifndef STRING_MODIFY_H_INCLUDED
#define STRING_MODIFY_H_INCLUDED

std::string replace_sub_string(const std::string &str, const std::string old_s, const std::string new_s);
void replace_char(std::string &str, const char old_c, const char new_c);
std::string escape_url(const std::string &pre_url);
void modify_savepath(std::string &pre_url);

#endif
