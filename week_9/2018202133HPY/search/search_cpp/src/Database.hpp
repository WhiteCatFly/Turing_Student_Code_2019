#ifndef _COWR_1_DATABASE

#define _COWR_1_DATABASE

#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/algorithm/string.hpp>

#include "Jieba.hpp"

class Word {
private:
    friend class boost::serialization::access;

    struct WordPos {
        friend class boost::serialization::access;

        int line_num;
        int word_num;

        WordPos() = default;
        WordPos(int linum, int wordnum)
            : line_num(linum)
            , word_num(wordnum)
        {
        }

        template <class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& line_num;
            ar& word_num;
        }

        bool operator<(const WordPos& r) const
        {
            if (line_num != r.line_num)
                return line_num < r.line_num;
            else
                return word_num < r.word_num;
        }
    };

    int num;
    std::string word;
    std::map<int, std::set<WordPos>> pos;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& num;
        ar& word;
        ar& pos;
    }

public:
    Word() = default;
    Word(std::string word)
        : word(word)
    {
    }

    std::string getWord() const
    {
        return word;
    }

    void setWord(std::string word)
    {
        this->word = word;
    }

    bool add(int doc_id, int linum, int wordnum)
    {
        if (pos[doc_id].insert(WordPos(linum, wordnum)).second) {
            num++;
            return true;
        } else
            return false;
    }

    int getNum() const
    {
        return num;
    }

    decltype(auto) size()
    {
        return pos.size();
    }

    decltype(auto) begin()
    {
        return pos.begin();
    }

    decltype(auto) end()
    {
        return pos.end();
    }

    decltype(auto) count(int index) const
    {
        return pos.count(index);
    }

    decltype(auto) operator[](int index)
    {
        return pos[index];
    }
};

class DataBase {
private:
    friend class boost::serialization::access;
    friend class SearchEngine;

    int doc_num;
    int word_num;

    std::map<int, std::string> id2doc;

    std::map<std::string, int> doc_map, word_map;
    std::map<int, std::vector<std::vector<int>>> doc_cut;
    std::map<int, int> doc_word_num;
    std::map<int, Word> words;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& doc_num;
        ar& word_num;

        ar& doc_map;
        ar& word_map;

        ar& doc_cut;
        ar& doc_word_num;

        ar& words;

        build_rev();
    }

public:
    DataBase()
    {
        doc_num = 0;
        word_num = 0;
    }

    void add(std::string doc_name, std::string passage)
    {
        Jieba jieba;
        jieba.initialize();

        if (doc_map.count(doc_name)) {
            throw std::invalid_argument("Invalid doc name");
        }

        int doc_id = doc_num++;
        doc_map[doc_name] = doc_id;

        std::vector<std::vector<int>> sentenses_in_doc;

        std::vector<std::string> sentenses;
        boost::algorithm::split(sentenses, passage, boost::is_any_of("\n"), boost::token_compress_on);

        int linum = 1, wordnum = 0;
        for (auto& sentense : sentenses) {
            auto result = jieba.cut(sentense);
            std::vector<int> words_in_sentenses;

            int colum = 1;

            for (auto& [word, flag] : result) {
                if (flag == "x")
                    continue;

                int word_id;

                if (word_map.count(word))
                    word_id = word_map[word];
                else {
                    word_map[word] = word_id = word_num++;
                    words[word_id] = Word(word);
                }

                words_in_sentenses.push_back(word_id);
                words[word_id].add(doc_id, linum, colum);

                colum++;
                wordnum++;
            }

            sentenses_in_doc.push_back(words_in_sentenses);
            linum++;
        }

        doc_word_num[doc_id] = word_num;
        doc_cut[doc_id] = std::move(sentenses_in_doc);
    }

    double query_idf(std::string word)
    {
        if (!word_map.count(word))
            return 1;

        int word_id = word_map[word];
        Word& word_obj = words[word_id];

        return log((double)doc_num / (1.0 + word_obj.size()));
    }

    std::map<int, double> query_tf(std::string word)
    {
        std::map<int, double> ret;
        if (!word_map.count(word))
            return ret;

        int word_id = word_map[word];
        Word& word_obj = words[word_id];

        for (auto& [doc_id, word_pos_ar] : word_obj) {
            ret[doc_id] = (double)word_pos_ar.size() / doc_word_num[doc_id];
        }

        return ret;
    }

    void build_rev()
    {
        for (auto& [doc, id] : doc_map) {
            id2doc[id] = doc;
        }
    }
};

#endif
