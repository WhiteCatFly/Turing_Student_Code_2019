#include "BigInt.h"
#include <iostream>
int main(){
	using std::cout;
	using std::endl;

	std::string strNum("19260817");
	BigInt<> himNum(strNum); // test string constructor
	cout << "him:" << himNum << endl;
	cout << "-him: " << -himNum << endl; // test -BigNum

	BigInt<> neg(-1); // test long long constructor
	unsigned flow = (unsigned) neg; // test explict cast
	int noflow = (int) neg;
	cout << "flow: " << flow << "\n" << "noflow: " << noflow << endl;


	BigInt<> mult = himNum * himNum; // test "*"
	cout << "mult: him*him = " << mult << endl;

	BigInt<> divi = mult / 100; // test "/"
	cout << "divi: " << divi << endl;
}
