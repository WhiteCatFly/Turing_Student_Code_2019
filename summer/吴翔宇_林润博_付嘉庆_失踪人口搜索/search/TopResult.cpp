#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include "PersonData.h"

const double eps = 1e-2;

bool CompByScore(PersonData a, PersonData b)
{
	if (abs(a.score - b.score) > eps)
		return a.score > b.score;
	else return a.value > b.value;
}

void SortByScore(vector<PersonData> &data)
{
	sort(data.begin(), data.end(), CompByScore);
}

void print(vector<PersonData> &data, int shows, int page)
{
	int t = min(page * shows, (int)data.size());
	cout<<"<h3 style =\"color:white\" >\n";
	for (int i = (page - 1) * shows; i < t; i++)
		{
			
		cout << ("姓名:") << data[i].name <<"<br>"<< ("得分:") << data[i].score <<"<br>""<a href=\""<< "../data/" << data[i].DataName<<"\">详细信息</a> "<<endl;
		cout<<"<br><br>\n";
		}
	cout<<"</h3>\n";
}