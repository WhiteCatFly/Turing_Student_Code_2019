#include<regex>
#include<string>
#include<iostream>
#include<set>
#include<fstream>
#include<queue>
#include<fstream>

std::string trans_URLs(std::string root, std::string url, std::set<std::string> &label);

std::string Get_Source_Code(std::string url);

void insert_URLs(std::string url, std::string source_code, std::set<std::string>& temp, std::queue<std::string>& tempqueue, std::set<std::string>& label);

