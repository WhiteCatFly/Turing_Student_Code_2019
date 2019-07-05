#include <iostream>
#include <fstream>
#include <string>
#include "Query.h"
#include <assert.h>
#include "utf8change.h"

ComplexQuery::ComplexQuery()
{
	name = sex = birthplace.first = birthplace.second = lostplace.first = lostplace.second = MayToGo.first = MayToGo.second = "";
	birthday = lostday = height = 0;
}

/*  name
	sex
	birthday
	lostday
	height
	birthplacefirst
	birthplacesecond
	lostplacefirst
	lostplacesecond
	maytogofirst
	maytogosecond
	information
*/

ComplexQuery::ComplexQuery(const string &data)
{
	ComplexQuery();
	name = sex = birthplace.first = birthplace.second = lostplace.first = lostplace.second = MayToGo.first = MayToGo.second = "";
	birthday = lostday = height = 0;
	int pos = 0, npos;
	do
	{
		npos = data.find('&', pos);
		string s = data.substr(pos, npos - pos);
		int epos = s.find('=');
		if (s[0] == 'n')
			{
			name = s.substr(epos + 1);
			name = UrlDecode(name);
			}
		else if (s[0] == 's')
			{
				sex = s.substr(epos + 1);
				sex =UrlDecode(sex);
			}
		else if (s[0] == 'b')
		{
			if (s[5] == 'd')
			{
				if (s.substr(epos + 1).empty())
					birthday = 0;
				else birthday = stoi(s.substr(epos + 1));
			}
			else if (s[10] == 'f')
			{
				birthplace.first = s.substr(epos + 1);
				birthplace.first = UrlDecode(birthplace.first);
			}
			else
				{
					birthplace.second = s.substr(epos + 1);
					birthplace.second = UrlDecode(birthplace.second);
				}
		}
		else if (s[0] == 'l')
		{
			if (s[4] == 'd')
			{
				if (s.substr(epos + 1).empty())
					lostday = 0;
				else lostday = stoi(s.substr(epos + 1));
			}
			else if (s[9] == 'f')
				{
					lostplace.first = s.substr(epos + 1);
					lostplace.first = UrlDecode(lostplace.first);
				}
			else
				{
					lostplace.second = s.substr(epos + 1);
					lostplace.second = UrlDecode(lostplace.second);
				}
		}
		else if (s[0] == 'h')
		{
			if (s.substr(epos + 1).empty())
				height = 0;
			else height = stoi(s.substr(epos + 1));
		}
		else if (s[0] == 'i')
		{
			information = s.substr(epos + 1);
			information = UrlDecode(information);
			cout << "infor" << information << endl;
			ifstream fin;
			ofstream fout;
			string part;
			fout.open("input.txt");
			fout << information << endl;
			system("py take_apart.py");
			fin.open("cache.txt");
			information = "";
			while(getline(fin,part))
			{
				information += part;
			}
		}
		pos = npos + 1;
	} while (npos != string::npos);
}

void ComplexQuery::print()
{
}
