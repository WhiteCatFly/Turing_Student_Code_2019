#include "bigint.h"
#include <iostream>
#include <string>

int main(){
    std::string a = "1438529346660";
    long long b =   -5189123578916;
    BigInt A(a);
    BigInt B(b);
    std::cerr << A << std::endl;
    std::cerr << B << std::endl;
    std::cerr << A+B << std::endl;
    std::cerr << B+A << std::endl;
    std::cerr << A-B << std::endl;
    std::cerr << B-A << std::endl;
}