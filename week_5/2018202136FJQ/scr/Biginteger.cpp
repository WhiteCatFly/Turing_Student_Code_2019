#include "Biginteger.h"
Biginteger::Biginteger(int a)
{
	int n = 0,aa,b[10000] = {0};
	aa = abs(a);
	while(aa != 0)
	{
		b[n] = aa%10;
		aa = aa/10;
		n++;
	}
	if(a < 0)
        {
                m_bigint = new char[n+1];
                this->m_bigint[0] = '-';
        }
        else
        {
		m_bigint = new char[n];
        }

	for(int i = n-1;i >= 0;i--)
	{
		if(a < 0)
			this->m_bigint[n-i] = char(b[i]+48);
		else
			this->m_bigint[n-1-i] = char(b[i]+48);
	}

}
Biginteger::Biginteger(long int a)
{
	long int aa;
        int n = 0,b[10000] = {0};
        aa = abs(a);
	 while(aa != 0)
        {
                b[n] = aa%10;
                aa = aa/10;
                n++;
        }
        if(a < 0)
        {
                m_bigint = new char[n+1];
                this->m_bigint[0] = '-';
        }
        else
        {
                m_bigint = new char[n];
        }
        for(int i = n-1;i >= 0;i--)
        {
                if(a < 0)
                        this->m_bigint[n-i] = char(b[i]+48);
                else
                        this->m_bigint[n-1-i] = char(b[i]+48);
        }
}
