#include "HTMLParser.h"

using namespace std;

HTMLParser::HTMLParser(const string & sourcecode){
    _sourceCode = sourcecode;
    translate();
    Tree.initializeTree(_treeLanguage);
}

HTMLParser::HTMLParser(ifstream & file){
    string sourcecode, temp;
    while(getline(file, temp)){
        temp += "\n";
        sourcecode += temp;
    }
    _sourceCode = sourcecode;
    translate();
    Tree.initializeTree(_treeLanguage);
}

void HTMLParser::translate(){
    regex Pattern("[<|>].*?(?=[<|>])");
    smatch Result;
    string::const_iterator iter = _sourceCode.begin();
    string::const_iterator iterEnd = _sourceCode.end();
    string temp;
    while (regex_search(iter, iterEnd, Result, Pattern)){
        temp = Result[0];
        //_nodeList.push_back (temp.substr(1,temp.length() - 1));
        if (temp[0] == '<'){
            temp.erase(0,1);
            temp.insert(0,"1");
        }
        else {
            temp.erase(0,1);
            temp.insert(0,"2");
        }
        temp += "\n";
        _treeLanguage += temp;
        iter = Result[0].second;
    }
}
