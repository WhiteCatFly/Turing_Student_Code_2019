#include <string>
#include <vector>
#ifndef _BIGINTEGER_H_
#define _BIGINTEGER_H_

class BigInteger
{
private:
	bool minus;
	std::vector<short> bit;
public:
	BigInteger();
	BigInteger(const std::string s);
	BigInteger(long long v);
	~BigInteger();
	friend void swap(BigInteger& a, BigInteger& b);
	friend bool operator ==(const BigInteger a, const BigInteger b);
	friend bool operator <(const BigInteger a, const BigInteger b);
	friend bool operator <=(const BigInteger a, const BigInteger b);
	friend bool operator >(const BigInteger a, const BigInteger b);
	friend bool operator >=(const BigInteger a, const BigInteger b);
	friend BigInteger operator +(BigInteger a, BigInteger b);
	friend BigInteger operator -(BigInteger a, BigInteger b);
	friend BigInteger operator *(BigInteger a, BigInteger b);
	friend BigInteger operator /(BigInteger a, BigInteger b);
	friend BigInteger operator %(BigInteger a, BigInteger b);
	friend std::ostream& operator <<(std::ostream& os, BigInteger a);
};

#endif