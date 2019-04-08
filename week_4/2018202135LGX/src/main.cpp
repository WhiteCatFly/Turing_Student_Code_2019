#include"HTMLparser.h"

int main(){

    std::string root;

    std::cout << "Please enter your website:" << std::endl;

    std::cin >> root;

    std::string &url = root;
    
    HTMLparser test(url);

    std::cout << "Press a to get the title\n"
              << "Press b to get the image links\n"
              << "Press c to get the links and their titles\n"
              << "Press d to exit\n";

    while(1){
        
        char m;

        std::cin >> m;

        if(m == 'a' || m == 'A'){

            test.GetTitle();

        }

        else if(m == 'b' || m == 'B'){

            test.GetImg();

        }

        else if(m == 'c' || m == 'C'){

            test.GetBody();

        }

        else if(m == 'd' || m == 'D'){

            exit(0);

        }
        else std::cout << "Invalid input!" << std::endl;
    } 


}