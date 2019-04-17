#include "BigInteger.h"
BigInteger::BigInteger()
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
}

BigInteger::BigInteger(int num_int)
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
    for(int i = 0;i < MAX;i ++)
    {
        if(num_int == 0)
        break;
        else
        {
            number[i] = num_int % SIZE;
            num_int = num_int / SIZE;
            GroupSize ++;
        }
    }
};

BigInteger::BigInteger(string str)
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
    int len = str.size();
    string temp;
    GroupSize = len / strSIZE;
    if(len % strSIZE != 0)
    GroupSize = GroupSize + 1;
    for(int i = 0;i < MAX;i ++)
    {
        if(len == 0)
        break;
        if(len < strSIZE)
        {
            temp.clear();
            temp = str.substr(0);
            number[i] = atoi(temp.c_str());
            len = 0;
        }
        else
        {
            temp.clear();
            temp = str.substr(len - strSIZE);
            number[i] = atoi(temp.c_str());
            str.erase(len - strSIZE,strSIZE);
            len = len - strSIZE;
        }
    }
};

BigInteger::BigInteger(long int num_int)
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
    for(int i = 0;i < MAX;i ++)
    {
        if(num_int == 0)
        break;
        else
        {
            number[i] = num_int % SIZE;
            num_int = num_int / SIZE;
            GroupSize ++;
        }
    }
};

BigInteger::BigInteger(long long int num_int)
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
    for(int i = 0;i < MAX;i ++)
    {
        if(num_int == 0)
        break;
        else
        {
            number[i] = num_int % SIZE;
            num_int = num_int / SIZE;
            GroupSize ++;
        }
    }
};

BigInteger::BigInteger(const char * Cstr)
{
    GroupSize = 0;
    memset(number,0,sizeof(number));
    string str = Cstr;
    int len = str.size();
    string temp;
    GroupSize = len / strSIZE;
    if(len % strSIZE != 0)
    GroupSize = GroupSize + 1;
    for(int i = 0;i < MAX;i ++)
    {
        if(len == 0)
        break;
        if(len < strSIZE)
        {
            temp.clear();
            temp = str.substr(0);
            number[i] = atoi(temp.c_str());
            len = 0;
        }
        else
        {
            temp.clear();
            temp = str.substr(len - strSIZE);
            str.erase(len - strSIZE,strSIZE);
            number[i] = atoi(temp.c_str());
            len = len - strSIZE;
        }
    }    
};

BigInteger BigInteger::operator+(const BigInteger &Bint) const
{
    BigInteger sum;
    if(GroupSize > Bint.GroupSize)
    sum.GroupSize = GroupSize;
    else sum.GroupSize = Bint.GroupSize;
    for(int i = 0;i < sum.GroupSize;i ++)
    {
        sum.number[i] = number[i] + sum.number[i] + Bint.number[i];
        if(sum.number[i] >= SIZE)
        {
            sum.number[i + 1] = sum.number[i + 1] + 1;
            sum.number[i] = sum.number[i] - SIZE;
        }
    }
    if(sum.number[GroupSize] != 0)
    sum.GroupSize = sum.GroupSize + 1;
    return sum;
};

BigInteger operator+(int num_int,const BigInteger &Bint)
{
    return Bint + num_int;
};

BigInteger BigInteger::operator*(const BigInteger &Bint) const
{
    BigInteger mult;
    mult.GroupSize = GroupSize + Bint.GroupSize - 1;
    for(int i = 0;i < GroupSize;i ++)
    {
        for(int j = 0;j < Bint.GroupSize;j ++)
        {
            mult.number[i + j] = number[i] * Bint.number[j] + mult.number[i + j];
        }
    }
    for(int i = 0;i < mult.GroupSize;i ++)
    {
        mult.number[i + 1] = mult.number[i + 1] + mult.number[i] / SIZE;
        mult.number[i] = mult.number[i] % SIZE;
    }
    if(mult.number[mult.GroupSize] != 0)
    mult.GroupSize = mult.GroupSize + 1;
    return mult;
};

BigInteger operator*(int num_int,const BigInteger &Bint)
{
    return Bint * num_int;
};

ostream & operator<<(ostream &os,BigInteger &Bint)
{
    for(int i = Bint.GroupSize - 1;i >= 0;i --)
    {
        if(Bint.number[i] == 0)
        {
            os << "000" ;
        }
        else
        os << Bint.number[i];
    }
    return os;
};