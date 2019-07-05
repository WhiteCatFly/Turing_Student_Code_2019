#ifndef BASECRAWLER_H
#define BASECRAWLER_H

using std::string;
class BaseCrawler
{
    private:
        const string Root_, Store_directory_, Wget_;
    public:
        const string False_ = "0", Ahead_ = "href=";
        std::set<string> url_set;
        std::queue<string> url_queue;
        Parser *parser_root;
        BaseCrawler(const string Root, const string Store_directory, const string Wget):
            Root_(Root), Store_directory_(Store_directory), Wget_(Wget){}
        ~BaseCrawler(){};
        void crawler();
        virtual void use_wget(string url, string directory);
        std::set<string> &get_set(){return url_set;}
        std::queue<string> get_queue(){return url_queue;}
        void insert_to_set(string &str){url_set.insert(str);}
        void push_to_queue(string &str){url_queue.push(str);}
        void true_url(string &directory, int num);
        bool belong_to_Root(string &str);
        string get_directory(string &s);
        bool is_url(string &a_string);
};
bool is_absolute_address(string &url);

#endif