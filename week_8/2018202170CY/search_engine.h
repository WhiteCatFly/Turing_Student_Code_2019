#ifndef SEARCH_ENGINE
#define SEARCH_ENGINE

using std::string;
class posting
{
    public:
        int file_id, lines, id;
        int word_id;
        bool operator <(const posting &x)
        {
            return file_id == x.file_id ? (lines == x.lines ? id < x.id : lines < x.lines) : file_id < x.file_id;
        }
        bool operator ==(const posting &x)
        {
            return file_id == x.file_id && lines == x.lines && id == x.id;
        }
        posting(int file_id, int lines, int id): file_id(file_id), lines(lines), id(id){}
        posting(){}
};

class data
{
    public:
        int file_id, lines, id;
        string word;
        data(int file_id, int lines, int id, string word):file_id(file_id), lines(lines), id(id), word(word){}
        data(){}
};

class Search_engine
{
    private:
        std::map<int, string> int_to_file;
        std::vector<std::list<posting> > word_list;
    public:
        void build_list();
        std::map<string, int> word_to_int;
        void search(string target);
};

#endif