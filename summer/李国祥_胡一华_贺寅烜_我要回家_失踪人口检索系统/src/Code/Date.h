#ifndef __DATE_H__
#define __DATE_H__

#include<fstream>

    class Date
{
  private:
    int year;
    int month;
    int day;
public:
    Date(){}
    ~Date(){}
    Date(int year_, int month_, int day_):year(year_), month(month_), day(day_){}
    const int GetYear()const {return year;}
    const int GetMonth()const {return month;}
    const int GetDay() const {return day;}

    friend bool operator< (const Date&left, const Date&right);
};

std::ostream &operator<<(std::ostream &os,const Date &date);

#endif