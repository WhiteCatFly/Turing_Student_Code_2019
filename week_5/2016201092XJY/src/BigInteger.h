#include <iostream>
#include <string>
#include <vector>
//#include <fstream>

using std::string;
using std::vector;
using std::ostream;

class BigInteger{
    friend ostream & operator << (ostream& out, BigInteger& BI);
    private:
        bool _sign;     // True for positive(and 0), False for negative
        int  _size;
        vector <int> _data;

    public:
        BigInteger() = default;
        explicit BigInteger(string num);
        BigInteger(long long num);

        BigInteger & operator + (const BigInteger& BI);
        ~BigInteger() = default;
};

ostream & operator << (ostream& out, BigInteger& BI);

