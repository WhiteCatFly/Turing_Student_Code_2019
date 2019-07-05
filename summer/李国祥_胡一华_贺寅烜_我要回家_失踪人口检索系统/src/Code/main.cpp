#include"Base.h"
using namespace std;

int main()
{
    cout<<"Content-type:text/html"<<endl<<endl;
    string a;
    a=getenv("QUERY_STRING");
    Base test_base;
    std::vector<bool> empty;
    std::vector<bool> des = {0,0,0,1};
    Query query_3(a, 0);
    QueryResult result = test_base.scoring(query_3);
    //test_base.test_name(query_3.GetName());

    cout<<"<!DOCTYPE html>"<<endl;
    cout<<"<html lang=\"zh-CN\"><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">"<<endl;
    cout<<"<title>查询结果</title>"<<endl;
    
    cout<<"<link href=\"../missing search system/bootstrap.min.css\" rel=\"stylesheet\">"<<endl;
    cout<<"<link href=\"../missing search system/common.css\" rel=\"stylesheet\">"<<endl;
    cout<<"<link href=\"../missing search system/hface.css\" rel=\"stylesheet\">"<<endl;
    cout<<"<script src=\"../missing search system/jquery-1.11.2.min.js\"></script>"<<endl;
    cout<<"<script src=\"../missing search system/jquery.lazyload.js\"></script></head>"<<endl;
    
    cout<<"<body>"<<endl;
    
    if(result.size()==0)
    {
        cout<<"<div class=\"container wrapper\">"<<endl;
        cout<<"<div class=\"wrapper-banner\"><img src=\"../missing search system/no-result.jpg\"></div>"<<endl;
        cout<<"<div class=\"container wrapper roamer-list\">"<<endl;
        cout<<"<div class=\"wrapper-banner\"><img src=\"../missing search system/list-banner.jpg\"></div>"<<endl;
        cout<<"</body></html>"<<endl;
        return 0;
    }
    
    for(int i=0;i<result.size();i++)
    {
        cout<<"<div class=\"container wrapper\">"<<endl;
        cout<<"<div class=\"wrapper-banner\"><img src=\"../missing search system/result-banner.jpg\"></div>"<<endl;
        cout<<"<form class=\"form-horizontal\"  id=\"searchForm\">"<<endl;
        
        //第一行
        cout<<"<div class=\"form-group\">"<<endl;
        //ID
        cout<<"<label class=\"control-label col-xs-1\">编号</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"ID\">"<<endl;
        if(test_base[result[i]].get_string_id().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_id()<<endl;
        cout<<"</p></div>"<<endl;
        //Name
        cout<<"<label class=\"control-label col-xs-1\">姓名</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"NAME\">"<<endl;
        if(test_base[result[i]].get_string_name().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_name()<<endl;
        cout<<"</p></div>"<<endl;
        //Gender
        cout<<"<label class=\"control-label col-xs-1\">性别</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"gender\">"<<endl;
        if(test_base[result[i]].get_string_gender().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_gender()<<endl;
        cout<<"</p></div></div>"<<endl;
        
        //第二行
        cout<<"<div class=\"form-group\">"<<endl;
        //Birthday
        cout<<"<label class=\"control-label col-xs-1\">出生日期</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"birthday\">"<<endl;
        cout<<test_base[result[i]].get_string_birthday()<<endl;
        cout<<"</p></div>"<<endl;
        //Lostday
        cout<<"<label class=\"control-label col-xs-1\">失踪日期</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"lostday\">"<<endl;
        cout<<test_base[result[i]].get_string_lostday()<<endl;
        cout<<"</p></div>"<<endl;
        //Height
        cout<<"<label class=\"control-label col-xs-1\">身高</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"height\">"<<endl;
        if(test_base[result[i]].get_string_height().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_height()<<endl;
        cout<<"</p></div></div>"<<endl;

        //第三行
        cout<<"<div class=\"form-group\">"<<endl;
        //Birthplace
        cout<<"<label class=\"control-label col-xs-1\">籍贯</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"birthplace\">"<<endl;
        if(test_base[result[i]].get_string_birthplace().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_birthplace()<<endl;
        cout<<"</p></div>"<<endl;
        //Lostplace
        cout<<"<label class=\"control-label col-xs-1\">失踪地</label>"<<endl;
        cout<<"<div class=\"col-xs-3\"><p class=\"form-control\" name=\"lostplace\">"<<endl;
        if(test_base[result[i]].get_string_lostplace().empty())
            cout<<"不详"<<endl;
        else
            cout<<test_base[result[i]].get_string_lostplace()<<endl;
        cout<<"</p></div></div>"<<endl;
        
        //Detail Information
        cout<<"<div><label class=\"control-label col-xs-1\">详细信息</label><p class=\"detail-content\">"<<endl;
        if(test_base[result[i]].get_string_detailed_description().empty())
            cout<<"空"<<endl;
        else
            cout<<test_base[result[i]].get_string_detailed_description()<<endl;
        cout<<"</p></div>"<<endl;

        //URL
        cout<<"<div><label class=\"control-label col-xs-1\">网址</label><p class=\"detail-content\">"<<endl;
        string url="http://www.zgszrkdak.cn/home/person/show/id/" + test_base[result[i]].get_string_index() + ".html";
        cout<<" <a href=\" "<<url<<" \" target=\"_blank\"> "<<url<<endl;
        cout<<"</a></p></div></form></div>"<<endl;
    }

    cout<<"<div class=\"container wrapper roamer-list\">"<<endl;
    cout<<"<div class=\"wrapper-banner\"><img src=\"../missing search system/list-banner.jpg\"></div>"<<endl;
    cout<<"</body></html>"<<endl;
    return 0;
}