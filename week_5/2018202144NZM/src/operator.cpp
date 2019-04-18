#include "bigint.h"

bool operator < (const BigInterger &a, const BigInterger &b)
{
		if(a.len != b.len) return a.len < b.len;
		for(int i = a.len; i; i --)
			if(a.bigint[i] != b.bigint[i])
				return a.bigint[i] < b.bigint[i];
		return false;
}

BigInterger operator + (const BigInterger &a, const BigInterger &b)
{
	BigInterger w;
	w.len = max(a.len, b.len);          
	for(int i = 1; i <= w.len; i++) {
		w.bigint[i] += a.bigint[i] + b.bigint[i]; 
		w.bigint[i + 1] += w.bigint[i] / 10;   
		w.bigint[i] %= 10;                 
	}
	if(w.bigint[w.len + 1] != 0)
		w.len ++;
	return w;
}

BigInterger operator - (const BigInterger &a, const BigInterger &b)
{
	BigInterger w;
	w.len = a.len;
	int temp[a.MAX_LEN];
	for(int i = 1; i <= w.len; i++)
		temp[i] = a.bigint[i];                
	for(int i = 1; i <= w.len; i++) {
		if(temp[i] < b.bigint[i]) {  
			temp[i+1] --;      
			temp[i] += 10;     
		}
		w.bigint[i] += temp[i] - b.bigint[i];
	}
	while(w.bigint[w.len] == 0 && (w.len != 1))
		w.len --;
	return w;
}

BigInterger operator * (const BigInterger &a, const BigInterger &b)
{
	BigInterger w;
	int x;              
	for(int i = 1; i <= a.len; i++) {      
		x = 0;
		for(int j=1; j<=b.len; j++) { 
			w.bigint[i+j-1] += a.bigint[i] * b.bigint[j] + x; 
			x = w.bigint[i+j-1] / 10;
			w.bigint[i+j-1] %= 10;        
		} 
		w.bigint[i+b.len] = x; 
	}
	w.len = a.len + b.len;
	while(w.bigint[w.len] == 0 && (w.len != 1))
		w.len --; 
	return w;
}

BigInterger operator / (const BigInterger &a, const BigInterger &b) {
	if(a < b)
		return BigInterger(0);
	BigInterger ans;
	ans.len = a.len - b.len + 1;
	for(int i = ans.len; i >= 1; i--) {
		for(int j = 1; j <= 9; j++) {
			ans.bigint[i] ++;
			if(a < (ans * b)) {
				ans.bigint[i] --;
				break; 
			}
		}
	        if(ans.bigint[ans.len] == 0)
	        	ans.len --;
        }
	while(ans.len > 1 && !ans.bigint[ans.len])
		ans.len --;
	return ans;
}

ostream & operator << (ostream &os, const BigInterger &a) {
	for(int i = a.len; i >=1; i--)
		os << a.bigint[i];
	return os;
}
