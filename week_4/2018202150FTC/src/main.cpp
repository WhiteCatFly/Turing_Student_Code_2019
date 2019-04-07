#include"parser.h"
int main()
{
    system("wget -O source.html info.ruc.edu.cn");
    Htmlparser test=Htmlparser("source.html");
    test.readin();
    test.getpara();
    test.getpic();
    test.gettitle();
    test.geturl();
}