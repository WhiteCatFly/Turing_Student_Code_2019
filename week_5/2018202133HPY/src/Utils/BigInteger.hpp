#ifndef _COWR_UTILS_BIGINT
#define _COWR_UTILS_BIGINT

#include <string>
#include <vector>

namespace cowr {

class BigInteger {
protected:
    static inline constexpr int base = 10;
    static inline constexpr int base_length = 1;

    bool negative;
    std::vector<long long> data;

    void _shrink_to_fit()
    {
        auto it = data.end();
        it--;

        while (it != data.begin() && *it == 0)
            it--;

        if (it == data.begin())
            it++;

        data.erase(it, data.end());
    }

public:
    BigInteger()
        : negative(false)
        , data(1, 0)
    {
    }
    BigInteger(const BigInteger& bigint) = default;
    BigInteger(BigInteger&& bigint) = default;

    BigInteger(const std::string& str)
        : BigInteger(valueOf(str))
    {
    }

    BigInteger(long long val)
        : BigInteger(valueOf(val))
    {
    }

    void shrink_to_fit()
    {
        data.shrink_to_fit();
    }

    std::string toString() const;

    BigInteger operator-() const
    {
        BigInteger ret = *this;
        ret.negative ^= true;

        return ret;
    }

    friend BigInteger operator+(const BigInteger& l, long long r)
    {

        if (l.negative ^ (r < 0)) {
            return l - (-r);
        } else {

            BigInteger ret = l;

            long long tmp = r;

            while (tmp)
                ret.data.push_back(0), tmp /= base;

            ret.data[0] += r;

            for (int i = 0;; i++) {
                if (ret.data[i] >= base)
                    ret.data[i + 1] += ret.data[i] / base, ret.data[i] %= base;
                else
                    break;
            }

            while (ret.data.size() > 1 && ret.data.back() == 0)
                ret.data.pop_back();

            return ret;
        }
    }

    friend BigInteger operator-(const BigInteger& l, long long r)
    {
        if (l.negative ^ (r < 0)) {
            return l + (-r);
        } else {
            r = r > 0 ? r : -r;

            BigInteger ret = l;

            long long tmp = r;

            while (tmp)
                ret.data.push_back(0), tmp /= base;
            ret.data.push_back(0); // sign

            ret.data[0] -= r;

            for (int i = 0; i + 1 < ret.data.size(); i++) {
                if (ret.data[i] < 0)
                    ret.data[i + 1] += (ret.data[i] - base + 1) / base, ret.data[i] = (ret.data[i] % base + base) % base;
                else
                    break;
            }

            if (ret.data.back() < 0) {
                ret.data.back() = base - 1;
                for (auto& x : ret.data)
                    x = base - x - 1;

                ret.data[0]++;

                for (int i = 0;; i++) {
                    if (ret.data[i] >= base)
                        ret.data[i + 1] += ret.data[i] / base, ret.data[i] %= base;
                    else
                        break;
                }

                ret.negative ^= true;
            }

            while (ret.data.size() > 1 && ret.data.back() == 0)
                ret.data.pop_back();

            return ret;
        }
    }
    friend BigInteger operator*(const BigInteger& l, long long r)
    {
        BigInteger ret = l;

        long long tmp = r;

        while (tmp)
            ret.data.push_back(0), tmp /= base;

        for (auto it = ret.data.begin(), end = ret.data.end(); it != end; it++)
            *it *= r;

        for (int i = 0;; i++) {
            if (ret.data[i] >= base)
                ret.data[i + 1] += ret.data[i] / base, ret.data[i] %= base;
            else
                break;
        }

        while (ret.data.size() > 1 && ret.data.back() == 0)
            ret.data.pop_back();

        ret.negative ^= (r < 0);

        return ret;
    }

    friend BigInteger operator+(const BigInteger& l, const BigInteger& r);
    friend BigInteger operator-(const BigInteger& l, const BigInteger& r);
    friend BigInteger operator*(const BigInteger& l, const BigInteger& r);

    BigInteger& operator=(long long val)
    {
        return ((*this) = valueOf(val));
    }

    BigInteger& operator=(const BigInteger& r)
    {
        negative = r.negative;
        data = r.data;

        return *this;
    }

    BigInteger& operator=(BigInteger&& r)
    {
        negative = r.negative;
        data = std::move(r.data);

        return *this;
    }

    friend BigInteger abs(const BigInteger& l)
    {
        BigInteger ret = l;
        ret.negative = false;
        return ret;
    }

    // friend BigInteger operator/(const BigInteger& l, const BigInteger& r)
    // {
    //     return div(l, r).first;
    // }

    // friend BigInteger operator%(const BigInteger& l, const BigInteger& r)
    // {
    //     return div(l, r).second;
    // }

    friend std::pair<BigInteger, BigInteger> div(const BigInteger& l, const BigInteger& r);

    static BigInteger valueOf(long long);
    static BigInteger valueOf(const std::string&);

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bigint)
    {
        return os << bigint.toString();
    }
};
}

#endif
