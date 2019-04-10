#ifndef HTML_H_INCLUDED
#define HTML_H_INCLUDED
class TagNode;
class Html {
private: 
	std::vector<TagNode *> root_tags;
	std::string html_content;
	std::vector<TagNode *> extract_tag(std::string &str);
	void get_depth(std::vector<TagNode *> &tags);
	void build_tree(std::vector<TagNode *> &tags);
	void erase_blank_text(std::vector<TagNode *> &tags);
public:
	Html() {}
	Html(Url url, std::string save_file_folder);
	Html(const std::string save_path);
	void print();
	void parse_title();
	void parse_text();
	void parse_href();
};

#endif