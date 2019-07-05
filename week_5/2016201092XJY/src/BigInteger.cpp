#include "BigInteger.h"

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

BigInteger::BigInteger(string num)
{
    if (num[0] == '-'){
        _sign = false;
        num.erase(0,1);
    }
    else {
        _sign = true;
        if (num[0] == '+'){
            num.erase(0,1);
        }
    }

    _size = num.size();

    for (int i = _size - 1; i >= 0; i--){
        int temp = num[i] - '0';
        _data.push_back(temp);
    }
}

BigInteger::BigInteger(long long num)
{
    string num_str = to_string(num);

    if (num_str[0] == '-'){
        _sign = false;
        num_str.erase(0,1);
    }
    else {
        _sign = true;
        if (num_str[0] == '+'){
            num_str.erase(0,1);
        }
    }

    _size = num_str.size();

    for (int i = _size - 1; i >= 0; i--){
        int temp = num_str[i]- '0';
        _data.push_back(temp);
    }
}

BigInteger& BigInteger::operator + (const BigInteger& BI){
    int max_size, min_size;
    int carry = 0;
    vector <int> temp_data = BI._data;

    if (this->_size < BI._size){
        max_size = BI._size;
        min_size = this->_size;
        for (int digit = min_size; digit <= max_size; digit++){
            this->_data.push_back(0);
        }
        temp_data.push_back(0);
    }
    else{
        max_size = this->_size;
        min_size = BI._size;
        for (int digit = min_size; digit <= max_size; digit++){
            temp_data.push_back(0);
        }
        this->_data.push_back(0);
    }

    if (this->_sign == BI._sign){
        for (int i = 0; i <= max_size; i++){
            this->_data[i] = this->_data[i] + temp_data[i] + carry;
            if (this->_data[i] >= 10){
                this->_data[i] = this->_data[i] - 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
        }
    }
    else{}

    if (this->_data[max_size] == 0){
        this->_data.pop_back();
        this->_size = max_size;
    }
    else{
        this->_size = max_size + 1;
    }

    return *this;
}

ostream & operator << (ostream& out, BigInteger& BI){
    if (BI._sign == false){
        out << '-';
    }
    for (int i = BI._size - 1; i >= 0; i--){
        out << BI._data[i];
    }
    return out;
}

