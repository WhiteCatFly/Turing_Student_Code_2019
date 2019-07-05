#include "head.h"
int datechange(string date)
{
	int loc1,loc2,m_date = 0;
	char middle[9];
	for(int i = 0;i < 4;i++)
	middle[i] = date[i];
	loc1 = date.find("月");
	if(loc1 == 7)
	{
		middle[4] = '0';
		middle[5] = date[6];
	}
	else if(loc1 == 8)
	{
		middle[4] = date[6];
		middle[5] = date[7];
	}
	loc2 = date.find("日");
	if(loc2-loc1 == 3)
	{
		middle[6] = '0';
		middle[7] = date[loc1+2];
	}
	else if(loc2-loc1 == 4)
	{
		middle[6] = date[loc1+2];
		middle[7] = date[loc1+3];
	}
	for(int i = 0;i < 8;i++)
	{
		m_date = m_date*10+int(middle[i]-48);
	}
	return m_date;
}