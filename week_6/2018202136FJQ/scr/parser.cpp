#include "head.h"
Parser::Parser(string root,char select)
{
	number = 0;
	if(select == 'A')
	get_title(_content);
	else if(select == 'B')
	get_text(_content);
	else if(select == 'C')
	get_url(_content);
	else if(select == 'D')
	get_in_a_certain_way(_content);
	else if(select == 'E')
	cout << "good bye" << endl;
	else 
	cout << "wrong command" << endl;	
}
Parser::Parser(ifstream &io,char select)
{
	number = 0;
	getcontent(io);
	if(select == 'A')
	get_title(_content);
	else if(select == 'B')
	get_text(_content);
	else if(select == 'C')
	get_url(_content);
	else if(select == 'D')
	get_in_a_certain_way(_content);
	else if(select == 'E')
	cout << "good bye" << endl;
	else 
	cout << "wrong command" << endl;
}