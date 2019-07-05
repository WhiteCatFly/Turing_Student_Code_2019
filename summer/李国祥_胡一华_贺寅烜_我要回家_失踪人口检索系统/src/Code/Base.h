#ifndef __BASE_H__
#define __BASE_H__

#include <vector>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <regex>
#include <cmath>
#include <algorithm>

#include "Date.h"
#include "Score.h"
#include "Person.h"
#include "Query.h"
#include "Statistics.h"
#include "QueryResult.h"
#include "../cppjieba/include/cppjieba/Jieba.hpp"

const char *const DICT_PATH = "../cppjieba/dict/jieba.dict.utf8";
const char *const HMM_PATH = "../cppjieba/dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "../cppjieba/dict/user.dict.utf8";
const char *const IDF_PATH = "../cppjieba/dict/idf.utf8";
const char *const STOP_WORD_PATH = "../cppjieba/dict/stop_words.utf8";

class QueryResult;
class Date;
class Statistics;
class Score;
class Person;
class Query;


class Base
{
    friend class QueryResult;

  private:
    std::vector<std::string> description_base;
    std::vector<std::string> description_synonym;
    std::vector<std::string> province;
    std::set<std::string> stopwords_base;
    std::map<std::string, std::string> synonyms;

    cppjieba::Jieba jieba;

    double Avgdl;
    std::map<int, Person> People;
    std::map<std::string, std::list<int>> id_map;
    std::map<std::string, std::list<int>> name_map;

    std::map<std::string, std::map<std::string, std::vector<int>>> sub_name_map;

    std::map<bool, std::list<int>> gender_map;
    std::map<std::string, std::list<int>> birthplace_map; //province
    std::map<Date, std::list<int>> birthday_map;
    std::map<int, std::list<int>> birthyear_map;
    std::map<Date, std::list<int>> lostday_map;
    std::map<int, std::list<int>> lostyear_map;
    std::map<int, std::list<int>> height_map;
    std::map<std::pair<int, int>, std::list<int>> heightrange_map;
    std::map<std::string, std::list<int>> lostplace_map; //province
    std::map<std::string, std::list<int>> description_map;
    std::map<std::string, std::vector<std::pair<int, int>>> segment_map;

  public:
    Base();
    ~Base() {}
    void redownload();
    void check();
    void construct_map(Statistics &Statistics, Person &per, int &i, std::string &detail);

    void test_gender(bool gender);
    void test_province(const std::string &place);
    void test_name(const std::string &name);
    void test_show_lostplace_map();
    void test_description_map(const std::string &character);
    void test_show_description_map();
    void test_lostday_map(int, int, int);
    void test_lostyear_map(int);
    void test_show_segment();

    void test_show_search_for_segment(const std::string &);

    QueryResult scoring(Query &query);

    void ParseFile(std::istringstream &iss, Person &person);
    void Modify(std::vector<std::string> &);

    Person operator[](int a);

    std::string get_last_name(std::string &name);
    std::vector<std::string> get_sub_names(std::string &last_name, std::string &first_name, int &size);
};

#endif