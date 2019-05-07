#include <iostream>
#include "BigInteger.h"
using namespace std;

BigInteger::BigInteger()
{
}

BigInteger::BigInteger(const string s)
{
	minus = s[0] == '-';
	if (s[0] == '-')
	{
		for (int i = s.length() - 1; i > 0; i--)
			bit.push_back(s[i] - '0');
	}
	else
	{
		for (int i = s.length() - 1; i >= 0; i--)
			bit.push_back(s[i] - '0');
	}
}

BigInteger::BigInteger(long long v)
{
	minus = v < 0;
	if (v == 0)
	{
		bit.push_back(0);
		return;
	}
	if (v < 0) v = -v;
	while (v > 0)
	{
		bit.push_back(v % 10);
		v /= 10;
	}
}

BigInteger::~BigInteger()
{
}

void swap(BigInteger &a, BigInteger &b)
{
	BigInteger t = a;
	a = b;
	b = t;
}

bool operator ==(const BigInteger a, const BigInteger b)
{
	if (a.bit.size() != b.bit.size()) return false;
	if (a.minus != b.minus)
	{
		if (a.bit.size() == 1 && a.bit[0] == 0 && b.bit[0] == 0) return true;
		else return false;
	}
	for (int i = 0; i < a.bit.size(); i++)
	{
		if (a.bit[i] != b.bit[i]) return false;
	}
	return true;
}

bool operator <(const BigInteger a, const BigInteger b)
{
	if (a.minus != b.minus) return a.minus > b.minus;
	if (a.bit.size() != b.bit.size()) return (!a.minus) * (a.bit.size() < b.bit.size());
	bool f = false;
	for (int i = a.bit.size() - 1; i >= 0; i--)
	{
		if (a.bit[i] != b.bit[i])
		{
			f = a.bit[i] < b.bit[i];
			break;
		}
	}
	return (!a.minus) * f;
}

bool operator <=(const BigInteger a, const BigInteger b)
{
	return a == b || a < b;
}

bool operator >(const BigInteger a, const BigInteger b)
{
	if (a.minus != b.minus) return a.minus < b.minus;
	if (a.bit.size() != b.bit.size()) return (!a.minus) * (a.bit.size() > b.bit.size());
	bool f = false;
	for (int i = a.bit.size() - 1; i >= 0; i--)
	{
		if (a.bit[i] != b.bit[i])
		{
			f = a.bit[i] > b.bit[i];
			break;
		}
	}
	return (!a.minus) * f;
}

bool operator >=(const BigInteger a, const BigInteger b)
{
	return a == b || a > b;
}

BigInteger operator +(BigInteger a, BigInteger b)
{
	BigInteger ans;
	bool type = a.minus ^ b.minus;
	if (type == false)
	{
		ans.minus = a.minus;
		if (a.bit.size() < b.bit.size()) swap(a, b);
		for (int i = 0; i < b.bit.size(); i++)
			ans.bit.push_back(a.bit[i] + b.bit[i]);
		for (int i = b.bit.size(); i < a.bit.size(); i++)
			ans.bit.push_back(a.bit[i]);
		for (int i = 0; i < ans.bit.size(); i++)
		{
			if (ans.bit[i] >= 10)
			{
				if (i != ans.bit.size() - 1) ans.bit[i + 1]++;
				else ans.bit.push_back(1);
				ans.bit[i] -= 10;
			}
		}
	}
	else
	{
		BigInteger ta = a, tb = b;
		ta.minus = 0;
		tb.minus = 0;
		if (ta < tb) swap(a, b);
		ans.minus = a.minus;
		for (int i = 0; i < b.bit.size(); i++)
			ans.bit.push_back(a.bit[i] - b.bit[i]);
		for (int i = b.bit.size(); i < a.bit.size(); i++)
			ans.bit.push_back(a.bit[i]);
		for (int i = 0; i < ans.bit.size(); i++)
		{
			if (ans.bit[i] < 0)
			{
				ans.bit[i + 1]--;
				ans.bit[i] += 10;
			}
		}
		while (ans.bit.size() > 1 && ans.bit[ans.bit.size() - 1] == 0) ans.bit.pop_back();
	}
	return ans;
}

BigInteger operator -(BigInteger a, BigInteger b)
{
	b.minus ^= 1;
	return a + b;
}

BigInteger operator *(BigInteger a, BigInteger b)
{
	BigInteger ans;
	ans.minus = a.minus ^ b.minus;
	for (int i = 1; i < a.bit.size() + b.bit.size(); i++) ans.bit.push_back(0);
	for (int i = 0; i < a.bit.size(); i++)
	{
		for (int j = 0; j < b.bit.size(); j++)
			ans.bit[i + j] += a.bit[i] * b.bit[j];
	}
	for (int i = 0; i < ans.bit.size(); i++)
	{
		if (ans.bit[i] >= 10)
		{
			if (i != ans.bit.size() - 1) ans.bit[i + 1] += ans.bit[i] / 10;
			else ans.bit.push_back(ans.bit[i] / 10);
			ans.bit[i] %= 10;
		}
	}
	return ans;
}

BigInteger operator /(BigInteger a, BigInteger b)
{
	BigInteger ans;
	bool tminus = a.minus ^ b.minus;
	a.minus = b.minus = false;
	for (int i = 1; i <= a.bit.size() - b.bit.size() + 1; i++) ans.bit.push_back(0);
	for (int i = a.bit.size() - b.bit.size() + 1; i >= 0; i--)
	{
		int l = 0, r = 9, t = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			ans.bit[i] = mid;
			if (ans * b <= a)
			{
				t = mid;
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
		ans.bit[i] = t;
	}
	while (ans.bit.size() > 1 && ans.bit[ans.bit.size() - 1] == 0) ans.bit.pop_back();
	ans.minus = tminus;
	return ans;
}

BigInteger operator %(BigInteger a, BigInteger b)
{
	return a - a / b * b;
}

ostream & operator <<(ostream &os, BigInteger a)
{
	if (a.minus) os << '-';
	for (int i = a.bit.size() - 1; i >= 0; i--)
		os << a.bit[i];
	return os;
}