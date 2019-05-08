#ifndef URL_UTILITY_H_INCLUDED
#define URL_UTILITY_H_INCLUDED

inline bool is_absolute_url(const std::string &href)
{
	const std::string HTTP = "http://";
	return href.find(HTTP) == 0;
}

inline bool is_pref(const std::string &pref, const std::string &str)
{
	return str.size() >= pref.size()
		   && str.substr(0, pref.size()) == pref;
}

inline bool is_suf(const std::string &suf, const std::string &str)
{
	return str.size() >= suf.size()
		   && str.substr(str.size() - suf.size()) == suf;
}

inline std::string file_name_of_url(const std::string &url)
{
	return url.substr(url.rfind('/') + 1);
}

std::string escape(const std::string &str);
std::string find_directory(const std::string &url);
std::string prev_directory(std::string url);
void replace_substring(std::string &str,
					   const std::string &tar,
					   const std::string &substitute);
void remove_suf(std::string &str, const std::string &suf);
void remove_char_to_end(std::string &str, char c);

#endif