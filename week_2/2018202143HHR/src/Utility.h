#ifndef _MENCI_WEB_CRAWLER_UTILITY_H
#define _MENCI_WEB_CRAWLER_UTILITY_H

#include <string>

bool checkSuffix(const std::string &str, const std::string &pattern);
bool checkPrefix(const std::string &str, const std::string &pattern);

void stringToLower(std::string &str);

#endif // _MENCI_WEB_CRAWLER_UTILITY_H
