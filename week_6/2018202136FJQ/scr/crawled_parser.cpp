#include "head.h"
Crawled_parser::Crawled_parser(string root):Crawled::Crawled(root)
{
        cout << "What do you want to do?" << endl;
        cout << "extract" << endl
             << "A: title;B : text;"<< endl
             <<" C : link ; D : in a certain form ;E : just look F: deep search" << endl;
        cin >> _command;
        if(_command == 'F')
        Crawled::deep_search();
        else
        {
            ifstream is;
            string command;
            command = "wget -O Parser.txt --tries=1 \"";
            command = command + root + "\"";
            system(command.data());
            is.open("Parser.txt");
            _parser = Parser(is,_command);
        }
}