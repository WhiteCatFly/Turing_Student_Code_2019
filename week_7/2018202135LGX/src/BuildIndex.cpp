#include"BuildIndex.h"

bool cmp(const Sites &A, const Sites &B)
{
  return (A.tf_idf > B.tf_idf);
}

// BuildIndex::BuildIndex(const std::string &str){
//   system("touch result_1");
//   system("python segmentator.py");
//   std::ifstream temp_fin("result_1");
//   std::string temp_str;
//   int m = 0;
//   bool Whether_a_Chinese_Character;
//   int the_number_of_lines = 0;
//   std::map<std::string, double> tf;
//   while(getline(temp_fin, temp_str)){
//     for(int i = 0; i < temp_str.length(); i ++){
//       if((temp_str[i]& 0X80) !=0) Whether_a_Chinese_Character = true;
//     }
//       if(Whether_a_Chinese_Character){
//         the_number_of_lines ++;
//         if(tf.find(temp_str) == tf.end()){
//           tf.insert(std::make_pair(temp_str, 1));
//         }
//         else{
//           tf.find(temp_str)->second ++;
//         }
//         if(SearchTable.find(temp_str) == SearchTable.end()){
//           std::vector<Sites> temp_vector;
//           Sites temp(str);
//           std::set<std::string> temp_set;
//           temp_set.insert(str);
//           temp_vector.push_back(temp);
//           SearchTable.insert(std::make_pair(temp_str, temp_vector));
//           SearchTable_No_.insert(std::make_pair(temp_str, temp_set));
//         }
//         else{
//           if(SearchTable_No_.find(temp_str)->second.count(str) == 0){
//             SearchTable.find(temp_str)->second.push_back(str);
//             SearchTable_No_.find(temp_str)->second.insert(str);
//           }
//         }
//       }
//       Whether_a_Chinese_Character = false;
//     }
//     for(auto point = SearchTable.begin(); point != SearchTable.end(); point ++){
//       double tf_ = tf[point->first] / the_number_of_lines;
//       if(!point->second.back().set_or_not){
//         point->second.back().set_or_not = true;
//         point->second.back().tf = tf_;
//       }
//     }
//     temp_fin.close();
//     system("rm result_1");
// }

void BuildIndex::Add(const std::string &url){
  system("touch result_1");
  system("python segmentator.py");
  std::ifstream temp_fin("result_1");
  std::string temp_str;
  int m = 0;
  bool Whether_a_Chinese_Character;
  int the_number_of_lines = 0;
  std::map<std::string, double> tf;
  while (getline(temp_fin, temp_str))
  {
    for (int i = 0; i < temp_str.length(); i++)
    {
      if ((temp_str[i] & 0X80) != 0)
        Whether_a_Chinese_Character = true;
    }
    if (Whether_a_Chinese_Character)
    {
      the_number_of_lines++;
      if (tf.find(temp_str) == tf.end())
      {
        tf.insert(std::make_pair(temp_str, 1));
      }
      else
      {
        tf.find(temp_str)->second++;
      }
      if (SearchTable.find(temp_str) == SearchTable.end())
      {
        std::vector<Sites> temp_vector;
        Sites temp(url);
        std::set<std::string> temp_set;
        temp_set.insert(url);
        temp_vector.push_back(temp);
        SearchTable.insert(std::make_pair(temp_str, temp_vector));
        SearchTable_No_.insert(std::make_pair(temp_str, temp_set));
      }
      else
      {
        if (SearchTable_No_.find(temp_str)->second.count(url) == 0)
        {
          SearchTable.find(temp_str)->second.push_back(url);
          SearchTable_No_.find(temp_str)->second.insert(url);
        }
      }
    }
    Whether_a_Chinese_Character = false;
  }
  for (auto point = SearchTable.begin(); point != SearchTable.end(); point++)
  {
    double tf_ = tf[point->first] / the_number_of_lines;
    if (!point->second.back().set_or_not)
    {
      point->second.back().set_or_not = true;
      point->second.back().tf = tf_;
    }
  }
  temp_fin.close();
  system("rm result_1");
}

void BuildIndex::GetIdf(){
  for(auto point = SearchTable.begin(); point != SearchTable.end(); point ++){
    double idf_ = log10(the_number_of_sites /double(1 + point->second.size()));
    for(int i = 0; i < point->second.size(); i ++){
      point->second[i].tf_idf = idf_ * point->second[i].tf;
    }
  }
}

void BuildIndex::Rank(){
  for(auto point = SearchTable.begin(); point != SearchTable.end(); point ++){
    std::sort(point->second.begin(), point->second.end(), cmp);
  }
}

void BuildIndex::Answer(const std::string &query){
  for(int i = 0; i < SearchTable[query].size(); i ++){
    std::cout << SearchTable[query][i].url << std::endl;
  }
}
