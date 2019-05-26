#include "Query.h"
using namespace std;
int main(int argv,char **argc)
{
    string term;
    int amount = N;
    if(argv == 1)
    {
        amount = atoi(argc[0]);
    }
    TextQuery infoweb(amount);
    cout << "input the term for query or input q to exit" << endl;
    for(;true;)
    {
        if(term == "q")
        {
            break;
        }
        else
        {
            infoweb.query(term);
        }
    }
    return 0;
}