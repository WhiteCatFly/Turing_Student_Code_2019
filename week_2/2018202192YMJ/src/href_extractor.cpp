#include <cstdio>

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "normalizer.h"
#include "href_extractor.h"

bool is_valid_href(const std::string &href,
				   const std::string &homepage)
{
	if (is_absolute_url(href))
	{
		return href.find(homepage) != std::string::npos;
	}
	return true;
}

void extract_href(const std::string &filename,
				  std::vector<std::string> &result,
				  const std::string &homepage)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		std::string content;
		const std::string REGEX_HREF = "<a[^<>]*?href=\"(http:[^\"]*|[\\da-zA-Z_/]+(.php[^\"]*|.html))\"[^<>]*?>";
		std::regex regex(REGEX_HREF);
		while (getline(fin, content))
		{
			std::smatch match;
			while (std::regex_search(content, match, regex))
			{
				if (is_valid_href(match[1].str(), homepage))
				{
					result.push_back(match[1].str());
				}
				content = match.suffix();
			}
		}
	}
	else
	{
		std::cerr << "error: cannot open file \""
				  << filename << "\"\n";
	}
}
