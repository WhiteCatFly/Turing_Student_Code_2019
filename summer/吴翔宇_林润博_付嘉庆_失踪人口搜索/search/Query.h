#pragma once
#include <string>
using namespace std;

class PersonData;

class Query
{
private:
	string name;
public:
	friend void scorer(PersonData &p, const Query &q);
};

class ComplexQuery
{
private:
	string name;
	string sex;
	int birthday;
	int lostday;
	int height;
	pair<string, string> birthplace;
	pair<string, string> lostplace;
	pair<string, string> MayToGo;
	string information;
public:
	ComplexQuery();
	ComplexQuery(const string &data);
	friend void scorer(PersonData &p, const ComplexQuery &q);
	void print();
};