#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;
const int SIZE = 1000;
const int strSIZE = 3;
const int MAX = 100;
class BigInteger
{
    private:
        int number[MAX];
        int GroupSize;
    public:
        BigInteger(int num_int);
        BigInteger(long int num_lint);
        BigInteger(long long int num_llint);
        BigInteger(string str);
        BigInteger(const char* str);
        BigInteger();
        ~BigInteger(){};
        BigInteger operator+(const BigInteger &Bint) const;
        BigInteger operator*(const BigInteger &Bint) const;
        friend ostream &operator<<(ostream &os,BigInteger &Bint);
        friend BigInteger operator*(int num_int,const BigInteger &Bint);
        friend BigInteger operator+(int num_int,const BigInteger &Bint);
};

#endif