#include<map>
#include<set>
#include<vector>
#include<utility>

class Searchengine{
    private:
    const int url_number=400;    
    std::map<std::string,std::vector< std::vector<int> >> wordmap;
    std::set <std::string> word_inmap;
    std::string query;
    int require_number;
    public:
    Searchengine(std::string _query,int number_require){
        query=_query;
        require_number=number_require;
        search(query,require_number);
        
    }
    void search(std::string query,int require_number);
    bool meaningful(std::string word);
    void singleword(std::string query,int require_number);
    void mutipleword(std::string query,int require_number); 

};