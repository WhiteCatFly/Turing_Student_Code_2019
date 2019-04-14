// example main


#include"BigInteger.h"

int main(){
    BigInteger a; //default a = 0
    BigInteger b(13422433); // initialize b with int
    BigInteger c("201820213520182021352018202135"); // initialize c with const char*
    std::string m = "1433223";
    BigInteger d = m; // initialize d with std::string
    BigInteger e = d; // initialize e with another BigInteger
    a = b + c; // BigInteger plus BigInteger
    BigInteger d_1 = d + 1327; // BigInteger plus int
    BigInteger d_2 = 1327 + d; // int plus BigInteger
    std::cout << d_1 << " " << d_2 << std::endl; // << overloading
}



