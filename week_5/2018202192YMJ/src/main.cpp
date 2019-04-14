#include <vector>
#include <string>
#include <iostream>

#include "bigint.h"

int main()
{
    /* construct by string */
    BigInt bint_test1("145779986623333333333");

    /* construct by 32bit-number */
    BigInt bint_test2(19793565);

    /* construct by 64bit-number */
    BigInt bint_test3(233333333345);

    /* negative */
    BigInt bint_test4("-5612537621783687126874");

    /* test plus */
    /* ------------------------- */
    // simple case
    BigInt bint_test5 = BigInt(3) + BigInt("7");
    std::cout << bint_test5 << std::endl;

    // no carrying
    BigInt bint_test6 = bint_test1 + bint_test3;
    std::cout << bint_test6 << std::endl;
    // The answer is 145779986856666666678

    // many carryings
    BigInt bint_test7 = BigInt("9999999999999999999999999999") + BigInt(1);
    std::cout << bint_test7 << std::endl;
    // everyone knows its answer
    /* ------------------------- */

    /* test minus */
    /* ------------------------- */
    // simple case
    BigInt bint_test8 = BigInt(5) - BigInt("3");
    std::cout << bint_test8 << std::endl;

    // hard case
    BigInt bint_test9 = bint_test4 - bint_test1;
    std::cout << bint_test9 << std::endl;
    // The answer is -5758317608407020460207 (tested by python, hope it is correct)
    /* ------------------------- */

    /* test multiply */
    /* ------------------------- */
    // simple case
    BigInt bint_test10 = BigInt(6) * BigInt(7);
    std::cout << bint_test10 << std::endl;
    // I don't want to show the answer

    // hard case
    BigInt bint_test11 = bint_test1 * bint_test4;
    std::cout << bint_test11 << std::endl;
    // The answer is -818195659426580988627366073641532104291042
    /* ------------------------- */
    
    /* test division */
    /* ------------------------- */
    // simple case
    BigInt bint_test12_div = BigInt(17) / BigInt(4);
    std::cout << bint_test12_div << std::endl;
    // 4
    BigInt bint_test12_mod = BigInt(17) % BigInt(4);
    std::cout << bint_test12_mod << std::endl;
    // 1

    // hard case
    BigInt bint_test13_div = bint_test4 / bint_test1;
    std::cout << bint_test13_div << std::endl;
    // the answer is -38
    BigInt bint_test13_mod = bint_test4 % bint_test1;
    std::cout << bint_test13_mod << std::endl;
    // -72898130097020460220
    /* ------------------------- */

    /* test mixed operands */
    BigInt bint_test14 = 23784687 + bint_test3;
    std::cout << bint_test14 << std::endl;
    // 233357118032
    BigInt bint_test15 = bint_test1 - 965713;
    std::cout << bint_test15 << std::endl;
    // 145779986623332367620
    BigInt bint_test16 = 777 * bint_test1;
    std::cout << bint_test16 << std::endl;
    // 113271049606329999999741

    // /* test cout */
    std::cout << "Bint1 : " << bint_test1 << std::endl;
    std::cout << "Bint2 : " << bint_test2 << std::endl;

}