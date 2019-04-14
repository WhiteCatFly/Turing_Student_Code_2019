#ifndef HTML_PARSER
#define HTML_PARSER
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using std::string;
using std::vector;


//SOME Consts
const string linkfile = "Links.txt", textfile = "Texts.txt";
const std::regex tag_re("<[\\w/].*?>"), str_re("[^<>\\t\\s]+"), s_re("[\\t\\s]*");
const std::regex link_re("(\"|\')?(http://|https://)?([^{}\\s]+/)*[^{}\\.]+(\\.(cn|com|net|org|ac|io|php|html|htm|jsp|do))?[^{}\\s\\.]*");


class Tag
{
	friend class HTMLParser;
private:
	string tagName;
	Tag *pre_;
	Tag *nxt_;
	Tag *prt_;
	Tag *son_; // the first son 
public:
	std::vector<string> strs;
	std::map<string, string> attrs;

	Tag():tagName(""), pre_(nullptr), nxt_(nullptr), prt_(nullptr), son_(nullptr){}
	~Tag() = default;
	string& getTagName(){return tagName;}
	Tag* prev(){return pre_;}
	Tag* next(){return nxt_;}
	Tag* parent(){return prt_;}
	Tag* son(){return son_;}

	string operator[](const string& key) const{
		if(attrs.count(key) > 0) return attrs.find(key) -> second;
		else return "";
	}

	Tag* find(const string& tag_name);
	int find_all(const string& tag_name, std::vector<Tag*> &v);
};

enum DFSMODE
{
	LINKMODE,
	TEXTMODE
};

const Tag nul_tag;
void delTagDfs(Tag* tag);
int output_dfs(Tag* tg,  DFSMODE md, std::ofstream& oflie);

class HTMLParser
{
private:
	Tag *root_, *title_, *current_;
	string source_;

	void parseTag(string str);
	void parseEndTag(string str);
	void parseText(const string &str, int l, int r); //[l, r)

public:
	HTMLParser(const string& source);
	HTMLParser(std::ifstream& in);
	~HTMLParser();

	string getTitle() const;
	int getTexts(const string& filename = textfile);
	int getLinks(const string& filename = linkfile);

	Tag* find(const string& tag_name);
	int find_all(const string& tag_name, std::vector<Tag*> &v);
};
#endif