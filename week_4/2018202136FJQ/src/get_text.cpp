#include "parser.h"
void Parser::get_text(string content)
{
	int len;
	int location_first = 0, location_end = 0;
        string text_format1 = "<div class=\"essay_body\">";
        string text_format2 = "</div>";
        location_first = content.find(text_format1);
        ofstream fout;
        fout.open("all_text");
        if(location_first == string::npos)
        return;
        else
        {
                while(location_first != string::npos)
                {
                        string text_to_be_finded;
                        location_end = content.find(text_format2,location_first+24);
                        len = location_end-location_first-24;
                        text_to_be_finded = content.substr(location_first+24,len);
                        if(text_already_be_parser.find(text_to_be_finded) == text_already_be_parser.end())
                        {
                                fout << text_to_be_finded << endl;
                        }
                        location_first = content.find(text_format1,location_first+1);
                        text_to_be_finded.erase(0,10000);
                }
        }
        return;
}
