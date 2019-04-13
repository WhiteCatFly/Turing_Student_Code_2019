#include<iostream>
#include<sstream>
#include<cstring>

using std::cin;
using std::cout;
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;

class BigInteger{
    private:
        string number;
        long long int len;
        
    public:
        BigInteger() = default;
        BigInteger(string &num){
            number = num;
            len = number.length();
        }
        BigInteger(long long int &num){
            stringstream s;
            s<<num;
            number = s.str();
            len = number.length();
        }
        BigInteger(int &num){
            stringstream s;
            s<<num;
            number = s.str();
            len = number.length();
        }
        string get_num()const{
            return number;
        }
        char& operator[](int index){
            return number[index];
        }
        friend ostream& operator <<(ostream& os,const BigInteger& t);
        friend BigInteger operator+(const BigInteger & num1,const BigInteger & num2);
        friend BigInteger operator+(const BigInteger & num1,long long int & num_2);
};