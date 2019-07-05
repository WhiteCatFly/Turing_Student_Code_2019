#include "head.h"
void Parser::getcontent(ifstream &io)
{
	string file,file_part;
	while(getline(io,file_part))
        {
                file += file_part;
        }
	_content = file;
}

