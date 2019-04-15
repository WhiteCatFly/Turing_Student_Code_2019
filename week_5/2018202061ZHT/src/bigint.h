#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>

typedef long long ll;

const int MAXN = 1e4+5;
const int init_len = 1;
const int ascii0 = 48;
const int decimal = 10;
const std::string opt = "print.out";

class BigInteger {
private:
	bool sign;
	int len, x[MAXN];
public:
	BigInteger();
	BigInteger(const std::string & s);
	BigInteger(const ll & v);
	BigInteger(const BigInteger & rhs);
	~BigInteger(){}
	bool operator < (const BigInteger & rhs) const;
	bool operator > (const BigInteger & rhs) const;
	BigInteger operator -() const;
	BigInteger operator +(const BigInteger & rhs) const;
	BigInteger operator -(const BigInteger & rhs) const;
	BigInteger operator *(const BigInteger & rhs) const;
	BigInteger operator /(const BigInteger & rhs) const;
	BigInteger operator %(const BigInteger & rhs) const;
	BigInteger move (int w) const;
	friend BigInteger operator +(ll v, const BigInteger &t);
	friend BigInteger operator *(ll v, const BigInteger &t);
	friend std::ostream & operator << (std::ostream & os, const BigInteger & t);
};

#endif
