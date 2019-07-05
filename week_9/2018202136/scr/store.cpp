#include "head.h"
vector<Documents> alldocuments; 
int DocLen = 960;
vector<BasicStats> stats;
void store(vector<Documents> alldocuments){
    for(int i = 0;i < 1340-960;i++)
    {
        string filename = "urlsource/";
        string allpart,part;
        string text,title,url;
        ifstream fin,in;
        ofstream fout;
        string word;
        Parser htmlParser;
        Documents temp(DocLen-960);
        Similarity s;
        filename += itostring(DocLen);
        fin.open(filename);
        fout.open("input.txt");
        if(fin.is_open() == false)
        continue;
        else

        htmlParser.getcontent(fin);
        htmlParser.get_text(htmlParser.get_content(),text);
        htmlParser.get_title(htmlParser.get_content(),title);
        temp.settitle(title);
        fout << text << endl;
        system("python take_apart.py");
        in.open("cache.txt");
        while(getline(in,word)){
            temp.CountTotalwords();
            if(analysis(word) == false)
            temp.setmap(word);
        }
        alldocuments.push_back(temp);
        DocLen++;
    }
}
