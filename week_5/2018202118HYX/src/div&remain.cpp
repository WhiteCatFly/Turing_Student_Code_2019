#include"head.h"
using namespace std;

string BigInteger::div(string n1,string n2) const//n1/n1
{
    int x=compare(n1,n2);
    
    if(x==0)
        return "1";
    if(x==-1)
        return "0";
    
    //x==1
	string dividend=n1,divisor=n2;
    string quotient(n1.length(),'0');
    while(compare(dividend,n2)!=-1)
    {
		int l1=dividend.length(),l2=n2.length();
        int l=l1-l2;
        if(l>0)
        {
            string temp(l,'0');
            divisor=n2+temp;
            if(compare(dividend,divisor)==-1)
            {
                divisor.erase(divisor.length()-1,1);
                l--;
            }
        }
        dividend=sub(dividend,divisor);
        quotient[l]+=1;
        divisor=n2;
    }
    string res(quotient.rbegin(),quotient.rend());
    return res;
}

string BigInteger::rem(string n1,string n2) const//n1%n2
{
    int x=compare(n1,n2);
    if(x==0)
        return "0";
    if(x==-1)
        return n2;
    
    //x==1
	string dividend=n1,divisor=n2;
    while(compare(dividend,n2)!=-1)
    {
		int l1=dividend.length(),l2=n2.length();
        int l=l1-l2;
        if(l>0)
        {
            string temp(l,'0');
            divisor=n2+temp;
            if(compare(dividend,divisor)==-1)
            {
                divisor.erase(divisor.length()-1,1);
                l--;
            }
        }
        dividend=sub(dividend,divisor);
        divisor=n2;
    }
    return dividend;
}

BigInteger BigInteger::operator / (const BigInteger &other) const
{
    if(this->num=="0")
    {
        BigInteger res("0");
        return res;
    }

    if(other.num=="0")
    {
        cout<<"0 cant be divisor!"<<endl;
        BigInteger res("0");
        return res;
    }
    
    string division=(this->num,other.num);
    if(this->sign ^ other.sign == 0)//同号
    { 
        BigInteger res(division);
        return res;
    }
    else
    {
        BigInteger res('-'+division);
        return res;
    }
}

BigInteger BigInteger::operator / (long long x)
{
    string temp=to_string(x);
    BigInteger other_(temp);
    return this->operator/(other_);
}

BigInteger operator / (long long x,BigInteger &B)
{
    string temp=to_string(x);
    BigInteger other_(x);
    return other_.operator/(B);
}

BigInteger BigInteger::operator % (const BigInteger &other) const
{
    if(this->num=="0")
    {
        BigInteger res("0");
        return res;
    }

    if(other.num=="0")
    {
        cout<<"0 cant be divisor!"<<endl;
        BigInteger res("0");
        return res;
    }
    
    string remainder_=(this->num,other.num);
    if(this->sign ^ other.sign == 0)//同号
    { 
        BigInteger res(remainder_);
        return res;
    }
    else
    {
        BigInteger res('-'+remainder_);
        return res;
    }
}

BigInteger BigInteger::operator % (long long x)
{
    string temp=to_string(x);
    BigInteger other_(temp);
    return this->operator/(other_);
}

BigInteger operator % (long long x,BigInteger &B)
{
    string temp=to_string(x);
    BigInteger other_(x);
    return other_.operator%(B);
}