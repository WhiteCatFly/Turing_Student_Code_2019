#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "PositionIndex.h"
#include "Utility.h"

using namespace std;

std::vector<std::string> scan_dir(const char *dir_name) {
    std::vector<std::string> ret_val;

    if (NULL == dir_name) {
        cout << " dir_name is null ! " << endl;
        return ret_val;
    }

    struct stat s;
    lstat(dir_name, &s);
    if (!S_ISDIR(s.st_mode)) {
        return ret_val;
    }

    DIR *dir;
    dir = opendir(dir_name);
    if (NULL == dir) {
        return ret_val;
    }

    struct dirent *filename;
    while ((filename = readdir(dir)) != NULL) {
        if (strcmp(filename->d_name, ".") == 0 ||
            strcmp(filename->d_name, "..") == 0)
            continue;

        ret_val.push_back(std::string(dir_name) + filename->d_name);
    }
    return ret_val;
}

main(int argc, char *argv[]) {
    std::vector<std::string> page_names = scan_dir(argv[1]);

    clock_t start_time = clock();
    PositionIndex pi(page_names);
    std::cerr << "total words :" << pi.size() << " load time used : "
              << (double)(clock() - start_time) / CLOCKS_PER_SEC << std::endl;

    std::string query_str;
    while (true) {
        std::cout << "input:";
        std::getline(std::cin, query_str);
        if (query_str == "quit") {
            break;
        }
        // if (!has_chinese(query_str)) {
        //     std::cout << "only support Chinese!" << std::endl;
        //     continue;
        // }
        std::vector<std::string> tmp;
        tmp.push_back(query_str);
        THULAC_result cut_result = split(tmp);
        std::vector<std::string> query;
        for (auto word : cut_result) {
            if (word.first.size()) query.push_back(word.first);
        }

        clock_t start_time = clock();
        std::pair<int, std::vector<DocMatchInfo>> result = pi.search(query);

        std::cout << result.first << " pages searched. "
                  << (double)(clock() - start_time) / CLOCKS_PER_SEC << " s used."
                  << std::endl;
        for (int i = 1; i <= result.second.size(); i++) {
            std::cout << i << ". ";
            pi.print(result.second[i - 1]);
        }
    }

    return 0;
}