#include "parser.h"
void Parser::get_in_a_certain_way(string content)
{
	string format_first = "http://\"";
	string format_end;
	cout << "please input the format you are looking" << endl;
	cin >> format_end;
	int len;
	int location_first = 0, location_end = 0;
        location_first = content.find(format_first);
        ofstream fout;
        fout.open("all_in_a_certain_way");
        if(location_first == string::npos)
        return;
        else
        {
                while(location_first != string::npos)
                {
                        string a_way_to_be_finded;
                        location_end = content.find(format_end,location_first);
                        len = location_end-location_first+3;
                        a_way_to_be_finded = content.substr(location_first,len);
                        if(a_way_already_be_parser.find(a_way_to_be_finded) == a_way_already_be_parser.end())
                        {
                                fout << a_way_to_be_finded << endl;
                        }
                        location_first = content.find(format_first,location_first+1);
                        a_way_to_be_finded.erase(0,200);
                }
        }
        return;

}

