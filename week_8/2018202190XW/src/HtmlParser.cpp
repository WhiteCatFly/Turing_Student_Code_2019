#include <malloc.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

#include "TagNode.h"
#include "HtmlParser.h"

HtmlParser::HtmlParser(const std::string savepath) {
    std::ifstream ifstrm(savepath);
    std::getline(ifstrm, url);
    std::string line;
    while (std::getline(ifstrm, line)) html_content += line;
    tags = extract_tag(html_content);
    erase_empty_tags();
}

std::vector<TagNode *> HtmlParser::extract_tag(std::string &str) {
    std::vector<TagNode *> tags;
    static const std::regex my_regex(
        "(<script[\\s\\S]*?</script>)|(<!-->)|(<!--[^>]*?-->)|(<[^>]*?>)");
    std::smatch match;
    std::string::const_iterator search_start = str.cbegin();

    while (std::regex_search(search_start, str.cend(), match, my_regex)) {
        search_start = match.suffix().first;

        std::ssub_match unmatched = match.prefix();
        if (unmatched.length() > 0) {
            TagNode *tag = new TagNode("Text", unmatched.str());
            tags.push_back(tag);
        }

        std::string matched =
            match[1].str() + match[2].str() + match[3].str() + match[4].str();
        TagNode *tag;
        if (match[1].str().size()) {
            tag = new TagNode("script", matched);
        } else if (match[2].str().size() || match[3].str().size()) {
            tag = new TagNode("Comment", matched);
        } else {
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

void HtmlParser::erase_empty_tags() {
    std::vector<TagNode *> tmp;
    for (auto tag : tags) {
        if (tag->get_type() != "Text" || tag->get_content().size()) {
            tmp.push_back(tag);
        }
    }
    tags = tmp;
}

std::vector<std::string> HtmlParser::parse_text() const {
    std::vector<std::string> ret_val;
    for (auto tag : tags) {
        if (tag->get_type() == "Text") {
            ret_val.push_back(tag->get_content());
        }
    }
    return ret_val;
}
std::vector<std::string> HtmlParser::parse_href() const {
    std::vector<std::string> ret_val;
    for (auto tag : tags) {
        std::vector<std::string> tmp = tag->parse_href();
        ret_val.insert(ret_val.end(), tmp.begin(), tmp.end());
    }
    return ret_val;
}

std::string HtmlParser::parse_title() const {
    std::string ret_val;
    for (int i = 0; i < tags.size(); i++) {
        if (tags[i]->get_type() == "title") {
            for (int j = i; j < tags.size(); j++) {
                if (tags[j]->get_type() == "/title") {
                    for (int k = i; k <= j; k++)
                        if (tags[k]->get_type() == "Text") {
                            ret_val += tags[k]->get_content();
                        }
                }
            }
        }
    }
    return ret_val;
}