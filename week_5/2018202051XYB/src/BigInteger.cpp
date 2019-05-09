#include <vector>
#include <iostream>
#include <fstream>

#include "BigInteger.h"

#define max(x, y) ((x)>(y)?(x):(y))
#define min(x, y) ((x)<(y)?(x):(y))

int FFT_LEN;
std::vector<int> rev;

void BigInteger::normalize()
{
    len = data.size();
    for(int i = 0; i < len - 1; i++)
        if(data[i] >= BASE)
        {
            data[i + 1] += data[i] / BASE;
            data[i] %= BASE;
        }

    while(data[len - 1] >= BASE)
    {
        data.push_back(data[len - 1] / BASE),
        data[len - 1] %= BASE;
        len++;
    }

    for(int i = 0; i < len - 1; i++)
        while(data[i] < 0)
        {
            data[i] += BASE;
            data[i + 1] --;
        }

    while(len > 1 && data[len - 1] == 0)
    {
        data.pop_back();
        len--;
    }
    if(len == 1 && data[0] == 0)
    {
        symbol = SYMBOL_POSI;
    }
}

BigInteger::BigInteger(int x)
{
    if(x < 0)
    {
        x = -x;
        symbol = SYMBOL_NEGA;
    }
    else 
        symbol = SYMBOL_POSI;
    data.push_back(x);
    normalize();
}

BigInteger::BigInteger(std::string str)
{
    if(str[0] == '-')
    {   
        symbol = SYMBOL_NEGA;
        str = str.substr(1);
    }
    else 
        symbol = SYMBOL_POSI;

    len = str.size();
    for(int i = len - 1; i >= 0; i--)
        data.push_back(str[i] - '0');
    normalize();
}

BigInteger operator-(BigInteger a)
{
    a.symbol ^= 1;
    return a;
}

BigInteger abs(BigInteger a)
{
    a.symbol = SYMBOL_POSI;
    return a;
}

// a >= 0 b >= 0 return a + b
BigInteger raw_add(BigInteger a, BigInteger b)
{
    BigInteger x;
    x.symbol = SYMBOL_POSI;
    int maxLen = max(a.len, b.len),
        minLen = min(a.len, b.len);

    for(int i = 0; i < minLen; i++)
        x.data.push_back(a.data[i] + b.data[i]);
    if(a.len > b.len)
        for(int i = minLen; i < maxLen; i++)
            x.data.push_back(a.data[i]);
    else 
        for(int i = minLen; i < maxLen; i++)
            x.data.push_back(b.data[i]);
    x.normalize();
    x.symbol = a.symbol;
    return x;
}
// a >= b >= 0  return a - b
BigInteger raw_minus(BigInteger a, BigInteger b)
{
    BigInteger x;
    x.symbol = SYMBOL_POSI;
    int maxLen = max(a.len, b.len),
        minLen = min(a.len, b.len);
    for(int i = 0; i < minLen; i++)
        x.data.push_back(a.data[i] - b.data[i]);
    for(int i = minLen; i < maxLen; i++)
        x.data.push_back(a.data[i]);
    x.normalize();
    return x;
}

bool operator==(BigInteger a, BigInteger b)
{
    if(a.symbol != b.symbol || a.len != b.len)
        return false;
    for(int i = 0; i < a.len; i++)
        if(a.data[i] != b.data[i])
            return false;
    return true;
}

bool operator!=(BigInteger a, BigInteger b)
{
    return ! (a == b);
}

bool operator<(BigInteger a, BigInteger b)
{
    if(a.symbol != b.symbol)
        return a.symbol == SYMBOL_NEGA;
    if(a.symbol == SYMBOL_NEGA)
        return (-b) < (-a);
    if(a.len != b.len)
        return a.len < b.len;
    for(int i = a.len - 1; i >= 0; i--)
        if(a.data[i] != b.data[i])
            return a.data[i] < b.data[i];
    return false;
}

bool operator>(BigInteger a, BigInteger b)
{
    return !((a < b) || (a == b));
}
bool operator<=(BigInteger a, BigInteger b)
{
    return (a < b) || (a == b);
}
bool operator>=(BigInteger a, BigInteger b)
{
    return (a > b) || (a == b);
}

BigInteger operator+(BigInteger a, BigInteger b)
{
    if(a.symbol == b.symbol)
        if(a.symbol == SYMBOL_POSI) 
            return raw_add(a, b);    // a > 0 b > 0
        else
            return -raw_add(-a, -b); // a < 0 b < 0
    else
        if(a.symbol == SYMBOL_NEGA) 
            return b - (-a);         // a < 0 b > 0
        else
            return a - (-b);         // a > 0 b < 0
}

BigInteger operator-(BigInteger a, BigInteger b)
{
    if(a.symbol != b.symbol)
        if(a.symbol == SYMBOL_POSI)  
            return a + (-b);         // a > 0 b < 0
        else 
            return a + (-b);         // a < 0 b > 0 
    else
        if(a.symbol == SYMBOL_NEGA)
            return -((-a) - (-b));   // a < 0 b < 0
        else if(abs(a) > abs(b))
            return raw_minus(a, b);  // a > b > 0
        else 
            return -(b - a);         // b > a > 0
}


BigInteger operator*(BigInteger a, BigInteger b)
{
    BigInteger x;
    x.symbol = a.symbol ^ b.symbol;
    InitFFT(a.len - 1, b.len - 1);
    std::vector<Complex> A, B;
    for(int i = 0; i < FFT_LEN; i++)
    {
        A.push_back(Complex(0, 0));
        B.push_back(Complex(0, 0));
    }
    for(int i = a.len - 1; i >= 0; i--)
        A[i] = Complex(a.data[i], 0);
    for(int i = b.len - 1; i >= 0; i--)
        B[i] = Complex(b.data[i], 0);

    FFT(A, 1);
    FFT(B, 1);
    for(int i = 0; i < FFT_LEN; i++)
        A[i] = A[i] * B[i];
    FFT(A, -1);
    for(int i = 0; i < a.len + b.len - 1; i++)
        x.data.push_back((int)(A[i].r + 0.5));
    x.normalize();
    return x;
}
/*
BigInteger operator*(BigInteger a, BigInteger b)
{
    BigInteger x;
    x.symbol = a.symbol ^ b.symbol;
    x.len = a.len + b.len;
    for(int i = 0; i < x.len; i++)
        x.data.push_back(0);
    for(int i = 0; i < a.len; i++)
        for(int j = 0; j < b.len; j++)
            x.data[i + j] += a.data[i] * b.data[j];
    x.normalize();
    return x;
}*/

bool div_check(BigInteger a, BigInteger b, int pos)
{
    if(pos + b.len - 1 > a.len - 1)
        return false;
    if(pos + b.len <= a.len - 1)
        a.data[pos + b.len - 1] += a.data[pos + b.len] * BASE;

    for(int i = b.len - 1; i >= 0; i--)
        if(b.data[i] > a.data[pos + i])
            return false;
        else 
        {

            a.data[pos + i] -= b.data[i];
            if(pos + i - 1 >= 0)
                a.data[pos + i - 1] += a.data[pos + i] * BASE;
        }
    return true;
}

void div_minus(BigInteger &a, BigInteger b, int pos)
{
    if(pos + b.len <= a.len - 1)
    {
        a.data[pos + b.len - 1] += a.data[pos + b.len] * BASE;
        a.data[pos + b.len] = 0;
    }
    for(int i = b.len - 1; i >= 0; i--)
        a.data[pos + i] -= b.data[i];
    
    a.normalize();
  
}

BigInteger operator/(BigInteger a, BigInteger b)
{
    if(abs(a) < abs(b))
        return BigInteger(0);
    if(b == 0)
        return a;
    BigInteger x;
    x.symbol = a.symbol ^ b.symbol;
   
    for(int i = 0; i < a.len - b.len + 1; i++)
        x.data.push_back(0); 
    
    for(int i = a.len - b.len; i >= 0; i--)
    {
        while(div_check(a, b, i))
        {
            div_minus(a, b, i);
            x.data[i]++;
        }
    }
    x.normalize();
    return x;
}

std::ostream& operator<<(std::ostream &os, BigInteger a)
{
    a.normalize();
    if(a.symbol == SYMBOL_NEGA)
        os << "-";
    for(int i = a.len - 1; i >= 0; i--)
        os << a.data[i];
}

BigInteger operator+(int k, BigInteger a)
{
    return (BigInteger)k + a;
}
BigInteger operator-(int k, BigInteger a)
{
    return (BigInteger)k - a;
}
BigInteger operator*(int k, BigInteger a)
{
    return (BigInteger)k * a;
}
BigInteger operator/(int k, BigInteger a)
{
    return (BigInteger)k / a;
}
BigInteger operator+(BigInteger a, int k)
{
    return (BigInteger)k + a;
}
BigInteger operator-(BigInteger a, int k)
{
    return (BigInteger)k - a;
}
BigInteger operator*(BigInteger a, int k)
{
    return (BigInteger)k * a;
}
BigInteger operator/(BigInteger a, int k)
{
    return (BigInteger)k / a;
}

int toint(BigInteger a)
{
    int f = a.symbol == SYMBOL_NEGA?-1 : 1;
    int ret = 0;
    for(int i = a.len - 1; i >= 0; i--)
        ret = ret * 10 + a.data[i];
    return ret * f;
} 

void swap(Complex &a, Complex &b)
{
    Complex c = a;
    a = b;
    b = c;
}

void InitFFT(int l1, int l2)
{
    rev.clear();
    for(FFT_LEN = 1; FFT_LEN <= l1 + l2; FFT_LEN <<= 1);
    for(int i = 0; i < FFT_LEN; i++)
        rev.push_back(0);

    for(int i = 1; i < FFT_LEN; i++)
        if(i & 1)
            rev[i] = (rev[i >> 1] >> 1) ^ (FFT_LEN >> 1);
        else
            rev[i] = (rev[i >> 1] >> 1);
}

void FFT(std::vector<Complex> &x, int op)
{
    for(int i = 0; i < FFT_LEN; i++)
        if(i < rev[i])
        {
            Complex t = x[i];
            x[i] = x[rev[i]];
            x[rev[i]] = t;
        }
    for(int h = 2; h <= FFT_LEN; h <<= 1)
    {
        Complex wn(cos(2 * PI / h), sin(2 * PI * op / h));
        for(int i = 0; i < FFT_LEN; i += h)
        {
            Complex w(1, 0);
            for(int j = i; j < i + h / 2; j++)
            {
                Complex u = x[j], t = x[j + h / 2];
                x[j] = u + w * t;
                x[j + h / 2] = u - w * t;
                w = w * wn;
            }
        }
    }
    if(op == -1)
        for(int i = 0; i < FFT_LEN; i++)
            x[i].r /= FFT_LEN;
}

