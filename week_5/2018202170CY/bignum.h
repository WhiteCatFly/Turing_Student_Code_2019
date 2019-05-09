#ifndef BIG_NUM_H
#define BIG_NUM_H

const int mod = 10;
class bignum
{
private:
    std::vector<int> mem;
    int sign;
public:
    bignum(){};
    ~bignum(){};
    friend bignum operator +(const bignum &a, const bignum &b);
    friend bignum operator -(const bignum &a, const bignum &b);
    friend bignum operator *(const bignum &a, const bignum &b);
    friend bignum operator /(const bignum &a, const bignum &b);
    friend bignum operator %(const bignum &a, const bignum &b);
    friend bool operator ==(const bignum &a, const bignum &b);
    friend bool operator <(const bignum &a, const bignum &b);
    friend bool operator <=(const bignum &a, const bignum &b);
    friend bool operator >(const bignum &a, const bignum &b);
    friend std::ostream& operator <<(std::ostream &out, const bignum &num);
    bignum(std::string str);
    bignum(long long num);
    bignum(unsigned long long num);
    bignum(int num);
    bignum(unsigned int num);
    int length() const
    {
        return mem.size();
    }
    void push_back(int num)
    {
        mem.push_back(num);
    }
    void pop_back()
    {
        mem.pop_back();
    }
    int& operator [](int id)
    {
        return mem[id];
    }
    int operator [](int id) const
    {
        return mem[id];
    }
    friend bignum abs(const bignum &a);
};

#endif