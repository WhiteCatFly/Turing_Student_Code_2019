#include "head.h"
void fromitoa(int i,string & s)
{
    int n,j = 0;
	char x[10] = {0},xx[10] = {0};
    n = i;
    while(n != 0)
    {
        x[j] = char(n%10+48);
        n = n/10;
        j++;
    }
	for(int k = 0;k < j;k++)
	{
		xx[k] = x[j-k-1];
	}
	s = xx;
    return ;
}