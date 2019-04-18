#include <iostream>
#include <vector>
#include "bignum.h"

using std::endl;
using std::cout;
int main(){
    /* construct by string */
    bignum bint_test1("145779986623333333333");
    /* construct by 32bit-number */
    bignum bint_test2(19793565);

    /* construct by 64bit-number */
    bignum bint_test3(233333333345LL);

    /* negative */
    bignum bint_test4("-5612537621783687126874");
    // -5612537621783687126874/145779986623333333333=-38.500056
    /* test plus */
    /* ------------------------- */
    // simple case
    // bignum bint_test7 = bignum(3) + bignum("7");

    // no carrying
    bignum bint_test5 = bint_test1 + bint_test3;
    std::cout << bint_test5 << std::endl;
    // The answer is 145779986856666666678

    // many carryings
    bignum bint_test6 = bignum("9999999999999999999999999999") + bignum(1);
    std::cout << bint_test6 << std::endl;
    // everyone knows its answer
    /* ------------------------- */

    /* test minus */
    /* ------------------------- */
    // simple case
    bignum bint_test7 = bignum(5) - bignum("3");
    std::cout << bint_test7 << std::endl;

    // hard case
    bignum bint_test8 = bint_test4 - bint_test1;
    std::cout << bint_test8 << std::endl;
    // The answer is -5758317608407020460207 (test by python, hope it is correct)
    /* ------------------------- */

    /* test multiply */
    /* ------------------------- */
    // simple case
    bignum bint_test9 = bignum(6) * bignum(7);
    std::cout << bint_test9 << std::endl;
    // I don't want to show the answer

    // hard case
    bignum bint_test10 = bint_test1 * bint_test4;
    std::cout << bint_test10 << std::endl;
    // The answer is -818195659426580988627366073641532104291042
    /* ------------------------- */
    
    /* test division */
    /* ------------------------- */
    // simple case
    bignum bint_test11_div = bignum(17) / bignum(4);
    std::cout << bint_test11_div << std::endl;
    // 4
    bignum bint_test11_mod = bignum(17) % bignum(4);
    std::cout << bint_test11_mod << std::endl;
    // 1

    // hard case
    bignum bint_test12_div = bint_test4 / bint_test1;
    std::cout << bint_test12_div << std::endl;
    // the answer is -39
    bignum bint_test12_mod = bint_test4 % bint_test1;
    std::cout << bint_test12_mod << std::endl;
    // 72881856526312873113
    /* ------------------------- */

    /* test mixed operator */
    bignum bint_test13 = 23784687 + bint_test3;
    std::cout << bint_test13 << std::endl;
    // 233357118032
    bignum bint_test14 = bint_test1 - 965713;
    std::cout << bint_test14 << std::endl;
    // 145779986623332367620
    bignum bint_test15 = 777 * bint_test1;
    std::cout << bint_test15 << std::endl;
    // 113271049606329999999741

    /* test cout */
    std::cout << "Bint1 : " << bint_test1 << endl;
    std::cout << "Bint2 : " << bint_test2 << endl;


}