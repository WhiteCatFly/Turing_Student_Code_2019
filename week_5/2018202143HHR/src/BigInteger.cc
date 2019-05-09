#include "BigInteger.h"

BigInteger &BigInteger::operator=(const std::string &str) {
    bool newIsMinus = false;
    std::vector<char> newDigits;
    for (ssize_t i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '-' && i == 0) {
            newIsMinus = true;
            break;
        } else if (!isdigit(str[i])) {
            throw std::invalid_argument("Not a valid integer");
        }

        newDigits.push_back(str[i] - '0');
    }

    // Remove trailing zeros.
    while (!newDigits.empty() && !newDigits.back()) newDigits.pop_back();

    if (newDigits.empty()) {
        newIsMinus = false;
        newDigits.push_back(0);
    }

    isMinus = newIsMinus;
    digits = newDigits;

    return *this;
}

std::vector<char> BigInteger::unsignedAdd(const std::vector<char> &a, const std::vector<char> &b) {
    std::vector<char> resultDigits;
    bool carry = false;
    for (size_t i = 0; i < std::max(a.size(), b.size()); i++) {
        int tmp = 0;
        if (i < a.size()) tmp += a[i];
        if (i < b.size()) tmp += b[i];

        if (carry) tmp++, carry = false;
        if (tmp >= 10) tmp -= 10, carry = true;

        resultDigits.push_back(tmp);
    }
    if (carry) resultDigits.push_back(1);

    return resultDigits;
}

std::vector<char> BigInteger::unsignedSub(const std::vector<char> &a, const std::vector<char> &b) {
    std::vector<char> resultDigits;
    bool borrow = false;
    for (size_t i = 0; i < a.size(); i++) {
        int tmp = a[i];
        if (i < b.size()) tmp -= b[i];

        if (borrow) tmp--, borrow = false;
        if (tmp < 0) tmp += 10, borrow = true;

        resultDigits.push_back(tmp);
    }

    // Remove leading zeros.
    size_t size = resultDigits.size();
    while (size > 1 && resultDigits[size - 1] == 0) size--;
    resultDigits.resize(size);

    return resultDigits;
}

std::vector<char> BigInteger::unsignedMul(const std::vector<char> &a, const std::vector<char> &b) {
    std::vector<char> resultDigits;
    resultDigits.resize(a.size() + b.size());
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b.size(); j++){
            resultDigits[i + j] += a[i] * b[j];
            resultDigits[i + j + 1] += resultDigits[i + j] / 10;
            resultDigits[i + j] %= 10;
        }
    }

    // Remove leading zeros.
    size_t size = resultDigits.size();
    while (size > 1 && resultDigits[size - 1] == 0) size--;
    resultDigits.resize(size);

    return resultDigits;
}

int BigInteger::unsignedCompare(const std::vector<char> &a, const std::vector<char> &b) {
    if (a.size() < b.size()) return -1;
    else if (a.size() > b.size()) return 1;
    else {
        // High digits are store to more backward positions.
        for (ssize_t i = a.size() - 1; i >= 0; i--) {
            if (a[i] < b[i]) return -1;
            else if (a[i] > b[i]) return 1;
        }

        return 0;
    }
}

int BigInteger::signedCompare(const BigInteger &a, const BigInteger &b) {
    if (a.isMinus && !b.isMinus) return -1;
    else if (!a.isMinus && !b.isMinus) return 1;
    else if (a.isMinus && b.isMinus) return -BigInteger::unsignedCompare(a.digits, b.digits);
    else return BigInteger::unsignedCompare(a.digits, b.digits);
}
