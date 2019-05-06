#include <sstream>
#include <stack>
#include <iostream>

#include "BigInteger.h"


BigInteger::BigInteger(std::string number) :
        _numberString(number){}

BigInteger::BigInteger(long long number) :
    _numberString(std::to_string(number)){}

BigInteger BigInteger::add(BigInteger other){
    BigInteger b1 = other > *this ? other : *this;
    BigInteger b2 = other > *this ? *this : other;
    if(b1.isNegative() || b2.isNegative()){
        if(b1.isNegative() && b2.isNegative()){
            return b1.negate().add(b2.negate()).negate();
        }
        else if(b1.isNegative() && !b2.isNegative()){
            return b1.negate().subtract(b2).negate();
        }
        else {
            return b2.negate().subtract(b1).negate();
        }
    }
    std::string results;
    int carry = 0;
    int diff = int(b1._numberString.size() - b2._numberString.size());
    for (int i = 0; i < diff; ++i){
        b2._numberString.insert(b2._numberString.begin(), '0');
    }
    for (int i = int(b1._numberString.size() - 1); i >= 0; --i){
        int sum = (b1._numberString[i] - '0') + (b2._numberString[i] - '0') + carry;
        carry = 0;
        if(sum <= 9 || i == 0){
            results.insert(0, std::to_string(sum));
        }
        else {
            results.insert(0, std::to_string(sum % 10));
            carry = 1;
        }
    }
    return BigInteger(results);
}

BigInteger BigInteger::addll(const long long &other){
    return this->add(BigInteger(other));
}

BigInteger BigInteger::addstr(const std::string &other){
    return this->add(BigInteger(other));
}


BigInteger BigInteger::subtract(BigInteger other){
    BigInteger b1 = *this, b2 = other;
    if(b1.isNegative() || b2.isNegative()){
        if(b1.isNegative() && b2.isNegative()){
            return b1.negate().add(b2.negate()).negate();
        }
        else if(b1.isNegative() && !b2.isNegative()){
            return b1.negate().add(b2).negate();
        }
        else {
            return b2.negate().add(b1);
        }
    }
    std::string results;
    int n = 0, p = 0;
    bool takeOffOne = false;
    bool shouldBeTen = false;

    if(b1 < b2){
        //Negative answer
        std::string t = b2.subtract(*this).negate().getString();
        for (unsigned int i = 1; i < t.length(); ++i){
            if(t[i] != '0') break;
            t.erase(1, 1);
        }
        return BigInteger(t);
    }
    if(b1._numberString.size() - b2.getString().size() > 1){
        for (unsigned long i = 0; i < b1._numberString.size() - b2.getString().size() - 1; ++i){
            b2._numberString.insert(b2._numberString.begin(), '0');
        }
    }
    int i = int(b1._numberString.size() - 1);
    for (int j = int(b2._numberString.size() - 1); j >= 0; --j){
        if(((b1._numberString[i] - '0') < (b2._numberString[j] - '0')) && i > 0){
            n = char((b1._numberString[i] - '0') + 10);
            takeOffOne = true;
            if(j > 0 || b1._numberString[i - 1] != '0'){
                p = char((b1._numberString[i - 1] - '0') - 1);
                if(p == -1){
                    p = 9;
                    shouldBeTen = true;
                }
                takeOffOne = false;
            }
            if(shouldBeTen){
                int index = i - 1;
                for (int a = i - 1; (b1._numberString[a] - '0') == 0; --a){
                    b1._numberString[a] = static_cast<char>(p + '0');
                    --index;
                }
                int t = (b1._numberString[index] - '0') - 1;
                b1._numberString[index] = static_cast<char>(t + '0');
            }
            b1._numberString[i - 1] = static_cast<char>(p + '0');
            shouldBeTen = false;
        }
        std::stringstream ss;
        if(((b1._numberString[i] - '0') == (b2._numberString[j] - '0'))){
            ss << "0";
        }
        else {
            if(n <= 0){
                ss << ((b1._numberString[i] - '0') - (b2._numberString[j] - '0'));
            }
            else {
                ss << (n - (b2._numberString[j] - '0'));
            }
        }

        results.insert(0, ss.str());
        --i;
        n = 0;
    }
    if(takeOffOne){
        std::string number = "";
        for (int j = b1._numberString.length() - b2._numberString.length() - 1; j >= 0; --j){
            if(b1._numberString[j] == '0'){
                number += "0";
                continue;
            }
            else {
                number.insert(number.begin(), b1._numberString[j]);
                int t = atoi(number.c_str());
                --t;
                b1._numberString.replace(0, number.size(), std::to_string(t));
                break;
            }
        }
    }
    while (i >= 0){
        std::stringstream ss;
        if(i == 0){
            if(b1._numberString[i] - '0' != 0){
                ss << (b1._numberString[i] - '0');
                results.insert(0, ss.str());
            }
        }
        else {
            ss << (b1._numberString[i] - '0');
            results.insert(0, ss.str());
        }

        --i;
    }
    if(results.find_first_not_of('0') == std::string::npos){
        results = "0";
    }
    else if(results[0] == '0'){
        int index = results.find_first_not_of('0');
        results = results.substr(index, results.length() - 1);
    }
    return BigInteger(results);
}

BigInteger BigInteger::subtractll(const long long &other){
    return this->subtract(BigInteger(other));
}

BigInteger BigInteger::subtractstr(const std::string &other){
    return this->subtract(BigInteger(other));
}

std::string BigInteger::getString(){
    return this->_numberString;
}

BigInteger BigInteger::setString(const std::string &newStr){
    this->_numberString = newStr;
    return *this;
}

BigInteger BigInteger::negate(){
    if(this->_numberString[0] == '-'){
        this->_numberString.erase(0, 1);
    }
    else {
        this->_numberString.insert(this->_numberString.begin(), '-');
    }
    return *this;
}

BigInteger BigInteger::trimLeadingZeros(){
    BigInteger b = *this;
    if(b._numberString.find_first_not_of('0') != std::string::npos){
        b.setString(b._numberString.erase(0, b._numberString.find_first_not_of('0')));
    }
    return b;
}

bool BigInteger::equals(const BigInteger &other){
    return this->_numberString == other._numberString;
}

bool BigInteger::equals(const long long &other){
    return this->getString() == std::to_string(other);
}

bool BigInteger::equals(const std::string &other){
    return this->getString() == other;
}

unsigned int BigInteger::digits(){
    return this->_numberString.length() - static_cast<int>(this->isNegative());
}

bool BigInteger::isNegative() const {
    return this->_numberString[0] == '-';
}

std::ostream &operator<<(std::ostream &os, const BigInteger &num){
    os << num._numberString;
    return os;
}

BigInteger operator+(BigInteger b1, const BigInteger &b2){
    return b1.add(b2);
}

BigInteger operator+(BigInteger b1, const long long &b2){
    return b1.addll(b2);
}

BigInteger operator+(BigInteger b1, const std::string &b2){
    return b1.addstr(b2);
}

BigInteger operator-(BigInteger b1, const BigInteger &b2){
    return b1.subtract(b2);
}

BigInteger operator-(BigInteger b1, const long long &b2){
    return b1.subtractll(b2);
}

BigInteger operator-(BigInteger b1, const std::string &b2){
    return b1.subtractstr(b2);
}

bool operator==(BigInteger b1, const BigInteger &b2){
    return b1.equals(b2);
}

bool operator==(BigInteger b1, const long long &b2){
    return b1.equals(b2);
}

bool operator==(BigInteger b1, const std::string &b2){
    return b1.equals(b2);
}

bool operator>(BigInteger b1, const BigInteger &b2){
    if(b1.isNegative() || b2.isNegative()){
        if(b1.isNegative() && b2.isNegative()){
            BigInteger bt = b2;
            b1._numberString.erase(0, 1);
            bt._numberString.erase(0, 1);
            return b1 < bt;
        }
        else {
            return !(b1.isNegative() && !b2.isNegative());
        }
    }
    b1 = b1.trimLeadingZeros();
    auto c = BigInteger(b2);
    c = c.trimLeadingZeros();
    if(b1 == c){
        return false;
    }
    if(b1._numberString.size() > c._numberString.size()){
        return true;
    }
    else if(c._numberString.size() > b1._numberString.size()){
        return false;
    }
    else {
        for (unsigned int i = 0; i < b1._numberString.size(); ++i){
            if(b1[i] == static_cast<unsigned int>(c._numberString[i] - '0')){
                continue;
            }
            return b1[i] > static_cast<unsigned int>(c._numberString[i] - '0');
        }
    }
    return false;
}

bool operator<(BigInteger b1, const BigInteger &b2){
    return !(b1 == b2) && !(b1 > b2);
}

unsigned int BigInteger::operator[](int index){
    if(this->_numberString[index] == '-'){
        std::cerr << "You cannot get the negative sign from the number" << std::endl;
    }
    return static_cast<unsigned int>(this->_numberString[index] - '0');
}

BigInteger& BigInteger::operator=(const BigInteger &other){
    this->_numberString = other._numberString;
    return *this;
}

BigInteger& BigInteger::operator=(const long long &other){
    this->_numberString = std::to_string(other);
    return *this;
}

BigInteger& BigInteger::operator=(const std::string &other){
    this->_numberString = other;
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger &other){
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator+=(const long long &other){
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator+=(const std::string &other){
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger &other){
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator-=(const long long &other){
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator-=(const std::string &other){
    *this = *this - other;
    return *this;
}
