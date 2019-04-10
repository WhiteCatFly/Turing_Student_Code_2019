#include<regex>
#include<string>
#include<iostream>
#include<set>
#include<fstream>
#include<queue>
#include<fstream>

#define SIZE_OF_STRING 32

std::string trans_URLs(std::string root, std::string url, std::set<std::string> &label);

std::string Get_Source_Code(std::string url);

void insert_URLs(std::string url, std::string source_code, std::set<std::string>& temp, std::queue<std::string>& tempqueue, std::set<std::string>& label);

inline bool filter_true(const std::string result);

inline bool filter_false(const std::string result);

const std::string filter_true1[] = {"ruc", "info"};
const std::string filter_false1[] = {"doc", "docx", "pdf", "mp3", "mp4", "xls", "xlsx", "pptx"};