#include <cmath>
#include <cctype>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <type_traits>

#include "bigint.h"

BigInt & BigInt::operator = (const std::string &str_num)
{
    m_is_neg = false;
    for (int i = str_num.size() - 1; i >= 0; --i)
    {
        if (i == 0 && str_num[i] == '-')
        {
            m_is_neg = true;
            break;
        }
        if (!isdigit(str_num[i]))
        {
            std::cerr << "error: invalid parameter for constructor\n";
            exit(1);
        }
        m_num.push_back(str_num[i] - '0');
    }
    return *this;
}

void BigInt::normalize()
{
    while (size() > 1 && (*this)[size()-1] == 0)
    {
        resize(size() - 1);
    }
    if (size() == 1 && (*this)[0] == 0)
    {
        m_is_neg = false;
    }
}

BigInt BigInt::operator - () const
{
    BigInt res = BigInt(!m_is_neg, m_num);
    res.normalize();
    return res;
}

bool BigInt::operator < (const BigInt &rhs) const
{
    if (m_is_neg ^ rhs.m_is_neg)
    {
        return m_is_neg;
    }
    else if ((*this).m_is_neg)
    {
        return -(*this) < -rhs;
    }
    else if (size() != rhs.size())
    {
        return size() < rhs.size();
    }
    for (int i = size() - 1; i >= 0; --i)
    {
        if ((*this)[i] != rhs[i])
        {
            return (*this)[i] < rhs[i];
        }
    }
    return false;
}

BigInt BigInt::unsigned_add(const BigInt &rhs) const
{
    BigInt res;
    res.resize(std::max(size(), rhs.size()) + 1);
    for (int i = 0; i < res.size() - 1; i++)
    {
        res[i] += (*this)[i] + rhs[i];
        if (res[i] >= BASE)
        {
            res[i] -= BASE;
            ++res[i + 1];
        }
    }
    res.normalize();
    return res;
}

BigInt BigInt::unsigned_subtract(const BigInt &rhs) const
{
    BigInt res = *this;
    for (int i = 0; i < res.size(); ++i)
    {
        res[i] -= rhs[i];
        if (res[i] < 0)
        {
            --res[i + 1];
            res[i] += BASE;
        }
    }
    res.normalize();
    return res;
}

BigInt BigInt::operator + (const BigInt &rhs) const
{
    if (m_is_neg ^ rhs.m_is_neg)
    {
        if (*this < 0)
        {
            if (abs() <= rhs.abs())
            {
                return rhs.unsigned_subtract(-(*this));
            }
            else
            {
                return -((-(*this)).unsigned_subtract(rhs));
            }
        }
        else
        {
            if (rhs.abs() <= abs())
            {
                return unsigned_subtract(-rhs);
            }
            else
            {
                return -((-rhs).unsigned_subtract(*this));
            }
        }
    }
    else if (*this < 0)
    {
        return -(-(*this) - rhs);
    }
    else
    {
        return unsigned_add(rhs);
    }
}

BigInt BigInt::operator * (const BigInt &rhs) const
{
    BigInt res;
    res.m_is_neg = m_is_neg ^ rhs.m_is_neg;
    res.resize(size() + rhs.size());
    for (int i = 0; i < size(); i++)
    {
        for (int j = 0; j < rhs.size(); j++)
        {
            res[i + j] += (*this)[i] * rhs[j];
            if (res[i + j] >= BASE)
            {
                res[i + j + 1] += res[i + j] / BASE;
                res[i + j] %= BASE;
            }
        }
    }
    res.normalize();
    return res;
}

BigInt BigInt::operator / (const BigInt &rhs) const
{
    BigInt res;
    res.resize(size());
    BigInt remain = 0;
    for (int i = size() - 1; i >= 0; --i)
    {
        (remain *= BASE) += (*this)[i];
        for (int j = BASE - 1; j >= 0; --j)
        {
            if (rhs.abs() * j <= remain)
            {
                remain -= rhs.abs() * j;
                res[i] = j;
                break;
            }
        }
    }
    res.m_is_neg = (*this).m_is_neg ^ rhs.m_is_neg;
    res.normalize();
    return res;
}

std::istream & operator >> (std::istream & is, BigInt & bigint_num)
{
    std::string str;
    is >> str;
    bigint_num = BigInt(str);
    return is;
}

std::ostream & operator << (std::ostream & os, const BigInt & bigint_num)
{
    if (bigint_num.m_is_neg)
    {
        os << '-';
    }
    for (int i = bigint_num.size() - 1; i >= 0; --i)
    {
        os << bigint_num[i];
    }
    return os;
}
