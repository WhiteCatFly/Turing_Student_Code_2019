#include "head.h"
int nsize;
int main(){
    int k = 0,page = 0;
    string information;
    ofstream fout;
    ifstream fin;
    havenapart temp;
    char command = 'Y';
    string name;
    nsize = 0;
    fout.open("information.txt");
    fin.open("cut.txt");
    cout << "please input what you want to search" << endl;
    cin >> information;
    fout << information << endl;
    system("python apart.py");
    while(getline(fin,word[nsize]))
    {
        nsize++;
    }
    HtmlParser search("http://info.ruc.edu.cn");
    search.deep_search();
    int t = clock();
    for(int i = 0;i < search.getnumber();i++)
        for(int j = i;j < search.getnumber();j++)
        {
            if(all[j].dft < all[j+1].dft)
            {
                temp = all[j+1];
                all[j+1] = all[j];
                all[j] = temp;
            }
        }
    while(command == 'Y'||command == 'y')
    {
        for(int i = k;i < k+10;i++)
        cout << all[i].url_name << endl;
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