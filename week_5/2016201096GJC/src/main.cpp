#include "BigInteger.h"
#include <fstream>

int main(){
	std::ofstream fout("print.out");
	BigInteger bint_test1("145779986623333333333");
    BigInteger bint_test2(19793565);
	BigInteger bint_test3(233333333345);
	BigInteger bint_test5 = bint_test1 + bint_test3;
	fout << bint_test5 << "\n";
	BigInteger bint_test6 = BigInteger("9999999999999999999999999999") + BigInteger(1);
	fout << bint_test6 << "\n";
	BigInteger bint_test13 = 23784687 + bint_test3;
	fout << bint_test13 << "\n";
	fout << "Bint1 : " << bint_test1 << "\n";
	fout << "Bint2 : " << bint_test2 << "\n";
	fout << std::flush;
	fout.close();
	return 0;
}
