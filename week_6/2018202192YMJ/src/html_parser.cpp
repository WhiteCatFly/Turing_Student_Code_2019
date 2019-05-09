#include <cstdio>
#include <cstring>

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "normalizer.h"
#include "url_utility.h"
#include "string_utility.h"
#include "html_parser.h"

const std::string HTML_Parser::REGEX_HREF \
				  = "href=(\"|\')?([^\"\'<> ]*)(\"|\')?";

const std::string \
	  HTML_Parser::list_accepted_format[NUM_OF_ACCEPTED_FORMAT] =
{
	".php",
	".html",
	".asp"
};

const std::string \
	  HTML_Parser::list_banned_substr[NUM_OF_BANNED_SUBSTR] =
{
	"javascript:",
	"mailto:",
	"https://"
};

HTML_Parser::HTML_Parser(const std::string &homepage__):
	homepage(homepage__)
{}

bool HTML_Parser::is_banned_href(const std::string &href) const
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

bool HTML_Parser::is_valid_href(const std::string &href) const
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

void HTML_Parser::extract_href(const std::string &filename,
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
