#include <cctype>
#include <cstring>

#include <string>
#include <iostream>

#include "url_utility.h"
#include "normalizer.h"

const std::string Normalizer::HTTP = "http://";
const std::string Normalizer::CUR_INDICATOR = "./";
const std::string Normalizer::PREV_INDICATOR = "../";
const std::string \
	  Normalizer::list_unneeded_suf[NUM_OF_UNNEEDED_SUF] =
{
	"index.php",
	"default.asp"
};
const Normalizer::pr_ss Normalizer::list_replace[NUM_OF_REPLACE] =
{
	std::make_pair("&amp;", "&")
};

Normalizer::Normalizer(const std::string &homepage__) :
	homepage(homepage__)
{}

std::string Normalizer::normalize_href(const std::string &href) const
{
	if (is_absolute_url(href))
	{
		return HTTP + normalize_href(href.substr(HTTP.size()));
	}
	if (is_pref(CUR_INDICATOR, href))
	{
		return normalize_href(href.substr(CUR_INDICATOR.size()));
	}
	std::string normalized_href;
	for (int i = 0; i < (int) href.size(); ++i)
	{
		if (href[i] == '/' && href[i-1] == '/')
		{
			continue;
		}
		normalized_href += href[i];
	}
	while (isspace(*normalized_href.rbegin()))
	{
		normalized_href.erase(--normalized_href.end());
	}
	return normalized_href;
}

std::string Normalizer::normalize_url(const std::string &cur_url,
									  const std::string &href) const
{
	std::string normalized_url;
	std::string normalized_href = normalize_href(href);
	remove_char_to_end(normalized_href, '#');
	if (is_pref(PREV_INDICATOR, href))
	{
		return normalize_url(prev_directory(cur_url),
							 href.substr(PREV_INDICATOR.size()));
	}
	if (is_absolute_url(normalized_href))
	{
		normalized_url = normalized_href.substr(HTTP.size());
	}
	else if (normalized_href[0] == '/')
	{
		normalized_url = homepage + normalized_href.substr(strlen("/"));
	}
	else
	{
		normalized_url = find_directory(cur_url) + normalized_href;
	}
	for (int i = 0; i < NUM_OF_UNNEEDED_SUF; ++i)
	{
		remove_suf(normalized_url, list_unneeded_suf[i]);
	}
	for (int i = 0; i < NUM_OF_REPLACE; ++i)
	{
		replace_substring(normalized_url,
						  list_replace[i].first,
						  list_replace[i].second);
	}
	if (file_name_of_url(normalized_url).find('.') == std::string::npos
		&& *normalized_url.rbegin() != '/')
	{
		normalized_url += '/';
	}
	return normalized_url;
}
