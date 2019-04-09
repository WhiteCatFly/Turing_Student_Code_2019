#ifndef PARSER_H_
#define PARSER_H_

class Parser
{
private:
	std::string website, name;
	std::regex regex_str;
	std::smatch result;
	std::vector<std::string> v;
	int type;
public:
	Parser();
	~Parser();
	void set_type();
	void analyze();
	void print();
};

#endif