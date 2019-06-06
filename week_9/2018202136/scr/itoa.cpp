#include "head.h"
string itostring(int i)
{
    string s;
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
    xx[j] = '.';
    xx[j+1] = 'h';
    xx[j+2] = 't';
    xx[j+3] = 'm';
    xx[j+4] = 'l';   
	s = xx;
    return s;
}