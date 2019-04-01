#include <string>
#include <regex>

#include "my_string.h"
#include "bfs.h"

std::string normalize_url(std::string str, std::string &f_url)
{
    std::string empty_str = ""; 
	if(str[str.size()-2] == '/') 
		str = str.substr(6, str.size() - 8);
	else
		str = str.substr(6, str.size() - 7);

    for(auto s : black_sub_list)
    {
        if(str.find(s) != std::string::npos)
        {
            return empty_str;
        }
    }
    if(str.substr(0, root_url.length()) == root_url) 
		return str;
	if(str.substr(0, 7) == "http://" ||
	   str.substr(0, 8) == "https://")
		return empty_str; // empty
	
	if(str[0] == '/') 
		return root_url + str.substr(1);


    std::size_t found = f_url.find_last_of("/");
	return f_url.substr(0, found + 1) + str;
}

void parse_html(std::string *content, std::string &f_url)
{
    std::sregex_iterator it(content->begin(),
                            content->end(),
                            re_href),
                         end;
    for(; it != end; it++)
    {
        std::string next_url = normalize_url(it->str(), f_url);
        if(!next_url.empty())
            push_into_waiting(next_url);
    }

}

