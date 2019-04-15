#include "head.h"
using namespace std;

HTMLparser::HTMLparser(string target_, int openway)
{
    if (openway == 0) //file open
    {
        ifstream fin;
        fin.open(target_);

        string line;
        while (getline(fin, line))
            ;
        this->target = line;

        fin.close();
    }
    else //string open
    {
        this->target = target_;
    }

    getcontent();
}

HTMLparser::~HTMLparser()
{
    cout << "DONE!" << endl;
}

void HTMLparser::getcontent()
{
    this->file = "file.html";
    string order = "wget --tries=3 --timeout=5s -O " + file + "  " + '\"' + target + '\"';

    cout << order << endl;
    system(order.c_str());

    /*ifstream fin ;
    fin.open(file);
    string line;
    while(getline(fin,line)){
        this->content+=line;
    }
    fin.close();*/
}