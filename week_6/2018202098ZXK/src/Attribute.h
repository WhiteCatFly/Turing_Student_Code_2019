#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <map>
#include <string>
#include <iostream>

using std::string;
class Attribute
{
private:
	std::map<string, string> attrs;
public:
	Attribute();
	~Attribute() = default;
	string& operator[](const string& key);
};
Attribute creatAttr(int argc, char const *argv[]);


#endif