#include <cstring>

#include <string>
#include <iostream>

#include "normalizer.h"

std::string escape(const std::string &str)
{
	const std::string ESCAPE_CHARACTERS = "\\&()";
	std::string res;
	for (char c: str)
	{
		if (ESCAPE_CHARACTERS.find(c) != std::string::npos)
		{
			res += '\\';
		}
		res += c;
	}
	return res;
}

std::string find_directory(const std::string &url)
{
	auto pos = url.rfind("/");
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

std::string normalize_url(const std::string &homepage,
						  const std::string &cur_url,
						  const std::string &href)
{
	std::string normalized_url;
	if (is_absolute_url(href))
	{
		normalized_url = href.substr(strlen("http://"));
	}
	else if (href[0] == '/')
	{
		normalized_url = homepage + href.substr(1);
	}
	else
	{
		normalized_url = find_directory(cur_url) + href;
	}
	if (href.find(".php") == std::string::npos
		&& href.find(".html") == std::string::npos
		&& href.find(".aspx") == std::string::npos)
	{
		if (*normalized_url.rbegin() != '/') normalized_url += '/';
		normalized_url += "index.php";
	}
	replace_substring(normalized_url, "&amp;", "&");
	return normalized_url;
}
