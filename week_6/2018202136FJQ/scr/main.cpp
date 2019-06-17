#include "head.h"
int main(){
    char command = 'N';
    while(command != 'E'){
        cout << "please input your command : " << endl;
        cout << "C : crawled , P : parser , B : both , E : exit" << endl;
        cin >> command;
        if(command == 'C'||command == 'c')
        {
            string root;
            cout << "please input the website you are going to crawled :" << endl;
            cin >> root ;
            Crawled run = Crawled(root);
            run .deep_search();
        }
        else if (command == 'P'||command == 'p') {
            char command_do;
            string name;
            ifstream is;
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
        }
        else if (command == 'B'||command == 'b'){
            string root;
            cout << "please input the website you are going to crawled :" << endl;
            cin >> root ;
            Crawled_parser run = Crawled_parser(root);
        }
        else if (command == 'E'||command == 'e'){
            break;
        }
        else
        {
            cout << "wrong command" << endl;
            cout << "please try again" << endl;
        }
        
    }
    return 0;
}
