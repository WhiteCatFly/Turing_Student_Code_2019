#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
class Integer{
    private:
    std::string val;
    char mode;
    public:
    Integer(int init);
    Integer()=default;
    Integer(long long init);
    Integer(std::string init);
    ~Integer(){};
    friend Integer operator+(const Integer & add1,const Integer & add2);
    //friend Integer operator+(int add1,const Integer & add2);
    friend Integer operator*(const Integer & mul1,const Integer & mul2);
    friend Integer operator-(const Integer & sub1,const Integer & sub2);
    Integer operator++();
    Integer operator--();
    friend Integer operator-(const Integer & origin);
    friend Integer operator/(const Integer & dividend,const Integer & divisor);
    friend Integer operator%(const Integer & dividend,const Integer & divisor);
    friend std::ostream & operator<<(std::ostream & os, Integer & showint);  
    inline std::string getval(){return val;}
    inline void show(){
        if(mode=='-')
            std::cout<<mode;
        std::cout<<val<<std::endl;}

};
 std::ostream &  operator<<(std::ostream & os,const Integer & showint);  
 Integer operator%(const Integer & dividend,const Integer & divisor);
Integer operator+(const Integer & add1,const Integer & add2);
//Integer operator+(int add1,const Integer & add2);
Integer operator*(const Integer & mul1,const Integer & mul2);
Integer operator/(const Integer & dividend,const Integer & divisor);
 Integer operator-(const Integer & sub1,const Integer & sub2);
 Integer operator-(const Integer & origin);
 int power(int base,int exp);