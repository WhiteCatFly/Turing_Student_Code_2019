#include "BigInteger.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

#include "FFT.hpp"

namespace cowr {

BigInteger BigInteger::valueOf(long long x)
{
    BigInteger bigint;

    if (x < 0)
        bigint.negative = true, x = -x;

    long long width = 0, temp = x;

    while (temp)
        width++, temp /= base;

    if (width) {

        bigint.data.resize(width);

        for (int i = 0; i < width; i++) {
            bigint.data[i] = x % base;
            x /= base;
        }
    }

    return bigint;
}

BigInteger BigInteger::valueOf(const std::string& x)
{
    BigInteger bigint;

    auto it = x.begin(), end = x.end();

    if (*it == '-')
        bigint.negative = true, it++;

    while (it != end && *it == '0')
        it++;

    int dis = (std::distance(it, end) + base_length - 1) / base_length;

    if (dis) {
        bigint.data.resize(dis);
        end--;

        for (int i = 0; i < dis; i++) {
            long long val = 0;
            long long multiplier = 1;
            for (int j = 0; j < base_length; j++, end--, multiplier *= 10) {
                val = val + multiplier * (*end - '0');

                if (end == it)
                    break;
            }
            bigint.data[i] = val;
        }
    }

    return bigint;
}

std::string BigInteger::toString() const
{
    std::stringstream ss;

    if (negative)
        ss << '-';

    for (auto it = data.rbegin(), end = data.rend(); it != end; it++) {
        ss << *it << std::setw(base_length) << std::setfill('0');
    }

    return ss.str();
}

BigInteger operator+(const BigInteger& l, const BigInteger& r)
{
    if (l.negative ^ r.negative)
        return l - (-r);
    else {
        BigInteger ret = l;

        for (int i = 0; i < r.data.size(); i++)
            ret.data.push_back(0);

        for (int i = 0; i < r.data.size(); i++)
            ret.data[i] += r.data[i];

        for (int i = 0; i + 1 < ret.data.size(); i++) {
            if (ret.data[i] >= cowr::BigInteger::base)
                ret.data[i + 1] += ret.data[i] / cowr::BigInteger::base,
                    ret.data[i] %= cowr::BigInteger::base;
        }

        while (ret.data.size() > 1 && ret.data.back() == 0)
            ret.data.pop_back();

        return ret;
    }
}

BigInteger operator-(const BigInteger& l, const BigInteger& r)
{
    if (l.negative ^ r.negative)
        return l + (-r);
    else {
        BigInteger ret = l;

        for (int i = 0; i < r.data.size(); i++)
            ret.data.push_back(0);

        ret.data.push_back(0); //sign

        for (int i = 0; i < r.data.size(); i++)
            ret.data[i] -= r.data[i];

        for (int i = 0; i + 1 < ret.data.size(); i++) {
            if (ret.data[i] < 0)
                ret.data[i + 1] += (ret.data[i] - cowr::BigInteger::base + 1) / cowr::BigInteger::base,
                    ret.data[i] = (ret.data[i] % cowr::BigInteger::base + cowr::BigInteger::base) % cowr::BigInteger::base;
        }

        if (ret.data.back() < 0) {
            ret.data.back() = cowr::BigInteger::base - 1;
            for (auto& x : ret.data)
                x = cowr::BigInteger::base - x - 1;

            ret.data[0]++;

            for (int i = 0;; i++) {
                if (ret.data[i] >= cowr::BigInteger::base)
                    ret.data[i + 1] += ret.data[i] / cowr::BigInteger::base, ret.data[i] %= cowr::BigInteger::base;
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

BigInteger operator*(const BigInteger& l, const BigInteger& r)
{
    BigInteger ret;

    ret.negative = l.negative ^ r.negative;

    int width = l.data.size() + r.data.size();
    ret.data.resize(width, 0);

    int outer_width = 2;

    while (outer_width < width)
        outer_width *= 2;

    std::vector<std::complex<double>> buffer_l(outer_width), buffer_r(outer_width);

    for (int i = 0; i < l.data.size(); i++)
        buffer_l[i] = l.data[i];
    for (int i = 0; i < r.data.size(); i++)
        buffer_r[i] = r.data[i];

    FFT::FFT(buffer_l, outer_width);
    FFT::FFT(buffer_r, outer_width);

    for (int i = 0; i < outer_width; i++)
        buffer_l[i] *= buffer_r[i];

    FFT::iFFT(buffer_l, outer_width);

    for (int i = 0; i < width; i++)
        ret.data[i] = round(abs(buffer_l[i]));

    for (int i = 0; i + 1 < ret.data.size(); i++) {
        if (ret.data[i] >= cowr::BigInteger::base)
            ret.data[i + 1] += ret.data[i] / cowr::BigInteger::base,
                ret.data[i] %= cowr::BigInteger::base;
    }

    while (ret.data.size() > 1 && ret.data.back() == 0)
        ret.data.pop_back();

    return ret;
}
}
