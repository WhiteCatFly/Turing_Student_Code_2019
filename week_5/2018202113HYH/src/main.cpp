
#include "BigInteger.h"

int main ()
{
    std::string number1 ;
    std::string number2 ;
    char operator_;

    std::cout << "please enter the former number" << std::endl;
    std::cin  >> number1 ;
    std::cout << "please enter the operator( +, - or * only)" << std::endl;
    std::cin  >> operator_ ;
    std::cout << "please enter the latter number" << std::endl;
    std::cin  >> number2 ;

    BigInteger former(number1);
    BigInteger latter(number2);
    BigInteger result;

    if(operator_ == '+')
    {
        result = former + latter;
    }
    else if(operator_ == '-')
    {
        result = former - latter;

    }
    else if(operator_ == '*')
    {
        result = former * latter;
      
    }
    std::cout << "the answer is :" << std::endl;
    std::cout << result << std::endl;
    
    return 0;
}