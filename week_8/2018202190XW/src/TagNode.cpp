#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "TagNode.h"

const char *TagNode::empty_elements[] = {
    "!DOCTYPE", "script",   "Comment", "Text",  "area",   "base",  "br",
    "col",      "colgroup", "command", "embed", "hr",     "img",   "input",
    "keygen",   "link",     "meta",    "param", "source", "track", "wbr"};

void TagNode::erase_eol(std::string &str) const {
    std::string ret;
    for (auto c : str) {
        switch (c) {
            case '\n':
                break;
            case '\r':
                break;
            case '\t':
                break;
            default:
                ret += c;
                break;
        }
    }
    str = ret;
}

TagNode::TagNode(const std::string type, const std::string content) {
    tag_type = type;
    std::string tmp = content;
    while (tmp.size() && isspace(tmp[0])) tmp.erase(tmp.begin());
    while (tmp.size() && isspace(tmp[tmp.size() - 1])) tmp.pop_back();
    erase_eol(tmp);
    tag_content = tmp;
    parse_attributes();
}

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
    } else {
        if (str.size()) str.erase(str.begin());
        if (str.size()) str.pop_back();
        if ((pos = str.find(" ")) != std::string::npos) {
            tag_type = str.substr(0, pos);
            if (str.size() && is_empty_element() &&
                str[str.size() - 1] == '/') {
                str.pop_back();
            }
            str = str.substr(pos + 1);
        } else {
            tag_type = str;
            if (str.size() && is_empty_element() &&
                str[str.size() - 1] == '/') {
                str.pop_back();
            }
            return;
        }
    }

    static const std::regex my_regex(
        "([\\S]+?)[\\s]*=[\\s]*(?:\"([\\s\\S]*?)\"|\'([\\s\\S]*?)\'|([\\s\\S]*?"
        ")"
        "(?: |$))");

    std::smatch match;
    std::string::const_iterator search_start = str.cbegin();

    while (std::regex_search(search_start, str.cend(), match, my_regex)) {
        search_start = match.suffix().first;

        std::pair<std::string, std::string> pss;
        pss = std::make_pair(match[1].str(),
                             match[2].str() + match[3].str() + match[4].str());
        attributes.push_back(pss);
    }
}

std::vector<std::string> TagNode::parse_href() {
    std::vector<std::string> ret_val;
    for (auto attribute : attributes) {
        if (attribute.first == "href") {
            ret_val.push_back(attribute.second);
        }
    }
    return ret_val;
}