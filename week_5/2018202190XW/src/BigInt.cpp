#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "BigInt.h"

const int BigInt::BASE = 10;

BigInt &BigInt::operator=(const std::string &num) {
    std::string tmp = num;
    if (tmp.empty())
        throw std::invalid_argument("Invalid number : \"" + num + "\"");
    if (tmp[0] == '-') {
        symbol = 1;
        tmp.erase(tmp.begin());
    } else
        symbol = 0;
    digit.clear();
    for (int i = tmp.size() - 1; i >= 0; i--) digit.push_back(tmp[i] - '0');
    if (digit.empty())
        throw std::invalid_argument("Invalid number : \"" + num + "\"");
    this->normalize();
    return *this;
}

bool BigInt::operator<(const BigInt &rhs) const {
    if (this->symbol ^ rhs.symbol) return this->symbol == 1;
    bool flag = this->symbol;
    if (this->digit.size() != rhs.digit.size()) {
        return (this->digit.size() < rhs.digit.size()) ^ flag;
    }
    for (int i = this->digit.size() - 1; i >= 0; i--) {
        if ((*this)[i] != rhs[i]) return ((*this)[i] < rhs[i]) ^ flag;
    }
    return false;
}
bool BigInt::operator>(const BigInt &rhs) const {
    if (this->symbol ^ rhs.symbol) return this->symbol == 0;
    bool flag = this->symbol;
    if (this->digit.size() != rhs.digit.size()) {
        return (this->digit.size() > rhs.digit.size()) ^ flag;
    }
    for (int i = this->digit.size() - 1; i >= 0; i--) {
        if ((*this)[i] != rhs[i]) return ((*this)[i] > rhs[i]) ^ flag;
    }
    return false;
}
bool BigInt::operator==(const BigInt &rhs) const {
    if (this->symbol != rhs.symbol) return false;
    if (this->digit.size() != rhs.digit.size()) return false;
    for (int i = this->digit.size() - 1; i >= 0; i--) {
        if ((*this)[i] != rhs[i]) return false;
    }
    return true;
}
bool BigInt::operator<=(const BigInt &rhs) const {
    return (*this) < rhs || (*this) == rhs;
}
bool BigInt::operator>=(const BigInt &rhs) const {
    return (*this) > rhs || (*this) == rhs;
}
bool BigInt::operator!=(const BigInt &rhs) const { return !((*this) == rhs); }

BigInt BigInt::abs() const {
    BigInt ret_value(*this);
    ret_value.symbol = 0;
    return ret_value;
}
BigInt BigInt::operator-() const {
    BigInt ret_value(*this);
    ret_value.symbol ^= 1;
    return ret_value;
}

std::vector<int> BigInt::unsigned_sub(const std::vector<int> &lhs,
                                      const std::vector<int> &rhs) const {
    std::vector<int> ret_value;
    int borrow = 0;
    for (int i = 0; i < rhs.size(); i++) {
        ret_value.push_back(lhs[i] - rhs[i] + borrow);
        if (ret_value[i] < 0) {
            ret_value[i] += BASE;
            borrow = -1;
        } else
            borrow = 0;
    }
    for (int i = rhs.size(); i < lhs.size(); i++) {
        ret_value.push_back(lhs[i] + borrow);
        if (ret_value[i] < 0) {
            ret_value[i] += BASE;
            borrow = -1;
        } else
            borrow = 0;
    }
    size_t size = ret_value.size();
    while (size > 1 && ret_value[size - 1] == 0) size--;
    ret_value.resize(size);
    return ret_value;
}

BigInt BigInt::operator+(const BigInt &rhs) const {
    if (this->symbol != rhs.symbol) return (*this) - (-rhs);
    BigInt lhs(*this), ret_value;
    ret_value.symbol = lhs.symbol;
    ret_value.digit.clear();
    int rest = 0;
    for (int i = 0; i < std::max(lhs.digit.size(), rhs.digit.size()); i++) {
        ret_value.digit.push_back((rest += (lhs[i] + rhs[i])) % BASE);
        rest /= BASE;
    }
    if (rest) ret_value.digit.push_back(rest);
    ret_value.normalize();
    return ret_value;
}
BigInt BigInt::operator-(const BigInt &rhs) const {
    if (this->symbol != rhs.symbol) return (*this) + (-rhs);
    BigInt lhs(*this), ret_value;
    if (lhs.abs() < rhs.abs()) {
        ret_value.symbol = lhs.symbol ^ 1;
        ret_value.digit = unsigned_sub(rhs.digit, lhs.digit);
    } else {
        ret_value.symbol = lhs.symbol;
        ret_value.digit = unsigned_sub(lhs.digit, rhs.digit);
    }
    ret_value.normalize();
    return ret_value;
}
BigInt BigInt::operator*(const BigInt &rhs) const {
    BigInt ret_value;
    ret_value.symbol = this->symbol ^ rhs.symbol;
    ret_value.digit.clear();
    ret_value.digit.resize(this->digit.size() + rhs.digit.size() - 1);
    for (int i = 0; i < this->digit.size(); i++) {
        for (int j = 0; j < rhs.digit.size(); j++) {
            ret_value.digit[i + j] += (*this)[i] * rhs[j];
        }
    }
    for (int i = 0; i < ret_value.digit.size() - 1; i++) {
        ret_value.digit[i + 1] += ret_value.digit[i] / BASE;
        ret_value.digit[i] %= BASE;
    }
    ret_value.erase_leading_zero();
    ret_value.normalize();
    return ret_value;
}
BigInt BigInt::operator/(const BigInt &rhs) const {
    if (rhs == 0) throw std::logic_error("Attempted division by zero");
    BigInt ret_value;
    ret_value.symbol = this->symbol ^ rhs.symbol;
    ret_value.digit.clear();
    if (this->digit.size() < rhs.digit.size()) return BigInt(0);
    BigInt tmp = sub_digit(this->digit.size() - rhs.digit.size() + 1, this->digit.size() - 1);
    for (int i = this->digit.size() - rhs.digit.size(); i >= 0; i--) {
        tmp = tmp * BASE + (*this)[i];
        int now_value = 0;
        while (tmp - rhs.abs() >= 0) {
            now_value++;
            tmp -= rhs.abs();
        }
        ret_value.digit.push_back(now_value);
    }
    ret_value.reverse();
    ret_value.erase_leading_zero();
    ret_value.normalize();
    return ret_value;
}
BigInt BigInt::operator%(const BigInt &rhs) const {
    return (*this) - (*this) / rhs * rhs;
}

BigInt &BigInt::operator+=(const BigInt &rhs) {
    *this = *this + rhs;
    return *this;
}
BigInt &BigInt::operator-=(const BigInt &rhs) {
    *this = *this - rhs;
    return *this;
}
BigInt &BigInt::operator*=(const BigInt &rhs) {
    *this = *this * rhs;
    return *this;
}

BigInt &BigInt::operator++() { return (*this) += 1; }
BigInt &BigInt::operator--() { return (*this) -= 1; }
BigInt BigInt::operator++(int) {
    BigInt pre = *this;
    ++(*this);
    return pre;
}
BigInt BigInt::operator--(int) {
    BigInt pre = (*this);
    --(*this);
    return pre;
}

std::istream &operator>>(std::istream &istrm, BigInt &num) {
    std::string input;
    istrm >> input;
    num = BigInt(input);
    return istrm;
}
std::ostream &operator<<(std::ostream &ostrm, const BigInt &num) {
    BigInt tmp(num);
    if (tmp.symbol) ostrm << '-';
    for (int i = tmp.digit.size() - 1; i >= 0; i--) ostrm << tmp[i];
    return ostrm;
}

/*int main() {
	BigInt a, b;
	std::cin >> a >> b;
	std::cout << a / b << std::endl;
    return 0;
}*/