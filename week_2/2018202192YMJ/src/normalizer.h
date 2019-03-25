#ifndef NORMALIZER_H_INCLUDED
#define NORMALIZER_H_INCLUDED

inline bool is_absolute_url(const std::string &href)
{
	return href.find("http://") == 0;
}

std::string escape(const std::string &str);
std::string find_directory(const std::string &url);
std::string normalize_url(const std::string &homepage,
						  const std::string &cur_url,
						  const std::string &href);

#endif