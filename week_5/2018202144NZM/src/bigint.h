#include <bits/stdc++.h>

using namespace std;

class BigInterger {
	private:
		enum {
			MAX_LEN = 1000001
		};
		int bigint[MAX_LEN];
		int len;
	public:
		BigInterger();
		BigInterger(long long num);
		BigInterger(string str);
		~BigInterger();
		friend bool operator < (const BigInterger &a, const BigInterger &b);
		friend BigInterger operator + (const BigInterger &a, const BigInterger &b);
		friend BigInterger operator - (const BigInterger &a, const BigInterger &b);
		friend BigInterger operator * (const BigInterger &a, const BigInterger &b);
		friend BigInterger operator / (const BigInterger &a, const BigInterger &b);	
		friend ostream & operator << (const ostream &os, const BigInterger &a);
};
