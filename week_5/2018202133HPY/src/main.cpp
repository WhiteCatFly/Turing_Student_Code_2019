#include <iostream>

#include "Utils/BigInteger.hpp"

int main(void)
{

    std::cout << cowr::BigInteger::valueOf(10001ULL).toString() << std::endl;

    std::cout << cowr::BigInteger::valueOf(-10001).toString() << std::endl;

    std::cout << cowr::BigInteger::valueOf("123456789").toString() << std::endl;

    std::cout << (cowr::BigInteger::valueOf(123434231) * cowr::BigInteger::valueOf(-9998623136)).toString() << std::endl;

    return 0;
}
