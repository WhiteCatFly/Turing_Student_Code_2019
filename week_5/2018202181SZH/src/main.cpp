#include"BigInteger.h"
int main(){
    long long int num1 = 1111111111;
    string num2 = "999876543234567";
    BigInteger number1(num1); //用long long int初始化
    BigInteger number2(num2); //用string初始化
    long long int number3 = 99991;
    BigInteger k1 = number1 + number2;//使用操作符重载加法，计算两个big integer的和
    cout<<k1<<endl;//使用操作符重载输出
    BigInteger k2 = number1 + number3;
    //使用操作符重载加法，计算big integer和long long int的和
    cout<<k2<<endl;//使用操作符重载输出
    return 0;
}