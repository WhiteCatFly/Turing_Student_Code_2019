#include "bigint.h"
#include <iostream>

std::ostream & operator << (std::ostream &x, BigInt y){
    if(y.sign == 0)
        x << 0;
    else if(y.sign == -1)
        x << '-';
    for(int i = y.data.size() - 1; i >=0 ; i--){
        x << y.data[i];
    }return x;
}

BigInt :: BigInt (const std::string &x){
    for(int i = x.size() - 1; i > 0; i--)
        if(x[i] < '0' || x[i] > '9'){
            std::cerr << "construction from string failed." << std::endl;
            return;
        }
    if((x[0] < '0' || x[0] > '9') && x[0] != '-'){
            std::cerr << "construction from string failed." << std::endl;
            return;
    }
    sign = 1;
    for(int i = x.size() - 1; i > 0; i--)
        data.push_back(x[i] - '0');
    if(x[0] == '-') sign = -1;
    else data.push_back(x[0] - '0');
    
    while(data.size() > 0 && data[data.size() - 1] == '0')
        data.pop_back();
    if(data.size() == 0)
        sign = 0;
}

BigInt :: BigInt (const long long &x){
    long long tmp = x;
    if(tmp == 0)        sign = 0;
    else if(tmp > 0)    sign = 1;
    else                sign = -1;
    if(tmp < 0)         tmp *= -1;
    while(tmp != 0){
        data.push_back(tmp % POW);
        tmp /= POW;
    }
}

BigInt :: BigInt(const BigInt &x){
    sign = x.sign;
    data = x.data;
}

BigInt :: BigInt (){;}
BigInt :: ~BigInt (){;}

