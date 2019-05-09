#include"BigInteger.h"

BigInteger::BigInteger(__int128_t a){
    digits.clear();
    if(a == 0) digits.push_back(a);
    while(a >= 1){
        int temp = a % 10;
        digits.push_back(temp);
        a = (a - temp) / 10;
    }
}

BigInteger::BigInteger(const std::string &str){
    digits.clear();
    for(int i = str.length() - 1; i >= 0; i --){
        int temp = str[i] - '0';
        digits.push_back(temp);
    }
    while(1){
        if(digits.back() == 0){
            digits.pop_back();
        }
        else break;
    }
    if(digits.empty()){
        digits.push_back(0);
    }
}

// BigInteger::BigInteger(const char *c_str){
//     digits.clear();
//     std::string str = c_str;
//     for(int i = str.length() - 1; i >= 0; i --){
//         int temp = str[i] - '0';
//         digits.push_back(temp);
//     }
//     while(1){
//         if(digits.back() == 0){
//             digits.pop_back();
//         }
//         else break;
//     }
//     if(digits.empty()){
//         digits.push_back(0);
//     }
// }

// BigInteger::BigInteger(std::vector<int> &_digits){
//     this->digits = _digits;
// }

// BigInteger::BigInteger(const BigInteger &other){
//     this->digits = other.digits;
// }

BigInteger BigInteger::operator+(const BigInteger &other) const {
    std::vector<int>::const_iterator iter1 = other.digits.begin();
    std::vector<int>::const_iterator iter2 = digits.begin();
    std::vector<int> temp;
    while(iter1 != other.digits.end() || iter2 != digits.end()){
        if(iter1 != other.digits.end() && iter2 != digits.end()){
            temp.push_back(*iter1 + *iter2);
            iter1 ++;
            iter2 ++;
            continue;
        }
        if(iter1 != other.digits.end() && iter2 == digits.end()){
            temp.push_back(*iter1);
            iter1 ++;
            continue;
        }
        if(iter1 == other.digits.end() && iter2 != digits.end()){
            temp.push_back(*iter2);
            iter2 ++;
            continue;
        }
    }
    for(int i = 0; i <= temp.size(); i ++){
        if(temp[i] >= 10){
            temp[i] -= 10;
            i ++;
            if(i >= temp.size()){
                temp.push_back(1);
            }
            else
            temp[i] += 1;
            i --;
        }
    }
    const BigInteger tmp(temp);
    return tmp;
}

BigInteger operator+(const BigInteger &other,long long int a){
    BigInteger temp(a);
    BigInteger b;
    b = temp + other;
    return b;
}

BigInteger operator+(long long int a, const BigInteger &other){
    BigInteger temp(a);
    BigInteger b;
    b = temp + other;
    return b;
}

std::ostream & operator<<(std::ostream &out, const BigInteger &temp){
    std::vector<int> tmp = temp.digits;
    while(!tmp.empty()){
        out << tmp.back();
        tmp.pop_back();
    }
    return out;
}
