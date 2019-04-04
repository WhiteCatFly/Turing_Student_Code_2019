#ifndef _FIND_APPEND_H_
#define _FIND_APPEND_H_

class append_finder
{
private:
	std::regex regex_str;
	std::smatch result;
public:
	append_finder();
	~append_finder();
	void find_append(std::queue<std::string> &q, std::map<std::string, bool> &mp, std::ifstream &fin, const std::string now_page, const std::regex regex_str_homepage);
};

#endif