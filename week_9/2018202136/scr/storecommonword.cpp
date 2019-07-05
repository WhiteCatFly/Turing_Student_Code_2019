#include "head.h"
string commonword;
void storecommonword(void)
{
    ifstream fin;
    string commonwordpart;
    fin.open("commonwords.txt");
    while(getline(fin,commonwordpart))
    {
       commonword += commonwordpart;
    }
}