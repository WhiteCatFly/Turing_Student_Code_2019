#include <algorithm>
#include <cmath>
#include <iostream>  //
#include <map>
#include <set>
#include <string>
#include <vector>

#include "TagNode.h"
#include "HtmlParser.h"
#include "PositionIndex.h"
#include "Utility.h"

PositionIndex::PositionIndex(const std::vector<std::string> &page_names) {
    num_of_page = page_names.size();
    for (auto page : page_names) {
        HtmlParser html(page);
        std::string url = html.get_url();
        title[url] = html.parse_title();
        std::vector<std::string> text = html.parse_text();
        std::vector<std::string> chinese_text = extract_chinese(text);
        escape_html(chinese_text);
        THULAC_result result = split(chinese_text);

        std::set<std::string> appear_words;
        for (auto word : result) {
            content[url].push_back(word.first);
            appear_words.insert(word.first);
        }

        for (int i = 0; i < result.size(); i++) {
            std::string word = result[i].first;
            //if (!has_chinese(word)) continue;
            if (terms[word].empty() || (*terms[word].rbegin()).first != url) {
                terms[word].push_back(std::make_pair(url, std::vector<int>()));
            }
            (*terms[word].rbegin()).second.push_back(i);
        }
        for (auto word : appear_words) {
            df[word]++;
        }
    }
    for (auto term : terms) {
        std::string word = term.first;
        idf[word] = log((double)num_of_page / df[word]) / log(10.0);
    }
}

bool cmp(DocMatchInfo lhs, DocMatchInfo rhs) { return lhs.tf_idf > rhs.tf_idf; }

std::pair<int, std::vector<DocMatchInfo>> PositionIndex::search(
    std::vector<std::string> query) {
    if (query.empty()) return std::make_pair(0, std::vector<DocMatchInfo>());
    std::vector<DocMatchInfo> matched;
    doc_index di = terms[query[0]];
    for (auto doc : di) {
        DocMatchInfo now_doc;
        now_doc.doc_name = doc.first;
        for (auto index : doc.second) {
            bool match = true;
            for (int i = 1; i < query.size(); i++) {
                if (!(index + i < content[doc.first].size() &&
                      content[doc.first][index + i] == query[i])) {
                    match = false;
                    break;
                }
            }
            if (match) now_doc.match_index.push_back(index);
        }
        if (now_doc.match_index.size()) {
            now_doc.tf_idf = 0;
            for (auto word : query) {
                double now_tf =
                    (1 + log(query.size() * now_doc.match_index.size()) /
                             log(10.0));
                now_doc.tf_idf += now_tf * idf[word];
            }
            matched.push_back(now_doc);
        }
    }
    std::sort(matched.begin(), matched.end(), cmp);
    std::vector<DocMatchInfo> ret_val;
    for (int i = 0; i < matched.size() && i < 5; i++) {
        ret_val.push_back(matched[i]);
    }
    return std::make_pair(matched.size(), ret_val);
}

void PositionIndex::print(DocMatchInfo doc) {
    std::cout << title[doc.doc_name] << std::endl;
    std::cout << doc.doc_name << std::endl;

    std::string all_str, output;
    for (int i = 0; i < 2 && i < doc.match_index.size(); i++) {
        if (i != 0) all_str += "...";
		std::string str;
        for (int index = doc.match_index[i]; index >= 0 && str.size() < 100;
             index--) {
            str = content[doc.doc_name][index] + str;
        }
        for (int index = doc.match_index[i] + 1;
             index < content[doc.doc_name].size() && str.size() < 200;
             index++) {
            str += content[doc.doc_name][index];
        }
		all_str += str;
    }
    int len = 0;
    bool wait_for_eol = false;
    for (auto c : all_str) {
        if (wait_for_eol && ((unsigned char)c >> 6) != 2) {
			output += '\n';
			wait_for_eol = false;
		}
        if (!isspace(c)) {
            output += c;
            len++;
        	if (len % 120 == 0) wait_for_eol = true;
        }
    }
    std::cout << output << std::endl;

    std::cout << std::endl;
}