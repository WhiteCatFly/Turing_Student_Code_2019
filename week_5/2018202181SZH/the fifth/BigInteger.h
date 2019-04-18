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
        BigInteger(const BigInteger& num){
            this->number = num.number;
            this->len = num.len;
        }
        BigInteger(string &num){
            number = num;
            len = number.length();
        }
        BigInteger(const char* num){
            int len_temp = strlen(num);
            char temp[len_temp + 1];
            strcpy(temp,num);
            this->number = temp;
            len = number.length();
        }
        BigInteger(const long long int& num){
            stringstream s;
            s<<num;
            number = s.str();
            len = number.length();
        }
        BigInteger(const long int& num){
            stringstream s;
            s<<num;
            number = s.str();
            len = number.length();
        }
        BigInteger(const int & num){
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
        void get_len(){
            cout<<this->len<<endl;
        }
        friend ostream& operator <<(ostream& os,const BigInteger& t);
        friend BigInteger operator+(const BigInteger & num1,const BigInteger & num2);
        friend BigInteger operator+(const BigInteger & num1,long long int & num_2);
        friend BigInteger operator+(long long int & num_2,const BigInteger & num1);
};