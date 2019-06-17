#include "textquery.h"

bool judge_meaning(std::string word)  //判断是否为停用词
{
    std::set<std::string> forbidden_list = {"1","2","3","4","5","6","7","8","9","，","。","年","月","日",". ","&",
    ".",",","、","的","后","共","名","其中","所","了","由","为","在","与","上","于","是","等","人","和",";","将",";",":"
    ,"：","a","the","with","an","by","to","of","and","it","about","-","(",")","on","in","we","is","for","!","！"};
    //set<stirng> iterator it;
    for(auto it : forbidden_list)
    {
        if(word.find(it) != std::string::npos)
        {
            return false;
        }

    }
    return true;
}
void textquery::add_new_word(int &file_no, std::string &word)  //map中加入新的词汇
{
    word_in_map.insert(word);
    std::vector<std::vector<int>> new_vector;
    new_vector.push_back(std::vector<int> (2));

    new_vector[0][0] = file_no;
    new_vector[0][1] = 1;

    wordmap.insert(std::map<std::string, std::vector<std::vector<int> >>::value_type(word,new_vector));

    return;
}
void textquery::add_new_file(int &file_no, std::string &word)  //map中的词汇出现在新的文件中
{
    int size = wordmap[word].size();
    wordmap[word].push_back(std::vector<int> (2));
                    
    wordmap[word][size][0] = file_no;
    wordmap[word][size][1] = 1;
}
textquery::textquery(int num)
{
    file_num = num;
    
    std::string word;
    std::string number;
    std::string filename = "_cut.txt";

    for(int i = 1; i <= num; i++ )
    {
        std::stringstream ss;
        ss << i;
        ss >> number ;
        //cout << number << endl;

        filename = "/home/halcyon/桌面/text/" + number + filename;
        
        fin.open(filename);
        if(!fin)
            cout << "cannot open the file" << endl;
        filename = "_cut.txt";
        while(fin >> word)
        {
            if(judge_meaning(word) == false)
                continue;
            if(word_in_map.find(word) == word_in_map.end())
            {
                //word_in_map.insert(word);
                add_new_word(i , word);
            }
            else
            {
                if(wordmap[word][(wordmap[word].size() - 1)][0] == i)
                {
                    wordmap[word][wordmap[word].size() - 1 ][1] ++;
                }   
                else
                {
                    add_new_file(i, word);
                }
                     
            }
        
        }

        fin.close();
        
    }    // map complete

    std::ofstream fout("map.txt");
    for(auto it : word_in_map)
    {
        fout << it << endl;
        for(int i = 0; i < wordmap[it].size(); i ++)
        {
            fout << wordmap[it][i][0] << " , " << wordmap[it][i][1] << endl;
        }
    }
    fout.close();

}