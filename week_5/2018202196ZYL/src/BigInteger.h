#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include<string>
using namespace std;
class BigInteger
{
private:
    string bigint;

public:
    BigInteger();
    BigInteger(string& str_bigint);
    BigInteger(int& int_bigint);
    BigInteger(long long int& long_bigint);
    ~BigInteger();
    BigInteger operator+(BigInteger & a);
    BigInteger operator+(int n);
    friend BigInteger operator+(int n,BigInteger & a);
    friend ostream & operator<<(ostream & os,const BigInteger & a);
};

#endif