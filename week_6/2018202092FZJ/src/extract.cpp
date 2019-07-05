#include "crawler.h"

using namespace std;

int Parser::Extract(const std::regex &reg, vector<string> &result){
    string *code = new string;
    smatch s;
    *code = Source_Code;
    result.clear();
    while(regex_search(*code, s, reg)){
        result.push_back(s.str());
        *code = s.suffix().str();
    }
    delete code;
    return result.size();
}

int Parser::Get_Title(vector<string> &result){
    Extract(regex("<title>([^<>]*)</title>"), result);
    for(int i = 0; i < result.size(); i++){
        result[i] = result[i].substr(7, result[i].size() - 14);    
    }
    return result.size();
}

int Parser::Get_Href(vector<string> &result){
    Extract(regex("<a href=\"([^\"']*)"), result);
	for(int i = 0; i < result.size(); i++)
		result[i] = result[i].substr(9, result[i].size() - 10);
	return result.size();
}

int Parser::Get_Body(vector<string> &result){
    int i = 0, j = 0;
	result.clear();
	while((i = Source_Code.find("<body>", j)) != string::npos && (j = Source_Code.find("</body>", i)) != string::npos){
		result.push_back(Source_Code.substr(i + 6, j - i - 6));
	}
	return result.size();
}

int Parser::Get_Img(vector<string> &result){
    Extract(regex("<img src=\"([^\"']*)"), result);
	for(int i = 0; i < result.size(); i++)
		result[i] = result[i].substr(10, result[i].size() - 9);
	return result.size(); 
}