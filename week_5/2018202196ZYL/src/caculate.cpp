#include"caculate.h"
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
void unite(string & a,int n)
{
    for(int i=1;i<=n;i++)
        a='0'+a;
}
string caculate_add(string & data1,string & data2)
{
    int n=data1.length();
    int mod=0;
    string sum;
    for(int i=n-1;i>=0;i--)
    {
        char New=(data1[i]+data2[i]+mod-96)%10+48;
        sum=New+sum;
        mod=(data1[i]+data2[i]+mod-96)/10;
    }
    if(mod>0)
    {
        char New=mod+48;
        sum=New+sum;
    }
    return sum;
}
string caculate_subtract(string & data1,string & data2)
{
    string sum;
    int n=data1.length();
    int s;
    for(int i=n-1;i>=0;i--)
    {
        s=data1[i]-data2[i];
        if(s<0)
        {
            s+=10;
            data1[i-1]--;
        }
        sum[i]=s+48;
    }
    while(sum[0]=='0')
        sum=sum.substr(1,sum.length()-1);
    return sum;
}
string add(string & data1,string & data2)
{
    string sum;
    char sign;
    if(data1[0]=='-')
    {
        data1=data1.substr(1,data1.length()-1);
        if(data2[0]=='-')
        {
            data2=data2.substr(1,data2.length()-1);
            sign='-';
            unite(data1.length()<data2.length()?data1:data2,abs(int(data1.length()-data2.length())));
            sum=caculate_add(data1,data2);
        }
        else
        {
            unite(data1.length()<data2.length()?data1:data2,abs(int(data1.length()-data2.length())));
            if(data1[0]>data2[0])  
                sign='-';
            sum=caculate_subtract(data1>data2?data1:data2,data1<data2?data1:data2);           
        }
        
    }
    else
    {
        if(data2[0]=='-')
        {
            data2=data2.substr(1,data2.length()-1);
            unite(data1.length()<data2.length()?data1:data2,abs(int(data1.length()-data2.length())));
            if(data2[0]>data1[0])  
                sign='-';
            sum=caculate_subtract(data1>data2?data1:data2,data1<data2?data1:data2);
        }
        else
        {
            unite(data1.length()<data2.length()?data1:data2,abs(int(data1.length()-data2.length())));
            sum=caculate_add(data1,data2);
        }
        
    }
    if(sign=='-')
        sum=sign+sum;
    return sum;
}