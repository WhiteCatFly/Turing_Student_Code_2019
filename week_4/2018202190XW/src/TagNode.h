#ifndef TAG_NODE_H_INCLUDED
#define TAG_NODE_H_INCLUDED
class TagNode {
private:
	static const char *empty_elements[];
	int depth;
	std::string tag_type;
	std::string tag_content;
	std::vector<std::pair<std::string, std::string>> attributes;
	std::vector<TagNode *> child_list;
	void parse_attributes();
public:
	TagNode(const TagNode &copy) {
		depth = copy.depth;
		tag_type = copy.tag_type;
		tag_content = copy.tag_content;
	}
	TagNode(const std::string tag_type, const std::string tag_content);
	std::string get_type() { return tag_type; }
	int get_depth() { return depth; }
	std::string get_content() { return tag_content; }
	bool is_empty_element();
	bool is_begin_element();
	bool is_end_element();
	void set_depth(const int dep) { depth = dep; }
	void add_child(TagNode * tag) { child_list.push_back(tag); }
	void traversal_print();
	void find_tag(std::string tag_name, bool has_found);
	void find_attribute(std::string attribute_name);
};

#endif