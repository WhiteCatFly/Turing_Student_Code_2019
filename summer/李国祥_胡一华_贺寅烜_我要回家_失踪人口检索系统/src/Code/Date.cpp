#include"Date.h"

std::ostream &operator<<(std::ostream &os,const Date &date)
{
    os << date.GetYear() << "年" << date.GetMonth() << "月" << date.GetDay() << "日";
    return os;
}

bool operator<(const Date &left, const Date &right)
{
    if (left.year < right.year)
        return true;
    if (left.year > right.year)
        return false;
    if (left.month < right.month)
        return true;
    if (left.month > right.month)
        return false;
    if (left.day < right.day)
        return true;
    if (left.day >= right.day)
        return false;
}