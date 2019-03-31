#ifndef NORMALIZER_H_INCLUDED
#define NORMALIZER_H_INCLUDED

class Normalizer
{
private:
	static const std::string HTTP;
	static const std::string CUR_INDICATOR;
	static const std::string PREV_INDICATOR;
	static const int NUM_OF_UNNEEDED_SUF = 2;
	static const std::string list_unneeded_suf[NUM_OF_UNNEEDED_SUF];
	static const int NUM_OF_REPLACE = 1;
	using pr_ss = std::pair<std::string, std::string>;
	static const pr_ss list_replace[NUM_OF_REPLACE];
	const std::string homepage;
public:
	Normalizer(const std::string &homepage__);
	~Normalizer(){}
	std::string normalize_href(const std::string &href) const;
	std::string normalize_url(const std::string &cur_url,
							  const std::string &href) const;
};

#endif