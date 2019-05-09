#ifndef HTML_H_INCLUDED
#define HTML_H_INCLUDED
class TagNode;
class Html {
private: 
	std::vector<TreeTagNode *> root_tags;
	std::string html_content;
	std::vector<TreeTagNode *> extract_tag(std::string &str);
	void get_depth(std::vector<TreeTagNode *> &tags);
	void build_tree(std::vector<TreeTagNode *> &tags);
	void erase_blank_text(std::vector<TreeTagNode *> &tags);
public:
	Html() {}
	Html(const std::string save_path);
	Html(const Html &rhs) {
		html_content = rhs.html_content;
		for (auto root : rhs.root_tags) {
			TreeTagNode *tmp = new TreeTagNode(*root);
			root_tags.push_back(tmp);
		}
	}
	Html &operator=(const Html &rhs) {
		for (auto root : root_tags) {
			delete root;
		}
		root_tags.clear();
		html_content = rhs.html_content;
		for (auto root : rhs.root_tags) {
			TreeTagNode *tmp = new TreeTagNode(*root);
			root_tags.push_back(tmp);
		}
	}
	void print();
	std::vector<std::string> parse_title() const;
	std::vector<std::string> parse_text() const;
	std::vector<std::string> parse_href() const;
	~Html() {
		for (auto root : root_tags) {
			delete root;
		}
	}
};

#endif