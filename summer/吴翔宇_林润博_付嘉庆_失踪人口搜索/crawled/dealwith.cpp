#include "head.h"
void dealwith12(string command,string file,int Len,int loc)
{
        string name = "../data/";
        string stringdata;
        int intdata;
        int Loc,Loc1,Loc2;
        int i = 0;
        while(command[loc+Len+i] <= '9'&&command[loc+Len+i] >= '0')
        {
            name += command[loc+Len+i];
            i++;
        }
        name += ".html";
        ofstream foutdata;
        foutdata.open(name);
        foutdata << name << endl;
        Loc = file.find("<td class=\"t-title\">失踪人姓名</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        foutdata << stringdata << endl;
        Loc = file.find("<td class=\"t-title\">性别</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        if(stringdata == "男")
        foutdata << 0 << endl;
        else
        foutdata << 1 << endl;
        Loc = file.find("<td class=\"t-title\">失踪人籍贯</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        foutdata << stringdata << endl;
        Loc = file.find("<td class=\"t-title\">出生日期</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        int birthday;
        birthday = datechange(stringdata);
        foutdata << birthday << endl;
        Loc = file.find("<td class=\"t-title\">失踪日期</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        int lostday;
        lostday = datechange(stringdata);
        foutdata << lostday << endl;
        Loc = file.find("<td class=\"t-title\">失踪时身高</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        int height = 0;
        for(int j = 0;j < Loc2-Loc1-4;j++)
        {
            height = height*10 + int(stringdata[j]-48);
        }
        foutdata << height << endl;
        Loc = file.find("<td class=\"t-title\">失踪地点</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        foutdata << stringdata << endl;
        Loc = file.find("<td class=\"t-title\">可能去向</td>");
        Loc1 = file.find("<td>",Loc+1);
        Loc2 = file.find("</td>",Loc1+1);
        stringdata = file.substr(Loc1+4,Loc2-Loc1-4);
        foutdata << stringdata << endl;
        Loc = file.find("<td class=\"t-title\">详细信息</td>");
        Loc1 = file.find("<td",Loc+1);
        Loc2 = file.find("</span></p></td>",Loc1+1);
        stringdata = file.substr(Loc1+3,Loc2-Loc1-3);
        string prestringdata;
        for(int k = 0 ; k < Loc2-Loc1-3;k++)
        {
            if(!(stringdata[k] < 48&&stringdata[k] >= 0&&stringdata[k] > 57&&stringdata[k] < 128))
            {
                prestringdata += stringdata[k];
            }
        }
        ofstream foutinput;
        ifstream finca;
        string _part,all;
        foutinput.open("input.txt");
        foutinput << prestringdata << endl;
        system("python take_apart.py");
        finca.open("cache.txt");
        while(getline(finca,_part))
        {
                all += _part;
        }
        foutdata << all << endl; 
}
void dealwith3(string command, string file, int Len, int loc)
{
    string name = "../data/";
    string article = "<div class=\"article-content\">";
    string stringdata;
    string information;
    int intdata,len1;
    int Loc,Loc1,Loc2;
    int i = 0;
    while(command[loc+Len+i] <= '9'&&command[loc+Len+i] >= '0')
    {
        name += command[loc+Len+i];
        i++;
    }
    name += ".html";
    ofstream foutdata;
    foutdata.open(name);
    foutdata << name << endl;
    Loc = file.find(article);
    information = "姓名： ";
    Loc1 = file.find(information);
    len1 = information.length();
    Loc2 = file.find(",",Loc1+1);
    stringdata = file.substr(Loc1+len1,Loc2-Loc1-len1);
    foutdata << stringdata << endl;
    Loc1 = file.find(" ",Loc2+1);
    stringdata = file.substr(Loc1+1,1);
    if(stringdata == "男")
    foutdata << 0 << endl;
    else
    foutdata << 1 << endl;
    //籍贯
    information = "出生于";
    Loc1 = file.find("出生于",Loc1+1);
    len1 = information.length();
    Loc2 = file.find("日",Loc1+1);
    stringdata = file.substr(Loc1+len1,Loc2-Loc1-len1+1);

    Loc1 =  file.find("</div>",Loc+1);
    stringdata = file.substr(Loc1+3,Loc2-Loc1-3);
    string prestringdata;
    for(int k = 0 ; k < Loc2-Loc1-3;k++)
    {
        if(!(stringdata[k] < 48&&stringdata[k] >= 0&&stringdata[k] > 57&&stringdata[k] < 128))
        {
            prestringdata += stringdata[k];
        }
    }
    ofstream foutinput;
    ifstream finca;
    string _part,all;
    foutinput.open("input.txt");
    foutinput << prestringdata << endl;
    system("python take_apart.py");
    finca.open("cache.txt");
    while(getline(finca,_part))
    {
            all += _part;
    }
    foutdata << all << endl; 


}