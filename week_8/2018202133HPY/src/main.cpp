#include <codecvt>
#include <iostream>
#include <string>

#include <python3.7m/Python.h>

PyObject* getJieba()
{
    return PyImport_ImportModule("jieba");
}

int main(void)
{
    std::u32string str;
}
