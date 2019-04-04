#ifndef STRING_TOOLS_
#define STRING_TOOLS_
#include <string>
#include <fstream>

std::string load2text(const std::string &filename);
bool hasPrefix(std::string const &fullString, std::string const &prefix);
bool hasEnding (std::string const &fullString, std::string const &ending);
void strReplace(std::string &str, char pre, char tar);


#endif