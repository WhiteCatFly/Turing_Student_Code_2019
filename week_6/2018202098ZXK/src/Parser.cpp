#include "HTMLParser.h"
using namespace std;
#define DEBUG 0

//删除属性的引号
inline void DelQuota(string& str)
{
	if(str[0] == '\'' || str[0] == '"') str.erase(0, 1);
	if(str.back() == '/') str.pop_back();
	if(str.back() == '\'' || str.back() == '"') str.pop_back();	
}

//某些标签是单个使用的，<img ..>
inline bool halfPar(const string &str){
	string possilbeHalfPar[] = {"img", "meta", "input", "link"};
	for(auto pbhp: possilbeHalfPar){
		if(str == pbhp) return true;
	}
	return false;
}

//处理文本
inline void HTMLParser::parseText(const string &str, int l, int r) //[l,r)
{
	string temp = str.substr(l, r - l);
	if(regex_match(temp, s_re)) return;  
	current_ -> strs.push_back(temp);
}

//DFS清理内存
HTMLParser::~HTMLParser(){
	delTagDfs(root_);
	root_ = title_ = current_ = nullptr;
}


Tag* HTMLParser::find(const string& tag_name){
	return root_ -> find(tag_name);
}

int HTMLParser::find_all(const string& tag_name, std::vector<Tag*> &v){
	return root_ -> find_all(tag_name, v);
}


void HTMLParser::parseTag(string str){
	Tag* son = new Tag;
	son -> prt_ = current_;
	son -> nxt_ = current_ -> son_;
	if(current_ -> son_) current_ -> son_ -> pre_ = son;
	current_ -> son_ = son;
	current_ = son;

	Tag* ct = current_;
	smatch att;
	bool firstFlag = true;
	
	int equal_pos = 0;
	string att_str(""), key(""), val(""), temp("");
	while(regex_search(str, att, str_re)){
		for(int i = 0; i < (int)att.size(); i++){
			att_str = att[i];
			if(firstFlag){
				firstFlag = false;
				ct -> tagName = att_str;
				if(ct -> tagName == "title"){
					title_ = ct;
				}
				continue;
			}
			if(att_str.find("=") == string::npos) continue;
			DelQuota(att_str);
			equal_pos = att_str.find("=");
			key = att_str.substr(0, equal_pos);
			val = att_str.substr(equal_pos+1);
			DelQuota(val);
			ct -> attrs[key] = val;
		}
		str = att.suffix().str();
		if((int)att.size() > 0) temp = att[att.size() - 1];
	}
	if(temp.back() == '/') current_ = current_ -> prt_;
}

void HTMLParser::parseEndTag(string str){
	str.erase(0,2).pop_back(); // erase </ >
	if(str == current_ -> tagName){
		if(!current_ -> prt_) cerr << "Error: end_tag " << str << endl;
		else current_ = current_ -> prt_; 
	}
	else if(!halfPar(str)){
		while(current_ != root_ && str != current_ -> tagName)
			current_ = current_ -> prt_;
		if(current_ != root_){
			current_ = current_ -> prt_;
		}
	}
}

HTMLParser::HTMLParser(std::ifstream& in){
	smatch sma;
	const int strLengthLimit = 4096; //regex可能存在bug， 当输入的字符串过长，会卡死
	root_ = current_ = new Tag;
	source_.clear();


	//parse in to normal text
	string tmp(""), str(""), sma_str("");
	while(!in.eof()){
		getline(in, tmp);
		if(tmp.length() > strLengthLimit) continue;
		for(int i = 0; i < (int)tmp.length(); i++){
			if(tmp[i] == '\r') tmp[i] = ' ';
		}
		source_ += tmp;
	}
	str = source_;

	while(regex_search(str, sma, tag_re)){
		for(int i = 0; i < (int)sma.size(); i++){
			sma_str = sma[i];
			parseText(str, 0, sma.position(i));
			if(sma_str.find("!DOCT") != string::npos) continue;
			else if(sma_str[1] == '!') continue; //comment ignore
			else if(sma_str[1] == '/') parseEndTag(sma_str);
			else parseTag(sma_str);
		}
		str = sma.suffix().str();
	}
	if(str.length()) parseText(str, 0, str.length());
	in.close();
}


HTMLParser::HTMLParser(const string& source){
	root_ = current_ = new Tag;
	smatch sma;
	const int strLengthLimit = 4096;
	source_.clear();
	stringstream in = stringstream(source);
	//parse in to normal text
	string tmp(""), str(""), sma_str("");
	while(!in.eof()){
		getline(in, tmp);
		if(tmp.length() > strLengthLimit) continue;
		for(int i = 0; i < (int)tmp.length(); i++){
			if(tmp[i] == '\r') tmp[i] = ' ';
		}
		source_ += tmp;
	}

	str = source_;

	while(regex_search(str, sma, tag_re)){
		for(int i = 0; i < (int)sma.size(); i++){
			sma_str = sma[i];
			if(sma_str.find("!DOCT") != string::npos) continue;
			else if(sma_str[1] == '!') continue; //comment ignore
			else if(sma_str[1] == '/') parseEndTag(sma_str);
			else parseTag(sma_str);
		}
		str = sma.suffix().str();
	}
	if(str.length()) parseText(str, 0, str.length());
}

string HTMLParser::getTitle() const{
	if(title_ == nullptr) return "";
	string res("");
	for(auto s: title_ -> strs) res += s;
	return res;
}

int HTMLParser::getLinks(const string& filename){
	ofstream out(filename);
	if(!out){
		std::string fileError = "your file does not exists";
		throw std::invalid_argument(fileError);
	}
	int num = output_dfs(root_, LINKMODE, out);
	out.close();
	return num;
}

int HTMLParser::getTexts(const string& filename){
	ofstream out(filename);
	if(!out){
		std::string fileError = "your file does not exists";
		throw std::invalid_argument(fileError);
	}
	int num = output_dfs(root_, TEXTMODE, out);
	out.close();
	return num;
}


