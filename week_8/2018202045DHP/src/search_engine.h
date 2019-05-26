#ifndef SEARCH_ENGINE_INCLUDED
#define SEARCH_ENGINE_INCLUDED

#include <set>
#include <map>
#include <vector>

class SearchEngine{
    private:
        std::map<int, std::string>  idtoword;
        std::map<std::string, int>  wordtoid;
        std::map<int, std::string>  idtopage;
        std::map<std::string, int>  pagetoid;
        std::map<int, int>          sizeofpage;
        //wordtopages : all of the pages that contains wordid. 
        std::map<int, std::vector<std::pair<int, int> > > wordtopages;
        std::map<int, std::vector<double>> value_wordtopages;
        std::vector<std::vector<std::string>> content;
        
    public:
        SearchEngine();
        ~SearchEngine();
        void Initialize();
        void LoadData(FILE *fp);
        void Evaluate();
        void Search(std::string);
        void TEST();
};

#endif