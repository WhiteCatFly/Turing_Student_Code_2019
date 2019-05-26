#include "Jieba.hpp"

#include <iostream>

std::shared_ptr<PyObject> make_pyobject(PyObject* object, bool borrowed = false)
{

    return std::shared_ptr<PyObject>(
        object,
        borrowed
            ? [](void* p) {}
            : [](void* p) { Py_DECREF(p); });
}

std::shared_ptr<PyObject> make_pyobject_borrowed(PyObject* object)
{

    return make_pyobject(object, true);
}

Jieba::Jieba()
{
    if (!Py_IsInitialized())
        Py_Initialize();

    pseg = make_pyobject(PyImport_ImportModule("jieba.posseg"));
    jieba = make_pyobject(PyImport_ImportModule("jieba"));

    if (jieba == nullptr || pseg == nullptr)
        throw std::logic_error("Cannot import jieba");
}

void Jieba::initialize()
{
    auto init = make_pyobject(PyObject_GetAttrString(jieba.get(), "initialize"));
    PyObject_CallObject(init.get(), NULL);
}

std::vector<std::pair<std::string, std::string>> Jieba::cut(std::string sentense)
{
    // std::cout << "!!!" << sentense << std::endl;

    std::vector<std::pair<std::string, std::string>> ret;
    auto cut = make_pyobject(PyObject_GetAttrString(pseg.get(), "cut"));
    auto param = make_pyobject(PyTuple_New(1));
    auto pstr = make_pyobject_borrowed(PyUnicode_FromString(sentense.c_str()));

    PyTuple_SetItem(param.get(), 0, pstr.get());

    auto pret_gen = make_pyobject(PyObject_CallObject(cut.get(), param.get()));

    auto pbuiltin = make_pyobject(PyImport_ImportModule("builtins"));
    auto plists = make_pyobject(PyObject_GetAttrString(pbuiltin.get(), "list"));

    PyTuple_SetItem(param.get(), 0, pret_gen.get());
    auto pret = make_pyobject(PyObject_CallObject(plists.get(), param.get()));

    int size = Py_SIZE(pret.get());

    // std::cout << size << std::endl;

    for (int i = 0; i < size; i++) {
        auto pword = make_pyobject(PyList_GetItem(pret.get(), i), true);
        auto word = make_pyobject(PyObject_GetAttrString(pword.get(), "word"));
        auto flag = make_pyobject(PyObject_GetAttrString(pword.get(), "flag"));

        std::string sword = PyUnicode_AsUTF8(word.get());
        std::string sflag = PyUnicode_AsUTF8(flag.get());

        ret.push_back(std::make_pair(sword, sflag));
    }

    return ret;
}
