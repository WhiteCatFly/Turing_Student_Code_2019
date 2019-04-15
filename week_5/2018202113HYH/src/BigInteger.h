#include <string>
#include <iostream>
#include <algorithm>

std::string change(long long int num);

class BigInteger
{
    public:
    friend BigInteger operator+(int former,BigInteger latter)
    {
        return (BigInteger)former + latter;
    }
    friend BigInteger operator+(BigInteger former,int latter)
    {
        return (BigInteger)latter + former;
    }
    friend BigInteger operator-(int former,BigInteger latter)
    {
        return (BigInteger)former - latter;
    }
    friend BigInteger operator-(BigInteger former,int latter)
    {
        return former - (BigInteger)latter;
    }
    friend BigInteger operator*(int former,BigInteger latter)
    {
        return (BigInteger)former * latter;
    }
    friend BigInteger operator*(BigInteger former,int latter)
    {
        return (BigInteger)latter * former;
    }
    friend std::string change(long long int num);
    friend std::string add_zero(std::string num,int &begin,int &end);
    friend std::ostream &operator<<(std::ostream &os,const BigInteger &it);
    friend std::string cal_sub(std::string &former,std::string &latter,std::string &result,int &len);

   
    BigInteger()
    {

    }
    BigInteger(long long int num)
    {
        number = change(num);
        //std::cout << number << std::endl;
    }
    BigInteger(std::string num)
    {
        number = num;
    }
    BigInteger operator+(BigInteger latter);
    BigInteger operator-(BigInteger latter);
    BigInteger operator*(BigInteger latter);
   
    private:
    std::string number;
   
};
