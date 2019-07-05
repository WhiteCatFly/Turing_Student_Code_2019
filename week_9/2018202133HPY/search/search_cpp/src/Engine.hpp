#ifndef _COWR_SEARCHENGINE

#define _COWR_SEARCHENGINE

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#include "Database.hpp"
#include "HTMLParser/Parser.hpp"

class SearchEngine {
    DataBase& db;

public:
    SearchEngine(DataBase& db)
        : db(db)
    {
    }

    void train(std::string filename)
    {
        cowr::HTMLParser parser { std::filesystem::path { filename } };
        auto dom = parser.parse();
        auto bodies = dom->$("body");

        if (bodies.size()) {
            auto body = bodies.front();
            auto text = body->innerText();
            db.add(filename, text);
        }
    }

    void query(std::string sentense)
    {
        Jieba jieba;

        auto words = jieba.cut(sentense);

        std::map<int, double> score;

        for (auto& [word, flag] : words) {
            double idf = db.query_idf(word);
            auto tfs = db.query_tf(word);

            for (auto& [doc, tf] : tfs) {
                score[doc] += tf * idf;
            }
        }

        int num = 0;
        for (auto [id, qaq] : score) {
            std::cout << id << '\t' << qaq << '\t' << db.id2doc[id] << std::endl;

            if ((++num) == 20)
                break;
        }
    }
};

#endif
