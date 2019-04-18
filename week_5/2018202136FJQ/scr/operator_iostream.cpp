#include "Biginteger.h"
std::ostream &operator<<(std::ostream &os,const Biginteger &bi)
{
	os << bi.m_bigint;
	return os;
}
std::istream &operator>>(std::istream &is,const Biginteger &bi)
{
	is >> bi.m_bigint;
	return is;
}
