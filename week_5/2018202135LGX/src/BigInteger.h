#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>

class BigInteger{
private:
    std::vector<int> digits;
  
    BigInteger(std::vector<int> &_digits) : digits(_digits) {} //construct with std::vector<int>, used to help the operator+ overloading
  public:
    BigInteger() : BigInteger(0) {}
    BigInteger(int a) : BigInteger((__int128_t)a) {} //construct with int
    BigInteger(long int a) : BigInteger((__int128_t)a) {} //construct with long
    BigInteger(long long int a) : BigInteger((__int128_t)a) {} //construct with long long
    BigInteger(__int128_t a); //construct with __int128_t
    BigInteger(const std::string &str); //construct with std::string
    BigInteger(const BigInteger &other) = default; //copy constructor
    BigInteger operator+(const BigInteger &other) const;
    friend BigInteger operator+(const BigInteger &other,long long int a);
    friend BigInteger operator+(long long int a,const BigInteger &other);
    friend std::ostream & operator<<(std::ostream &out, const BigInteger &temp);
};

#endif
