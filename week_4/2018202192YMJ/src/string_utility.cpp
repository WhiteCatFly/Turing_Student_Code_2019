#include <cstring>

#include <string>
#include <sstream>

#include "string_utility.h"

bool string_begin_with(const std::string &str,
                       const std::string &sub)
{
    return str.size() >= sub.size()
           && str.substr(0, sub.size()) == sub;
}

bool string_end_with(const std::string &str,
                     const std::string &sub)
{
    return str.size() >= sub.size()
           && str.substr(str.size() - sub.size()) == sub;
}

bool string_has_contents(const std::string &str)
{
    for (char c: str)
    {
        if (!isspace(c))
        {
            return true;
        }
    }
    return false;
}

std::string string_remove_space(const std::string &str)
{
    std::string res;
    for (char c: str) if (!isspace(c))
    {
        res += c;
    }
    return res;
}

std::string string_remove_extra_space(const std::string &str)
{
    std::string res;
    for (int i = 0; i < (int) str.size(); ++i)
    {
        char c = str[i];
        if (isspace(c) && 
            ((i + 1 < (int) str.size() && str[i+1] == '=')
             || (i > 0 && str[i-1] == '=')))
        {
            continue;
        }
        res += c;
    }
    return res;
}

std::string string_first_part(const std::string &str)
{
    std::stringstream strm(str);
    std::string res;
    strm >> res;
    return res;
}

std::string string_escape_tab_newline(const std::string &str)
{
    std::string res;
    for (char c: str)
    {
        if (c == '\n')
        {
            res += "\\n";
        }
        else if (c == '\r')
        {
            res += "\\t";
        }
        else if (c == '\t')
        {
            res += "\\t";
        }
        else
        {
            res += c;
        }
    }
    return res;
}

void string_remove_suf(std::string &str,
                       const std::string &sub)
{
    if (string_end_with(str, sub))
    {
        str.resize(str.size() - sub.size());
    }
}