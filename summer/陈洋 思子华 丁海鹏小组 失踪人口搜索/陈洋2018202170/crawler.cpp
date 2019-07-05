#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <fstream>
// #include "crawler.h"

using std::string;
const string Wget_ = "wget -o a.out -O";

bool is_wanted(string title)
{
    if (title.find("亲人寻家") != string::npos || title.find("家寻亲人") != string::npos) return true;
    else if (title.find("寻亲启事") != string::npos || title.find("姓名") != string::npos) return true;
    else if (title.find("[") != string::npos) return true;
    else return false;
}

string Filename(string url)
{
    for (int i = 0; i < url.length(); i++)
    if (url[i] == '/') url[i] = '_';
    return url;
}

string change_int_to_string(int num)
{
    string str;
    while (num > 0)
    {
        str += num % 10 + '0';
        num /= 10;
    }
    string re;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        re += str[i];
    }
    return re;
}

int size_of_file(std::ifstream &fin)
{
    int size = 0;
    string str;
    while (fin >> str)
    {
        size += str.length();
    }
    return size;
}

void use_wget(string url, int id)
{
    string filename = change_int_to_string(id) + ".txt";
    for (int i = url.length() - 1; i >= 0; i--)
    {
        if (url[i] == '&' || url[i] == '(' || url[i] == ')')
        {
            url.insert(i, "\\");
        } 
    }
    string wget = Wget_ + " a.txt " + url; 
    // string wget = Wget_ + "/home/cy/Desktop/集训/data/ " + filename + " " + url;
    system(wget.c_str());
    std::ifstream fin;
    fin.open("a.txt");
    if (size_of_file(fin) >= 1000)
    {
        std::ofstream fout;
        fout.open("/home/cy/Desktop/集训/data/" + filename);
        fin.close();
        fin.open("a.txt");
        string a_line;
        while (getline(fin, a_line))
        {
            fout << a_line << std::endl;
        }
    }
}

int IncludeChinese(char *str)
{
    char c;
    while(1)
    {
        c=*str++;
        if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
        if (c&0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
        if (*str & 0x80) return 1;
    }
    return 0;
}

void getinfomation()
{
    std::ifstream fin;
    fin.open("a.txt");
    std::ofstream fout,fout2;
    fout.open("c.txt");
    fout2.open("b.txt");
    string a_line;
    bool have_title = false;
    while(getline(fin, a_line))
    {
        int pl;
        if (IncludeChinese(&a_line[0]) == true)
        fout << a_line << std::endl;
    }
}

void crawl()
{
    string now_url = "http://www.zgszrkdak.com/wzxx/show.asp?id=";
    for (int i = 16651; i <= 26000; i++)
    {
        string id = change_int_to_string(i);
        std::cout << now_url + id << std::endl;
        for (int j = 1; j <= 2e8; j++);
        use_wget(now_url + id, i);
    }
}

int main()
{
    crawl();
}