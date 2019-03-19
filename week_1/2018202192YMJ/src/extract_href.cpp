#include <cstdio>

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::string> extract_href_from_string(std::string content)
{
	std::regex regex("<a [^<>]*href=\"(http://info.ruc.edu.cn/[^\"]*|[\\da-zA-Z_/]+(.php[\\da-zA-Z\\?&=]*|.html))\"[^<>]*>");
	std::smatch match;
	std::vector<std::string> extracted_url;
	while (std::regex_search(content, match, regex))
	{
		extracted_url.push_back(match[1].str());
		content = match.suffix();
	}
	return extracted_url;
}

std::vector<std::string> extract_href_from_file(std::string filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		std::string content;
		int c;
		while ((c = fin.get()) != EOF)
		{
			content += c;
		}
		return extract_href_from_string(content);
	}
	else
	{
		std::cerr << "error: cannot open file \"" << filename << "\"" << "\n";
		return std::vector<std::string>();
	}
}
