#include <string>
#include <iostream>
#include <algorithm>

std::string change(int num);

class BigInteger
{
    public:
    friend std::string change(int num);
    friend std::string add_zero(std::string num,int &begin,int &end);
    friend std::ostream &operator<<(std::ostream &os,const BigInteger &it);
    friend std::string cal_sub(std::string &former,std::string &latter,std::string &result,int &len);

   
    BigInteger()
    {

    }
    BigInteger(int num)
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
