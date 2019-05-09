#ifndef _BIGINTEGER_H
#define _BIGINTEGER_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#define BASE 10
#define PI acos(-1.0)

#define SYMBOL_NEGA true
#define SYMBOL_POSI false

class BigInteger
{
private:
    std::vector<int> data;
    int len;
    bool symbol; 
    void normalize();

public:
    BigInteger()
    {
        symbol = SYMBOL_POSI;
    }
    BigInteger(int x);
    BigInteger(std::string str);

    friend BigInteger fft_mul(BigInteger a, BigInteger b);

    friend BigInteger operator-(BigInteger a);
    friend BigInteger abs(BigInteger a);
    friend BigInteger raw_add(BigInteger a, BigInteger b);
    friend BigInteger raw_minus(BigInteger a, BigInteger b);

    friend bool operator==(BigInteger a, BigInteger b);
    friend bool operator<(BigInteger a, BigInteger b);

    friend BigInteger operator+(BigInteger a, BigInteger b);
    friend BigInteger operator-(BigInteger a, BigInteger b);
    friend BigInteger operator*(BigInteger a, BigInteger b);
    friend BigInteger operator/(BigInteger a, BigInteger b);

    friend bool div_check(BigInteger a, BigInteger b, int pos);
    friend void div_minus(BigInteger &a, BigInteger b, int pos);

    friend std::ostream& operator<<(std::ostream& os, BigInteger a);

    friend int toint(BigInteger a);
};

int toint(BigInteger a); //自然溢出

struct Complex
{
    double r, i;
    Complex(double rx = 0.0, double ix = 0.0)
    {
        r = rx;
        i = ix;
    }
    Complex operator+(Complex b)
    {
        return Complex(r + b.r, i + b.i);
    }
    Complex operator-(Complex b)
    {
        return Complex(r - b.r, i - b.i);
    }
    Complex operator*(Complex b)
    {
        return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
};
   
extern int FFT_LEN;
extern std::vector<int>rev;

BigInteger operator-(BigInteger a);
BigInteger abs(BigInteger a);

BigInteger raw_add(BigInteger a, BigInteger b);
BigInteger raw_minus(BigInteger a, BigInteger b);

bool operator==(BigInteger a, BigInteger b);
bool operator!=(BigInteger a, BigInteger b);
bool operator<(BigInteger a, BigInteger b);
bool operator>(BigInteger a, BigInteger b);
bool operator<=(BigInteger a, BigInteger b);
bool operator>=(BigInteger a, BigInteger b);

BigInteger operator+(BigInteger a, BigInteger b);
BigInteger operator-(BigInteger a, BigInteger b);
BigInteger operator*(BigInteger a, BigInteger b);
BigInteger operator/(BigInteger a, BigInteger b);

bool div_check(BigInteger a, BigInteger b, int pos);
void div_minus(BigInteger &a, BigInteger b, int pos);

std::ostream& operator<<(std::ostream& os, BigInteger a);

BigInteger operator+(int k, BigInteger a);
BigInteger operator-(int k, BigInteger a);
BigInteger operator*(int k, BigInteger a);
BigInteger operator/(int k, BigInteger a);

BigInteger operator+(BigInteger a, int k);
BigInteger operator-(BigInteger a, int k);
BigInteger operator*(BigInteger a, int k);
BigInteger operator/(BigInteger a, int k);

void swap(Complex &a, Complex &b);
void InitFFT(int l1, int l2);
void FFT(std::vector<Complex> &x, int op);


#endif