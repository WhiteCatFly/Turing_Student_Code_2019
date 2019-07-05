#include <string>
#include <vector>
#include <iostream>

#define POW 10

class BigInt {
    friend BigInt operator - (BigInt x);
    friend BigInt Minus(BigInt x, BigInt y);

    friend BigInt operator + (BigInt x, BigInt y);
    friend BigInt operator - (BigInt x, BigInt y);
    friend BigInt operator * (BigInt x, BigInt y);
//    friend BigInt operator / (BigInt x, BigInt y);
//    friend BigInt operator % (BigInt x, BigInt y);

    friend BigInt operator + (long long x, BigInt y);
    friend BigInt operator - (long long x, BigInt y);
    friend BigInt operator * (long long x, BigInt y);
//    friend BigInt operator / (long long x, BigInt y);
//    friend BigInt operator % (long long x, BigInt y);

    friend BigInt operator + (BigInt x, long long y);
    friend BigInt operator - (BigInt x, long long y);
    friend BigInt operator * (BigInt x, long long y);
//    friend BigInt operator / (BigInt x, long long y);
//    friend BigInt operator % (BigInt x, long long y);

    friend bool operator < (BigInt x, BigInt y);
    friend bool operator > (BigInt x, BigInt y);
    friend bool operator > (long long x, BigInt y);
    friend bool operator < (long long x, BigInt y);
    friend bool operator > (BigInt x, long long y);
    friend bool operator < (BigInt x, long long y);

    friend std::ostream & operator << (std::ostream &x, BigInt y);

    private:
        int sign;
        std::vector <int> data;
        void CheckZero(){
            while(data.size() != 0 && data[data.size() - 1] == 0) 
                data.pop_back();
            if(data.size() == 0)
                sign = 0;
        }
    public:
        explicit BigInt(const long long &x);
        BigInt(const std::string &x);
        BigInt(const BigInt &x);
        BigInt();
        ~BigInt();
}; 