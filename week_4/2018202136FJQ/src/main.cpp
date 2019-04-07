#include "parser.h"
int main()
{
	int time,time_beg,time_end;
	string root;
	char command_do;
	string name;
	ifstream is;
	time_beg = clock();
	cout << "What do you want to do?" << endl;
	cout << "extract" << endl
		<< "A: title;B : text;"<< endl
		<<" C : link ; D : in a certain form ;E : just look" << endl;
	cout << "Please input the letter  you are going to do" << endl;
	cin >> command_do;
	cout << "please input the name where you are going to parser" << endl;
	cin >> name;
	is.open(name);
	if(is.is_open() == true)
	Parser parser(is,command_do);
	else
	Parser parser(name,command_do);	
        time_end = clock();
        time = time_end-time_beg;
        cout << time << endl;
        return 0;
}

