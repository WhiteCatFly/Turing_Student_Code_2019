#include "bigint.h"
#include <complex>

bool operator > (BigInt x, BigInt y){
    if(x.sign != y.sign) return x.sign > y.sign;
    int ans = 0;
    if(x.data.size() > y.data.size()) ans = 1;
    else if(x.data.size() < y.data.size()) ans = -1;
    else{
        for(int i = x.data.size() - 1; i >= 0; i--)
            if(x.data[i] > y.data[i]){
                ans = 1;
                break;
            }else if(x.data[i] < y.data[i]){
                ans = -1;
                break;
            }
    }
    if(x.sign == 1) {
        if(ans == 1) return true;
        else return false;
    }else {
        if(ans == -1) return true;
        else return false;
    }
}

bool operator < (BigInt x, BigInt y){
    if(x.sign != y.sign) return x.sign < y.sign;
    int ans = 0;
    if(x.data.size() < y.data.size()) ans = 1;
    else if(x.data.size() > y.data.size()) ans = -1;
    else{
        for(int i = x.data.size() - 1; i >= 0; i--){
            if(x.data[i] < y.data[i]){
                ans = 1;
                break;
            }else if(x.data[i] > y.data[i]){
                ans = -1;
                break;
            }
        }
    }
    if(x.sign == 1){
        if(ans == 1) return true;
        else return false;
    }else {
        if(ans == -1) return true;
        else return false;
    }
}

BigInt operator - (BigInt x){
    x.sign *= -1;
    return x;
}

BigInt operator + (BigInt x, BigInt y){
    if(x.sign == 0) return y;
    if(y.sign == 0) return x;
    int memsignx = x.sign; if(x.sign == -1) x.sign *= -1;
    int memsigny = y.sign; if(y.sign == -1) y.sign *= -1;
    if(x < y) {
        BigInt tmpbigint = x;
        x = y;
        y = tmpbigint;
        int tmpsign = memsignx;
        memsignx = memsigny;
        memsigny = tmpsign;
    }

    if(memsignx != memsigny){
        x = Minus(x, y);
        x.sign *= memsignx;
        return x;
    }
//unsigned addition
    for(int i = 0; i < y.data.size(); i++)
        x.data[i] += y.data[i];
//    std::cerr << x.data.size() << std::endl;
    for(int i = 0; i < x.data.size() - 1; i++){
       x.data[i+1] += x.data[i] / POW;
        x.data[i] %= POW;
    }
    if(x.data[x.data.size() - 1] >= POW){
        x.data[x.data.size() - 1] -= POW;
        x.data.push_back(1);
    }
//unsigned addition
    x.sign *= memsignx;
    return x;
}

BigInt Minus(BigInt x, BigInt y){
    for(int i = 0; i < y.data.size(); i++){
        x.data[i] -= y.data[i];
        if(x.data[i] < 0){
            x.data[i] += POW;
            x.data[i + 1] --;
        }
    }for(int i = y.data.size(); i < x.data.size() ; i--){
        if(x.data[i] < 0){
            x.data[i] += POW;
            x.data[i + 1] --;
        }
    }
    x.CheckZero();
    return x;
}

BigInt operator - (BigInt x, BigInt y){
    if(x.sign == 0) return -y;
    if(y.sign == 0) return x;
    return x + (-y);
}

BigInt operator * (BigInt x, BigInt y){
    if(x.sign == 0) return y;
    if(y.sign == 0) return x;
    BigInt ans;
    ans.sign = x.sign * y.sign;
    for(int i = 0; i < x.data.size() + y.data.size() - 1; i++)
        ans.data.push_back(0);
    for(int i = 0; i < x.data.size(); i++)
        for(int j = 0; j < y.data.size(); j++)
            ans.data[i + j] += x.data[i] * y.data[j];
    for(int i = 0; i < ans.data.size() - 1; i++){
        ans.data[i + 1] += ans.data[i] / POW;
        ans.data[i] %= POW;
    }
    for(int i = ans.data.size() - 1; ans.data[i] >= POW; i++){
        ans.data.push_back(ans.data[i] / POW);
        ans.data[i] %= POW;
    }return ans;
}

bool operator > (long long x, BigInt y){return BigInt(x) > y;}
bool operator < (long long x, BigInt y){return BigInt(x) < y;}
BigInt operator + (long long x, BigInt y){return BigInt(x) + y;}
BigInt operator - (long long x, BigInt y){return BigInt(x) - y;}
BigInt operator * (long long x, BigInt y){return BigInt(x) * y;}

bool operator > (BigInt x, long long y){return x > BigInt(y);}
bool operator < (BigInt x, long long y){return x < BigInt(y);}
BigInt operator + (BigInt x, long long y){return x + BigInt(y);}
BigInt operator - (BigInt x, long long y){return x - BigInt(y);}
BigInt operator * (BigInt x, long long y){return x * BigInt(y);}

