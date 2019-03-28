#include "spiderString.h"

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

std::string parseUrl(std::string const &ori, const std::string &url){
	using std::string;
	string base = "http://info.ruc.edu.cn/";

	//std::cout << "Input to parseUrl " << url << "\n";

	if(hasPrefix(url, "mailto")) return base;
	if(url[0] == ';') return base;

	string suffixs[9] = {".css", ".docx", ".doc", ".xls", ".xlsx", ".pdf", "rar", ".flv", ".png"}; // filter by suffix
	for(int i = 0; i < 9; i++){
		if(hasEnding(url, suffixs[i])) return base;
	}
	if(hasPrefix(url, "http")){
		if(hasPrefix(url, "http://info.ruc.edu.cn/")) return url;
		else return base;
	}
	
	if(url[0] == '/') return "http://info.ruc.edu.cn" + url;
	int pos = ori.rfind("/");
	return ori.substr(0, pos+1) + url;
}

void strReplace(std::string &str, char pre, char tar){
	int i;
	int len = str.length();
	for(i = 0; i < len; i++){
		if(str[i] == pre)
			str[i] = tar;
	}
}