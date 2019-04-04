#ifndef SPIDER_STRING_
#define SPIDER_STRING_

#include <string>

bool inline hasEnding (std::string const &fullString, std::string const &ending);
bool inline hasPrefix(std::string const &fullString, std::string const &prefix);
std::string parseUrl(std::string const &ori, const std::string &url);
void strReplace(std::string &str, char pre, char tar);

#endif