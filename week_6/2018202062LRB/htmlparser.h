#ifndef PARSER_H_
#define PARSER_H_

class Parser
{
private:
	std::string website, name;
	std::regex regex_str;
	std::smatch result;
	std::vector<std::string> v;
	std::queue<std::string> q;
	std::map<std::string, bool> mp;
	int type;
	bool toparse, tocrawl;
public:
	Parser();
	Parser(std::string website_, int type_, std::string name_, bool parse_, bool crawl_);
	void init(std::string website_, int type_, std::string name_, bool parse_, bool crawl_);
	~Parser();
	bool set_type();
	void parse();
	void find_append(const std::string now_page);
	void crawl();
	void print_parser();
	void print_crawler();
};

#endif