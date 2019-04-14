#include "html_parser.h"

html_parser::html_parser() {}

html_parser::html_parser(string input_str)
{
	this->source_str = input_str;
}

html_parser::html_parser(string file_name, int arg)
{
	ifstream fp;
	fp.open(file_name.c_str());
	char temp_str[this->MAX_STR] = {0};
	while(fp.getline(temp_str, this->MAX_STR)) {
		this->source_str.append(string(temp_str));
		this->source_str.append(" ");
		memset(temp_str, 0 ,sizeof(temp_str));
	}
}

html_parser::~html_parser() {}
