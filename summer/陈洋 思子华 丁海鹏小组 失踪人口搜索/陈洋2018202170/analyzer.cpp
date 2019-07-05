#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <fstream>

using std::string;

bool is_wanted(string title)
{
	if (title.find("寻人寻亲微信快报") != string::npos) return false;
	if (title.find("《") != string::npos) return false; 
	if (title.find("误区") != string::npos || title.find("寻找方法") != string::npos) return false;
    if (title.find("寻亲") != string::npos || title.find("寻家") != string::npos) return true;
    else if (title.find("寻找") != string::npos || title.find("姓名") != string::npos) return true;
//    else if (title.find("[") != string::npos) return true; 
    else return false;
}

string Filename(string url)
{
    for (int i = 0; i < url.length(); i++)
    if (url[i] == '/') url[i] = '_';
    return url;
}

string int_to_string(int num)
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

int IncludeChinese(string str)
{
    for (int i = 0; i < str.length() - 1; i++)
    {
        if ( (str[i] & 0x80) && (str[i + 1] & 0x80) )
        return 1;
    }
    return 0;
}

string get_content(string str)
{
	int pl = 0;
	string content;
	while(pl < str.length())
	{
		if (str[pl] == '<')
		{
			int cnt = 1;
			while (cnt != 0)
			{
				pl++;
				if (str[pl] == '<') cnt++;
				if (str[pl] == '>') cnt--;
			}
		}
		else
		{
			content += str[pl];
		}
		pl++;
	}
	return content;
}

int place(string content, string target, int pl = 0)
{
	if (content.find(target, pl) != string::npos) return content.find(target, pl);
	else return content.length();
}

string get_name(string content)
{
	int pl;
	string name;
	if ( (pl = content.find("姓名：")) != string::npos || (pl = content.find("姓名:")) != string::npos )
	{
		if( pl <= 30 )
		{
			if (content.find("姓名：") != string::npos) pl += string("姓名：").length();
			else pl += string("姓名:").length();
			int ed = std::min(place(content, ",", pl), place(content, "，", pl));
			ed = std::min(ed, place(content, " ", pl));
			for (int i = pl; i < ed; i++)
			name += content[i];
		}
	}
	else if ( (pl = content.find("寻亲启事：")) != string::npos)
	{
		if (pl <= 30)
		{
			pl += string("寻亲启事：").length();
			int ed = std::min(place(content, ",", pl), place(content, "，", pl));
			ed = std::min(ed, place(content, " ", pl));
			for (int i = pl; i < ed; i++)
			name += content[i];
		}
	}
	for (int i = 0; i < name.length(); i++)
	if (isdigit(content[i]))
	{
		name = "-1";
		break;
	}
	if (name.length() == 0) name = "-1";
	return name;
}

string get_gender(string content)
{
	int pl1 = place(content, "男"), pl2 = place(content, "女");
	if (pl1 == pl2) return "-1";
	else if (pl1 < pl2) return "男";
	else return "女"; 
}

int get_tag(string content)
{
	int tag = -1;
	if (content.find("姓名") != string::npos) tag = 1;
	else if (content.find("性别") != string::npos) tag = 2; 
	else if (content.find("出生日期") !=  string::npos) tag = 3;
	else if (content.find("籍贯") != string::npos) tag = 4;
	else if (content.find("失踪时间") != string::npos || content.find("失踪日期") != string::npos) tag = 5;
	else if (content.find("失踪地点") != string::npos) tag = 6;
	else if (content.find("述") != string::npos || content.find("详细信息") != string::npos || content.find("失踪人详细") != string::npos) tag = 7;
	else if (content.find("年龄") != string::npos) tag = 8;
	else if (content.find("身高") != string::npos && content.length() < 20) tag = 9;
	else if ((content.find("寻找类别") != string::npos || content.find("酬金") != string::npos) && content.length() < 20) tag = 10; 
	return tag; 
}

void get_lostdate(int lostdate[], string content)
{
	int pl1, pl2, pl3;
	if (content.find("年") != string::npos)
	{
		pl1 = content.find("年"), pl2 = content.find("月"), pl3 = content.find("日");
		for (int i = 0; i < pl1 && isdigit(content[i]); i++) 
		if (isdigit(content[i]) == true) lostdate[0] = lostdate[0] * 10 + content[i] - '0';
		for (int i = pl1 + 2; i < pl2 && isdigit(content[i]); i++) lostdate[1] = lostdate[1] * 10 + content[i] - '0';
		for (int i = pl2 + 2; i < pl3 && isdigit(content[i]); i++) lostdate[2] = lostdate[2] * 10 + content[i] - '0';
	}
	else if (content.find(".") != string::npos)
	{
		pl1 = content.find(".");content[pl1] = 'a';
		pl2 = content.find(".");content[pl2] = 'a';
		pl3 = content.length();
		for (int i = 0; i < pl1 && isdigit(content[i]); i++) 
		if (isdigit(content[i]) == true) lostdate[0] = lostdate[0] * 10 + content[i] - '0';
		for (int i = pl1 + 1; i < pl2 && isdigit(content[i]); i++) lostdate[1] = lostdate[1] * 10 + content[i] - '0';
		for (int i = pl2 + 1; i < pl3 && isdigit(content[i]); i++) lostdate[2] = lostdate[2] * 10 + content[i] - '0';
	}
	else if (content.find("-") != string::npos)
	{
		pl1 = content.find("-");content[pl1] = 'a';
		if ((pl2 = content.find("-")) != string::npos) content[pl2] = 'a';
		else pl2 = content.length();
		pl3 = content.length();
		for (int i = 0; i < pl1 && isdigit(content[i]); i++) 
		if (isdigit(content[i]) == true) lostdate[0] = lostdate[0] * 10 + content[i] - '0';
		for (int i = pl1 + 1; i < pl2 && isdigit(content[i]); i++) lostdate[1] = lostdate[1] * 10 + content[i] - '0';
		for (int i = pl2 + 1; i < pl3 && isdigit(content[i]); i++) lostdate[2] = lostdate[2] * 10 + content[i] - '0';
	}
	if (lostdate[0] < 100)
	{
		if (lostdate[0] < 20) lostdate[0] += 2000;
		else lostdate[0] += 1900;
	}
}

int get_age(string content)
{
	int year = 0, age = -1, pl;
	if (content.length() != 0)
	{
		if ((pl = content.find("岁")) != string::npos)
		{
			int base = 1;
			age = 0;
			for (int i = pl - 1; isdigit(content[i]); i--)
			{
				age += base * (content[i] - '0');
				base *= 10;
			}
		}
		for (int i = 0; i < content.length() - 3; i++)
		{
			bool flag = true;
			for (int j = 0; j < 4; j++)
			{
				if (!isdigit(content[i + j])) flag = false;
			} 
			if (flag == true)
			{
				year = 0;
				for (int j = 0; j < 4; j++)
				{
					year = year * 10 + content[i + j] - '0';
				}
				age = 2019 - year + 1;
				break;
			}
		}
	}
	return age;
}

void getinfomation_table(int id)
{
    std::ifstream fin;
    string filename = "C:\\Users\\dell\\Desktop\\集训\\data2\\" + int_to_string(id) + ".txt";
    fin.open(filename.c_str());
    if (!fin) return ;
    string a_line;
    bool have_title = false;
    string content;
    string name = "-1", gender = "-1", birthplace = "-1", lostplace = "-1", others = "-1";
    int age = -1, height = -1, lostdate[3] = {0, 0, 0};
    int tag = -1;
    bool started = false, end = false;
    int cnt = 0;
    std::ofstream fout;
	fout.open("table_result.txt", std::ios::app);
    while(getline(fin, a_line))
    {
        int pl;
        cnt ++;
        if ((pl = a_line.find("<title>") )!= string::npos && have_title == false)
        {
            have_title = true;
            string title;
            int len = 0, begin = pl + string("<title>").length();
            for (int i = begin; ; i++)
            {
                if (a_line[i] == '<') break;
                len++;
            }
            title = a_line.substr(begin, len);
            if (!is_wanted(title)) return ;
        }
        if (a_line.find("<TBODY>") != string::npos) started = true;
        if (started == true && a_line.find("</table>") != string::npos) end = true;
        if (started == true && end == false)
        {
        	string content = get_content(a_line);
        	while ((pl = content.find("&nbsp;") )!= string::npos) content.erase(pl, string("&nbsp;").length());
        	if ((pl = content.find("如：被拐被骗、迷路走失、离家出走、失散亲友、其他")) != string::npos)
        	content.erase(pl, string("如：被拐被骗、迷路走失、离家出走、失散亲友、其他").length());
        	if ((pl = content.find("如：家寻亲人、亲人寻家")) != string::npos)
        	content.erase(pl, string("如：家寻亲人、亲人寻家").length());
        	if (content.find("</TBODY>") != string::npos) tag = -1;
        	if (get_tag(content) != -1 && tag != 7)
        	{
        		tag = get_tag(content);
//        		fout << "\n" << cnt << " " << content << " " << tag << "\n";
        	}
        	else
        	{
        		if (tag == 1)
        		{
        			if (content.length() != 0) name = content;
        		}
        		else if (tag == 2)
        		{
        			if (content.length() != 0) gender = content;
        		}
        		else if (tag == 3)
        		{
        			if (age == -1)
        			age = get_age(content);
        		}
        		else if (tag == 4)
        		{
        			if (content.length() != 0) birthplace = content;
        		}
        		else if (tag == 5)
        		{
        			if (content.length() != 0)
        			{
        				get_lostdate(lostdate, content);
	        		}
        		}
        		else if (tag == 6)
        		{
        			if (content.length() != 0) lostplace = content;	
        		} 
        		else if (tag == 7)
        		{
        			if (others.find("-1") != string::npos) others.clear();
        			if (content.find("分享到") != string::npos) break;
        			if (content.length() != 0) others += content + ",";
        		}
        		else if (tag == 8)
        		{
        			pl = 0;
        			age = 0;
        			while (isdigit(content[pl]) == true)
        			{
        				age = age * 10 + content[pl] - '0';
        				pl++;
        			}
        		}
        		else if (tag == 9 && (height == -1 || height == 0))
        		{
        			height = 0;
        			for (int i = 0; i < content.length(); i++)
        			{
        				if (content[i] < 0) break;
//        				std::cerr << content[i] << " " << isdigit(content[i]) << "\n";
						if (isdigit(content[i]) == true) height = height * 10 + content[i] - '0';
					}
//					std::cerr << "h:" << height << std::endl;
        		}
        	}
        }
    }
    fin.close();
    if (name == "-1" && gender == "-1" && birthplace == "-1" && lostplace == "-1" && others == "-1" && age == -1 && height == -1) return ;
    int pl;
    while ((pl = others.find(" ") ) != string::npos) others.erase(pl, 1);
    if ((pl = others.find("身高") ) != string::npos && height == -1)
    {
    	while(!isdigit(others[pl])) pl++;
    	int ed = pl;
    	while (isdigit(others[ed + 1]) == true || others[ed + 1] == '.') ed++;
    	height = 0;
    	bool flag = false;
    	for (int i = pl; i <= ed; i++)
    	{
    		if (isdigit(others[i]) == true)
    		height = height * 10 + others[i] - '0';
    		if (others[i] == '.') flag = true;
    	}
    	if (flag && height < 100 && others[pl] != '0')
    	height *= 10;
    }
    if (age < 0 || age > 120) age = -1;
    if (height < 0 || height > 200) height = -1;
	fout << id << " " << name << " " << gender << " " << age << " " << height << " " << birthplace << " ";
	for (int i = 0; i < 3; i++)
	fout << lostdate[i] << " ";
	if (others.empty()) others = "-1"; 
	fout << lostplace << " " << others << "\n"; 
}

int get_height(string content)
{
	int height = 0;
	if (content.find("身高") == string::npos) return 0;
	else
	{
		int pl = content.find("身高");
		int ed = std::min(place(content, ",", pl), place(content, "，", pl));
		for (int i = pl; i < ed; i++)
		{
			if (isdigit(content[i]))
			{
				height = height * 10 + content[i] - '0';
			}
		}
	}
	if (height < 20) height *= 10;
	return height;
}

class date
{
	public:
		int year, month, day;
		date(int year = 0, int month = 0, int day = 0):year(year), month(month), day(day){}
		bool operator <(const date &x)
		{
			if (year != x.year) return year < x.year;
			else if (month != x.month) return month < x.month;
			else return day < x.day;
		}
};

date get_date(string &content)
{
	int pl1, pl2, pl3;
	int year = 0, month = 0, day = 0;
	if (content.find("年") != string::npos)
	{
		pl1 = content.find("年"), pl2 = content.find("月"), pl3 = content.find("日");
		for (int i = std::max(0, pl1 - 10); i < pl1; i++) 
		if (isdigit(content[i]) == true) year = year * 10 + content[i] - '0';
		for (int i = pl1 + 2; i < pl2 && isdigit(content[i]); i++) month = month * 10 + content[i] - '0';
		for (int i = pl2 + 2; i < pl3 && isdigit(content[i]); i++) day = day * 10 + content[i] - '0';
		
	}
	content.erase(pl1, 2);
	return date(year, month, day);
}

int get_age2(string content)
{
	int age1 = 0;
	date Min = date(9999, 0 ,0), now;
	int age2 = 0, pl;
	if ((pl = content.find("岁")) != string::npos)
	{
		int base = 1;
		for (int i = pl - 1; isdigit(content[i]); i--)
		{
			age2 += base * (content[i] - '0');
			base *= 10;
		}
	}
	while (true)
	{
		now = get_date(content);
		if (now.year == 0) break;
		if (now < Min) Min = now;
	}
	if (Min.year != 9999) age1 = 2019 - Min.year + 1;
	if (age1 < 0 || age1 > 120) age1 = 0;
	if (age2 < 0 || age2 > 120) age2 = 0;
	return std::max(age1, age2);;
}

date get_lostdate2(string content)
{
	date Max, now;
	while(true)
	{
		now = get_date(content);
		if (now.year == 0) break;
		if (Max < now) Max = now;
//		std::cerr << now.year << " " << now.month << " " << now.day << "\n";
	}
	return Max;
}

void getinfomation_passage(int id)
{
    std::ifstream fin;
    string filename = "C:\\Users\\dell\\Desktop\\集训\\data\\" + int_to_string(id) + ".txt";
    fin.open(filename.c_str());
    if (!fin) return ;
    string a_line;
    bool have_title = false;
    string content, title;
    std::ofstream fout;
    fout.open("passage_result.txt", std::ios::app);
    while(getline(fin, a_line))
    {
        int pl;
        if ((pl = a_line.find("<title>") )!= string::npos && have_title == false)
        {
            have_title = true;
            int len = 0, begin = pl + string("<title>").length();
            for (int i = begin; ; i++)
            {
                if (a_line[i] == '<') break;
                len++;
            }
            title = a_line.substr(begin, len);
            if (!is_wanted(title)) return ;
			title.erase(0, string("寻人启事-寻人启事网_").length());
        }
        if(IncludeChinese(a_line))
        {
        	while ( (pl = a_line.find("&nbsp;")) != string::npos) a_line.erase(pl, string("&nbsp;").length());
        	if (a_line.find("中国失踪人口档案库") != string::npos || a_line.find("newstitle") != string::npos 
			|| a_line.find("警告") != string::npos) continue;
        	string now_content = get_content(a_line);
        	if (now_content.length() > content.length()) content = now_content;
        }
    }
    fin.close();
    int pl;
    while( (pl = content.find("&nbsp;") ) != string::npos) 
    {
    	content.erase(pl, string("&nbsp;").length());
    }
    date lostdate = get_lostdate2(content);
    string name = get_name(title);
    int age = get_age2(content), height = get_height(content);
    if ((2019 - lostdate.year + 1) == get_age2(content) ) lostdate = date(0,0,0); 
    if (name == "-1" && age == 0 && height == 0 && lostdate.year == 0) return ;
    fout << id << " " << name << " " << get_gender(title) << " " << age << 
	" " << height << " 0 " << lostdate.year << " " << lostdate.month << " " << lostdate.day << " 0 " << content;
	fout << "\n";
//    fout << content << std::endl;
}

void analyze_table()
{
    std::ofstream fout;
    fout.open("table_result.txt");
    fout.close();
    for (int i = 1; i <= 25000; i++)
    {
        string id = int_to_string(i);
        std::cout << id << std::endl;
        getinfomation_table(i);
    }
}

void analyze_passage()
{
	std::ofstream fout;
    fout.open("passage_result.txt");
    fout.close();
    fout.open("content.txt");
    fout.close();
    for (int i = 1; i <= 26000; i++)
    {
        std::cout << i << std::endl;
        getinfomation_passage(i);
    }
}

int main()
{
//	string test = "aaa1991年1月1日";
//	date d = get_date(test);
//	std::cerr << d.year << " " << d.month << " " << d.day << "\n";
    analyze_passage();
}
