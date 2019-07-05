#ifndef __PERSON_H__
#define __PERSON_H__

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include"Date.h"

class Person_2{
int a;
};

class Person{

friend Date string_to_date(const std::string &string_date);

friend class Base;
friend class QueryResult;
private:
    int index;
    std::string id;
    std::string name;
    bool gender; // 0 for female, 1 for male;
    std::string birthplace;
    Date birthday;
    Date lostday;
    int height;
    std::string lostplace;
    std::string detailed_description;
    std::vector<bool> descriptions;
    std::vector<std::string> Segmentated_descriptions;  //切完词之后的详细信息
    static std::ofstream fout;
public:
    Person(){ };
    ~Person(){};
    Person(const Person&);
    void set_id(std::string id_) { id = id_; }
    void set_name(std::string name_) { name = name_; }
    void set_gender(bool gender_) { gender = gender_; }
    void set_birthplace(std::string birthpalce_) { birthplace = birthpalce_; }
    void set_birthday(Date birthday_) { birthday = birthday_; }
    void set_lostday(Date lostday_) { lostday = lostday_; }
    void set_height(int height_) { height = height_; }
    void set_lostplace(std::string lostplace_) { lostplace = lostplace_; }
    void set_detailed_description(std::string description_) { detailed_description += description_; }
    void push_descriptions(bool m) { descriptions.push_back(m); }
    void set_descriptions(int n, bool m) { descriptions[n] = m; }
    void set_index(int index_) { index = index_; }

    void store_result(std::ofstream &fout);
    void showall();

    std::string get_string_index(){return std::to_string(index);};
    std::string get_string_id(){return id;};
    std::string get_string_name() { return name; };
    std::string get_string_gender() { if(gender) return "男"; return "女"; };
    Date get_string_birthday() { return birthday; };
    Date get_string_lostday() { return lostday; };
    std::string get_string_height(){return std::to_string(height);};
    std::string get_string_lostplace(){return lostplace;};
    std::string get_string_birthplace(){return birthplace;};
    std::string get_string_detailed_description(){return detailed_description;};
};

#endif