#include"HTMLparser.h"

int main(){
    HTMLparser test("info.ruc.edu.cn");
    test.GetImg();
    test.GetBody();
    test.GetTitle();
}