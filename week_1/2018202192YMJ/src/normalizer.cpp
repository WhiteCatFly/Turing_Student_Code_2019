#include <cstring>

#include <string>
#include <iostream>

bool is_absolute(std::string href)
{
	return href.find("http://") == 0;
}

std::string find_directory(std::string url)
{
	auto pos = url.rfind("/");
	return url.substr(0, pos + 1);
}

std::string normalize_url(std::string cur_url, std::string href)
{
	extern std::string homepage;
	std::string normalized_url;
	if (is_absolute(href))
	{
		normalized_url = href.substr(strlen("http://"));
	}
	else if (href[0] == '/')
	{
		normalized_url = homepage + href;
	}
	else
	{
		normalized_url = find_directory(cur_url) + href;
	}
	if (href.find(".php") == std::string::npos
		&& href.find(".html") == std::string::npos)
	{
		normalized_url += '/';
		if (*normalized_url.rbegin() == '/' && *(++normalized_url.rbegin()) == '/')
		{
			normalized_url.resize(normalized_url.size() - 1);
		}
		normalized_url += "index.php";
	}
	for (int i = 0; i < normalized_url.size(); ++i)
	{
		if (normalized_url.substr(i, 5) == "&amp;")
		{
			normalized_url = normalized_url.substr(0, i) + "&" + normalized_url.substr(i + 5);
		}
	}
	return normalized_url;
}
