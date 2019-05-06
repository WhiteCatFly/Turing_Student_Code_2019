#ifndef NDEBUG
#undef NDEBUG
#endif

#include "BigInteger.h"
#include <iostream>
#include <assert.h>

int main(){
    assert((BigInteger(50) + BigInteger(32)).getString() == "82");
    assert((BigInteger(5) + BigInteger(622)).getString() == "627");
    assert((BigInteger("-33") + BigInteger("8")).getString() == "-25");
    assert((BigInteger("0") + BigInteger("15535666666666")).getString() == "15535666666666");
    assert((BigInteger("126") + BigInteger("39285")).getString() == "39411");
    assert((BigInteger("0") + BigInteger("0")).getString() == "0");
    assert(BigInteger(5) + 10 == 15);
    assert(BigInteger("-41") + 40 == -1);
    BigInteger ad1(600);
    ad1 += 50;
    ad1 += "50";
    assert(ad1.getString() == "700");
    assert(ad1 == 700);

    //Subtraction
    assert((BigInteger("50") - BigInteger("32")).getString() == "18");
    assert((BigInteger("50") - BigInteger("60")).getString() == "-10");
    assert((BigInteger("0") - BigInteger("46")).getString() == "-46");
    assert((BigInteger("50") - BigInteger("50")).getString() == "0");
    assert((BigInteger("482847") - BigInteger("89787941")).getString() == "-89305094");
    assert((BigInteger("6828") - BigInteger("1")).getString() == "6827");
    assert((BigInteger("100") - BigInteger("50")).getString() == "50");
    assert((BigInteger("42") - BigInteger("49")).getString() == "-7");
    assert((BigInteger("100") - BigInteger("5")) == 95);
    BigInteger sb1 = 200;
    sb1 -= 40;
    assert(sb1 == 160);
    sb1 = sb1 - 180;
    assert(sb1 == "-20");
    sb1 -= "20";
    assert(sb1 == BigInteger(-40));
}