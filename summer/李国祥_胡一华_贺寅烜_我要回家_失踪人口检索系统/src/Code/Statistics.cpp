#include"Statistics.h"

int string_to_int(const std::string &str)
{
  std::stringstream iss(str);
  int result = 0;
  iss >> result;
  return result;
}

void string_replace(std::string &str, const std::string &strold, const std::string &strnew) //将str中所有的strold改为strnew
{
    std::string::size_type nfind = 0;
    while (nfind != std::string::npos)
    {
        nfind = str.find(strold, nfind);
        if (nfind != std::string::npos)
        {
            str.replace(nfind, strold.length(), strnew);
            nfind += strnew.length();
        }
        else
            break;
    }
}

Date string_to_date(const std::string &string_date)
{
    std::string year = "年", month = "月", day = "日";
    int time[3] = {0};
    std::string space = " ";

    std::string temp_str = string_date;
    string_replace(temp_str, year, space);
    string_replace(temp_str, month, space);
    string_replace(temp_str, day, space);

    std::stringstream ss(temp_str);

    for (int i = 0; i < 3; i++)
    {
        ss >> time[i];
    }
    Date date(time[0], time[1], time[2]);

    return date;
}

void parse_to_Person(std::string &content, Person &person, std::string &detail, std::ofstream &fout, int index)
{
    std::regex pattern_id("<td class=\"t-title\">编号</td>\\s*<td>((.*?))</td>");
    std::regex pattern_name("<td class=\"t-title\">失踪人姓名</td>\\s*<td>((.*?))</td>");
    std::regex pattern_gender("<td class=\"t-title\">性别</td>\\s*<td>((.*?))</td>");
    std::regex pattern_birthplace("<td class=\"t-title\">失踪人籍贯</td>\\s*<td>((.*?))</td>");
    std::regex pattern_birthday("<td class=\"t-title\">出生日期</td>\\s*<td>((.*?))</td>");
    std::regex pattern_lostday("<td class=\"t-title\">失踪日期</td>\\s*<td>((.*?))</td>");
    std::regex pattern_height("<td class=\"t-title\">失踪时身高</td>\\s*<td>((.*?))</td>");
    std::regex pattern_lostplace("<td class=\"t-title\">失踪地点</td>\\s*<td>((.*?))</td>");
    std::regex pattern_description("<td class=\"t-title\">详细信息([^]*?)</tr>");
    std::regex pattern_("(<(.*?)>)");

    std::smatch a;

    while (std::regex_search(content, a, pattern_id))
    {
        person.set_id(a[1].str());
        content = a.suffix();
    }

    while (std::regex_search(content, a, pattern_name))
    {
        person.set_name(a[1].str());
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_gender))
    {
        std::string temp = a[1].str();
        bool Gender = false;
        if (temp == "男")
            Gender = true;
        person.set_gender(Gender);
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_birthplace))
    {
        person.set_birthplace(a[1].str());
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_birthday))
    {
        Date temp_date = string_to_date(a[1].str());
        person.set_birthday(temp_date);
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_lostday))
    {
        Date temp_date = string_to_date(a[1].str());
        person.set_lostday(temp_date);
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_height))
    {
        int temp = 0;
        std::stringstream ss;
        ss << a[1].str();
        ss >> temp;
        ss.clear();
        person.set_height(temp);
        content = a.suffix();
    }
    while (regex_search(content, a, pattern_lostplace))
    {
        person.set_lostplace(a[1].str());
        content = a.suffix();
    }
    //std::string temp_str;

    std::string result;
    regex_search(content,a,pattern_description);
    result = a[1].str();

    detail = result;
    //std::cout << detail << std::endl;
    while(regex_search(result,a,pattern_)){
        string_replace(detail,a[1].str(),"");
        result = a.suffix();
        
    }

    string_replace(detail,"&nbsp;","");
    person.set_detailed_description(detail);
    person.set_index(index
    );
    person.store_result(fout);
}

Statistics::Statistics(){
    std::ifstream fin("result");
    std::ifstream pos("position");
    std::string MAX;
    int max = 0;
    while(getline(pos, MAX)){
        if(max < string_to_int(MAX)) max = string_to_int(MAX);
    }
    if(max == 0)
    max = 1000;
    maximum = 1005;
    std::ifstream fin_2("position");
    std::string temp_str_2;
    while (getline(fin_2, temp_str_2))
    {
        if (temp_str_2 == "")
            break;
        positions.push_back(string_to_int(temp_str_2));
    }
    if (fin.peek() != EOF && fin && max >= maximum - 1)
    {
        std::ifstream fin_1("result");

        std::string temp_str_1;
        while(getline(fin_1, temp_str_1)){
            Content += temp_str_1;
            Content += "\n";
        }
        //std::cout << Content << std::endl;
        return;
    };
    std::ofstream fout("result", std::ios::app);
    std::ofstream position("position", std::ios::app);
    std::string cmd = "wget -O temp www.zgszrkdak.cn/home/person/show/id/";
    std::string no_use_string;

    for (int i = max + 1; i < maximum; i++) // 1 based
    {
        std::string temp_cmd = cmd + std::to_string(i) + ".html --tries=2 --timeout=2";
        int feedback = system(temp_cmd.c_str());
        if (feedback == 0)
        {
            Person no_use;
            std::ifstream fin_temp;
            fin_temp.open("temp");
            std::string content;
            std::string temp_str;
            while (getline(fin_temp, temp_str))
                content += temp_str;
            if (content.find("编号") != content.npos)
            {
                positions.push_back(i);
                fout << "#" + std::to_string(i) + "#" << std::endl;
                parse_to_Person(content, no_use, no_use_string, fout, i);
                //no_use.showall();
                fout << "#" + std::to_string(i) + "#" << std::endl;
                fout << std::endl;
                system("rm temp");
                position << i;
                position << std::endl;
                sleep(2);  //延时函数
            }
        }
    }
    std::string temp_str_3;
    std::ifstream fin_result("result");
    while (getline(fin_result, temp_str_3))
    {
        Content += temp_str_3;
        Content += "\n";
    }
    fin_result.close();
    //position << std::endl;
}
