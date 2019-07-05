#include "Score.h"


bool CmpByValue(std::pair<int, double>& left, std::pair<int, double>& right){
    return (left.second > right.second);
}

void Score::add_score(int number, double score){
    people_score.insert(std::make_pair(number, score));
}

QueryResult Score::rank(){
    std::vector<std::pair<int, double>> temp_vector(people_score.begin(), people_score.end());
    
    sort(temp_vector.begin(), temp_vector.end(), CmpByValue);
    std::vector<int> result_vector;
      
    for(int i = 0; i < temp_vector.size(); i ++){
        if(temp_vector[i].second == 0) break;
        result_vector.push_back(temp_vector[i].first);
    }
    QueryResult result(result_vector);

    return result;
}
