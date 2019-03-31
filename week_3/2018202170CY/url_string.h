#ifndef URL_STRING_H
#define URL_STRING_H

using std::string;

class Url_string
{
    private:
        string Ahead_, False_, Root_;
        Others others;
    public:
        Url_string(const string Ahead, const string False, const string Root):Ahead_(Ahead), False_(False), Root_(Root){};
        Url_string(){};
        string get_url(string &a_string);
        bool is_url(string &a_string);
        string get_direction(string &s);
        void copy(const Url_string new_one)
        {
            Ahead_ = new_one.Ahead_;
            False_ = new_one.False_;
            Root_ = new_one.Root_;
            others.copy(Others());
            // std::cout << Root_ << '\n' << False_ << '\n' << Ahead_ << "\n\n";
        };
};

#endif