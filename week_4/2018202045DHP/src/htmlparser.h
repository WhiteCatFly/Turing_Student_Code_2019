#ifndef HTMLPARSER_H_INCLUDED
#define HTMLPARSER_H_INCLUDED

#include <string>
#include <vector>

#define SPACE ' '
#define TAB '\t'
#define QUOTE '\"'
#define SLASH '/'
#define EMPTY " "

class Element{
    private:
        std::string type_;
        std::string content_;
        std::vector <std::string> parameter;
        std::vector <std::string> value;
        bool terminated;
    public:
        Element(){};
        Element(std::string);
        ~Element(){};
        void Terminate();
        bool is_end();
        void AddContent(std::string content);
        void ShowFeature(std::ostream &dir, int depth);
        void ShowContent(std::ostream &dir, int depth);
        void OutTitle(std::ostream &dir);
        void OutContent(std::ostream &dir);
        void OutLink(std::ostream &dir);

};

bool Download(std::string &page);
void MainBodyAnalyzer(std::ostream &tree, std::ostream &title, std::ostream &content, std::ostream &link, std::string &page);

#endif