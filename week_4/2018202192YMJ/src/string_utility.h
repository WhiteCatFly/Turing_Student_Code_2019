#ifndef STRING_UTILITY_H_INCLUDED
#define STRING_UTILITY_H_INCLUDED

inline bool char_is_quotation(char c)
{
    return c == '"' || c == '\'';
}
bool string_begin_with(const std::string &str,
                       const std::string &sub);
bool string_end_with(const std::string &str,
                     const std::string &sub);
bool string_has_contents(const std::string &str);

std::string string_remove_space(const std::string &str);
std::string string_remove_extra_space(const std::string &str);
std::string string_first_part(const std::string &str);
std::string string_escape_tab_newline(const std::string &str);

void string_remove_suf(std::string &str,
                       const std::string &sub);

#endif