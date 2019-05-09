#include "BigInteger.h"

BigInteger::BigInteger(string str){
	bigInteger_.clear();
	for(int i=0; i<str.length(); i++){
		bigInteger_.push_back( std::stoi(str.substr(i, 1)) );
	}
}

BigInteger::BigInteger(long long number){
	string str;
	std::stringstream ss;
	ss << number;
	ss >> str;
	bigInteger_.clear();
	for(int i=0; i<str.length(); i++){
		bigInteger_.push_back( std::stoi(str.substr(i, 1)) );
	}
}

BigInteger BigInteger::operator = (string str){
	bigInteger_.clear();
	for(int i=0; i<str.length(); i++){
		bigInteger_.push_back( std::stoi(str.substr(i, 1)) );
	}
	return *this;
}

BigInteger BigInteger::operator + (const BigInteger& addition) const{
	BigInteger sum;
	sum.bigInteger_.clear();
	int s = 0;
	for (int i=0; ; i++){
		if ( i>bigInteger_.size() && i>addition.bigInteger_.size() ) break;
		if ( i<bigInteger_.size() ) s+=bigInteger_[ bigInteger_.size()-1-i ];
		if ( i<addition.bigInteger_.size() ) s+=addition.bigInteger_[ addition.bigInteger_.size()-1-i ];
		if ( s!=0 ) sum.bigInteger_.insert(sum.bigInteger_.begin(), s%10);
		s = s/10;
	}
	return sum;
}

ostream & operator << (ostream &os, const BigInteger& bigInteger){
	for(int i=0; i<bigInteger.GetSize(); i++){
		os << bigInteger.GetMember(i);
	}
	return os;
}

BigInteger operator + (long long number, const BigInteger& bigInteger){
	BigInteger addition(number);
	BigInteger sum = addition + bigInteger;
	return sum;
}
