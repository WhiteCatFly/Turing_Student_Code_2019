#include "head.h"
void Parser::get_text(string content)
{
	int len ,format_len;
	int location_first = 0, location_end = 0;
        string text_format1 = "<div class=\"essay_body\">";
        string text_format2 = "</div>";
        format_len = text_format1.length();
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
                        location_end = content.find(text_format2,location_first+format_len);
                        len = location_end-location_first-format_len;
                        text_to_be_finded = content.substr(location_first+format_len,len);
                        if(text_already_be_parser.find(text_to_be_finded) == text_already_be_parser.end())
                        {
                                fout << text_to_be_finded << endl;
                        }
                        location_first = content.find(text_format1,location_first+1);
                        text_to_be_finded.erase(0,len);
                }
        }
        return;
}
