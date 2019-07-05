#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "DOMTree.h"

using namespace std;

class HTMLParser{
    private:
        string _url;
        string _sourceCode;
        string _treeLanguage;
        vector <string> _nodeList;
        DOMTree Tree;
        void translate();       // From _sourceCode to _treeLanguage
    public:
        HTMLParser() = default;
        HTMLParser(const string & sourcecode);
        HTMLParser(ifstream & file);
        void show(){
            cout <<_sourceCode<<endl;
            cout <<_treeLanguage<<endl;
            for (auto i:_nodeList){
                cout << i << endl;
            }
        }
};
