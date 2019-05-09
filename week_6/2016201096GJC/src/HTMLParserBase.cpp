#include "HTMLParser.h"

void HTMLParserBase::DownloadFromUrl(){
	std::stringstream downloadOrder;
	downloadOrder << "curl ";
    downloadOrder << url_;
	downloadOrder << " >> ";
	downloadOrder << location_;
	std::cout << downloadOrder.str() << std::endl;
	system(downloadOrder.str().c_str());
}

HTMLParserBase::HTMLParserBase(string url, string starturl){
	url_ = url;
	location_ = GetCmdResult("pwd");
	location_ = location_.append("/htmlFile.html");
	DownloadFromUrl();
	std::ifstream inhtml;
	inhtml.open(location_);
	string tmp;
	while(getline(inhtml,tmp)){
		tmp += '\n';
		html_ += tmp;
	}
	inhtml.close();
	starturl_ = starturl;
}

HTMLParserBase::~HTMLParserBase(){
	if ( location_!="" ){
    	std::stringstream rmOrder;
		rmOrder << "rm ";
		rmOrder << location_;
		system(rmOrder.str().c_str());
	}	
}

string HTMLParserBase::GetTitle(){
    string regularExpression = "<title>[\\s\\S]*?</title>";
	std::regex linkxp(regularExpression);
	string title;
	for (std::sregex_iterator it(html_.begin(), html_.end(), linkxp), end; it != end; ++it){
		title = it->str();
	}
	title.erase(0, 7);
	title.erase(title.length()-8, 8);//7 and 8 is the length of <title> and </title>
	return title;
}

string HTMLParserBase::replace(string str, string pattern, string repattern){
    string retStr = "";
	string::size_type pos;
    int i = 0, l_count = 0, szStr = str.length();
	int count = szStr;
	for(i = 0; i < szStr; i++){
		if(string::npos == (pos=str.find(pattern,i)))  break;
		if(pos < szStr){
			retStr += str.substr(i,pos-i) + repattern;
			i = pos + pattern.length() - 1;
			if(++l_count >= count){
				i++;
				break;
			}
		}
	}
	retStr += str.substr(i);
	return retStr;
}

void HTMLParserBase::DeleteLabel(string& body){
	string regularExpression = "<[^>]*>";
	std::regex linkxp(regularExpression);
    std::vector<string>labels;
	for (std::sregex_iterator it4(body.begin(), body.end(), linkxp), end; it4 != end; ++it4){
		string label = it4->str();
		labels.push_back(label);	
	}
	for (int i = 0; i < labels.size(); i++){
		body = replace(body, labels[i], "");
	}
}

string HTMLParserBase::GetBody(){
    string regularExpression = "<p>[\\s\\S]*</p>";
	string body;
	std::regex linkxp(regularExpression);
	for (std::sregex_iterator it2(html_.begin(), html_.end(), linkxp), end; it2 != end; ++it2){
		body = it2->str();
	}
	body = replace(body, "&nbsp;", " ");
	body = replace(body, "&ldquo;", "“");
	body = replace(body, "&rdquo;", "”");
    DeleteLabel(body);
	return body;
}

