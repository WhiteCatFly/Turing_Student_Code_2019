#include "parser.h"

using namespace std;

int main(){
    int key1 = 1, key2, key3;
    Parser *parser = NULL;

    while(key1 != 2){
        key1 = 2;
        cout << "Please select your action." << endl;
        cout << "1.Handle a new web page." << endl;
        cout << "2.Exit program." << endl;
        cout << endl;
        cin >> key1;
        if(key1 == 1){
            key2 = 0;
            cout << "Please select the way you want to input the code of the web page" << endl;
            cout << "0.Return to the top." << endl;
            cout << "1.From the keyboard." << endl;
            cout << "2.From the file." << endl;
            cout << "3.From the url." << endl;
            cout << endl;
            cin >> key2;
            if(key2 == 1){
                cout << "Please input the code of the web page,and at last,please input the </html> to end" << endl;
                string buf, code = "";
                while(buf != "</html>"){
                    getline(cin, buf);
                    code += buf;
                    code += '\n';
                }
                parser = new Parser(code);
            }
            else if(key2 == 2){
                string filename;
                cin >> filename;
                getline(cin,filename);
                parser = new Parser(filename.c_str());
            }
            else if(key2 == 3){
                string url;
                cin >> url;
                string order = "wget --tries=3 \"";
                order += url;
                order += "\" ";
                order += "-O ";
                order += url;
                order += ".html";
                system(order.c_str());

                url += ".html";
                parser = new Parser(url.c_str());
            }

            if(key2 == 1 || key2 == 2 || key2 == 3){
                cout << "The web page code has been entered into the program,and its tree structure has been saved to the file:TreeStructure _(The name of the web page).out" << endl;
                
                key3 == 1;
                
                    cout << "Please select your action on this web page." << endl;
                    cout << "0.Return to the top." << endl;
                    cout << "1.Get the title." << endl;
                    cout << "2.Get the main body." << endl;
                    cout << "3.Get the hyperlinks." << endl;
                    cout << "4.Get the image links." << endl;
                    cout << "5.Custom extraction." << endl;
                    cout << endl;
                    cin >> key3;

                    vector<string> result;
                    string RegExp;

                    switch(key3){
                        case 1:
                            parser->Get_Title(result);
                            break;
                        case 2:
                            parser->Get_Body(result);
                            break;
                        case 3:
                            parser->Get_Href(result);
                            break;
                        case 4:
                            parser->Get_Img(result);
                            break;
                        case 5:
                            cout << "Please input a regular expression." << endl;
                            cin >> RegExp;
                            parser->Extract(regex(RegExp.c_str()), result);
                            break;
                    }
                    if(key3 != 0){
                        ofstream fout("result");
                        for(int i = 0; i < result.size(); i++){
                            fout << result[i] << endl;
                        }
                        fout.close();
                        cout << "The result has been output to result.out" << endl;
                    }
                    if(key3 == 1|| key3 == 2)
                    {
                        const char *sys = "./thulac <../result >../result.out";
                        system(sys);
                    }
        }
            delete parser;
        }
    }
    return 0;
}