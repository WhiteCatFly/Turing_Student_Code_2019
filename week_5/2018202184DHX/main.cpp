#include "BigInteger.h"
#include <iostream>
#include <fstream>
int main(){
    system("touch print.out");
    freopen("print.out","w",stdout);
    /* construct by string */
    BigInteger bint_test1("145779986623333333333");
    /* construct by 32bit-number */
    BigInteger bint_test2(19793565);

    /* construct by 64bit-number */
    BigInteger bint_test3(233333333345);

    /* negative */
    //BigInteger bint_test4("-5612537621783687126874");

    /* test plus */
    /* ------------------------- */
    // simple case
    BigInteger bint_test7 = BigInteger(3) + BigInteger("7");

    // no carrying
    BigInteger bint_test5 = bint_test1 + bint_test3;
    std::cout << bint_test5 << std::endl;
    // The answer is 145779986856666666678

    // many carryings
    BigInteger bint_test6 = BigInteger("9999999999999999999999999999") + BigInteger(1);
    std::cout << bint_test6 << std::endl;
    // everyone knows its answer
    /* ------------------------- */

    /* test minus */
    /* ------------------------- */
    // simple case
    //BigInteger bint_test7 = BigInteger(5) - BigInteger("3");
    //std::cout << bint_test7 << std::endl;

    // hard case
    //BigInteger bint_test8 = bint_test4 - bint_test1;
    //std::cout << bint_test8 << std::endl;
    // The answer is -5758317608407020460207 (test by python, hope it is correct)
    /* ------------------------- */

    /* test multiply */
    /* ------------------------- */
    // simple case
    BigInteger bint_test9 = BigInteger(6) * BigInteger(7);
    std::cout << bint_test9 << std::endl;
    // I don't want to show the answer

    // hard case
    //BigInteger bint_test10 = bint_test1 * bint_test4;
    //std::cout << bint_test10 << std::endl;
    // The answer is -818195659426580988627366073641532104291042
    /* ------------------------- */
    
    /* test division */
    /* ------------------------- */
    // simple case
    //BigInteger bint_test11_div = BigInteger(17) / BigInteger(4);
    //std::cout << bint_test11_div << std::endl;
    // 4
    //BigInteger bint_test11_mod = BigInteger(17) % BigInteger(4);
    //std::cout << bint_test11_mod << std::endl;
    // 1

    // hard case
    //BigInteger bint_test12_div = bint_test4 / bint_test1;
    //std::cout << bint_test12_div << std::endl;
    // the answer is -39
    //BigInteger bint_test12_mod = bint_test4 % bint_test1;
    //std::cout << bint_test12_mod << std::endl;
    // 72881856526312873113
    /* ------------------------- */

    /* test mixed operator */
    BigInteger bint_test13 = 23784687 + bint_test3;
    std::cout << bint_test13 << std::endl;
    // 233357118032
    //BigInteger bint_test14 = bint_test1 - 965713;
    //std::cout << bint_test14 << std::endl;
    // 145779986623332367620
    BigInteger bint_test15 = 777 * bint_test1;
    std::cout << bint_test15 << std::endl;
    // 113271049606329999999741

    /* test cout */
    std::cout << "Bint1 : " << bint_test1 << std::endl;
    std::cout << "Bint2 : " << bint_test2 << std::endl;
    fclose(stdout);
}

