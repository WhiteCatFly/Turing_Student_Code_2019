#include <regex>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <malloc.h>
#include <fstream>
#include <iostream>

#include "StringModify.h"
#include "TagNode.h"
#include "Html.h"

Html::Html(const std::string savepath) {
	std::ifstream ifstrm(savepath);
	std::string line;
	while (std::getline(ifstrm, line)) html_content += line + '\n';
	escape_blank(html_content);
	std::vector<TreeTagNode *> tags = extract_tag(html_content);
	erase_blank_text(tags);
	get_depth(tags);
	build_tree(tags);
}

std::vector<TreeTagNode *> Html::extract_tag(std::string &str) {
	std::vector<TreeTagNode *> tags;
	static const std::regex my_regex("(<script[\\s\\S]*?</script>)|(<!-->)|(<!--[^>]*?-->)|(<[^>]*?>)");
	std::smatch match;
	std::string::const_iterator search_start = str.cbegin();

	while (std::regex_search(search_start, str.cend(), match, my_regex)) {
        search_start = match.suffix().first;

        std::ssub_match unmatched = match.prefix();
        if (unmatched.length() > 0) {
			TreeTagNode *tag = new TreeTagNode("Text", unmatched.str());
            tags.push_back(tag);
        }

        std::string matched = match[1].str() + match[2].str() + match[3].str() + match[4].str();
		TreeTagNode *tag;
		if (match[1].str().size()) {
			tag = new TreeTagNode("script", matched);
		}
		else if (match[2].str().size() || match[3].str().size()) {
			tag = new TreeTagNode("Comment", matched);
		}
		else {
			tag = new TreeTagNode("Tag", matched);
		}
		tags.push_back(tag);
    }
	if (search_start != str.cend()) {
		std::string content;
		content.assign(search_start, str.cend());
		TreeTagNode *tag = new TreeTagNode("Text", content);
        tags.push_back(tag);
    }
	return tags;
}

void Html::erase_blank_text(std::vector<TreeTagNode *> &tags) {
	for (auto iter = tags.begin(); iter != tags.end();) {
		if ((*iter)->get_type() == "Text") {
			bool is_blank = true;
			std::string content = (*iter)->get_content();
			for (auto c : content) {
				if (c != '\\' && c != ' ' && c != 't' && c != 'n' && c != 'r') {
					is_blank = false;
					break;
				}
			}
			if (is_blank) {
				for (int i = 0; i < content.size(); i++) {
					if (content[i] == ' ') continue;
					else if (content[i] == '\\') {
						if (i == content.size() - 1 || content[i + 1] == '\\') {
							is_blank = false;
							break;
						}
					}
					else {
						if (i == 0 || content[i - 1] != '\\') {
							is_blank = false;
							break;
						}
					}
				}
			}
			if (is_blank) {
				tags.erase(iter);
			}
			else iter++;
		}
		else iter++;
	}
}

void Html::get_depth(std::vector<TreeTagNode *> &tags) {
	int now_dep = 0;
	for (auto tag : tags) {
		if (tag->is_end_element()) now_dep--;
		tag->set_depth(now_dep);
		if (tag->is_begin_element()) now_dep++;
	}
}

void Html::build_tree(std::vector<TreeTagNode *> &tags) {
	std::stack<TreeTagNode *> tag_stack;
	for (auto tag : tags) {
		if (tag->is_end_element()) {
			if (!tag_stack.empty()) tag_stack.pop();
			continue;
		}
		if (tag_stack.empty()) {
			root_tags.push_back(tag);
		}
		else tag_stack.top()->add_child(tag);
		if (tag->is_begin_element()) {
			tag_stack.push(tag);
		}
	}
}

void Html::print() {
	for (auto root_tag : root_tags) {
		root_tag->traversal_print();
	}
}

std::vector<std::string> Html::parse_title() const{
	std::vector<std::string> ret;
	for (auto root_tag : root_tags) {
		std::vector<std::string> tmp = root_tag->find_tag("title", 0);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}
std::vector<std::string> Html::parse_text() const{
	std::vector<std::string> ret;
	for (auto root_tag : root_tags) {
		std::vector<std::string> tmp = root_tag->find_tag("Text", 0);
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}

std::vector<std::string> Html::parse_href() const{
	std::vector<std::string> ret;
	for (auto root_tag : root_tags) {
		std::vector<std::string> tmp = root_tag->find_attribute("href");
		ret.insert(ret.end(), tmp.begin(), tmp.end());
	}
	return ret;
}