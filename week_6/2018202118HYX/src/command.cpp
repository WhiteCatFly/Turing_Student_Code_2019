#include"head.h"
using namespace std;

void command()
{
    cout<<"基本功能："<<endl;
    cout<<"1.网络爬虫"<<endl;
    cout<<"2.HTMLparser"<<endl;
    cout<<"0.关闭程序"<<endl;
    cout<<"PS：输入序号并按下换行符"<<endl;

    int i;
    bool m=1;
    while(cin>>i)
    {
        if(i==1)
        {
            cout<<"基本功能："<<endl;
            cout<<"1.info.ruc.edu.cn"<<endl;
            cout<<"2.econ.ruc.edu.cn"<<endl;
            cout<<"3.other url"<<endl;
            cout<<"0.返回上一级"<<endl;
            cout<<"PS：输入序号并按下换行符"<<endl;

            int j;
            bool n=1;
            while(cin>>j)
            {
                switch(j)
                {
                    case 0:n=0;break;
                    case 1:
                    {
                        Info s;
                        s.BFS();
                        break;
                    }
                    case 2:
                    {
                        Econ s;
                        s.BFS();
                        break;
                    }
                    case 3:
                    {
                        cout<<"please input the url:"<<endl;
                        string t;
                        cin>>t;
                        if(t.find("http://")!=t.npos)
                            t.erase(0,7);
                        if(t.find("https://")!=t.npos)
                            t.erase(0,8);
                        Base s(t);
                        s.BFS();
                    }
                    default:
                        cout<<"ERROR! PLEASE FOLLOW THE COMMAND!"<<endl;
                }
                if(n==0)
                    break;
            }
        }
        else if(i==2)
        {
            cout<<"基本功能："<<endl;
            cout<<"1.获取标题"<<endl;
            cout<<"2.获取正文"<<endl;
            cout<<"3.获取连接"<<endl;
            cout<<"0.关闭程序"<<endl;
            cout<<"PS：输入序号并按下换行符"<<endl;
            cout<<endl;
            cout<<"please input the url"<<endl;
            string t;
            cin>>t;
            Parser s(t);
            
            int j;
            bool n=1;
            while(cin>>j)
            {
                switch(j)
                {
                    case 0:n=0;break;
                    case 1:s.extract_title();break;
                    case 2:s.extract_content();break;
                    case 3:s.extract_url();break;
                    default:
                        cout<<"ERROR!"<<endl;
                }
                if(n==0)
                    break;
            }
        }
        else if(i==0)
            m=0;
        else
            cout<<"ERROR!"<<endl;
        
        if(m==0)
            break;
    }
}