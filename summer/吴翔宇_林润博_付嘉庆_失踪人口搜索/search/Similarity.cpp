#include <algorithm>
#include <string>
#include <assert.h>
#include "PersonData.h"
#include "Query.h"
#include <math.h>
using namespace std;

double NameSimilarity(const string p, const string q)
{
	if (p.length() >= 12)
		return 0.0;
	if (p == q)
		return 1.0;
	int lp = p.length(), lq = q.length();
	if (lp == 0 || lq == 0)
		return 0;
	int dp[20][20];
	for (int i = 0; i <= lp; i++)
		dp[i][0] = 0;
	for (int i = 1; i <= lq; i++)
		dp[0][i] = 0;
	for (int i = 3; i <= lp; i += 3)
	{
		for (int j = 3; j <= lq; j += 3)
		{
			dp[i][j] = max(dp[i - 3][j], dp[i][j - 3]);
			dp[i][j] = max(dp[i][j], dp[i - 3][j - 3] + 3 * (p[i] == q[j] && p[i - 1] == q[j - 1] && p[i - 2] == q[i - 2]));
		}
	}
	return (double)(dp[lp][lq]) * dp[lp][lq] / lp / lq;
}

double SexSimilarity(const string p, const string q)
{
	if (p == "不详")
		return 1.0;
	return (double)(p == q);
}

double DaySimilarity(const int p, const int q)
{
	if (p == 0)
		return 0.0;
	int diff = abs(p - q);
	int y = abs(p / 10000 - q / 10000),
		m = abs(p % 10000 / 100 - q % 10000 / 100),
		d = abs(p % 100 - q % 100);
	if (y < 0 || y > 100 || m < 0 || m > 12 || d < 0 || d > 31)
		return 0.0;
	return 1.0 - y / 150.0 - m / 36.0 - d / 90.0;
}

double HeightSimilarity(const int p, const int q)
{
	if (p == 0 || q <= 0 || q > 300)
		return 0.0;
	return 1.0 - double(abs(p - q)) * abs(p - q) / p / q;
}

double PairStringSimilarity(const string p, const pair<string, string> q)
{
	if (q.first == "不详" || q.first.empty() || p.find(q.first) == string::npos)
		return 0.0;
	else if (q.second == "不详" || q.second.empty() || p.find(q.second) == string::npos)
		return 0.75;
	else return 1.0;
}

double PairStringSimilarity(const pair<string, string> p, const pair<string, string> q)
{
	if (q.first == "不详" || q.first.empty() || p.first != q.first)
		return 0.0;
	else if (q.second == "不详" || q.second.empty() || p.second != q.second)
		return 0.75;
	else return 1.0;
}

double InformationSimilarity(const string p, const string q)
{
	if(p.length() == 0)
	{
		return 0.0;
	}
	if(p.find(q) != string::npos)
		return 1.0;
	else
	{
		int total = 0;
		int k = 0;
		int sum = 0;
		int loc1 = 0,loc2;
		string preq;
		cout << preq << endl;
		cout << loc1 << loc2  << endl;
		while(!(q[k] <= 'z' && q[k] >= 'A' ))
		{
			preq += q[k];
			k++;
		}
		while(preq.find("/",loc1) != string::npos)
		{
			string part;
			total++;
			loc2 = preq.find("/",loc1+1);
			part = preq.substr(loc1,loc2-loc1);
			if(p.find(part) != string::npos)
			sum++;
			loc1 = loc2;
		}
		return log(1.0+(sum+1.0)/(total+1.0));
	}
}