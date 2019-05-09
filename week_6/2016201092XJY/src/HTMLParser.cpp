#include "HTMLParser.h"

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
    string result;
    while (regex_search(iter, iterEnd, Result, Pattern)){
        result = Result[0];
        //_nodeList.push_back (temp.substr(1,temp.length() - 1));
        if (result[0] == '<'){
            result.erase(0,1);
            result.insert(0,"1");     // 1 for TagNode
            result += "\n";
        }
        else {
            result.erase(0,1);
            if (result != ""){
                result.insert(0,"2"); // 2 for TextNode
                result += "\n";
            }
        }
        if ( (result[0] == '1') && (result[result.size()-2] == '/') ){     // Search for self-ending tag
            result.erase(result.size()-2,1);
            string temp = result;
            temp.insert(1,"/");
            result = result  + temp;
        }
        _treeLanguage += result;
        iter = Result[0].second;
    }
}

set <string> & HTMLParser::getAllUrls(Node* root){
    return Tree.searchHierarchy(root, "href", "a")
}
