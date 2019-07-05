#include "Base.h"

void noresult(){
    std::cout << "No result!" << std::endl;
}

bool ifempty(std::vector<int>&vec){
    if(vec.empty()) { return true;}
    return false;
}

std::pair<int, int> make_range(int height)
{
    return std::make_pair(height / 10 * 10, height / 10 * 10 + 9);
}

bool string_to_bool(const std::string &str)
{
    if (str == "1")
        return true;
    return false;
}
std::string Base::get_last_name(std::string &name){
    std::vector<std::string> words;
    std::string last_name;

    jieba.CutAll(name, words);

    last_name = words[0];

    return last_name;
}
std::vector<std::string> Base::get_sub_names(std::string &last_name, std::string &first_name, int &size){
    
    std::vector<std::string> sub_names;
    std::string sub_name;
		for(int i = 0;i < size;i++)
		{
			//cout << i << endl;
			//cout << first_name.substr(i*3,i*3+3) << endl;
			//cout << first_name << endl;
			sub_name = last_name + first_name.substr(i*3,i*3+3);
			sub_names.push_back(sub_name);
			//cout << sub_name << endl;
		}
    return sub_names;
	
}
void Base::construct_map(Statistics &statistics, Person &per, int &i, std::string &detail)
{
    //我要死了
    std::string name = per.name;
    std::string last_name = get_last_name(name);  //std::cout << last_name << std::endl;
    string_replace(name,last_name,"");
    std::string first_name = name;     //std::cout << first_name << std::endl;
    
    int sub_name_size = first_name.size()/3;    //std::cout << sub_name_size << std::endl; 

    std::vector<std::string> sub_names = get_sub_names(last_name,first_name,sub_name_size);
    
    if (sub_name_map.find(last_name) == sub_name_map.end()) //第一次出现这个姓
    {
        for(int j = 0; j < sub_name_size; j ++ ){       //对每一个subname进行枚举
            std::map<std::string,std::vector<int>> sub_map;
            std::vector<int> sub_map_id;

            sub_map_id.push_back(statistics.positions[i]);
            //std::cout << statistics.positions[i] << " " << sub_names[j] << std::endl;
            sub_map.insert(std::make_pair(sub_names[j],sub_map_id));

            sub_name_map.insert(std::make_pair(last_name,sub_map));
        }
    }
    else{             //已经出现过这个姓
        for(int j = 0; j < sub_name_size; j ++ ){           //对sub_names进行枚举
            if(sub_name_map[last_name].find(sub_names[j]) == sub_name_map[last_name].end()){   //新的sub_name
                //std::map<std::string,std::vector<int>> sub_map;
                std::vector<int> sub_map_id;

                sub_map_id.push_back(statistics.positions[i]);
                //std::cout << statistics.positions[i] << " " << sub_names[j] << std::endl;
                //sub_map.insert(std::make_pair(sub_names[j],sub_map_id));

                sub_name_map[last_name].insert(std::make_pair(sub_names[j],sub_map_id));
            }
            else{
                sub_name_map[last_name][sub_names[j]].push_back(statistics.positions[i]);
            }
        }
    }
    
    if (id_map.find(per.id) == id_map.end())
    {
        std::list<int> temp_list;
        temp_list.push_back(statistics.positions[i]);
        id_map.insert(std::make_pair(per.id, temp_list));
    }
    else
        id_map[per.id].push_back(statistics.positions[i]);

    if (name_map.find(per.name) == name_map.end())
    {
        std::list<int> temp_list;
        temp_list.push_back(statistics.positions[i]);
        name_map.insert(std::make_pair(per.name, temp_list));
    }
    else
        name_map[per.name].push_back(statistics.positions[i]);

    if (gender_map.find(per.gender) == gender_map.end())
    {
        std::list<int> temp_list;
        temp_list.push_back(statistics.positions[i]);
        gender_map.insert(std::make_pair(per.gender, temp_list));
    }
    else
        gender_map[per.gender].push_back(statistics.positions[i]);

    for (int j = 0; j <= 32; j++)
    {

        if (per.birthplace.find(province[j]) != per.birthplace.npos)
        {
            if (birthplace_map.find(province[j]) == birthplace_map.end())
            {
                std::list<int> temp_list;
                temp_list.push_back(statistics.positions[i]);
                birthplace_map.insert(std::make_pair(per.birthplace, temp_list));
            }
            else
                birthplace_map[province[j]].push_back(statistics.positions[i]);
            break;
        }
    }
    if (birthday_map.find(per.birthday) == birthday_map.end())
    {
        std::list<int> temp_date;
        temp_date.push_back(statistics.positions[i]);
        birthday_map.insert(std::make_pair(per.birthday, temp_date));
    }
    else
        birthday_map[per.birthday].push_back(statistics.positions[i]);

    int year_1 = per.birthday.GetYear();
    if (birthyear_map.find(year_1) == birthyear_map.end())
    {
        std::list<int> temp_year;
        temp_year.push_back(statistics.positions[i]);
        birthyear_map.insert(std::make_pair(year_1, temp_year));
    }
    else
        birthyear_map[year_1].push_back(statistics.positions[i]);

    if (lostday_map.find(per.lostday) == lostday_map.end())
    {
        std::list<int> temp_date;
        temp_date.push_back(statistics.positions[i]);
        lostday_map.insert(std::make_pair(per.lostday, temp_date));
    }
    else
        lostday_map[per.lostday].push_back(statistics.positions[i]);

    Date temp_date_2 = per.lostday;
    int year_2 = temp_date_2.GetYear();
    if (lostyear_map.find(year_2) == lostyear_map.end())
    {
        std::list<int> temp_year;
        temp_year.push_back(statistics.positions[i]);
        lostyear_map.insert(std::make_pair(year_2, temp_year));
    }
    else
        lostyear_map[year_2].push_back(statistics.positions[i]);

    if (height_map.find(per.height) == height_map.end())
    {
        std::list<int> temp_list;
        temp_list.push_back(statistics.positions[i]);
        height_map.insert(std::make_pair(per.height, temp_list));
    }
    else
        height_map[per.height].push_back(statistics.positions[i]);

    if (heightrange_map.find(make_range(per.height)) == heightrange_map.end())
    {
        std::pair<int, int> temp_pair = make_range(per.height);
        std::list<int> temp_list;
        temp_list.push_back(statistics.positions[i]);
        heightrange_map.insert(std::make_pair(temp_pair, temp_list));
    }
    else
        heightrange_map[make_range(per.height)].push_back(statistics.positions[i]);

    for (int j = 0; j <= 32; j++)
    {
        if (per.lostplace.find(province[j]) != per.lostplace.npos)
        {
            if (lostplace_map.find(province[j]) == lostplace_map.end())
            {
                std::list<int> temp_list;
                temp_list.push_back(statistics.positions[i]);
                lostplace_map.insert(std::make_pair(province[j], temp_list));
            }
            else
                lostplace_map[province[j]].push_back(statistics.positions[i]);
        }
    }

    for (int j = 0; j <= 22; j++)
    {
        if (detail.find(description_base[j]) == detail.npos)
            per.push_descriptions(0);
        else
        {
            per.push_descriptions(1);
            if (description_map.find(description_base[j]) == description_map.end())
            {
                std::list<int> temp_list;
                temp_list.push_back(statistics.positions[i]);
                description_map.insert(std::make_pair(description_base[j], temp_list));
            }
            else
            {
                description_map[description_base[j]].push_back(statistics.positions[i]);
            }
        }
    }

    for (int j = 0; j < per.Segmentated_descriptions.size(); j++)
    {
        if (stopwords_base.find(per.Segmentated_descriptions[j]) != stopwords_base.end())
            continue;
        if (segment_map.find(per.Segmentated_descriptions[j]) == segment_map.end())
        {
            std::vector<std::pair<int, int>> temp_vector;
            temp_vector.push_back(std::make_pair(statistics.positions[i], 1));
            segment_map.insert(std::make_pair(per.Segmentated_descriptions[j], temp_vector));
        }
        else
        {
            if (segment_map[per.Segmentated_descriptions[j]][segment_map[per.Segmentated_descriptions[j]].size() - 1].first == statistics.positions[i])
            {
                segment_map[per.Segmentated_descriptions[j]][segment_map[per.Segmentated_descriptions[j]].size() - 1].second++;
            }
            else
            {
                segment_map[per.Segmentated_descriptions[j]].push_back(std::make_pair(statistics.positions[i], 1));
            }
        }
    }
}
void Base::Modify(std::vector<std::string>&terms){
    for(int i = 0; i < terms.size(); i ++){
        if(synonyms.find(terms[i]) != synonyms.end()){
            terms[i] = synonyms[terms[i]];
        }
    }
}

Base::Base() : jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH)
{
    description_base = {"高", "矮", "胖", "瘦", "疤", "痣", "聋", "哑", "盲", "纹身", "胎记", "残疾", "痴呆", "长发", "短发", "智力残疾", "方脸", "圆脸", "瓜子脸", "大眼睛", "小眼睛", "单眼皮", "双眼皮"};
    description_synonym = {"弱智", "智障", "瞎", "长头发", "短头发"};
    province = {"北京", "天津", "上海", "重庆", "河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南", "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙", "广西", "宁夏", "新疆", "香港", "澳门"}; // 0-32

    Statistics statistics;
    std::string Stopwords_ = "stopwords";
    std::ifstream sto(Stopwords_);
    std::string word;
    while (getline(sto, word))
    {
        stopwords_base.insert(word);
    }

    std::ifstream syn("synonyms");
    std::string line;
    while(getline(syn, line)){
        std::stringstream ss(line);
        std::string word_1, word_2;
        ss >> word_1 >> word_2;
        synonyms.insert(std::make_pair(word_2, word_1));
    }


    double All_documents = 0;

    for (int i = 0; i < statistics.positions.size(); i++)
    {
        //std::cout << statistics.positions[i] << std::endl;
        int begin = statistics.Content.find("#" + std::to_string(statistics.positions[i]) + "#");
        int end = statistics.Content.find("#" + std::to_string(statistics.positions[i]) + "#", begin + 1);
        // std::cout << i << std::endl;
        // std::cout << begin << std::endl;
        // std::cout << end << std::endl;
        //std::cout << statistics.Content << std::endl;
        std::string entry = statistics.Content.substr(begin, end - begin);
        std::istringstream iss(entry);

        Person per;
        per.index = statistics.positions[i];
        ParseFile(iss, per);
        std::string detail = "";

        detail = per.detailed_description;
        string_replace(detail, "身高", "");

        jieba.CutAll(per.detailed_description, per.Segmentated_descriptions);
        
        All_documents += per.Segmentated_descriptions.size();
        Modify(per.Segmentated_descriptions);

        construct_map(statistics, per, i, detail);

        if (detail.find(description_synonym[0]) != detail.npos)
            per.set_descriptions(15, 1);
        if (detail.find(description_synonym[1]) != detail.npos)
            per.set_descriptions(15, 1);
        if (detail.find(description_synonym[2]) != detail.npos)
            per.set_descriptions(8, 1);
        if (detail.find(description_synonym[3]) != detail.npos)
            per.set_descriptions(13, 1);
        if (detail.find(description_synonym[4]) != detail.npos)
            per.set_descriptions(14, 1);

        People.insert(std::make_pair(statistics.positions[i], per));
    }
    // for(auto it = sub_name_map["张"].begin() ;it != sub_name_map["张"].end();it ++)
    //                {
    //                         std::cout << it->first << std::endl;
    //                }
    Avgdl = All_documents / statistics.positions.size();
}

void Base::ParseFile(std::istringstream &iss, Person &per)
{
    std::string no_use_str;
    std::string id;
    std::string name;
    std::string gender; // 0 for female 1 for male
    std::string birthplace;
    std::string birthday;
    std::string lostday;
    std::string height;
    std::string lostplace;
    std::string description;

    getline(iss, no_use_str);
    getline(iss, id);
    getline(iss, name);
    getline(iss, gender);
    getline(iss, birthplace);
    getline(iss, birthday);
    getline(iss, lostday);
    getline(iss, height);
    getline(iss, lostplace);
    std::string temp_str;
    while(getline(iss,temp_str)){
        description += temp_str;
    }

    string_replace(description, " ", "");

    per.set_id(id);
    per.set_name(name);
    per.set_gender(string_to_bool(gender));
    per.set_birthplace(birthplace);
    per.set_birthday(string_to_date(birthday));
    per.set_lostday(string_to_date(lostday));
    per.set_height(string_to_int(height));
    per.set_lostplace(lostplace);
    per.set_detailed_description(description);
}

QueryResult Base::scoring(Query& query){
    std::vector<int> whole;
   
    QueryResult result;

    if(query.name != ""){  
                      //query不是空的

        std::string name = query.name;        // std::cout << name << std::endl;
        std::string last_name = get_last_name(name);  //std::cout << last_name << std::endl;
        string_replace(name,last_name,"");
        std::string first_name = name;    // std::cout << first_name << std::endl;
    
        int sub_name_size = first_name.size()/3;   // std::cout << sub_name_size << std::endl; 

        std::vector<std::string> sub_names = get_sub_names(last_name,first_name,sub_name_size);

        //std::cout << query.name << "222" << std::endl;
        if(name_map.find(query.name) == name_map.end()){             //不能找到同名的人
            //noresult();
            if(sub_name_map.find(last_name) == sub_name_map.end())  //输入的名字连对应的姓都找不到，没救了
            {
                return result;    //空的，没结果
            }
            else                 //找得到姓
            {
               //std::cout << "possible result :" << std::endl;
               if(sub_name_size == 0)      //只输入一个姓并且找得到
               {
                   for(auto it = sub_name_map[last_name].begin() ;it != sub_name_map[last_name].end();it ++)
                   {
                       //std::cout << it->first << std::endl;
                       for(int j = 0; j < it->second.size(); j++)
                       {
                            int test = 0;
                            for(int r = 0; r < whole.size() ; r ++)
                            {
                               if (whole[r] == it->second[j])
                               test = 1;
                            }  
                            if(test == 0)
                            whole.push_back(it->second[j]);
                       }     
                   }
               }
               else     //输入了一个完整的名字,sub_names里面是query各种情况
               {
                    int test = 0;
                    for(int j = 0; j < sub_name_size; j ++)    //对sub_names进行枚举
                    {
                        if(sub_name_map[last_name].find(sub_names[j]) != sub_name_map[last_name].end())  //找到了sub_names[j]对应的，开始联想
                        {
                            test = 1;
                            for(int k = 0; k < sub_name_map[last_name][sub_names[j]].size(); k ++)
                            {
                                int temp = 0;
                                for(int r = 0; r < whole.size(); r ++)
                                {
                                    if(whole[r] == sub_name_map[last_name][sub_names[j]][k])
                                    temp = 1;
                                }
                                if(temp == 0)
                                whole.push_back(sub_name_map[last_name][sub_names[j]][k]);
                            }         
                        }
                    }
                    if(test == 0){           //联想失败，只有姓符合，把同姓的全部丢进去
                        for(auto it = sub_name_map[last_name].begin() ;it != sub_name_map[last_name].end();it ++)
                        {

                            for(int j = 0; j < it->second.size(); j++)
                            {
                                int test = 0;
                                for(int r = 0; r < whole.size() ; r ++)
                                {
                                    if (whole[r] == it->second[j])
                                    test = 1;
                                }  
                                if(test == 0)
                                whole.push_back(it->second[j]);  
                            }     
                        }
                    }
                }
            }                    
        }
        else            //找得到同名的人
        {
            std::vector<int> newvec(name_map[query.name].begin(), name_map[query.name].end());
            whole = newvec;
            if(ifempty(whole)) return result;
        }
       
    }
    else{             //query是空的,whole赋全值
        for(auto i = People.begin();  i!= People.end();  i ++){
            whole.push_back(i->first);
            //std::cout << i->first << std::endl;
         }
    }

    // for(int k = 0; k < whole.size(); k ++){
    //     std::cout << whole[k] << std::endl;
    // }
    if(query.id != ""){
        if(id_map.find(query.id) == id_map.end())
        {
            //noresult();
            return result;
        }
        whole = {id_map[query.id].front()};
    }
    if(query.gender != -1){
        std::vector<int> temp_vec(gender_map[query.gender].begin(), gender_map[query.gender].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole)) return result;
    }
    if(query.birthplace != ""){
        if(birthplace_map.find(query.birthplace) == birthplace_map.end()){
            //noresult();
            return result;
        }
        std::vector<int> temp_vec(birthplace_map[query.birthplace].begin(), birthplace_map[query.birthplace].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole))
            return result;
    }
    if(query.min_height != -1){
        std::pair<int, int> temp_pair = std::make_pair(query.min_height, query.max_height);
        if(heightrange_map.find(temp_pair) == heightrange_map.end()){
            //noresult();
            return result;
        }
        std::vector<int> temp_vec(heightrange_map[temp_pair].begin(), heightrange_map[temp_pair].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole))
            return result;
    }
    if(query.lostplace != ""){
        //std::cout << query.lostplace << std::endl;
        if(lostplace_map.find(query.lostplace) == lostplace_map.end()){
            //noresult();
            return result;
        }
        std::vector<int> temp_vec(lostplace_map[query.lostplace].begin(), lostplace_map[query.lostplace].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole))
            return result;
    }
    for(int i = 0; i < query.descriptions.size(); i ++){
        if(query.descriptions[i]){
            if(description_map.find(description_base[i]) == description_map.end()){
                continue;
            }
            std::vector<int> temp_vec(description_map[description_base[i]].begin(), description_map[description_base[i]].end());
            std::vector<int> newvec;
            std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
            whole = newvec;
        }
    }
    if (query.birthyear != -1)
    {
        if (birthyear_map.find(query.birthyear) == birthyear_map.end())
        {
            //noresult();
            return result;
        }
        std::vector<int> temp_vec(birthyear_map[query.birthyear].begin(), birthyear_map[query.birthyear].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole))
            return result;
    }
    if (query.lostyear != -1)
    {
        if (lostyear_map.find(query.lostyear) == lostyear_map.end())
        {
            //noresult();
            return result;
        }
        std::vector<int> temp_vec(lostyear_map[query.lostyear].begin(), lostyear_map[query.lostyear].end());
        std::vector<int> newvec;
        std::set_intersection(whole.begin(), whole.end(), temp_vec.begin(), temp_vec.end(), std::back_inserter(newvec));
        whole = newvec;
        if (ifempty(whole))
            return result;
    }

    if(query.query_string == ""){

        result.set_result(whole);
        return result;
    }

    std::string temp_str = query.query_string;
    std::vector<std::string> terms;
    jieba.CutAll(query.query_string, terms);
    Modify(terms);
    Score score;
    double k1 = 1;
    double b = 0.75;
    for (int j = 0; j < whole.size(); j ++)  // using BM25
    {
        double score_ = 0;
        for (int i = 0; i < terms.size(); i++)
        {
            int judge = 0;
            for(int l = 0; l < People[whole[j]].Segmentated_descriptions.size(); l ++){
                if (terms[i] == People[whole[j]].Segmentated_descriptions[l])
                    judge++;
            }
            if(judge == 0) continue;
            double m;
            double idf = log10((whole.size() - segment_map[terms[i]].size() + 0.5) / segment_map[terms[i]].size() + 0.5);
            int k;
            for (k = 0; k < segment_map[terms[i]].size(); k++)
            {
                if (segment_map[terms[i]][k].first == whole[j])
                    break;
            }
            m = segment_map[terms[i]][k].second * (k1 + 1) / (segment_map[terms[i]][k].second + k1 * (1 - b + b * People[whole[j]].Segmentated_descriptions.size() / Avgdl));
            score_ += idf * m;
        }
        score.add_score(whole[j], score_);
    }
    
    result = score.rank();
    return result;
}

Person Base::operator[](int a){
    return People[a];
}

// those functions below are for debugging
void Base::test_gender(bool gender){
    for(auto it = gender_map[gender].begin(); it != gender_map[gender].end(); it ++){
        People[*it].showall();
    }
}

void Base::test_province(const std::string&place){
    for(auto it = lostplace_map[place].begin(); it != lostplace_map[place].end(); it ++){
        People[*it].showall();
    }
}

void Base::test_name(const std::string&name){
    for(auto it = name_map[name].begin(); it != name_map[name].end(); it ++){
        People[*it].showall();
    }
}

void Base::test_show_lostplace_map(){
    for(auto it = lostplace_map.begin(); it != lostplace_map.end(); it++){
        std::cout  << it->first << std::endl;
    }
}

void Base::test_description_map(const std::string&character){
        for(auto it = description_map[character].begin(); it != description_map[character].end(); it ++){
        People[*it].showall();
    }
}

void Base::test_show_description_map(){
    for(auto it = description_map.begin(); it != description_map.end(); it++){
        std::cout  << it->first << std::endl;
    }
}

void Base::test_lostday_map(int year, int month, int day){
    Date temp(year, month, day);
    for(auto it = lostday_map[temp].begin(); it != lostday_map[temp].end(); it ++){
        People[*it].showall();
    }
}

void Base::test_lostyear_map(int year){
    for(auto it = lostyear_map[year].begin(); it != lostyear_map[year].end(); it++){
        People[*it].showall();
    }
}

void Base::test_show_segment(){
    for(auto i = People.begin(); i != People.end(); i ++){
        for(int j = 0; j < i->second.Segmentated_descriptions.size(); j ++){
            std::cout << i->second.Segmentated_descriptions[j] << " ";
        }
        std::cout << std::endl;
    }
}

void Base::test_show_search_for_segment(const std::string& term){
    if(segment_map.find(term) == segment_map.end()){
        std::cout << "No result!" << std::endl;
        return;
    }
    for(int i = 0; i < segment_map[term].size(); i ++){
        People[segment_map[term][i].first].showall();
    }
}