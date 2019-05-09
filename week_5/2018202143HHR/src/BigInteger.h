#ifndef _MENCI_BIGINTEGER_BIGINTEGER_H
#define _MENCI_BIGINTEGER_BIGINTEGER_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <type_traits>

class BigInteger {
    bool isMinus;
    std::vector<char> digits;

    BigInteger(bool isMinus, const std::vector<char> &digits)
    : isMinus(digits.size() == 1 && digits[0] == 0 ? false : isMinus), // Zero has no minus sign.
      digits(digits) {}

    static std::vector<char> unsignedAdd(const std::vector<char> &a, const std::vector<char> &b);
    static std::vector<char> unsignedSub(const std::vector<char> &a, const std::vector<char> &b);
    static std::vector<char> unsignedMul(const std::vector<char> &a, const std::vector<char> &b);
    static int unsignedCompare(const std::vector<char> &a, const std::vector<char> &b);
    static int signedCompare(const BigInteger &a, const BigInteger &b);

public:
    BigInteger() {
        *this = 0;
    }

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger(T x) {
        *this = x;
    }
    
    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger &operator=(T x) {
        return *this = std::to_string(x);
    }

    BigInteger(const std::string &str) {
        *this = str;
    }

    BigInteger &operator=(const std::string &str);

    BigInteger &operator=(const BigInteger &x) {
        digits = x.digits;
        isMinus = x.isMinus;
        return *this;
    }

    friend bool operator<(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) == -1; }
    friend bool operator>(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) == 1; }
    friend bool operator<=(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) != 1; }
    friend bool operator>=(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) != -1; }
    friend bool operator==(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) == 0; }
    friend bool operator!=(const BigInteger &a, const BigInteger &b) { return signedCompare(a, b) != 0; }

    BigInteger operator-() const {
        return BigInteger(!isMinus, digits);
    }

    friend BigInteger operator+(const BigInteger &a, const BigInteger &b) {
        if (a.isMinus == b.isMinus) return BigInteger(a.isMinus, unsignedAdd(a.digits, b.digits));
        else {
            int compareResult = unsignedCompare(a.digits, b.digits);
            if (compareResult > 0) return BigInteger(a.isMinus, unsignedSub(a.digits, b.digits));
            else if (compareResult < 0) return BigInteger(b.isMinus, unsignedSub(b.digits, a.digits));
            else return 0;
        }
    }

    friend BigInteger operator-(const BigInteger &a, const BigInteger &b) {
        return a + -b;
    }

    friend BigInteger operator*(const BigInteger &a, const BigInteger &b) {
        return BigInteger(a.isMinus != b.isMinus, unsignedMul(a.digits, b.digits));
    }

    BigInteger &operator+=(const BigInteger &other) {
        *this = *this + other;
        return *this;
    }

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger &operator+=(T other) {
        *this = *this + BigInteger(other);
        return *this;
    }

    BigInteger &operator-=(const BigInteger &other) {
        *this = *this - other;
        return *this;
    }
    
    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger &operator-=(T other) {
        *this = *this - BigInteger(other);
        return *this;
    }


    BigInteger &operator*=(const BigInteger &other) {
        *this = *this * other;
        return *this;
    }

    template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
    BigInteger &operator*=(T other) {
        *this = *this * BigInteger(other);
        return *this;
    }

    BigInteger &operator++() {
        return *this += 1;
    }

    BigInteger operator++(int) {
        BigInteger original = *this;
        ++(*this);
        return original;
    }

    BigInteger &operator--() {
        return *this -= 1;
    }

    BigInteger operator--(int) {
        BigInteger original = *this;
        ++(*this);
        return original;
    }

    operator bool() const {
        return !(digits.size() == 1 && digits[0] == 0);
    }
    
    operator std::string() const {
        std::string result;
        if (isMinus) result.push_back('-');
        for (ssize_t i = digits.size() - 1; i >= 0; i--) result.push_back(digits[i] + '0');
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInteger &val) {
        return os << (std::string)val;
    }

    friend std::istream &operator>>(std::istream &is, BigInteger &val) {
        std::string str;
        if (is >> str) {
            try {
                val = str;
            } catch (const std::invalid_argument &e) {
                is.setstate(std::ios_base::failbit);
            }
        }

        return is;
    }
};


template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator+(const BigInteger &a, T b) {
    return a + BigInteger(b);
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator+(T a, const BigInteger &b) {
    return BigInteger(a) + b;
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator-(const BigInteger &a, T b) {
    return a - BigInteger(b);
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator-(T a, const BigInteger &b) {
    return BigInteger(a) - b;
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator*(const BigInteger &a, T b) {
    return a * BigInteger(b);
}

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
BigInteger operator*(T a, const BigInteger &b) {
    return BigInteger(a) * b;
}

#endif // _MENCI_BIGINTEGER_BIGINTEGER_H
