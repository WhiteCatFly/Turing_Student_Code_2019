#ifndef BIG_INT_
#define BIG_INT_
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

template<typename T = long long int, T m = 10000000LL, unsigned places = 7>
class BigInt
{
private:
    bool  cPos;
    std::vector<T> d;
public:
	BigInt() = default;
    BigInt(T x);
    BigInt(std::string num);
    BigInt(const BigInt &num):cPos(num.cPos), d(num.d){}

	unsigned length() const;
    BigInt abs() const{BigInt res(*this); res.cPos = true; return res;}
    BigInt operator-(){BigInt res(*this); res.cPos = !res.cPos; return res;}

    BigInt operator-(const BigInt& r) const{BigInt nr = r; nr.cPos = !nr.cPos; return (*this)+nr;}
    BigInt operator+(const BigInt& r) const;
    BigInt operator*(const BigInt& r) const;
    BigInt operator/(const BigInt& r) const;
    BigInt operator%(const BigInt& r) const;

	template<typename TT>
    explicit operator TT() const;
    bool operator<(const BigInt& r) const; 
    bool operator>(const BigInt& r) const;
    bool operator==(const BigInt& r) const{return cPos==r.cPos && d == r.d;}

    ~BigInt() = default;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& num){
    	auto it = num.d.rbegin();
    	if(!num.cPos) os << '-';
    	os << *it++;
    	while(it != num.d.rend()){
    		os << std::setfill('0') << std::setw(places) << *it++;
    	}
    	return os;
    }
};

template<typename T, T m, unsigned places>
unsigned int BigInt<T, m, places>::length() const{
	unsigned res = 0;
	res += (d.size()-1) * places;
	std::stringstream ss;
	std::string s;
	ss << d.back();
	ss >> s;
	res += (unsigned)s.length();
	return res;
}

template<typename T, T m, unsigned places>
BigInt<T, m, places>::BigInt(T x)
{
    if(x >= 0){
        cPos = true;
    }
    else{
        cPos = false;
        x = -x;
    }
    while(x > m){
        d.push_back(x % m);
        x /= m;
    }
    d.push_back(x);
}


template<typename T, T m, unsigned places>
BigInt<T, m, places>::BigInt(std::string num){
	//符号位
	if(num[0] == '-'){
		num = num.substr(1);
		cPos = false;
	}
	else
	{
		cPos = true;
	}
	std::stringstream ss;
	T tmp;
	while(num.length() > places){
		ss << num.substr(num.length()-places);
		num = num.substr(0, num.length()-places);
        ss >> tmp;
        ss.clear();
		d.push_back(tmp);
	}
	ss << num;
	ss >> tmp;
	d.push_back(tmp);
}

template<typename T, T m, unsigned places>
BigInt<T, m, places> BigInt<T, m, places>::operator+(const BigInt<T, m, places>& r) const{
	BigInt res;
	//符号位相同
    if(cPos == r.cPos){
    	T carry = 0;
    	res.cPos = cPos;
    	auto &e = r.d;
    	auto n = std::max(d.size(), e.size());
    	for(auto i = 0; i < n; i++){
    		T a = i < d.size() ? d[i]: 0;
    		T b = i < e.size() ? e[i]: 0;
    		res.d.push_back((a+b+carry) % m);
    		carry = (a+b+carry) / m;
    	}
    	if(carry){
    		res.d.push_back(carry);
    	}
    	return res;
    }
    //符号位相反， 取绝对值大的符号
    else{
    	BigInt lhs, rhs;
    	if(abs() > r.abs()){
    		res.cPos = cPos;
    		lhs = abs();
    		rhs = r.abs();
    	}
    	else{
    		res.cPos = r.cPos;
    		lhs = r.abs();
    		rhs = abs();
    	}
    	for(int i = 0; i < lhs.d.size(); i++){
    		T a = lhs.d[i];
    		T b = i < rhs.d.size() ? rhs.d[i] : 0;
    		if(a >= b){
    			res.d.push_back(a-b);
    		}
    		else{
    			a += m;
    			lhs.d[i+1] -= 1;
    			res.d.push_back(a-b);
    		}
    	}
    	while(res.d.size() > 1 && res.d.back() == 0){
    		res.d.pop_back();
    	}
    	if(res.d.size() == 1 && res.d.back() == 0){
    		res.cPos = true;
    	}
    	return res;
    }
}

template<typename T, T m, unsigned places>
BigInt<T, m, places> BigInt<T, m, places>::operator*(const BigInt<T, m, places>& r) const{
	BigInt res;
	res.cPos = !(cPos ^ r.cPos);
	auto &e = r.d;
	res.d.resize(d.size()+ e.size(), 0);
	for(auto i = 0; i  < d.size(); i++){
		for(auto j = 0; j < e.size(); j++){
			T tmp = d[i] * e[j] + res.d[i+j];
			res.d[i+j] = tmp % m;
			res.d[i+j+1] +=   tmp / m;
		}
	}

	//case: r == 0
	while(res.d.size() > 1 && res.d.back()==0){
		res.d.pop_back();
	}
	return res;
}

template<typename T, T m, unsigned places>
BigInt<T, m, places> BigInt<T, m, places>::operator/(const BigInt<T, m, places>& r) const{
	BigInt res(0);
	BigInt base(1);
	BigInt lhs = abs();
	BigInt rhs = r.abs();
	while(lhs > rhs || lhs == rhs){
		base = BigInt(1);
		while(lhs > rhs * base * 2){
			base = base * 2;
		}
		res = res + base;
		lhs = lhs - rhs * base;
	}
	if(cPos == r.cPos){
		res.cPos = true;
	}
	else{
		if(lhs == 0){
			res.cPos = false;
		}
		else{
			res = res + 1;
			res.cPos = false;
		}
	}
	return res;
}

template<typename T, T m, unsigned places>
BigInt<T, m, places> BigInt<T, m, places>::operator%(const BigInt<T, m, places>& r) const{
	BigInt<> q = (*this) / r;
	return (*this) - q * r;
}

template<typename T, T m, unsigned places>
template<typename TT>
BigInt<T, m, places>::operator TT() const{
	TT res = 0;
	auto it = d.rbegin();
	while(it != d.rend()){
		res *= m;
		res += *it++;
	}
	return cPos? res: -res;
}

template<typename T, T m, unsigned places>
bool BigInt<T, m, places>::operator>(const BigInt<T, m, places>& r) const{
	if(cPos != r.cPos){
		if(cPos) return true;
		else return false;
	}
	else{
		bool res = false;
		auto &e = r.d;
		//size, every num
		if(d.size() > e.size()) res = true;
		else if(d.size() < e.size()) res = false;
		else{
			for(int i = d.size()-1; i >= 0; i--){
				if(d[i] > e[i]){
					res = true;
					break;
				}
				if(d[i] < e[i]){
					res = false;
					break;
				}
			}
		}
		return cPos? res: !res;
	}
}

template<typename T, T m, unsigned places>
bool BigInt<T, m, places>::operator<(const BigInt<T, m, places>& r) const{
	return !(*this>r || *this==r);
}


template<typename TT, typename T, T m, unsigned places>
BigInt<T, m, places> operator+(TT num, BigInt<T, m, places> bigNum){
	BigInt<T, m, places> lhs((T)num);
	return lhs+bigNum;
}

template<typename TT, typename T, T m, unsigned places>
BigInt<T, m, places> operator-(TT num, BigInt<T, m, places> bigNum){
	BigInt<T, m, places> lhs((T)num);
	return lhs-bigNum;
}

template<typename TT, typename T, T m, unsigned places>
BigInt<T, m, places> operator*(TT num, BigInt<T, m, places> bigNum){
	BigInt<T, m, places> lhs((T)num);
	return lhs*bigNum;
}

template<typename TT, typename T, T m, unsigned places>
BigInt<T, m, places> operator/(TT num, BigInt<T, m, places> bigNum){
	BigInt<T, m, places> lhs((T)num);
	return lhs/bigNum;
}

#endif
