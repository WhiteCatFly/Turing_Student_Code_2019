#include "textquery.h"
#include "queryresult.h"

#include <iostream>

int main()
{
    int file_number;
     
    cout << "please enter the number of files" << endl;
    cin  >> file_number;

    run_query(file_number);

    return 0;
}