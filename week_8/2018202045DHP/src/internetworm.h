#ifndef INTERNETWORM_H
#define INTERNETWORM_H
#include <iostream>
#include <string>
#include <queue>
#include <set>

#define OUT_INTERVAL 10
#define EMPTY std::string(" ")
#define SLASH '/'
#define DOT '.'

class URL{
    friend URL operator + (const URL &x, const URL &y) ;
    friend bool operator > (const URL &x, const URL &y) ;
    friend bool operator < (const URL &x, const URL &y) ;
    friend std::ostream & operator << (std::ostream &x, const URL &y);
    private:
        std::string _url;
        std::string _page;
        std::string _Chinese;
        bool _available;
    public:
        URL ();
        URL (std::string url);
        ~URL ();
        std::string OriginLink  ();
        std::string OriginPage  ();
        std::string OriginChinese();
        bool Download();
        void Write          (std::ostream &out);
        void WritePage      (std::ostream &out);
        void WriteChinese   (std::ostream &out);
        void FilterChinese  ();

        bool Scheck     ();
        bool DScheck    ();
        bool DDScheck   ();
        void DeletePeriod();
        bool Direct     ();
        bool ContainRoot();
        bool isban      ();
};

void IniLoader();
URL Format_Normalizer(URL x, URL y);
bool BreakpointLoader   (std::queue<URL> &waitinglist, std::set<URL> &repeatjudge);
void Backup             (std::queue<URL>  waitinglist, std::set<URL>  repeatjudge);
#endif
