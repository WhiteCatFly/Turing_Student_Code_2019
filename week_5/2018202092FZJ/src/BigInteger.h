#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

class BigInteger {
public:
    BigInteger(std::string number);
    BigInteger(long long number);
    BigInteger add(BigInteger other);
    BigInteger subtract(BigInteger other);
    BigInteger multiply(BigInteger other);
    std::string getString();
    BigInteger setString(const std::string &newStr);
    BigInteger negate();
    BigInteger trimLeadingZeros();
    bool equals(const BigInteger &other);
    bool equals(const long long &other);
    bool equals(const std::string &other);
    bool isNegative() const;
    unsigned int digits();
    friend std::ostream &operator<<(std::ostream &os, const BigInteger &num);
    friend BigInteger operator+(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator+(BigInteger b1, const long long &b2);
    friend BigInteger operator+(BigInteger b1, const std::string &b2);
    friend BigInteger operator-(BigInteger b1, const BigInteger &b2);
    friend BigInteger operator-(BigInteger b1, const long long &b2);
    friend BigInteger operator-(BigInteger b1, const std::string &b2);
    friend bool operator==(BigInteger b1, const BigInteger &b2);
    friend bool operator==(BigInteger b1, const long long &b2);
    friend bool operator==(BigInteger b1, const std::string &b2);
    friend bool operator>(BigInteger b1, const BigInteger &b2);
    friend bool operator<(BigInteger b1, const BigInteger &b2);
    BigInteger& operator=(const BigInteger &other);
    BigInteger& operator=(const long long &other);
    BigInteger& operator=(const std::string &other);
    BigInteger& operator+=(const BigInteger &other);
    BigInteger& operator+=(const long long &other);
    BigInteger& operator+=(const std::string &other);
    BigInteger& operator-=(const BigInteger &other);
    BigInteger& operator-=(const long long &other);
    BigInteger& operator-=(const std::string &other);
    unsigned int operator[](int index);
private:
    std::string _numberString;
    BigInteger addll(const long long &other);
    BigInteger addstr(const std::string &other);
    BigInteger subtractll(const long long &other);
    BigInteger subtractstr(const std::string  &other);
};



#endif
