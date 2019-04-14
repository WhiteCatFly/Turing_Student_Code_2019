#include "head.h"
using namespace std;

void geturl(string &target_, int &openway)
{
    cout << "仅允许输入一个网址(例如：info.ruc.edu.cn)" << endl;
    cout << "文件读入请输入0，string读入请输入1" << endl;
    cin >> openway;
    cout << "请输入文件地址或网址" << endl;
    cin >> target_;
}

void use(HTMLparser &t)
{
    cout<<"基本功能："<<endl;
    cout<<"1.获取标题"<<endl;
    cout<<"2.获取正文"<<endl;
    cout<<"3.获取连接"<<endl;
    cout<<"0.关闭程序"<<endl;
    cout<<"PS：输入序号并按下换行符"<<endl;

    int i;
    bool m=0;
    while(cin>>i)
    {
        switch(i)
        {
            case 0: m=1;break;
            case 1: t.extract_title();break;
            case 2: t.extract_content();break;
            case 3: t.extract_url();break;
            default: cout<<"ERROR!"<<endl;
        }
        if(m==1)    break;
    }
}