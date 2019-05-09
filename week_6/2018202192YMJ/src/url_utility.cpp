#include <cctype>
#include <cstring>

#include <string>

#include "url_utility.h"

std::string escape(const std::string &str)
{
	const std::string ESCAPE_CHARACTERS = "\\&()";
	std::string escaped_str;
	for (char c: str)
	{
		if (ESCAPE_CHARACTERS.find(c) != std::string::npos)
		{
			escaped_str += '\\';
		}
		escaped_str += c;
	}
	return escaped_str;
}

std::string find_directory(const std::string &url)
{
	auto pos = url.rfind("/");
	return url.substr(0, pos + 1);
}

std::string prev_directory(std::string url)
{
	auto pos = url.rfind("/");
	url = url.substr(0, pos);
	pos = url.rfind("/");
	return url.substr(0, pos + 1);
}

void replace_substring(std::string &str,
					   const std::string &tar,
					   const std::string &substitute)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str.substr(i, tar.size()) == tar)
		{
			str = str.substr(0, i) + substitute
				  + str.substr(i + tar.size());
		}
	}
}

void remove_suf(std::string &str, const std::string &suf)
{
	if (is_suf(suf, str))
	{
		str.resize(str.size() - suf.size());
	}
}

void remove_char_to_end(std::string &str, char c)
{
	int pos;
	if ((pos = str.find(c)) != std::string::npos)
	{
		str.erase(pos, str.size() - pos);
	}
}
