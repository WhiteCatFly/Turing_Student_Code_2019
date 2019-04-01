#include "Utility.h"

bool checkSuffix(const std::string &str, const std::string &pattern) {
    if (str.length() < pattern.length()) return false;
    std::string suffix = str.substr(str.length() - pattern.length());
    for (size_t i = 0; i < pattern.length(); i++) {
        if (toupper(suffix[i]) != toupper(pattern[i])) return false;
    }
    return true;
}

bool checkPrefix(const std::string &str, const std::string &pattern) {
    if (str.length() < pattern.length()) return false;
    for (size_t i = 0; i < pattern.length(); i++) {
        if (toupper(str[i]) != toupper(pattern[i])) return false;
    }
    return true;
}

void stringToLower(std::string &str) {
    for (size_t i = 0; i < str.length(); i++) str[i] = tolower(str[i]);
}
