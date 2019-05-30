#include "head.h" 
void HtmlParser::get_title(string content)
{
	int len ,format_len;
	int location_first = 0, location_end = 0;
	string title_format1 = "<title>";
        string title_format2 = "</title>";
        format_len = title_format1.length();
	location_first = content.find(title_format1);
	ofstream fout;
	fout.open("all_titles");
        if(location_first == string::npos)
        return;
        else
        {
                while(location_first != string::npos)
                {
                        string title_to_be_finded;
                        location_end = content.find(title_format2,location_first+format_len);
                        len = location_end-location_first-format_len;
                        title_to_be_finded = content.substr(location_first+format_len,len);
                        if(title_already_be_HtmlParser.find(title_to_be_finded) == title_already_be_HtmlParser.end())
                        {
                        	fout << title_to_be_finded << endl;
                        }
                        location_first = content.find(title_format1,location_first+1);
                        title_to_be_finded.erase(0,len);
                }
        }
        return;

}
