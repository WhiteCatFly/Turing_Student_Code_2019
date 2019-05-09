#include"head.h"
using namespace std;

string BigInteger::mult(string n1,string n2) const//均不为0
{
    //逐位相乘
    string r1(n1.rbegin(), n1.rend()); //逆序
    string r2(n2.rbegin(), n2.rend());
    int l1 = r1.length(), l2 = r2.length();
    string res(l1+l2+1,'0');
    for(int i=0;i<l2;i++)//n2中每一位去乘以n1
    {
        if(r2[i]=='0')
        	continue;
        
		string temp(l1+1,'0');
        for(int j=0;j<l1;j++)
        {
            int t=(r2[i]-'0')*(r1[j]-'0')+(temp[j]-'0');
            int a=t%10,b=t/10;
            temp[j]=a+'0';
            temp[j+1]=b+'0';
        }
        
        if(i>0)
        {
            string p(i,'0');
            string q(l2-i,'0');
            temp=p+temp+q;//i+l1+1+l2-i 补齐
        }

        for(int k=0;k<=(i+l1);k++)
        {
            int t=temp[k]-'0'+res[k]-'0';
            int a=t%10,b=t/10;
            res[k]=a+'0';
            res[k+1]=b+'0';
        }
    }
    string pos(res.rbegin(), res.rend());//正序
    while (pos[0] == '0' && (pos.length() > 1))
        pos.erase(0,1);
    return pos;
}

BigInteger BigInteger::operator*(const BigInteger &other) const
{
    if(this->num=="0"||other.num=="0")
    {
        BigInteger res("0");
        return res;
    }
    
    string multiplication=mult(this->num,other.num);
    if(this->sign ^ other.sign == 0)//同号
    {
        BigInteger res(multiplication);
        return res;
    }
    else
    {
        BigInteger res('-'+multiplication);
        return res;
    }
}

BigInteger BigInteger::operator*(long long x)
{
    string temp=to_string(x);
    BigInteger other_(temp);
    return this->operator*(other_);
}

BigInteger operator*(long long x,BigInteger &B)
{
    return B.operator*(x);
}