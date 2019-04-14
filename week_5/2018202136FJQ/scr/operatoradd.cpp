#include "Biginteger.h"
Biginteger Biginteger::operator+(const Biginteger &bi) const
{
	int a[1000] = {0},b[1000] = {0};
	int len1,len2;
	change_into_int(*this,a);
	change_into_int(bi,b);
	if(this->m_bigint[0] != '-')
		len1 = strlen(this->m_bigint);
	else
		len1 = strlen(this->m_bigint)-1;
	if(bi.m_bigint[0] != '-')
                len2 = strlen(bi.m_bigint);
        else
                len2 = strlen(bi.m_bigint)-1;
	return addtogether(a,b,len1,len2);
}
Biginteger Biginteger::operator+(const int &bi) const
{
	Biginteger b(bi);
	return *this+b;
}
Biginteger Biginteger::operator+(const long int &bi) const
{
	Biginteger b(bi);
        return *this+b;
}
Biginteger operator+(int const&n,const Biginteger &bi)
{
        return bi+n;
}
Biginteger operator+(long int const&n,const Biginteger &bi)
{
        return bi+n;
}

void change_into_int(const Biginteger &bi,int *a)
{
	int len;
	if(bi.m_bigint[0] != '-')
	{       
		len = strlen(bi.m_bigint);
		for(int i = 0;i < len;i++)
                a[len-1-i] = int(bi.m_bigint[i])-48;
	}
        else
	{
                len = strlen(bi.m_bigint)-1;
		for(int i = 0;i < len;i++)
                a[len-1-i] = 48-int(bi.m_bigint[i+1]);
	}
}
Biginteger addtogether(int *a,int *b,int n1,int n2)
{
	char *result;
	int c[1000] = {0};
	int d[1000] = {0};
	int l ;
	if(n1 < n2)
		l = n2;
	else
		l = n1;
	for(int i = 0; i < l;i++)
	{
		c[i] = a[i]+b[i];
	}
	while(c[l-1] == 0&&l != 0)
	l--;
	if(l == 0)
	{
		Biginteger res(c[0]);
		return res;
	}
	else
	{
		for(int i = 0; i < l;i++)
		{
			if(c[i] >= 10)
			{
				d[i] = d[i]+c[i]-10;
				d[i+1]++;
			}
			else
			{
				d[i] = d[i] + c[i];
			}
		}	
		if(d[l] != 0)
		{
			result = new char[l+1];
			for(int i = l;i >= 0;i--)
			result[l-i] = d[i]+48;
		}
		else
		{
			result = new char[l];
			for(int i = l-1;i >= 0;i--)
                        result[l-1-i] = d[i]+48;
		}
		Biginteger res(result);
		delete [] result;
	       return res;	
	}
}
