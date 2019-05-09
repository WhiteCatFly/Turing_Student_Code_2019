#ifndef BIG_INT_H
#define BIG_INT_H

class BigInt {
   private:
    std::vector<int> digit;
    bool symbol;
    static const int BASE;
    void normalize() {
        if (digit.size() == 1 && digit[0] == 0) symbol = 0;
    }
    void erase_leading_zero() {
        size_t size = digit.size();
        while (size > 1 && digit[size - 1] == 0) size--;
        digit.resize(size);
    }
    void reverse() {
        std::vector<int> tmp;
        for (int i = digit.size() - 1; i >= 0; i--) tmp.push_back(digit[i]);
        digit = tmp;
    }


   public:
    BigInt() : symbol(0) { digit.push_back(0); };

    BigInt(const std::string &num) { *this = num; }
    BigInt(const char *p) { *this = (std::string)p; }
    template <typename T>
    BigInt(const T &num) {
        *this = std::to_string(num);
    }

    BigInt &operator=(const std::string &num);
    BigInt &operator=(const char *p) { *this = BigInt(p); }
    BigInt &operator=(const BigInt &num) {
        this->symbol = num.symbol;
        this->digit = num.digit;
    }
    template <typename T>
    BigInt &operator=(const T &num) {
        (*this) = std::to_string(num);
    }

    int operator[](const size_t index) const {
        if (index >= digit.size()) return 0;
        return digit[index];
    }

    bool operator<(const BigInt &rhs) const;
    bool operator<(const std::string &rhs) const {
        return (*this) < BigInt(rhs);
    }
    template <typename T>
    bool operator<(const T &rhs) const {
        return (*this) < std::to_string(rhs);
    }

    bool operator>(const BigInt &rhs) const;
    bool operator>(const std::string &rhs) const {
        return (*this) > BigInt(rhs);
    }
    template <typename T>
    bool operator>(const T &rhs) const {
        return (*this) > std::to_string(rhs);
    }

    bool operator<=(const BigInt &rhs) const;
    bool operator<=(const std::string &rhs) const {
        return (*this) <= BigInt(rhs);
    }
    template <typename T>
    bool operator<=(const T &rhs) const {
        return (*this) <= std::to_string(rhs);
    }

    bool operator>=(const BigInt &rhs) const;
    bool operator>=(const std::string &rhs) const {
        return (*this) >= BigInt(rhs);
    }
    template <typename T>
    bool operator>=(const T &rhs) const {
        return (*this) >= std::to_string(rhs);
    }

    bool operator==(const BigInt &rhs) const;
    bool operator==(const std::string &rhs) const {
        return (*this) == BigInt(rhs);
    }
    template <typename T>
    bool operator==(const T &rhs) const {
        return (*this) == std::to_string(rhs);
    }

    bool operator!=(const BigInt &rhs) const;
    bool operator!=(const std::string &rhs) const {
        return (*this) != BigInt(rhs);
    }
    template <typename T>
    bool operator!=(const T &rhs) const {
        return (*this) != std::to_string(rhs);
    }

    BigInt abs() const;
    BigInt operator-() const;
    std::vector<int> unsigned_sub(const std::vector<int> &lhs,
                                  const std::vector<int> &rhs) const;
    BigInt sub_digit(size_t l, size_t r) const {
        if (l > r) return 0;
        BigInt ret_value;
        ret_value.symbol = 0;
        ret_value.digit.clear();
        for (int i = l; i <= r; i++) ret_value.digit.push_back((*this)[i]);
        return ret_value;
    }

    BigInt operator+(const BigInt &rhs) const;
    BigInt operator+(const std::string &rhs) const {
        return (*this) + BigInt(rhs);
    }
    template <typename T>
    BigInt operator+(const T &rhs) const {
        return (*this) + std::to_string(rhs);
    }

    BigInt operator-(const BigInt &rhs) const;
    BigInt operator-(const std::string &rhs) const {
        return (*this) - BigInt(rhs);
    }
    template <typename T>
    BigInt operator-(const T &rhs) const {
        return (*this) - std::to_string(rhs);
    }

    BigInt operator*(const BigInt &rhs) const;
    BigInt operator*(const std::string &rhs) const {
        return (*this) * BigInt(rhs);
    }
    template <typename T>
    BigInt operator*(const T &rhs) const {
        return (*this) * std::to_string(rhs);
    }

    BigInt operator/(const BigInt &rhs) const;
    BigInt operator/(const std::string &rhs) const {
        return (*this) / BigInt(rhs);
    }
    template <typename T>
    BigInt operator/(const T &rhs) const {
        return (*this) / std::to_string(rhs);
    }

    BigInt operator%(const BigInt &rhs) const;
    BigInt operator%(const std::string &rhs) const {
        return (*this) % BigInt(rhs);
    }
    template <typename T>
    BigInt operator%(const T &rhs) const {
        return (*this) % std::to_string(rhs);
    }

    BigInt &operator+=(const BigInt &rhs);
    BigInt &operator+=(const std::string &rhs) {
        return (*this) += BigInt(rhs);
    }
    template <typename T>
    BigInt &operator+=(const T &rhs) {
        return (*this) += std::to_string(rhs);
    }

    BigInt &operator-=(const BigInt &rhs);
    BigInt &operator-=(const std::string &rhs) {
        return (*this) -= BigInt(rhs);
    }
    template <typename T>
    BigInt &operator-=(const T &rhs) {
        return (*this) -= std::to_string(rhs);
    }

    BigInt &operator*=(const BigInt &rhs);
    BigInt &operator*=(const std::string &rhs) {
        return (*this) *= BigInt(rhs);
    }
    template <typename T>
    BigInt &operator*=(const T &rhs) {
        return (*this) *= std::to_string(rhs);
    }

    BigInt &operator/=(const BigInt &rhs);
    BigInt &operator/=(const std::string &rhs) {
        return (*this) /= BigInt(rhs);
    }
    template <typename T>
    BigInt &operator/=(const T &rhs) {
        return (*this) /= std::to_string(rhs);
    }

    BigInt &operator%=(const BigInt &rhs);
    BigInt &operator%=(const std::string &rhs) {
        return (*this) %= BigInt(rhs);
    }
    template <typename T>
    BigInt &operator%=(const T &rhs) {
        return (*this) %= std::to_string(rhs);
    }

    BigInt &operator++();
    BigInt &operator--();
    BigInt operator++(int);
    BigInt operator--(int);

    // I/O stream operators:
    friend std::istream &operator>>(std::istream &istrm, BigInt &num);
    friend std::ostream &operator<<(std::ostream &ostrm, const BigInt &num);
};

template <typename T>
BigInt operator+(const T &lhs, const BigInt &rhs) {
    return BigInt(lhs) + rhs;
}
template <typename T>
BigInt operator-(const T &lhs, const BigInt &rhs) {
    return BigInt(lhs) - rhs;
}
template <typename T>
BigInt operator*(const T &lhs, const BigInt &rhs) {
    return BigInt(lhs) * rhs;
}
template <typename T>
BigInt operator/(const T &lhs, const BigInt &rhs) {
    return BigInt(lhs) / rhs;
}
template <typename T>
BigInt operator%(const T &lhs, const BigInt &rhs) {
    return BigInt(lhs) % rhs;
}

#endif