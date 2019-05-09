#include <sstream>
#include "string_tools.h"

std::string load2text(const std::string &filename){
	using namespace std;
	ifstream in(filename);
	if(!in) return "";
	ostringstream tmp;
	tmp << in.rdbuf();
	return tmp.str();
}

bool hasPrefix(std::string const &fullString, std::string const &prefix){
	if(fullString.length() < prefix.length()) return false;
	return fullString.substr(0, prefix.length()) == prefix;
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

std::pair <std::string, std::string> splitKeyVal(const std::string &line, char delim){
	if(line.find(delim) == std::string::npos) return std::make_pair("", "");
	size_t pos = line.find(delim);
	return std::make_pair(line.substr(0, pos), line.substr(pos+1));
}