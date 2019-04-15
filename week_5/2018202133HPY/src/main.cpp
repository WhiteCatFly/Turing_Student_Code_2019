#include <iostream>

#include "Utils/BigInteger.hpp"

int main(void)
{
    using cowr::BigInteger;

    std::cout << cowr::BigInteger("145779986623333333333145779986623333333333145779986623333333333") * cowr::BigInteger("145779986623333333333145779986623333333333145779986623333333333") << std::endl;

    BigInteger bint_test1 = cowr::BigInteger("145779986623333333333");
    BigInteger bint_test15 = 777 * bint_test1;

    std::cout << bint_test15 << std::endl;
    return 0;
}
