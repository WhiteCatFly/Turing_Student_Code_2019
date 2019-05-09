#ifndef TAG_NODE_H_INCLUDED
#define TAG_NODE_H_INCLUDED
class TagNode {
protected:
	static const char *empty_elements[];
	std::string tag_type;
	std::string tag_content;
	std::vector<std::pair<std::string, std::string>> attributes;
	void parse_attributes();
public:
	TagNode(const std::string tag_type, const std::string tag_content);
	std::string get_type() { return tag_type; }
	std::string get_content() { return tag_content; }
	bool is_empty_element();
	bool is_begin_element();
	bool is_end_element();
};
class TreeTagNode : public TagNode {
private:
	int depth;
	std::vector<TreeTagNode *> child_list;
public:
	TreeTagNode(const std::string tag_type, const std::string tag_content);
	TreeTagNode(const TreeTagNode &copy) : TagNode(copy) {
		depth = copy.depth;
		for (auto child : copy.child_list) {
			TreeTagNode *tmp = new TreeTagNode(*child);
			child_list.push_back(tmp);
		}
	}
	TreeTagNode &operator=(const TreeTagNode &rhs) {
		tag_type = rhs.tag_type;
		tag_content = rhs.tag_content;
		attributes = rhs.attributes;
		depth = rhs.depth;
		for (auto child : child_list) {
			delete child;
		}
		child_list.clear();
		for (auto child : rhs.child_list) {
			TreeTagNode *tmp = new TreeTagNode(*child);
			child_list.push_back(tmp);
		}
	}
	int get_depth() { return depth; }
	void set_depth(const int dep) { depth = dep; }
	void add_child(TreeTagNode *tag) { child_list.push_back(tag); }
	void traversal_print();
	std::vector<std::string> find_tag(std::string tag_name, bool has_found) const;
	std::vector<std::string> find_attribute(std::string attribute_name) const;
	~TreeTagNode() {
		for (auto child : child_list) {
			delete child;
		}
	}
};

#endif