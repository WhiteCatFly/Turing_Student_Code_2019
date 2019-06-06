#include "head.h"
void Similarity::idf(vector<BasicStats> &stats,Documents &doc)
{
    for(int i = 0;i < InputStringSize;i++)
    {
        Idf = Idf*log(stats[i].tf()) *log((doc.getFreq(stats[i].getword())+1.0)/(doc.getTotalnumber()+1.0));
    }
    return;
}
void Similarity::Scorce(Documents &doc){
    score = Idf*lambda-gamma;
    doc.setscorce(score);
    return ;
}