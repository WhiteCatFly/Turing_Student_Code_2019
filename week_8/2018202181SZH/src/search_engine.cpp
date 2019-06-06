#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<set>
using namespace std;
struct pairs
{ 
    double scores;
    int index_num;
};
class tfidf{
  private:
          vector<vector<string>>wordsInAllPassage;
          unsigned int num_passages;
          //unsigned int num_words_in;
          vector<vector<int>>data_words;//每个单词在该文章中出现的次数
          vector<string>vocabList;//单词列表
          vector<vector<double>> dataMat;
          vector<int> numOfTerms; // 该篇文章一共多少词 
          
          void init();
          void create_nums();
          void createVocabList();
          inline vector<double> get_words_eachPassage_times(const vector<string> & inputSet);
  public:
          tfidf(vector<vector<string>> & input): wordsInAllPassage(input){
            init();
          }
          void search(string key);

};
void tfidf::init(){
    createVocabList();
    create_nums();
}
void tfidf::create_nums(){
  int cnt = 0;
	for (auto it = wordsInAllPassage.begin(); it != wordsInAllPassage.end(); ++ it)
	{
		cnt ++;
		cout << cnt << "\r";
		std::cout.flush();//缓存区刷新
		dataMat.push_back(get_words_eachPassage_times(*it));
		numOfTerms.push_back(it->size());//存这篇文章内单词的数量
		it->clear();
	}
	cout << endl;
}
inline vector<double> tfidf::get_words_eachPassage_times(const vector<string> & inputSet)
{
	vector<double> returnVec(vocabList.size(), 0);
	for (string word : inputSet)//inputSet是每一个文章的所有词
	{
		size_t idx = find(vocabList.begin(), vocabList.end(), word) - vocabList.begin();
		if (idx == vocabList.size())
			cout << "word: " << word << "not found" << endl;
		else
			returnVec.at(idx) += 1;
	}
	return returnVec;//统计每个词在这个文章里面出现的次数
}

void tfidf::createVocabList()
{
	set<string> vocabListSet;
	for (vector<string> document : wordsInAllPassage)
	{
		for (string word : document)
			vocabListSet.insert(word);
	}
	copy(vocabListSet.begin(), vocabListSet.end(), back_inserter(vocabList));
    //将vocablistset复制到vocablist里面
}
int cmp(const void*a,const void*b){
  if((*(pairs*)a).scores>(*(pairs*)b).scores)return -1;
  if((*(pairs*)a).scores==(*(pairs*)b).scores) return 0;
  return 1;
}
void tfidf::search(string key){
  int idx = -1;
  for(string word : vocabList){
    if(word == key)break;
    
  }
  if(idx == vocabList.size()){
    cout<<"NO such word"<<endl;
    exit(1);
  }
  int sum = wordsInAllPassage.size();
  
  pairs ans[sum];
  for(int i = 0;i < sum;i++){
    ans[i].index_num = i;
    if(dataMat[i][idx] >= 1 ){
      double tf = dataMat[i][idx]/ (double)dataMat[i].size();
      double idf = 1.00;
      ans[i].scores = tf*idf;
    }
  }
  qsort((void*)ans,sum,sizeof(pairs),cmp);
  for(int i = 0;i < 10;i++)cout<<ans[i].index_num+1<<"    得分："<<ans[i].scores<<endl;
    //cout<<ans[i].index_num<<endl;
}

vector<vector<string>> loadData(){
  vector<vector<string>> data;
  
  for(int i = 1;i <= 1261;i++){
    string times = to_string(i);
    string filename  = times + "_cut.txt";
    ifstream in(filename);
		string str((istreambuf_iterator<char>(in)),
			            istreambuf_iterator<char>()); 
    in.close();
    
    stringstream ss(str);
    vector<string> vec; 
    string buf;
    while (ss >> buf)
        vec.push_back(buf);

    data.push_back(vec);
  }
  
  return data;
}

int main(){
  vector<vector<string>> input = loadData();
  tfidf run(input);
  string key;
  cout<<"Please input your word:"<<endl;
  cin>>key;
  run.search(key);
  return 0;
}