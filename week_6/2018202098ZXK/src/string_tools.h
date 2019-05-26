#ifndef STRING_TOOLS_
#define STRING_TOOLS_
#include <string>
#include <utility> 
#include <fstream>


std::string load2text(const std::string &filename);
bool hasPrefix(std::string const &fullString, std::string const &prefix);
bool hasEnding (std::string const &fullString, std::string const &ending);
std::pair <std::string, std::string> splitKeyVal(const std::string &line, char delim);

#endif