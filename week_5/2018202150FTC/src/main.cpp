#include"integer.h"
int main()
{
    std::fstream fout;
    fout.open("print.out");

     /* construct by string */

    BigInteger bint_test1("145779986623333333333");



    /* construct by 32bit-number */

    BigInteger bint_test2(19793565);



    /* construct by 64bit-number */

    BigInteger bint_test3(233333333345);



    /* negative */

    BigInteger bint_test4("-5612537621783687126874");



    /* test plus */

    /* ------------------------- */

    // simple case

    //there is a bug from redeclearation



    // no carrying

    BigInteger bint_test5 = bint_test1 + bint_test3;

    fout << bint_test5 << std::endl;

    // The answer is 145779986856666666678



    // many carryings

    BigInteger bint_test6 = BigInteger("9999999999999999999999999999") + BigInteger(1);

    fout << bint_test6 << std::endl;

    // everyone knows its answer

    /* ------------------------- */



    /* test minus */

    /* ------------------------- */

    // simple case

    BigInteger bint_test7 = BigInteger(5) - BigInteger("3");

    fout << bint_test7 << std::endl;



    // hard case

    BigInteger bint_test8 = bint_test4 - bint_test1;

    fout << bint_test8 << std::endl;

    // The answer is -5758317608407020460207 (test by python, hope it is correct)

    /* ------------------------- */



    /* test multiply */

    /* ------------------------- */

    // simple case

    BigInteger bint_test9 = BigInteger(6) * BigInteger(7);

    fout << bint_test9 << std::endl;

    // I don't want to show the answer



    // hard case

    BigInteger bint_test10 = bint_test1 * bint_test4;

    fout << bint_test10 << std::endl;

    // The answer is -818195659426580988627366073641532104291042

    /* ------------------------- */

    

    /* test division */

    /* ------------------------- */

    // simple case

    BigInteger bint_test11_div = BigInteger(17) / BigInteger(4);

    fout << bint_test11_div << std::endl;

    // 4

    BigInteger bint_test11_mod = BigInteger(17) % BigInteger(4);

    fout << bint_test11_mod << std::endl;

    // 1





    /* test mixed operator */

    BigInteger bint_test13 = 23784687 + bint_test3;

    fout << bint_test13 << std::endl;

    // 233357118032

    BigInteger bint_test14 = bint_test1 - 965713;

    fout << bint_test14 << std::endl;

    // 145779986623332367620

    BigInteger bint_test15 = 777 * bint_test1;

    fout << bint_test15 << std::endl;

    // 113271049606329999999741



    /* test cout */

    fout << "Bint1 : " << bint_test1 << std::endl;

    fout << "Bint2 : " << bint_test2 << std::endl;



    
}