#include "head.h"
#include <cmath>
using namespace std;

string BigInteger::add(string n1, string n2) const
{
    string r1(n1.rbegin(), n1.rend()); //逆序
    string r2(n2.rbegin(), n2.rend());
    int l1 = r1.length(), l2 = r2.length();
    int M = max(l1, l2);
    int m = min(l1, l2);
    string res(M + 1, '0');

    if (M > m) //长度较小的数补齐0
    {
        string p(M - m, '0');
        if (l1 == m)
            r1 += p;
        else
            r2 += p;
    }

    for (int i = 0; i < M; i++)
    {
        int temp = r1[i] - '0' + r2[i] - '0' + res[i] - '0';
        int a = temp % 10, b = temp / 10;
        res[i] = a + '0';
        res[i + 1] = b + '0';
    }
    string pos(res.rbegin(), res.rend());//正序
    while (pos[0] == '0' && (pos.length() > 1))
        pos.erase(0,1);
    return pos; //输出正序
}

string BigInteger::sub(string n1, string n2) const //n1>n2,即n1-n2
{
    string r1(n1.rbegin(), n1.rend()); //逆序
    string r2(n2.rbegin(), n2.rend());
    int l1 = r1.length(), l2 = r2.length(); //l1>=l2
    string res(l1, '0');

    if (l1 > l2)
    {
        string p(l1 - l2, '0');
        r2 += p;
    }
    for (int i = 0; i < l1; i++)
    {
        if (r1[i] >= r2[i])
            res[i] += r1[i] - r2[i];
        else
        {
            res[i] += r1[i] - r2[i] + 10;
            for (int j = i + 1;; j++)
            {
                if (r1[j] == '0')
                    r1[j] == '9';
                else
                {
                    r1[j] -= 1;
                    break;
                }
            }
        }
    }
    string pos(res.rbegin(), res.rend());
    while (pos[0] == '0' && (pos.length() > 1))
        pos.erase(0, 1);
    return pos;
}

BigInteger BigInteger::operator+(const BigInteger &other) const
{
    if (this->sign ^ other.sign == 0) //同号
    {
        if (this->num == "0" && other.num == "0")//0+0
        {
            BigInteger res('0');
            return res;
        }

        string addition = add(this->num, other.num);
        if (this->sign == 1) //this+other
        {
            BigInteger res(addition);
            return res;
        }
        else //-this+(-other)
        {
            BigInteger res('-' + addition);
            return res;
        }
    }
    else //异号
    {
        int x = compare(this->num, other.num);
        if (x == 0) //this+other==0
        {
            BigInteger res('0');
            return res;
        }
        if (x == 1) //this>other
        {
            string subtraction = sub(this->num, other.num);
            if (this->sign == 1) //this+(-other)
            {
                BigInteger res(subtraction);
                return res;
            }
            else //-this+other
            {
                BigInteger res('-' + subtraction);
                return res;
            }
        }
        if (x == -1) //this<other
        {
            string subtraction = sub(other.num, this->num);
            if (this->sign == 1) //this+(-other)
            {
                BigInteger res('-' + subtraction);
                return res;
            }
            else //-this+other
            {
                BigInteger res(subtraction);
                return res;
            }
        }
    }
}

BigInteger BigInteger::operator+(long long x)
{
    string temp = to_string(x);
    BigInteger other_(temp);
    return this->operator+(other_);
}

BigInteger operator+(long long x, BigInteger &B)
{
    return B.operator+(x);
}

BigInteger BigInteger::operator-(const BigInteger &other) const
{
    if (this->sign ^ other.sign == 0) //同号->异号
    {
        int x = compare(this->num, other.num);
        if (x == 0)
        {
            BigInteger res('0');
            return res;
        }
        if (x == 1)//this>other
        {
            string subtraction=sub(this->num,other.num);
            if(this->sign==1)//this-(+other)
            {
                BigInteger res(subtraction);
                return res;
            }
            else//-this-(-other)
            {
                BigInteger res('-'+subtraction);
                return res;
            }
        }
        if(x==-1)//this<other
        {
            string subtraction=sub(other.num,this->num);
            if(this->sign==1)//this-(+other)
            {
                BigInteger res('-'+subtraction);
                return res;
            }
            else//-this-(-other)
            {
                BigInteger res(subtraction);
                return res;
            }
        }
    }
    else //异号->同号
    {
        if (this->num == "0" && other.num == "0")//0+0
        {
            BigInteger res('0');
            return res;
        }

        string addition = add(this->num, other.num);
        if (this->sign == 1) //this-(-other)
        {
            BigInteger res(addition);
            return res;
        }
        else //-this-(+other)
        {
            BigInteger res('-' + addition);
            return res;
        }
    }
}

BigInteger BigInteger::operator-(long long x)//B-x
{
    string temp=to_string(x);
    BigInteger other_(temp);
    return this->operator-(other_);
}

BigInteger operator-(long long x,BigInteger &B)//x-B
{
    string temp=to_string(x);
    BigInteger other_(temp);
    return other_.operator-(B);
}