#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

class BigInteger{
private:
    std::vector<int> digits;
public:
    BigInteger();
    BigInteger(int a);  //construct with int
    BigInteger(long int a);  //construct with long
    BigInteger(long long int a); //construct with long long
    BigInteger(__int128_t a); //construct with __int128_t
    BigInteger(const std::string str); //construct with std::string
    BigInteger(const char *c_str); //construct with const char*
    BigInteger(std::vector<int> &_digits); //construct with std::vector<int>, used to help the operator+ overloading
    BigInteger(const BigInteger &other); //copy constructor
    BigInteger operator+(BigInteger &other);
    friend BigInteger operator+(BigInteger &other,const long long int a);
    friend BigInteger operator+(const long long int a, BigInteger &other);
    friend std::ostream & operator<<(std::ostream &out, const BigInteger temp);
};

#endif