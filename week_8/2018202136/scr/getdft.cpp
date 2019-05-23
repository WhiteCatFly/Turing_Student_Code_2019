#include "head.h"
void getdft(int n,string *p,int size)
{
    double pl = 1.0;
    for(int i = 0;i < size;i++)
    pl = pl*all[n].file[p[i]]/all[n].total_number;
    pl++;
    all[n].dft = log(pl)+1;
}