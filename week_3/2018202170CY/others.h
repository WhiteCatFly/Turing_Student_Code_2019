#ifndef OTHERS_H
#define OTHERS_H

using std::string;

class Others
{
    private:
        string Root_, Store_direction_;
    public:
        Others(const string Root, const string Store_direction):Root_(Root), Store_direction_(Store_direction){};
        Others(){};
        bool check1(string &str);
        void use_wget(string url, string direction);
        void true_url(string &direction, int num);
        void copy(Others new_one)
        {
            Root_ = new_one.Root_;
            Store_direction_ = new_one.Store_direction_;
        };
};

#endif