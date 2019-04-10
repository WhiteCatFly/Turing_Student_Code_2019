#include <cstdio>
#include <cstring>

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "normalizer.h"
#include "url_utility.h"
#include "href_extractor.h"

const std::string Href_Extractor::REGEX_HREF \
				  = "href=(\"|\')?([^\"\'<> ]*)(\"|\')?";
const std::string \
	  Href_Extractor::list_accepted_format[NUM_OF_ACCEPTED_FORMAT] =
{
	".php",
	".html",
	".asp"
};
const std::string \
	  Href_Extractor::list_banned_substr[NUM_OF_BANNED_SUBSTR] =
{
	"javascript:",
	"mailto:",
	"https://"
};

Href_Extractor::Href_Extractor(const std::string &homepage__) :
	homepage(homepage__)
{}

bool Href_Extractor::is_banned_href(const std::string &href) const
{
	for (int i = 0; i < NUM_OF_BANNED_SUBSTR; ++i)
	{
		if (href.find(list_banned_substr[i]) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

bool Href_Extractor::is_valid_href(const std::string &href) const
{
	if (is_banned_href(href))
	{
		return false;
	}
	if (is_absolute_url(href)
		&& href.find(homepage) == std::string::npos)
	{
		return false;
	}
	int pos_dot;
	std::string file_name;
	file_name = file_name_of_url(href);
	if ((pos_dot = file_name.find('.')) != std::string::npos)
	{
		for (int i = 0; i < NUM_OF_ACCEPTED_FORMAT; ++i)
		{
			if (file_name.substr(pos_dot, list_accepted_format[i].size())
				== list_accepted_format[i])
			{
				return true;
			}
		}
		return false;
	}
	return true;
}

void Href_Extractor::extract_href(const std::string &filename,
								  std::vector<std::string> &result) const
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		std::string content;
		std::regex regex(REGEX_HREF);
		while (getline(fin, content))
		{
			std::smatch match;
			while (std::regex_search(content, match, regex))
			{
				if (is_valid_href(match[EXTRACTED_ID].str()))
				{
					result.push_back(match[EXTRACTED_ID].str());
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
