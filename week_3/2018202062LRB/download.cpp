#include <cstdlib>
#include <string>
#include <iostream>
#include "download.h"
using namespace std;

void download(string website, string name)
{
	string tmp = "wget -O " + name + " '" + website + "'";
	cout << "tmp:" << tmp << endl;
	system(tmp.data());
}