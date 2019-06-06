#include "queryresult.h"

void run_query(int &file_num)
{
    std::stringstream ss;
    std::string line;    //要搜索的单个或多个词
    std::string word;

    double time;
    clock_t start,finish;

    start = clock();

    textquery tq(file_num); queryresult rq(tq);
    cout << "the map is ready" << endl;

    finish = clock();
    time =  (double)(finish - start) / CLOCKS_PER_SEC; 
    cout << time << " seconds used" << endl;
    cout << "--------------------------------------" << endl;

    cout << "please enter the words you want to search" << endl;
    getline(cin,line);

    while(getline(cin,line))
    {
        //cout << line << endl;
        if(line == "end")
            break;

        std::vector <std::string> words;
        ss << line;
        while(ss >> word)
        {
            words.push_back(word);
            //cout << word << endl;
        }
        start = clock();

        rq.get_result(words);

        finish = clock();
        time =  (double)(finish - start) / CLOCKS_PER_SEC; 

        cout << "used time : " << time << " seconds" << endl;
        ss.clear();

        cout << "--------------------------------------" << endl;
        cout << "(please enter 'end' if you want to end the process)" << endl;
    }
    
}
bool cmp(std::pair <int, double> a, std::pair<int, double> b)
{
    return a.second > b.second;
}
int int_cmp(int a, int b)
{
    if(a > b)
    return b;

    return a;
}
queryresult::queryresult(textquery &tq)
{
    num = tq.get_num();
    wordmap = tq.get_map();
    word_in_map = tq.get_words();
}
void queryresult::get_result(std::vector<std::string> &words)
{
    
    for(int i = 1; i <= num; i ++)
    {
        file_score.push_back(std::pair<int, double>(i,0));
    }

    for(auto it : words)
    {
        if(word_in_map.find(it) != word_in_map.end())
        {
            for(int i = 0;i < wordmap[it].size(); i ++)
            {
                double tf  = 1 + log10(wordmap[it][i][1]);  //文件编号为[i][0]
                double idf = log10((num * 1.0)/wordmap[it].size());

                file_score[wordmap[it][i][0] - 1].second += tf*idf; 
            }

        }

    }

    sort(file_score.begin(),file_score.end(),cmp);

    file_available = 0;  //记录tf*idf的值不为0的文件个数
    for(int i = 1; i <= num; i ++)
    {
        //cout << file_score[i-1].first << " , " << file_score[i-1].second << endl;
        if(file_score[i - 1].second == 0)
            break;
        
        else
            file_available ++;
        
    }
    //cout << file_available << endl;
    //cout << file_number << endl;
    print_result();
    
    return;
}
void queryresult::print_result()
{
    int show = int_cmp(file_available, 10);
    
    if(show == 0)
    {
        cout << "no file found" << endl;
        return;
    }
    else
    {
         cout << "the result is :" << endl;
        for(int i = 1; i <= show; i ++)
        {
            cout << "rank " << i << " ： text number " << file_score[i - 1].first << endl;
        }

    }
    
    cout << "These are all the results." << endl;

    return;
}