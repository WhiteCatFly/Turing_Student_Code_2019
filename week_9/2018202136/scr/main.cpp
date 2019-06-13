#include "head.h"
int InputStringSize;
int main()
{
    BasicStats tempstats;
    string word;
    int k = 0,page = 0;
    string information;
    int t = clock();
    ifstream fin;
    ofstream fout;
    char command = 'Y';
    string name;
    Documents tempdoc;
    fout.open("input.txt");
    cout << "please input what you want to search" << endl;
    cin >> information;
    fout << information << endl;
    system("python take_apart.py");
    fin.open("cache.txt");
    store(alldocuments);
    while(getline(fin,word)){
        if(analysis(word) == false)
        {
            InputStringSize++;
            tempstats = BasicStats(word,0,1340);
            stats.push_back(tempstats);
        }
    }
    Similarity s;
    for(int i = 0;i < DocLen-960;i++)
    {
        s.idf(stats,alldocuments[i]);
        s.Scorce(alldocuments[i]);
    }
    for(int i = 0; i < DocLen-960;i++)
        for(int j = i+1;j < DocLen-960;j++)
        {
            if(alldocuments[j].getscorce() > alldocuments[i].getscorce())
            {
                tempdoc = alldocuments[j];
                alldocuments[j] = alldocuments[i];
                alldocuments[i] = tempdoc; 
            }
        }
    cout << int(alldocuments.size());
    for(int i = 0; i < alldocuments.size();i++)
    cout << alldocuments[i].getTitle() << endl;
    while(command == 'Y'||command == 'y')
    {
        for(int i = k;i < k+10;i++)
        cout << alldocuments[k].getTitle() << endl;
        cout << "if get into another page:(Y/N)" << endl;
        cin >> command;
        if(command == 'Y'||command == 'y')
        {
            cout << "please input the page number" << endl;
            cin >> page;
        }
        k = page*10;
    }
    t = t-clock();
    cout << "time:" << t << endl;
    return 0;

}