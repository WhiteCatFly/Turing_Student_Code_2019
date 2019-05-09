#ifndef HTML_PARSER_H_INCLUDED
#define HTML_PARSER_H_INCLUDED

class HTML_Parser
{
private:
	static const int EXTRACTED_ID = 2;
	static const std::string REGEX_HREF;
	static const int NUM_OF_ACCEPTED_FORMAT = 3;
	static const std::string \
				 list_accepted_format[NUM_OF_ACCEPTED_FORMAT];
	static const int NUM_OF_BANNED_SUBSTR = 3;
	static const std::string \
				 list_banned_substr[NUM_OF_BANNED_SUBSTR];
	const std::string homepage;
	bool is_banned_href(const std::string &href) const;
	bool is_valid_href(const std::string &href) const;
public:
	HTML_Parser(const std::string &homepage__);
	~HTML_Parser(){}
	void extract_href(const std::string &filename,
					  std::vector<std::string> &result) const;
};

#endif