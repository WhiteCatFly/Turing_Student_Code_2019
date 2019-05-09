#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>

using std::string;
using std::ostream;

class BigInteger{
private:
	std::vector<int> bigInteger_;
public:
	BigInteger() = default;
	BigInteger(string str);
	BigInteger(long long number);
	BigInteger operator=(string str);
    BigInteger operator+(const BigInteger& addition) const;
    int GetSize() const{return bigInteger_.size();} 
	int GetMember(int i) const{return bigInteger_[i];}
	friend ostream & operator << (ostream &os, const BigInteger& bigInteger);
	friend BigInteger operator + (long long number, const BigInteger& bigInteger);
};
