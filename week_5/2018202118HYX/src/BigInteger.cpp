#include "head.h"
using namespace std;

BigInteger::BigInteger(string num_)
{
    if (num_[0] == '-') //负
    {
        this->sign = 0;
        num_.erase(0, 1);//去掉负号
    }
    else //正
        this->sign = 1;

    this->num = num_;
}

BigInteger::BigInteger(long long num_)
{
    if (num_ < 0)
        this->sign = 0;
    else
    {
        this->sign = 1;
        num_ = -num_;
    }
    this->num = to_string(num_);
}

BigInteger::~BigInteger()
{
    cout << "DONE!" << endl;
}

BigInteger BigInteger::operator-()
{
    this->sign = 1 - this->sign;
}

int BigInteger::compare(string n1, string n2) const
{
    if (n1 == n2)
        return 0;//n1==n2

    int l1 = n1.length(), l2 = n2.length();
    if (l1 > l2)
        return 1;//n1>n2
    if (l1 < l2)
        return -1;//n1<n2

    for (int i = 0; i <l1 ; i++)
    {
        if (n1[i] > n2[i])
            return 1;//n1>n2
        if (n1[i] < n2[i])
            return -1;//n1<n2
    }
}

ostream &operator<<(ostream &os, const BigInteger &B)
{
    if (B.sign == 0)
        cout << "-";
    cout << B.num << endl;
    return os;
}