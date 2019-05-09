#include <iostream>

#include "BigInteger.h"


int randNum()
{
    int f1 = (rand()&1) ? 1 : -1,
        f2 = (rand()&1) ? 1 : 0;
    int a = rand(),
        b = rand();
    return f1 * (f2 * a + b);

}

char c[10] = {'0', '+', '-', '*', '/' , 'n'};

int main()
{
    int casenum = 10000, errornum = 0;
    while(casenum--)
    {
        int a = randNum(),
            b = randNum();
        BigInteger x(a), y(b);
        int s[10], t[10];
            s[1] = toint(x + y), t[1] = a + b,
            s[2] = toint(x - y), t[2] = a - b,
            s[3] = toint(x * y), t[3] = a * b,
            s[4] = toint(x / y), t[4] = a / b,
            s[5] = toint(-x), t[5] = -a;
        for(int i = 1; i <= 4; i++)
            if(s[i] != t[i])
            {
                std::cout << a << c[i] << b << std::endl;
                std::cout << s[i] << std::endl;
                std::cout << t[i] << std::endl; 
                errornum++;
            }
        if(s[5] != t[5])
        {
            std::cout << '-' << a << std::endl;
            std::cout << s[5] << std::endl;
            std::cout << t[5] << std::endl; 
            errornum++;
        }
    }
    if(errornum == 0)
        std::cout << "No error\n";

}