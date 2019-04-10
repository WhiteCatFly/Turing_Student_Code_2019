#ifndef CRAWLER_H
#define CRAWLER_H

using std::string;
class Crawler
{
    private:
        std::set<string> url_set;
        std::queue<string> url_queue;
        const string Root_, Store_direction_, False_, Ahead_;
        bool solve_a_line(string &one_line, string &direction);
        Url_string url_string;
        Others others;
    public:
        ~Crawler(){};
        Crawler(const string Root, const string Store_direction, const string False, const string Ahead):
            Root_(Root), Store_direction_(Store_direction), False_(False), Ahead_(Ahead)
        {
            Url_string new_one(Ahead, False, Root);
            url_string.copy(new_one);
            others.copy(Others(Root, Store_direction));
            // std::cout << Root_ << '\n' <<Store_direction_ << '\n' << False_ << '\n' << Ahead_ << "\n\n";
        }
        void crawler();
};

#endif