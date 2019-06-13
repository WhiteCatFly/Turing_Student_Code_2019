#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <ctime>
#include <cctype>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <regex>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

class Documents{
private:
    map<string,int>  words;
    long int totalwords;
    int id;
    string title;
    string url_name;
    double scorce;
public:
    Documents(){}
    Documents(int ID){
        totalwords = 0;
        id = ID;
    }
    void setmap(string word){
        words[word]++;
    }
    int getFreq(string word){
        return words[word];
    }
    long int getTotalnumber(){
        return totalwords;
    }
    int getID(){
        return id;
    }
    void CountTotalwords(){
        totalwords++;
    }
    void settitle(string Title){
        title = Title;
    }
    string getTitle(){
        return title;
    }
    void seturl(string url){
        url_name = url;
    }
    string geturl(){
        return url_name;
    }
    void setscorce(double Scorce){
        scorce = Scorce;
    }
    double getscorce(){
        return scorce;
    }
};

class BasicStats{
private:
    string Word;
    int Freq;
    int TotalNumberOfDocuments;
    double Tf;
public:
    BasicStats(){}
    BasicStats(string word,int freq = 0,int totalnumberofdocuments = 0){
        Freq = freq;
        TotalNumberOfDocuments = totalnumberofdocuments;
        Word = word; 
    }
    void countfreq(vector<Documents> doc){
        for(int i = 0; i < TotalNumberOfDocuments;i++)
        {
            if(doc[i].getFreq(Word) != 0)
            Freq++;
        }
    }
    int getFreq(){
        return Freq;
    }
    int getTotalNumberOfDocuments(){
        return TotalNumberOfDocuments;
    }
    double tf(){
        Tf = (TotalNumberOfDocuments + 1.0 )/( Freq + 1.0 );
        return Tf;
    }
    string getword(){
        return Word;
    }
};

class Similarity{
private:
    double Idf;
    double gamma;
    double lambda;
    double score;
public:
    Similarity(){
        Idf = 1.0;
        gamma = 0.0;
        lambda = 1.0;
    }
    void idf(vector<BasicStats> &stats,Documents &doc);
    void Scorce(Documents &doc);
};

class Parser
{
   private:
	int number ;
	set<string> title_already_be_parser;
	set<string> url_already_be_parser;
	set<string> text_already_be_parser;
	set<string> a_way_already_be_parser;
    string _content;
   public:
	Parser()
	{
		number = 0;
	}
    void getcontent(ifstream &io);
	void get_title(string content,string &title);
 	void get_text(string content,string &text);
	void get_url(string content);
	void get_in_a_certain_way(string content);
    string get_content(){
        return _content;
    }
};

extern vector<Documents> alldocuments; 
extern vector<BasicStats> stats;
extern int DocLen;
extern string commonword;
extern int InputStringSize;
void store(vector<Documents> alldocuments);
bool analysis(string word);
void storecommonword(void);
string itostring(int Doclen);



