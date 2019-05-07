#ifndef HEAD_H
#define HEAD_H

#include<iostream>
#include<string>

class BigInteger
{
private:
    std::string num;
    bool sign;//1为正，0为负
    
    std::string add(std::string n1,std::string n2) const;
    std::string sub(std::string n1,std::string n2) const;
    std::string mult(std::string n1,std::string n2) const;
    std::string div(std::string n1,std::string n2) const;
    std::string rem(std::string n1,std::string n2) const;
    int compare(std::string n1,std::string n2) const;

public:
    BigInteger()=default;
    explicit BigInteger(std::string num_);
    BigInteger(long long num_);//short和int均可转换为long long
    ~BigInteger();

    BigInteger operator - ();//取负

    BigInteger operator + (const BigInteger &other) const;
    BigInteger operator + (long long x);
    friend BigInteger operator + (long long x,const BigInteger &B);
    
    BigInteger operator - (const BigInteger &other) const;
    BigInteger operator - (long long x);
    friend BigInteger operator - (long long x,const BigInteger &B);

    BigInteger operator * (const BigInteger &other) const;
    BigInteger operator * (long long x);
    friend BigInteger operator * (long long x,const BigInteger &B);

    BigInteger operator / (const BigInteger &other) const;
    BigInteger operator / (long long x);
    friend BigInteger operator / (long long x,const BigInteger &B);

    BigInteger operator % (const BigInteger &other) const;
    BigInteger operator % (long long x);
    friend BigInteger operator % (long long x,const BigInteger &B);
    
    friend std::ostream &operator << (std::ostream & os,const BigInteger &B);
};

#endif