#include "Similarity.h"

void scorer(PersonData &p, const Query &q)
{
	p.score = NameSimilarity(p.name, q.name) * 10000;
}

void scorer(PersonData &p, const ComplexQuery &q)
{
	p.score = 0;
	if (!q.name.empty())
		p.score += NameSimilarity(p.name, q.name) * 10000;
	if (!q.sex.empty())
		p.score += SexSimilarity(p.sex, q.sex) * 2000;
	if (q.birthday != 0)
		p.score += DaySimilarity(p.birthday, q.birthday) * 2000;
	if (q.lostday != 0)
		p.score += DaySimilarity(p.lostday, q.lostday) * 500;
	if (q.height != 0)
		p.score += HeightSimilarity(p.height, q.height) * 2000;
	p.score += PairStringSimilarity(p.birthplace, q.birthplace) * 3000
			 + PairStringSimilarity(p.lostplace, q.lostplace) * 1000;
			 + InformationSimilarity(p.information, q.information) * 4000;
}