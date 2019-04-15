#include "BigInteger.h"

std::string change(long long int a)
{
    std::string result;
    if(a == 0)
    result += '0';

    while(a)
    {
        result += (a%10+48);
        a = a/10;
        
    }
    reverse(result.begin(),result.end());
    
    return result;
}
std::string add_zero(std::string num,int &begin,int &end)
{
    
    for(int i = begin;i < end;i++)
    {
        num += '0';
        //std::cout << i << std::endl;
    }

    return num;

}
std::string cal_sub(std::string &former,std::string &latter,std::string &result,int &len)
{
    int minus = 0;
    for(int i = 0;i < len;i ++)
    {
        if(i)
        {
            result[i] = (former[i] - latter[i] + minus + 10)%10 + 48;
            minus = (former[i] - latter[i] + minus + 10) / 10 - 1;
        }
        else
        {
            result[i] = (former[i] - latter[i] + 10)%10 + 48;
            minus = (former[i] - latter[i] + 10) / 10 - 1;
        }
       //./astd::cout << minus << std::endl;
        

    }

    return result;
}


std::ostream &operator<<(std::ostream &os,const BigInteger &it)
{
    os << it.number << std::endl;
    return os;
}

BigInteger BigInteger::operator+(BigInteger latter)
{
    BigInteger sum;
    std::string former_num = number;
    std::string latter_num = latter.number;
    reverse(former_num.begin(),former_num.end());
    reverse(latter_num.begin(),latter_num.end());
    former_num += '0';
    latter_num += '0';
  
    int len1 = former_num.length();
    int len2 = latter_num.length();
    int len;
    int plus = 0;
    
    if(len1 > len2) 
    {
        latter_num = add_zero(latter_num,len2,len1);
        len = len1;
    }
    else
    {
        former_num = add_zero(former_num,len1,len2);
        len = len2; 
    } 
    //std::cout << latter.number << std::endl;
    //std::cout << number << std::endl; 
    std::string num(len,'0');
    sum.number = num;
    //std::cout << len << std::endl;
    
    for(int i = 0;i < len;i ++)
    {
        if(i)
        {
            sum.number[i] = (former_num[i] + latter_num[i] + plus - 96)%10 + 48;
            plus = (former_num[i] + latter_num[i] + plus - 96) / 10;

        }
        else
        {
            sum.number[i] = (former_num[i] + latter_num[i] - 96)%10 + 48;
            plus = (former_num[i] + latter_num[i] - 96)/10;
        }
        
        
    }
    if (sum.number[len - 1] == '0') {
        sum.number.erase(sum.number.end()-1);
    }

    //std::cout << sum.number << std::endl;
    reverse(sum.number.begin(),sum.number.end());
    return sum;
    
}
BigInteger BigInteger::operator-(BigInteger latter)
{
    BigInteger sub;
    std::string former_num = number;
    std::string latter_num = latter.number;

    reverse(former_num.begin(),former_num.end());
    reverse(latter_num.begin(),latter_num.end());
    int len1 = former_num.length();
    int len2 = latter_num.length();
    int len;
    int mark = 0;
    int minus;

    if(len1 > len2 || (number >= latter.number && len1 == len2))
    {
        mark = 1;
        len = len1;
        latter_num = add_zero(latter_num,len2,len1);
    }
    else
    {
        mark = -1;
        len = len2;
        former_num = add_zero(former_num,len1,len2);
    }
    std::string num(len,'0');
    sub.number = num;
    //std::cout << former_num << std::endl;
    //std::cout << latter_num << std::endl;
    //std::cout << mark << std::endl;

    if(mark == 1)
    {
        sub.number = cal_sub(former_num,latter_num,sub.number,len);
    }
    else
    {            
        sub.number = cal_sub(latter_num,former_num,sub.number,len);
    }
    while(sub.number[len - 1] == '0')
    {
        sub.number.erase(sub.number.end()-1);
        len -- ;
        if(len == 1)
        break;

    }
    if(mark == -1)
    sub.number += '-';

    reverse(sub.number.begin(),sub.number.end());
    

    return sub;

}
BigInteger BigInteger::operator*(BigInteger latter)
{
    BigInteger multi;
    std::string former_num = number;
    std::string latter_num = latter.number;

    reverse(former_num.begin(),former_num.end());
    reverse(latter_num.begin(),latter_num.end());
    int len1 = former_num.length();
    int len2 = latter_num.length();
    int len = len1 + len2;
    std::string num(len,'0');
    multi.number = num;
    //std::cout << multi.number << std::endl;

    for(int i = 0;i < len2;i ++)
    {
        int plus = 0;

        for(int j = 0;j <= len1; j ++)
        {
         
            if(j < len1 && j)
            {
                multi.number[i + j] += ((latter_num[i] - 48)*(former_num[j] - 48) + plus)%10;
                plus = ((latter_num[i] - 48)*(former_num[j] - 48) + plus) / 10;

            }
            else if(j == 0)
            {
                multi.number[i + j] += ((latter_num[i] - 48)*(former_num[j] - 48))%10;
                plus = ((latter_num[i] - 48)*(former_num[j] - 48)) / 10;
            }
            else
            {
                //std::cout << plus << std::endl;
                multi.number[i + j] += plus;
                plus = 0;
            }
            //std::cout << multi.number << std::endl;
            //std::cout << plus << std::endl;
        }

    }
    int plus = 0;
    for(int i = 0;i < len;i ++)
    {
        int temp = multi.number[i] + plus - 48;
        multi.number[i] = temp % 10 + 48; 
        plus = temp / 10;
        //std::cout << plus << std::endl;
    }
      while(multi.number[len - 1] == '0')
    {
        multi.number.erase(multi.number.end()-1);
        len -- ;
        if(len == 1)
        break;

    }
    reverse(multi.number.begin(),multi.number.end());

    return multi;
    
}