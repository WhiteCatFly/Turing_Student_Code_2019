#include <string>
#include <iostream>
#include <cmath>
#include <istream>
#include <ostream>
#include <math.h>
#include <string.h>
class Biginteger
{
	private:
		char * m_bigint;
	public:
		Biginteger(){
			m_bigint = new char[1];
			m_bigint[0] = '0';
		}
		Biginteger(std::string bigint)
		{
			m_bigint = new char[bigint.size()];
			strncpy(m_bigint,bigint.data(),sizeof(char));
		}
		Biginteger(char * bigint)
		{
			m_bigint = new char[strlen(bigint)];
			strncpy(m_bigint,bigint,strlen(bigint)*sizeof(char));
		}
		Biginteger(long int );
		Biginteger(int );
		~Biginteger(){
			//delete [] m_bigint;
		}
		//operator-overloading :+,-,*,/
		Biginteger operator+(const Biginteger &bi) const;
		Biginteger operator+(const int &bi) const;
		Biginteger operator+(const long int &bi) const;
		Biginteger operator-(const Biginteger &bi) {}
		Biginteger operator-(const int &bi) {}
                Biginteger operator-(const long int &bi) {}
		Biginteger operator*(const Biginteger &bi) {}
                Biginteger operator*(const int &bi) {}
                Biginteger operator*(const long int &bi) {}
		Biginteger operator/(const Biginteger &bi) {}
                Biginteger operator/(const int &bi) {}
                Biginteger operator/(const long int &bi) {}
		 friend  Biginteger operator+(int const&n,const Biginteger &bi) ;
                friend Biginteger operator+( long int const&ln,const Biginteger &bi);
		friend  Biginteger operator-(const int &n,const Biginteger &bi) {}
                friend Biginteger operator-(const long int &ln,const Biginteger &bi) {}
		friend  Biginteger operator*(const int &n,const Biginteger &bi) {}
                friend Biginteger operator*(const long int &ln,const Biginteger &bi) {}
		friend  Biginteger operator/(const int &n,const Biginteger &bi) {}
                friend Biginteger operator/(const long int &ln,const Biginteger &bi) {}
		friend void change_into_int(const Biginteger &a,int *b);
		friend Biginteger addtogether(int *a,int *b,int n1,int n2);
		friend std::ostream &operator<<(std::ostream &os,const Biginteger &bi);
		friend std::istream &operator>>(std::istream &is,const Biginteger &bi);
		//operator-overloading : ++ +=
		Biginteger operator++(){}
		Biginteger operator+=(const Biginteger &bi) const{}
                Biginteger operator+=(const int &bi) const{}
                Biginteger operator+=(const long int &bi) const{}
};
Biginteger operator+(int const &n,const Biginteger &bi);
Biginteger operator+(long int const&ln,const Biginteger &bi) ;
Biginteger operator-(const int &n,const Biginteger &bi) ;
Biginteger operator-(const long int &ln,const Biginteger &bi) ;
Biginteger operator*(const int &n,const Biginteger &bi) ;
Biginteger operator*(const long int &ln,const Biginteger &bi) ;
Biginteger operator/(const int &n,const Biginteger &bi) ;
Biginteger operator/(const long int &ln,const Biginteger &bi) ;
std::ostream &operator<<(std::ostream &os,const Biginteger &bi);
std::istream &operator>>(std::istream &is,const Biginteger &bi);
void change_into_int(const Biginteger &a,int *b) ;
Biginteger addtogether(int *a,int *b,int n1,int n2);
