#include "bigint.h"

BigInterger::BigInterger() 
{
	len = 0;
}

BigInterger::BigInterger(long long num)
{
	len = 0;
	for(int i = 1; num > 0; i++) {
		bigint[i] = num % 10;
		num /= 10;
		len++;
	}
}

BigInterger::BigInterger(string str)
{
	len = str.size();
	for(int i = 1; i <= len; i++) {
		bigint[i] = str[len - i] - '0';
	}
}

BigInterger::~BigInterger() {}
