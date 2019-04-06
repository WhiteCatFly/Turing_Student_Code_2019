#ifndef HREF_EXTRACTOR_H_INCLUDED
#define HREF_EXTRACTOR_H_INCLUDED

class Href_Extractor
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
	Href_Extractor(const std::string &homepage__);
	~Href_Extractor(){}
	void extract_href(const std::string &filename,
					  std::vector<std::string> &result) const;
};

#endif