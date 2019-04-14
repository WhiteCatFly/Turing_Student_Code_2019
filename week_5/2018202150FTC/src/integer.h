#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
class BigInteger{
    private:
    std::string val;
    char mode;
    public:
    //BigInteger(int init);
    BigInteger()=default;
    BigInteger(long long init);
    BigInteger(std::string init);
    ~BigInteger(){};
    friend BigInteger operator+(const BigInteger & add1,const BigInteger & add2);
    //friend Integer operator+(int add1,const Integer & add2);
    friend BigInteger operator*(const BigInteger & mul1,const BigInteger & mul2);
    friend BigInteger operator-(const BigInteger & sub1,const BigInteger & sub2);
    BigInteger operator++();
    BigInteger operator--();
    friend BigInteger operator-(const BigInteger & origin);
    friend BigInteger operator/(const BigInteger & dividend,const BigInteger & divisor);
    friend BigInteger operator%(const BigInteger & dividend,const BigInteger & divisor);
    friend std::ostream & operator<<(std::ostream & os, BigInteger & showint);  
    inline std::string getval(){return val;}
    inline void show(){
        if(mode=='-')
            std::cout<<mode;
        std::cout<<val<<std::endl;}

};
 std::ostream &  operator<<(std::ostream & os,const BigInteger & showint);  
BigInteger operator%(const BigInteger & dividend,const BigInteger & divisor);
BigInteger operator+(const BigInteger & add1,const BigInteger & add2);
//Integer operator+(int add1,const Integer & add2);
BigInteger operator*(const BigInteger & mul1,const BigInteger & mul2);
BigInteger operator/(const BigInteger & dividend,const BigInteger & divisor);
BigInteger operator-(const BigInteger & sub1,const BigInteger & sub2);
BigInteger operator-(const BigInteger & origin);
 int power(int base,int exp);