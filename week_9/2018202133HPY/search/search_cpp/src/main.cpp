#include <exception>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <readline/readline.h>

#include "Database.hpp"
#include "Engine.hpp"
#include "Jieba.hpp"

int main(void)
{
    DataBase db;
    SearchEngine engine { db };

    std::string line;

    try {
        while (true) {
            char* line_ch = readline(">>> ");

            if (line_ch == nullptr) {
                throw std::logic_error("");
            }

            line = line_ch;

            std::vector<std::string> splited;
            boost::algorithm::split(splited, line, boost::is_any_of(" \t"), boost::token_compress_on);

            if (splited[0] == "save") {
                std::ofstream os(splited[1]);
                boost::archive::binary_oarchive ar(os);
                ar << db;
                os.close();
            } else if (splited[0] == "load") {
                std::ifstream is(splited[1]);
                boost::archive::binary_iarchive ar(is);
                ar >> db;
                is.close();
            } else if (splited[0] == "train") {
                std::ifstream fin(splited[1]);

                std::string filename;

                int train_file_num = 0;

                while (std::getline(fin, filename)) {
                    engine.train(filename);

                    std::cout << (++train_file_num) << ' ' << filename << std::endl;
                }
                fin.close();
            } else if (splited[0] == "query") {
                engine.query(splited[1]);
            } else if (splited[0] == "help") {
                std::cout <<
                    R"RAW(Commands:
help              Display this text
save  filename    Save database to file
load  filename    Load database from file
train listfile    Train database
query text        Query)RAW"
                          << std::endl;
            } else {
                std::cout << "Unknown command: " << splited[0] << std::endl;
            }
        }
    } catch (std::logic_error e) {
        std::cout << "Exiting..." << std::endl;
    }
}
