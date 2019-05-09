#ifndef __HTMLPARSER_H__
#define __HTMLPARSER_H__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "DOMTree.h"

using std::ifstream;
using std::regex;
using std::smatch;

class HTMLParser{
    private:
        string _url;
        string _sourceCode;
        string _treeLanguage;
        vector <string> _nodeList;
        DOMTree Tree;
        void translate();       // Translate from _sourceCode to _treeLanguage
    public:
        HTMLParser() = default;
        HTMLParser(const string & sourcecode);
        HTMLParser(ifstream & file);
	
	void show(){Tree.printHierarchy(Tree.getRoot());}
	set <string> & getAllUrls(Node* root);
	vector <string> & getAllTitles(Node* root);
        
};
#endif
