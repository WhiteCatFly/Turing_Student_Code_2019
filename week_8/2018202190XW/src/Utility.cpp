#include <vector>
#include <string>

#include "include/thulac.h"
#include "LAC.h"
#include "Utility.h"
#include "HtmlEntity.h"

bool has_chinese(std::string str) {
    for (auto c : str) {
        if (((unsigned char)c >> 4) == 14) return true;
    }
    return false;
}

std::vector<std::string> extract_chinese(std::vector<std::string> text) {
    std::vector<std::string> ret_val;
    for (auto str : text) {
        if (str.find("\xef\xbb\xbf") != std::string::npos) continue;
        if (has_chinese(str)) ret_val.push_back(str);
    }
    return ret_val;
}
void escape_html(std::vector<std::string>& text) {
    std::vector<std::string> tmp_text;
    for (auto str : text) {
        std::string tmp_str;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != '&')
                tmp_str += str[i];
            else {
                i++;
                bool lead_escape = false;
                for (auto entity : StaticEntityNames) {
                    if (str.size() - i >= entity.Name1.size()) {
                        if (str.substr(i, entity.Name1.size()) ==
                            entity.Name1) {
                            tmp_str += entity.Value;
                            i += entity.Name1.size();
                            if (i < str.size() && str[i] == ';') ++i;
                            lead_escape = true;
                            break;
                        }
                    }
                    if (str.size() - i >= entity.Name2.size()) {
                        if (str.substr(i, entity.Name2.size()) ==
                            entity.Name2) {
                            tmp_str += entity.Value;
                            i += entity.Name2.size();
                            if (i < str.size() && str[i] == ';') ++i;
                            lead_escape = true;
                            break;
                        }
                    }
                }
                if (!lead_escape) tmp_str += '&';
                i--;
            }
        }
        tmp_text.push_back(tmp_str);
    }
    text = tmp_text;
}

THULAC_result split(std::vector<std::string> text) {
    std::string to_be_cut;
    for (auto str : text) {
        while (str.size() && isspace(str[0])) str.erase(str.begin());
        while (str.size() && isspace(str[str.size() - 1]))
            str.pop_back();
        to_be_cut += str + '\n';
    }
    if (to_be_cut.size()) to_be_cut.pop_back();
    static LAC my_lac;
    THULAC_result result = my_lac.cut(to_be_cut);
    result.pop_back();
    return result;
}