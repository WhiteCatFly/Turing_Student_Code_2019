#include <iostream>
#include <vector>
#include "BigInteger.h"

#include <cstdlib>

int randNum()
{
    int f1 = (rand()&1) ? 1 : -1,
        f2 = (rand()&1) ? 1 : 0;
    int a = rand(),
        b = rand();
    return f1 * (f2 * a + b);
}

int main()
{
    BigInteger a(randNum()),
               b(randNum());

    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " - " << b << " = " << a - b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
    std::cout << a << " / " << b << " = " << a / b << std::endl;

}
