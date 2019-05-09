#include "BigInt.h"
#include <iostream>
int main(){
	using std::cout;
	using std::endl;

	BigInt<int, 1000, 3> celebrate("20190504"); // test template parameters
	cout << "celebrate: " << celebrate << endl;
	cout << "time: "<< (19190504 - celebrate)/10000 << " years" << endl; // test int - BigInt

	std::string strNum("19260817");
	BigInt<> himNum(strNum); // test string constructor
	cout << "him: " << himNum << endl;
	cout << "-him: " << -himNum << endl; // test -BigNum

	BigInt<> neg(-1); // test long long constructor
	unsigned flow = (unsigned) neg; // test explict cast
	int noflow = (int) neg;
	cout << "flow: " << flow << "\n" << "noflow: " << noflow << endl;


	BigInt<> mult = himNum * himNum; // test "*"
	cout << "mult: him*him = " << mult << endl;
	cout << "mult: him*him*him = " << himNum * himNum * himNum << endl;

	BigInt<> divi = himNum / 100; // test "/"
	cout << "divi: " << divi << endl;

}
