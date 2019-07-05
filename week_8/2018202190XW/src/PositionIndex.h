#ifndef _POSITION_INDEX_H
#define _POSOTION_INDEX_H

typedef std::vector<std::pair<std::string, std::vector<int>>> doc_index;

struct DocMatchInfo {
    std::string doc_name;
    std::vector<std::string> query;
    std::vector<int> match_index;
    double tf_idf;
};

class PositionIndex {
   private:
    int num_of_page;
    std::map<std::string, doc_index> terms;
    std::map<std::string, int> df;
    std::map<std::string, double> idf;
    std::map<std::string, std::vector<std::string>> content;
    std::map<std::string, std::string> title;

   public:
    PositionIndex() {}
    PositionIndex(const std::vector<std::string> &page_names);
    std::pair<int, std::vector<DocMatchInfo>> search(
        std::vector<std::string> query);
    void print(DocMatchInfo doc);
    int size() { return terms.size(); }
};

#endif