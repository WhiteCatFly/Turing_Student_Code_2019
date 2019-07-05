#include <regex>
#include <string>
#include <vector>
#include <iostream>

#include "TagNode.h"
#include "Html.h"

const char *TagNode::empty_elements[] = {
	"!DOCTYPE",
	"script",
	"Comment",
	"Text",
	"area",
	"base",
	"br",
	"col",
	"colgroup",
	"command",
	"embed",
	"hr",
	"img",
	"input",
	"keygen",
	"link",
	"meta",
	"param",
	"source",
	"track",
	"wbr"
};

TagNode::TagNode(const std::string type, const std::string content) :
	tag_type(type),
	tag_content(content) {
	parse_attributes();
}

TreeTagNode::TreeTagNode(const std::string type, const std::string content) :
	TagNode(type, content),
	depth(0) {}

bool TagNode::is_empty_element() {
	for (auto tag_name : empty_elements) {
		if (tag_type == tag_name || tag_type == tag_name + '/') return true;
	}
	return false;
}
bool TagNode::is_begin_element() {
	if (is_empty_element()) return false;
	return tag_type[0] != '/';
}
bool TagNode::is_end_element() {
	if (is_empty_element()) return false;
	return tag_type[0] == '/';
}

void TagNode::parse_attributes() {
	if (tag_type == "Text" || tag_type == "Comment") return;
	std::string str = tag_content;
	size_t pos;
	if (tag_type == "script") {
		pos = str.find('>');
		str = str.substr(0, pos + 1);
	}
	else {
		str.erase(str.begin());
		str.erase(str.end() - 1);
		if ((pos = str.find(" ")) != std::string::npos) {
			tag_type = str.substr(0, pos);
			if (is_empty_element() && str[str.size() - 1] == '/') {
				str.erase(str.end() - 1);
			}
			str = str.substr(pos + 1);
		}
		else {
			tag_type = str;
			if (is_empty_element() && str[str.size() - 1] == '/') {
				str.erase(str.end() - 1);
			}
			return;
		}
	}
	const std::regex my_regex("([\\S]+)[\\s]*=[\\s]*(?:\"([\\s\\S]*?)\"|\'([\\s\\S]*?)\'|([\\s\\S]*?)(?: |>))");
	
	std::smatch match;
	std::string::const_iterator search_start = str.cbegin();

	while (std::regex_search(search_start, str.cend(), match, my_regex)) {
        search_start = match.suffix().first;

		std::pair<std::string, std::string> pss;
		pss = std::make_pair(match[1].str(), match[2].str() + match[3].str() + match[4].str());
		attributes.push_back(pss);
    }
}

void TreeTagNode::traversal_print() {
	for (int i = 0; i < depth; i++) std::cout << '\t';
	if (tag_type == "Text" || tag_type == "Comment") {
		std::cout << tag_type << "  " << tag_content << std::endl;
	}
	else if (tag_type == "script") {
		std::cout << "script  " << tag_content << std::endl;
	}
	else {
		std::cout << "TagNode(" << tag_type << ")" << std::endl;
	}
	for (auto attribute : attributes) {
		for (int i = 0; i < depth; i++) std::cout << '\t';
		std::cout << ' ';
		std::cout << "[Attribute] " << attribute.first << " = " << attribute.second << std::endl;
	}
	for (auto child_tag : child_list) child_tag->traversal_print();
}

std::vector<std::string> TreeTagNode::find_tag(std::string tag_name, bool has_found) const{
	std::vector<std::string> ret;
	if (tag_type == tag_name) has_found = true;
	if (has_found && tag_type == "Text") {
		ret.push_back(tag_content);
	}
	for (auto tag : child_list) {
		std::vector<std::string> tmp = tag->find_tag(tag_name, has_found);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}

std::vector<std::string> TreeTagNode::find_attribute(std::string attribute_name) const{
	std::vector<std::string> ret;
	for (auto attribute :attributes) {
		if (attribute.first == attribute_name) {
			ret.push_back(attribute.second);
		}
	}
	for (auto tag : child_list) {
		std::vector<std::string> tmp = tag->find_attribute(attribute_name);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}