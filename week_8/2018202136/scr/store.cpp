#include "head.h"
havenapart all[10000];
string word[100];
void store(int n)
{
    all[n].total_number = 0;
    all[n].ID = n;
    ifstream fin;
    string words;
    fin.open("data.txt");
    while(getline(fin,words))
    {
        all[n].total_number++;
        all[n].file[words]++;
    }
    getdft(n,word,nsize);
}