#include"BigInteger.h"
#include"caculate.h"
#include<sstream>
#include<iostream>
using namespace std;
BigInteger::BigInteger()
{
    bigint="0";
}
BigInteger::BigInteger(string& str_bigint)
{
    bigint=str_bigint;
}
BigInteger::BigInteger(int& int_bigint)
{
    stringstream ss;
    ss<<int_bigint;
    bigint=ss.str();
}
BigInteger::BigInteger(long long int& long_bigint)
{
    stringstream ss;
    ss<<long_bigint;
    bigint=ss.str();
}
BigInteger::~BigInteger()
{
}
BigInteger BigInteger::operator+(BigInteger & a)
{
    BigInteger sum;
    sum.bigint=add(bigint,a.bigint);
    return sum;
}
BigInteger BigInteger::operator+(int n)
{
    stringstream ss;
    ss<<n;
    string String=ss.str();
    BigInteger sum;
    sum.bigint=add(String,bigint);
    return sum;
}
BigInteger operator+(int n,BigInteger & a)
{
    stringstream ss;
    ss<<n;
    string String=ss.str();
    BigInteger sum;
    sum.bigint=add(String,a.bigint);
    return sum;
}
ostream & operator<<(ostream & os,const BigInteger & a)
{
    os<<a.bigint;
    return os;
}