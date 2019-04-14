#include "head.h"
using namespace std;

void geturl(string &target_, int &openway);
void use(HTMLparser &t);

int main()
{
    string target_;
    int openway;
    geturl(target_, openway);

    HTMLparser s(target_,openway);
    use(s);

    return 0;
}