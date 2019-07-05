#include"Person.h"

std::string bool_to_string(bool a){
    if(a) return "男";
    return "女";
}

Person::Person(const Person &other){
    index = other.index;
    id = other.id;
    name = other.name;
    gender = other.gender;
    birthday = other.birthday;
    birthplace = other.birthplace;
    lostday = other.lostday;
    height = other.height;
    lostplace = other.lostplace;
    detailed_description = other.detailed_description;
    descriptions = other.descriptions;
    Segmentated_descriptions = other.Segmentated_descriptions;
}

void Person::showall(){
    std::cout << "网址：　　　" << "www.zgszrkdak.cn/home/person/show/id/" + std::to_string(index) + ".html" << std::endl;
    std::cout << "编号：　　　" << id << std::endl;
    std::cout << "姓名：　　　" << name << std::endl;
    std::cout << "性别：　　　" << bool_to_string(gender) << std::endl;
    std::cout << "出生日期：　" << birthday << std::endl;
    std::cout << "失踪日期：　" << lostday << std::endl;
    std::cout << "身高：　　　" << height << std::endl;
    std::cout << "失踪地点：　" << lostplace << std::endl;
    std::cout << "籍贯：　　　" << birthplace << std::endl;
    std::cout << "详细信息：　" << detailed_description << std::endl;
    std::cout << "- - - - - - - - - - - -" << std::endl;
}

void Person::store_result(std::ofstream &fout)
{ //接受一个fout，将相应信息储存到fout当中
    fout << id << std::endl;
    fout << name << std::endl;
    fout << gender << std::endl;
    fout << birthplace << std::endl;
    fout << birthday << std::endl;
    fout << lostday << std::endl;
    fout << height << std::endl;
    fout << lostplace << std::endl;
    fout << detailed_description << std::endl;
}

