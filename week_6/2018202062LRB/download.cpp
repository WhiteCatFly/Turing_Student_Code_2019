#include <cstdlib>
#include <string>
#include <iostream>
#include "download.h"
using namespace std;

void download(string website, string name)
{
	string tmp = "wget -O " + name + " '" + website + "' -t 3";
	cout << "tmp:" << tmp << endl;
	system(tmp.data());
}