#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

class BigInt
{
private:
    static const int BASE = 10;
    bool m_is_neg;
    std::vector<int> m_num;
    BigInt unsigned_add(const BigInt &rhs) const;
    BigInt unsigned_subtract(const BigInt &rhs) const;

public:

    BigInt() { *this = 0; }
    BigInt(const char *p) { *this = (std::string) p; }
    BigInt(const std::string &str_num) { *this = str_num; }
    template <typename T> BigInt(T num) { *this = num; }
    BigInt(bool is_neg, std::vector<int> num):
        m_is_neg(is_neg), m_num(num) {}

    BigInt & operator = (const char *p)
    {
        return *this = (std::string) p;
    }
    BigInt & operator = (const std::string &str_num);
    template <typename T> BigInt & operator = (T num)
    {
        return *this = std::to_string(num);
    }

    int size() const { return m_num.size(); }
    void resize(int sz) { m_num.resize(sz); }
    BigInt abs() const { return BigInt(false, m_num); }
    void normalize();

    const int operator [] (int index) const
    {
        return index >= size() ? 0 : m_num[index];
    }
    int & operator [] (int index) { return m_num[index]; }

    BigInt operator - () const;

    bool operator == (const BigInt &rhs) const
    {
        return m_is_neg == rhs.m_is_neg && m_num == rhs.m_num;
    }
    bool operator != (const BigInt &rhs) const
    {
        return ! (*this == rhs);
    }
    bool operator <  (const BigInt &rhs) const;
    bool operator <= (const BigInt &rhs) const
    {
        return *this < rhs || *this == rhs;
    }
    bool operator >  (const BigInt &rhs) const
    {
        return *this != rhs && ! (*this < rhs);
    }
    bool operator >= (const BigInt &rhs) const
    {
        return *this > rhs || *this == rhs;
    }

    BigInt operator + (const BigInt &rhs) const;
    BigInt operator - (const BigInt &rhs) const
    {
        return *this + -rhs;
    }
    BigInt operator * (const BigInt &rhs) const;
    BigInt operator / (const BigInt &rhs) const;
    BigInt operator % (const BigInt &rhs) const
    {
        return *this - *this / rhs * rhs;
    }

    template <typename T> BigInt & operator += (T num)
    {
        return *this = *this + BigInt(num);
    }

    BigInt & operator += (const BigInt &rhs)
    {
        return *this = *this + rhs;
    }

    template <typename T> BigInt & operator -= (T num)
    {
        return *this = *this - BigInt(num);
    }

    BigInt & operator -= (const BigInt &rhs)
    {
        return *this = *this - rhs;
    }

    template <typename T> BigInt & operator *= (T num)
    {
        return *this = *this * BigInt(num);
    }

    BigInt & operator *= (const BigInt &rhs)
    {
        return *this = *this * rhs;
    }

    template <typename T> BigInt & operator /= (T num)
    {
        return *this = *this / BigInt(num);
    }

    BigInt & operator /= (const BigInt &rhs)
    {
        return *this = *this / rhs;
    }

    template <typename T> BigInt & operator %= (T num)
    {
        return *this = *this % BigInt(num);
    }

    BigInt & operator %= (const BigInt &rhs)
    {
        return *this = *this % rhs;
    }

    BigInt & operator ++ ()
    {
        return *this += 1;
    }
    BigInt operator ++ (int);
    BigInt & operator -- ()
    {
        return *this -= 1;
    }
    BigInt operator -- (int);

    friend std::istream & operator >> (std::istream & is, BigInt & bignum);
    friend std::ostream & operator << (std::ostream & os, const BigInt & bignum);
};

template <typename T> BigInt operator + (const BigInt &a, T b)
{
    return a + BigInt(b);
}

template <typename T> BigInt operator + (T a, const BigInt &b)
{
    return BigInt(a) + b;
}

template <typename T> BigInt operator - (const BigInt &a, T b)
{
    return a - BigInt(b);
}

template <typename T> BigInt operator - (T a, const BigInt &b)
{
    return BigInt(a) - b;
}

template <typename T> BigInt operator * (const BigInt &a, T b)
{
    return a * BigInt(b);
}

template <typename T> BigInt operator * (T a, const BigInt &b)
{
    return BigInt(a) * b;
}

template <typename T> BigInt operator / (const BigInt &a, T b)
{
    return a / BigInt(b);
}

template <typename T> BigInt operator / (T a, const BigInt &b)
{
    return BigInt(a) / b;
}

template <typename T> BigInt operator % (const BigInt &a, T b)
{
    return a % BigInt(b);
}

template <typename T> BigInt operator % (T a, const BigInt &b)
{
    return BigInt(a) % b;
}

#endif