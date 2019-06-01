#ifndef _COWR_JIEBA

#define _COWR_JIEBA

#include <memory>
#include <string>
#include <vector>

#include <python3.7m/Python.h>

class Jieba {
private:
    std::shared_ptr<PyObject> jieba, pseg;

public:
    Jieba();
    void initialize();
    std::vector<std::pair<std::string, std::string>> cut(std::string);
};

#endif
