#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>

#include "search_engine.h"

using std::string;
using std::cout;
using std::endl;

std::map<int, int> lines_of_file, files_have_word;
std::map<int, std::map<int, int> > num, word_appear_in_file;
std::vector<string> int_to_word;
std::vector<int> Result;
std::vector<int> word_num;
std::map<int, double> sum;
int files_num;

bool cmp_of_Result(const int &a, const int &b)
{
    return sum[a] > sum[b];
}

void Search_engine::build_list()
{
    std::list<posting> Empty;
    Empty.clear();
    std::ifstream fin;
    fin.open("after_seperation.txt");
    string one_line, one_word;
    getline(fin, one_line);
    int num_of_files = 0, num_of_words = 0;
    word_list.push_back(Empty);
    int_to_word.push_back("0");
    word_num.push_back(0);
    int place, lines;
    while(getline(fin, one_line))
    {
        if(one_line.find("belong   to   ") == 0)
        {
            string name;
            for (int i = strlen("belong   to   "); i < one_line.length(); i++)
            {
                if(one_line[i] != ' ')
                name += one_line[i];
            }
            lines_of_file[num_of_files] = lines;
            word_num.push_back(0);
            num_of_files++;
            int_to_file[num_of_files] = name;
            lines = 0;
            continue;
        }
        std::istringstream putin(one_line);
        place = 0; lines++;
        while(putin >> one_word)
        {
            place ++;
            word_num[num_of_files]++;
            if (one_word[0] >= 0)
            {
                continue;
            }
            if (word_to_int[one_word] == 0)
            {
                num_of_words++;
                word_to_int[one_word] = num_of_words;
                int_to_word.push_back(one_word);
                word_list.push_back(Empty);
            }
            std::list<posting> &now = word_list[word_to_int[one_word]];
            posting pos;
            pos.file_id = num_of_files;
            pos.id = place;
            pos.lines = lines;
            pos.word_id = word_to_int[one_word];
            now.push_back(pos);
        }
    }
    files_num = num_of_files;
}

void Search_engine::search(string target)
{
    // cout << target << endl;
    std::ofstream fout;
    fout.open("target.txt");
    fout << target;
    fout.close();
    system("./thulac -seg_only <target.txt >new_target.txt");
    std::ifstream fin;
    fin.open("new_target.txt");
    std::vector<string> word;
    string one_word;
    getline(fin, one_word);
    while(fin >> one_word)
    {
        word.push_back(one_word);
    }
    fin.close();
    int tot = word.size();
    cout << tot << endl;
    for (int i = 0; i < tot; i++)
    if (word_to_int.find(word[i]) == word_to_int.end())
    {
        cout << target << "is not found." << endl;
        return ;
    }
    std::vector<posting> pos[tot];
    fout.open("test.txt");
    word_appear_in_file.clear();
    for (int i = 0; i < tot; i++)
    {
        int id = word_to_int[word[i]];
        fout << word_list[id].size() << " " << id << endl;
        int pre = -1;
        for (auto it = word_list[id].begin(); it != word_list[id].end(); it++)
        {
            fout << (*it).file_id << " " << (*it).lines << " " << (*it).id << endl;
            word_appear_in_file[i][(*it).file_id]++;
            if (pre == -1 || (*it).file_id != pre)
            {
                files_have_word[i]++;
                pre = (*it).file_id;
            }
        }
    }
    fout.close();

    fin.open("test.txt");
    int cnt = 0;
    int nums, word_id;
    while(fin >> nums >> word_id)
    {
        int file_id, lines, id;
        for (int i = 0; i < nums; i++)
        {
            fin >> file_id >> lines >> id;
            pos[cnt].push_back(posting(file_id, lines, id));
        }
        cnt++;
    }
    fin.close();
    int tot_result = 0;
    int id[tot], Place;
    memset(id, 0, sizeof(id));
    while(true)
    {
        posting min = pos[0][id[0]];
        Place = 0;
        for (int i = 1; i < tot; i++)
        {
            if (pos[i][id[i]] < min)
            {
                min = pos[i][id[i]];
                Place = i;
            }
        }
        bool flag = true;
        for (int i = 1; i < tot; i++)
        {
            if (pos[i][id[i]].file_id != pos[i - 1][id[i - 1]].file_id
            || pos[i][id[i]].lines != pos[i - 1][id[i - 1]].lines
            || pos[i][id[i]].id != pos[i - 1][id[i - 1]].id + 1)
            flag = false;
        }
        if (flag == true)
        {
            tot_result++;
            Result.push_back(pos[0][id[0]].file_id);
        }
        if (id[Place] == pos[Place].size() - 1) break;
        id[Place]++;
    }
    if (Result.empty() == true)
    {
        cout << target << "is not found." << endl;
        return ;
    }
    int num_of_files = 1;
    for (int i = 1; i < tot_result; i++)
    {
        if (Result[i] != Result[i - 1])
        {
            num_of_files++;
        }
    }
    cout << tot_result << " times found in " << num_of_files << " files" << endl;
    int result[num_of_files];
    int file_id = 0;
    for (int i = 0; i < tot_result; i++)
    {
        if (Result[i] != Result[i - 1] || i == 0)
        {
            sum[Result[i]] = 0;
            result[file_id++] = Result[i];
            for (int j = 0; j < tot; j++)
            {
                sum[Result[i]] += (1 + std::log((double)word_appear_in_file[j][Result[i]])) * 
                std::log((double)files_num / files_have_word[j]);
            }
        }
    }
    std::sort(result, result + file_id, cmp_of_Result);
    int outnum = (num_of_files >= 5 ? 5 : num_of_files);
    // cout << sum[1] << endl;
    cout << "the first " << outnum << " files are:" << endl;
    for (int i = 0; i < outnum; i++)
    {
        cout << int_to_file[result[i]] << endl;
        // " " << sum[result[i]] << endl;
    }
}