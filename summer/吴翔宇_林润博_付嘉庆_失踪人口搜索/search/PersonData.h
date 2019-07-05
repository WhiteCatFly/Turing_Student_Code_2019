#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Query.h"

string itostring(int i);

class PersonData
{
private:
	string name;
	string sex;
	int birthday;//YYYYMMDD
	int lostday;//YYYYMMDD
	int height;
	pair<string, string> birthplace;
	pair<string,string> lostplace;
	string MayToGo;
	string information;
	string DataName;
	double score;
	double value;
public:
	friend void store(vector<PersonData>& alldata);
	friend double NameSimilarity(const string p, const string q);
	friend double SexSimilarity(const string p, const string q);
	friend double DaySimilarity(const int p, const int q);
	friend double HeightSimilarity(const int p, const int q);
	friend double PairStringSimilarity(const string p, const pair<string, string> q);
	friend double PairStringSimilarity(const pair<string, string> p, const pair<string, string> q);
        friend double InformationSimilarity(const string p, const string q);
	friend bool CompByScore(PersonData a, PersonData b);
	friend void SortByScore(vector<PersonData> &data);
	friend void print(vector<PersonData> &data, int shows, int page);
	friend void scorer(PersonData &p, const Query &q);
	friend void scorer(PersonData &p, const ComplexQuery &q);
	//PersonData() = default;
	PersonData(string dataname, string m_name, string m_sex, pair<string,string> m_birthplace, int m_birthday, int m_lostday, int m_height, pair<string,string> m_lostplace
	, string maytogo, string m_information): 
	DataName(dataname), name(m_name), sex(m_sex), birthplace(m_birthplace), birthday(m_birthday), lostday(m_lostday), height(m_height), lostplace(m_lostplace),
	MayToGo(maytogo), information(m_information), score(0), value(0) {}
	void ComputeDataValue();
};
