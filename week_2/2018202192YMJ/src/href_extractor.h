#ifndef HREF_EXTRACTOR_H_INCLUDED
#define HREF_EXTRACTOR_H_INCLUDED

bool is_valid_href(const std::string &href,
				   const std::string &homepage);
void extract_href(const std::string &filename,
				  std::vector<std::string> &result,
				  const std::string &homepage);

#endif