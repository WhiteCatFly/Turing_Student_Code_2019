#include <regex>
#include <stack>
#include <string>
#include <cctype>
#include <vector>
#include <malloc.h>
#include <fstream>
#include <iostream>

#include "StringModify.h"
#include "Url.h"
#include "TagNode.h"
#include "Html.h"

Html::Html(const std::string savepath) {
	std::ifstream ifstrm(savepath);
	std::string line;
	while (std::getline(ifstrm, line)) html_content += line + '\n';
	escape_blank(html_content);
	std::vector<TagNode *> tags = extract_tag(html_content);
	erase_blank_text(tags);
	get_depth(tags);
	build_tree(tags);
}
Html::Html(Url url, std::string save_file_folder) {
	std::string savepath = url.get_savepath();
	savepath = save_file_folder + savepath;

	const std::string command_prefix = "wget -t5 -T5 -o wget.log -O ";
	std::string current_command = command_prefix + escape_url(savepath) + " " + escape_url(url.get_path());
	int ret_value = system(current_command.c_str());
	*this = Html(savepath);
}

std::vector<TagNode *> Html::extract_tag(std::string &str) {
	std::vector<TagNode *> tags;
	static const std::regex my_regex("(<script[\\s\\S]*?</script>)|(<!-->)|(<!--[^>]*?-->)|(<[^>]*?>)");
	std::smatch match;
	std::string::const_iterator search_start = str.cbegin();

	while (std::regex_search(search_start, str.cend(), match, my_regex)) {
        search_start = match.suffix().first;

        std::ssub_match unmatched = match.prefix();
        if (unmatched.length() > 0) {
			TagNode *tag = new TagNode("Text", unmatched.str());
            tags.push_back(tag);
        }

        std::string matched = match[1].str() + match[2].str() + match[3].str() + match[4].str();
		TagNode *tag;
		if (match[1].str().size()) {
			tag = new TagNode("script", matched);
		}
		else if (match[2].str().size() || match[3].str().size()) {
			tag = new TagNode("Comment", matched);
		}
		else {
			tag = new TagNode("Tag", matched);
		}
		tags.push_back(tag);
    }
	if (search_start != str.cend()) {
		std::string content;
		content.assign(search_start, str.cend());
		TagNode *tag = new TagNode("Text", content);
        tags.push_back(tag);
    }
	return tags;
}

void Html::erase_blank_text(std::vector<TagNode *> &tags) {
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

void Html::get_depth(std::vector<TagNode *> &tags) {
	int now_dep = 0;
	for (auto tag : tags) {
		if (tag->is_end_element()) now_dep--;
		tag->set_depth(now_dep);
		if (tag->is_begin_element()) now_dep++;
	}
}

void Html::build_tree(std::vector<TagNode *> &tags) {
	std::stack<TagNode *> tag_stack;
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

void Html::parse_title() {
	for (auto root_tag : root_tags) {
		root_tag->find_tag("title", 0);
	}
}
void Html::parse_text() {
	for (auto root_tag : root_tags) {
		root_tag->find_tag("Text", 0);
	}
}

void Html::parse_href() {
	for (auto root_tag : root_tags) {
		root_tag->find_attribute("href");
	}
}