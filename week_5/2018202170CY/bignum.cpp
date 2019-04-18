#include <iostream>
#include <vector>
#include "bignum.h"

using std::string;
using std::cout;
using std::endl;
bignum::bignum(string str)
{
    // cout << str << endl;
    this -> sign = (str[0] == '-') ? -1 : 1;
    int begin = (this -> sign == 1) ? 0 : 1;
    for(int i = str.length() - 1; i >= begin; i--)
    {
        this -> mem.push_back(str[i] - '0');
    }
    // cout << "newly build:";
    // int len = mem.size() - 1;
    // for (int i = len; i >= 0; i--)
    // cout << mem[i];
    // cout << endl;
}

bignum::bignum(long long num) : bignum(std::to_string(num)) {}
bignum::bignum(unsigned long long num) : bignum(std::to_string(num)) {}
bignum::bignum(int num) : bignum(std::to_string(num)) {}
bignum::bignum(unsigned int num) : bignum(std::to_string(num)) {}


bignum abs(const bignum &A)
{
    bignum B = A;
    B.sign = 1;
    return B; 
}

bool operator <(const bignum &A, const bignum &B)
{
    if (A.sign != B.sign)
    {
        if (A.sign == -1) return true;
        else return false;
    }
    int sign = A.sign;
    bignum absA = abs(A), absB = abs(B);
    if (absA.length() != absB.length())
    {
        if (absA.length() < absB.length()) return sign == 1;
        else return sign == -1;
    }
    for (int i = absA.length() - 1; i >= 0; i--)
    {
        if (absA[i] != absB[i]) return ( (absA[i] < absB[i]) && (sign == 1) ) || ( (absA[i] > absB[i]) && (sign == -1) );
    }
    return false;
}

bool operator ==(const bignum &A, const bignum &B)
{
    if (A.sign != B.sign) return false;
    if (A.length() != B.length()) return false;
    for (int i = 0; i < A.length(); i++)
    if (A[i] != B[i]) return false;
    return true;
}

bool operator <=(const bignum &A, const bignum &B)
{
    return A < B || A == B;
}

bool operator >(const bignum &A, const bignum &B)
{
    if (A.sign != B.sign)
    {
        if (A.sign == 1) return true;
        else return false;
    }
    int sign = A.sign;
    bignum absA = abs(A), absB = abs(B);
    if (absA.length() != absB.length())
    {
        if (absA.length() > absB.length()) return sign == 1;
        else return sign == -1;
    }
    for (int i = absA.length() - 1; i >= 0; i--)
    {
        if (absA[i] != absB[i]) return ( (absA[i] > absB[i]) && (sign == 1) ) || ( (absA[i] < absB[i]) && (sign == -1) );
    }
    return false;
}

std::ostream& operator <<(std::ostream &out, const bignum &num)
{
    if (num.sign == -1) out << "-";
    for (int i = num.length() - 1; i >= 0; i--)
    {
        // cout << num[i];
        out << num[i];
    }
    out << endl;
    return out;
}


bignum operator +(const bignum &A, const bignum &B)
{
    if (A.sign != B.sign)
    {
        if (A.sign == 1) return A - B;
        else
        {
            bignum C = A;
            C.sign *= -1;
            return B - C;
        }
    }
    bignum C;
    C.sign = A.sign;
    for (int i = 0; i < std::min(A.length(), B.length()); i++)
    {
        C.push_back(A[i] + B[i]);
    }
    if (A.length() < B.length())
    {
        for (int i = A.length(); i < B.length(); i++)
        C.push_back(B[i]);
    }
    if (A.length() > B.length())
    {
        for (int i = B.length(); i < A.length(); i++)
        C.push_back(A[i]);
    }
    for (int i = 0; i < C.length() - 1; i++)
    {
        if (C[i] >= mod) C[i] -= mod, C[i + 1] ++;
    }
    if (C[C.length() - 1] >= mod)
    {
        C[C.length() - 1] -= mod;
        C.push_back(1);
    }
    return C;
}

bignum operator -(const bignum &A, const bignum &B)
{
    if (A.sign != B.sign)
    {
        bignum C = B;
        C.sign *= -1;
        return A + C;
    }
    bignum C;
    C.sign = A.sign;
    bignum nA, nB;
    if (abs(A) < abs(B))
    {
        nA = abs(B);
        nB = abs(A);
        C.sign *= -1;
    }
    else
    {
        nA = abs(A);
        nB = abs(B);
    }
    for (int i = 0; i < nB.length(); i++)
    C.push_back(nA[i] - nB[i]);
    for (int i = nB.length(); i < nA.length(); i++)
    C.push_back(nA[i]);
    for (int i = 0; i < nA.length() - 1; i++)
    if (C[i] < 0) C[i] += mod, C[i + 1]--;
    while (C[C.length() - 1] == 0 && C.length() > 1)
    {
        C.pop_back();
    }
    return C;
}

bignum operator *(const bignum &A, const bignum &B)
{
    bignum C;
    C.sign = A.sign * B.sign;
    for (int i = 0; i < A.length() + B.length() - 1; i++)
    C.push_back(0);
    for (int i = 0; i < A.length(); i++)
    for (int j = 0; j < B.length(); j++)
    C[i + j] += A[i] * B[j];
    for (int i = 0; i < A.length() + B.length() - 2; i++)
    {
        C[i + 1] += C[i] / mod;
        C[i] %= mod;
    }
    int len = C.length() - 1;
    while (C[len] >= mod)
    {
        C.push_back(C[len] / mod);
        C[len] %= mod;
        len++;
    }
    return C;
}

bignum half_of(const bignum &A)
{
    bignum C = A;
    for (int i = C.length() - 1; i >= 0; i--)
    {
        if (i > 0)
        C[i - 1] += C[i] % 2 * mod;
        C[i] /= 2;
    }
    int len = C.length() - 1;
    while (C[len] == 0)
    C.pop_back(), len--;
    return C;
}

bignum operator /(const bignum &A, const bignum &B)
{
    // cout << A << B;
    bignum absA = abs(A), absB = abs(B);
    bignum left = 0, right = absA;
    while (left < right)
    {
        bignum mid = half_of(left + right);
        // cout << left << right << mid << "\t" << absB * mid << "\t" << absB * (mid + 1) << "\t" << absA;
        if (absB * mid <= absA && absB * (mid + 1) > absA)
        {
            mid .sign = A.sign * B.sign;
            return mid;
        }
        else if (absB * mid <= absA)
        {
            left = mid + 1;
        }
        else if (absB * mid > absA)
        {
            right = mid;
        }
    }
}

bignum operator %(const bignum &A, const bignum &B)
{
    return A - ( (A / B) * B);
}