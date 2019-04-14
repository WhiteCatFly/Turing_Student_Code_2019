#include<iostream>
#include"parser.h"
#include<string>
#include<fstream>
using namespace std;

int main()
{
    string url;
    cout<<"Please enter the url you want to parse："<<endl;
    cin>>url;
    parser Parse(url);
    //Parse.PARSE_ALL();
    int choice;
    int a=0;
    int chosen[3]={0};
    while(1)
    {
        if(a==1)
        {
            char ifcontinue;
            cout<<"Do you want to continue?(y/n)"<<endl;
            cin>>ifcontinue;
            if(ifcontinue=='n')
                break;
        }
        a=1;
        cout<<"1.Show me the title."<<endl
            <<"2.Show me the text."<<endl
            <<"3.Show me the url."<<endl
            <<"Please choose the options(1~3):"<<endl;
        cin>>choice;
        if(chosen[choice-1]==1)
        {
            cout<<"You have chosen this option,please choose again."<<endl;
            continue;
        }
        if(choice==1)
            Parse.parse_title();
        else if(choice==2)
            Parse.parse_text();
        else if(choice==3)
            Parse.parse_url();
        else
        {
            cout<<"You choose the wrong option,please choose again."<<endl;
            continue;
        }
        chosen[choice-1]=1;
        //cout<<chosen[0]<<chosen[1]<<chosen[2]<<endl;
    }
    return 0;
}