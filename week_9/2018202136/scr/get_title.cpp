#include "head.h" 
void Parser::get_title(string content,string &title)
{
	int len;
	int location_first = 0, location_end = 0;
	string title_format1 = "<title>";
        string title_format2 = "</title>";
	location_first = content.find(title_format1);
        if(location_first == string::npos)
        return;
        else
        {
                string title_to_be_finded;
                location_end = content.find(title_format2,location_first+7);
                len = location_end-location_first-7;
                title_to_be_finded = content.substr(location_first+7,len);
                title = title_to_be_finded;
                title_to_be_finded.erase(0,200);
        }
        return;

}
