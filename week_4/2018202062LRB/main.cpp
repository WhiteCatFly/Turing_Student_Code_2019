#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include "htmlparser.h"
using namespace std;

int main()
{
	Parser p;
	p.set_type();
	p.analyze();
	p.print();
	return 0;
}