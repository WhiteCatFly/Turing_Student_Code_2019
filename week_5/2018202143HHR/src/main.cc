#include <iostream>
#include <string>

#include "BigInteger.h"

std::string removeNonDigitsOrMinusSign(const std::string &s) {
    std::string result;
    for (char ch : s) if (isdigit(ch) || ch == '-') result.push_back(ch);
    return result;
}

int main() {
    std::string expression;
    while (std::cout << ">>> ", std::getline(std::cin, expression)) {
        if (expression.empty()) continue;

        size_t operatorPosition = expression.find_first_of("+-*");
        if (operatorPosition == std::string::npos) {
            std::cerr << "Expression must contain one operator: +, - or *." << std::endl;
            continue;
        }

        char ch = expression[operatorPosition];
        std::string sa = expression.substr(0, operatorPosition),
                    sb = expression.substr(operatorPosition + 1);
        
        // Remove characters that are NOT digits or minus sign in sa and sb.
        sa = removeNonDigitsOrMinusSign(sa);
        sb = removeNonDigitsOrMinusSign(sb);

        BigInteger a = sa, b = sb;

        if (ch == '+') std::cout << a + b << std::endl;
        else if (ch == '-') std::cout << a - b << std::endl;
        else std::cout << a * b << std::endl;
    }

    std::cout << std::endl;
}
