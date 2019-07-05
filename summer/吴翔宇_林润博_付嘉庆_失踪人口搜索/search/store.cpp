#include "PersonData.h"

void store(vector<PersonData> &alldata)
{
    int max = 10860;
    ifstream fin;
    ofstream fout;
    for(int i = 0; i <= max;i++)
    {
        string name = "C:/Users/12772/Desktop/CMakeProject/data/" + itostring(i);
        fin.open(name);
        if(fin.is_open() == true)
        {
            int loc1,loc2;
            string place;
            string dataname;
	        string m_name;
	        bool m_sex;//0 : male
            string mm_sex;
	        int m_birthday;//YYYYMMDD
	        pair<string,string> m_birthplace;
	        int m_lostday;//YYYYMMDD
	        int m_height;
	        pair<string,string> m_lostplace;
	        string maytogo;
	        string m_information;
            fin >> dataname >> m_name >> m_sex >> place >> m_birthday;
            if(place.find("省") != string::npos)
            {
                loc1 = place.find("省");
                m_birthplace.first = place.substr(0,loc1+3);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_birthplace.second = place.substr(loc1+3,loc2-loc1+3);
                else
                {
                    m_birthplace.second = "不详";
                }
            }
            else if(place.find("自治区") != string::npos)
            {
                loc1 = place.find("自治区");
                m_birthplace.first = place.substr(0,loc1+9);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_birthplace.second = place.substr(loc1+9,loc2-loc1+3);
                else
                {
                    m_birthplace.second = "不详";
                }
            } 
            else if(place.find("特别行政区") != string::npos)
            {
                loc1 = place.find("特别行政区");
                m_birthplace.first = place.substr(0,loc1+15);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_birthplace.second = place.substr(loc1+15,loc2-loc1+3);
                else
                {
                    m_birthplace.second = "不详";
                }
            }
            else if(place.find("市") != string::npos)
            {
                loc1 = place.find("市");
                m_birthplace.first = place.substr(0,loc1+3);
                loc2 = place.find("区");
                if(loc2 != string::npos)
                m_birthplace.second = place.substr(loc1+3,loc2-loc1+3);
                else
                {
                    m_birthplace.second = "不详";
                }
            }
            else
            {
                m_birthplace.first = "不详";
                m_birthplace.second = "不详";
            }
            fin >> m_lostday >> m_height >> place;
            if(place.find("省") != string::npos)
            {
                loc1 = place.find("省");
                m_lostplace.first = place.substr(0,loc1+3);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_lostplace.second = place.substr(loc1+3,loc2-loc1+3);
                else
                {
                    m_lostplace.second = "不详";
                }
            }
            else if(place.find("自治区") != string::npos)
            {
                loc1 = place.find("自治区");
                m_lostplace.first = place.substr(0,loc1+9);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_lostplace.second = place.substr(loc1+9,loc2-loc1+3);
                else
                {
                    m_lostplace.second = "不详";
                }
            } 
            else if(place.find("特别行政区") != string::npos)
            {
                loc1 = place.find("特别行政区");
                m_lostplace.first = place.substr(0,loc1+15);
                loc2 = place.find("市");
                if(loc2 != string::npos)
                m_lostplace.second = place.substr(loc1+15,loc2-loc1+3);
                else
                {
                    m_lostplace.second = "不详";
                }
            }
            else if(place.find("市") != string::npos)
            {
                loc1 = place.find("市");
                m_lostplace.first = place.substr(0,loc1+3);
                loc2 = place.find("区");
                if(loc2 != string::npos)
                m_lostplace.second = place.substr(loc1+3,loc2-loc1+3);
                else
                {
                    m_lostplace.second = "不详";
                }
            }
            else
            {
                m_lostplace.first = "不详";
                m_lostplace.second = "不详";
            }         
            fin >> maytogo >> m_information;
            if(m_sex == 1)
            mm_sex = "女";
            else
            {
                mm_sex = "男";
            }
            
            PersonData temp( dataname ,m_name ,mm_sex , m_birthplace, m_birthday, m_lostday, m_height, m_lostplace,maytogo, m_information);
            alldata.push_back(temp);   
        }
        fin.close();
    }
}