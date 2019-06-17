#ifndef ADVANCEDCRAWLER
#define ADVANCEDCRAWLER

using std::string;
class AdvancedCrawler : public BaseCrawler
{
    private:
        const string Root_, Store_directory_, Wget_; 
    public:
        AdvancedCrawler(const string Root, const string Store_directory, const string wget):
            BaseCrawler(Root, Store_directory, wget), Root_(Root), Store_directory_(Store_directory), Wget_(wget){}
        virtual void use_wget(string url, string directory);
        virtual void crawler(int cnt);
        ~AdvancedCrawler(){};
        void make_break_point();
};

#endif