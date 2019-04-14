#include"BigInteger.h"
int main(){
     /* construct by string */
    BigInteger bint_test1("145779986623333333333");

    /* construct by 32bit-number */
    BigInteger bint_test2(19793565);

    /* construct by 64bit-number */
    BigInteger bint_test3(233333333345);


    /* test plus */
    /* ------------------------- */
    // simple case
    BigInteger bint_test7 = BigInteger(3) + BigInteger("7");

    // no carrying
    BigInteger bint_test5 = bint_test1 + bint_test3;
    cout << bint_test5 << endl;
    // The answer is 145779986856666666678

    // many carryings
    BigInteger bint_test6 = BigInteger("9999999999999999999999999999") + BigInteger(1);
    cout << bint_test6 << endl;
    // everyone knows its answer
    /* ------------------------- */

   
    /* test mixed operator */
    BigInteger bint_test13 = 23784687 + bint_test3;
    cout << bint_test13 << endl;
    // 233357118032
    

    /* test cout */
    cout << "Bint1 : " << bint_test1 << endl;
    cout << "Bint2 : " << bint_test2 << endl;
    //我的重载<<里面输出的结果多了“a big integer：”

}