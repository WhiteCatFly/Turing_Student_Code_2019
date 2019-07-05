#ifndef TAG_NODE_H_INCLUDED
#define TAG_NODE_H_INCLUDED
class TagNode {
private:
	static const char *empty_elements[];
	std::string tag_type;
	std::string tag_content;
	std::vector<std::pair<std::string, std::string>> attributes;
	void parse_attributes();
public:
	TagNode(const TagNode &copy) {
		tag_type = copy.tag_type;
		tag_content = copy.tag_content;
	}
	TagNode(const std::string tag_type, const std::string tag_content);
	std::string get_type() { return tag_type; }
	std::string get_content() { return tag_content; }
	bool is_empty_element();
	bool is_begin_element();
	bool is_end_element();
	void erase_eol(std::string &str) const;
    std::vector<std::string> parse_href();
};

#endif