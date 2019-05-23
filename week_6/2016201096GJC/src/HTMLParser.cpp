#include "HTMLParser.h"

HTMLParser::HTMLParser(string url, string starturl){
    HTMLParserBase(url, starturl);
}

HTMLParser::HTMLParser(std::ifstream &file, string starturl){
	string tmp;
	while(getline(file, tmp)){
		tmp += '\n';
		html_ += tmp;
	}
	starturl_ = starturl;
}

void HTMLParser::GenerateVector(string strurl, vector<string>& single_url_set_, vector<string>& history_url_set_){
	//if(strurl.rfind("php")!=string::npos||strurl.rfind("html")!=string::npos){
	if(strurl.rfind(".doc")==string::npos
			&&strurl.rfind(".ppt")==string::npos
			&&strurl.rfind("@")==string::npos
			&&strurl.rfind(".png")==string::npos
			&&strurl.rfind(".jpg")==string::npos
			&&strurl.rfind(".css")==string::npos
			&&strurl.rfind(".json")==string::npos
			&&strurl.rfind(".rar")==string::npos
			&&strurl.rfind(".csv")==string::npos
			&&strurl.rfind(".xlsx")==string::npos
			&&strurl.rfind(".pdf")==string::npos
			&&strurl.rfind(".xls")==string::npos
			&&strurl.rfind(".gif")==string::npos
			&&strurl.rfind(".jpeg")==string::npos
			&&strurl.rfind(".bmp")==string::npos
			&&strurl.rfind(".txt")==string::npos
			&&strurl.rfind(".zip")==string::npos
			&&strurl.rfind(".tar")==string::npos){
		if(strurl.find("http")!=string::npos){
			if(strurl.find(starturl_)!=string::npos){
				vector<string>::iterator it;
				it=find(history_url_set_.begin(), history_url_set_.end(), strurl);
				if(it==history_url_set_.end()){
					single_url_set_.push_back(strurl);
					history_url_set_.push_back(strurl);
				}
			}
		}else{
			string title = starturl_;
			if(strurl.substr(0, 1) != "/"){
				title = title.append("/");
			}
			strurl = title.append(strurl);
			vector<string>::iterator it2;
			it2=find(history_url_set_.begin(), history_url_set_.end(), strurl);
			if( it2==history_url_set_.end() ){
				single_url_set_.push_back(strurl);
				history_url_set_.push_back(strurl);
			}
		}
    }      
}

void HTMLParser::AddEscapeCharacter(string& strurl){
	if (strurl.find("page=") != string::npos){
		int position = strurl.find("page=");
		strurl = strurl.insert(position-2, "\\");
		strurl = strurl.insert(position, "\\");
	}
}

void HTMLParser::GetSubLinks(vector<string>& single_url_set_, vector<string>& history_url_set_){
	string regularExpression = "href\\s*=\\s*(?:\"([^\"]*)\"|\'([^\']*)\'|([^\"\'>\\s]+))";
	std::regex linkxp(regularExpression);
	string subLinks;
	for (std::sregex_iterator it3(html_.begin(), html_.end(), linkxp), end; it3 != end; ++it3){
		string link = it3->str();
		link.erase(0, 5);//5 is the length of href=
		if (link.find("\"")!=string::npos || link.find("\'")!=string::npos){
			link.erase(0, 1);
			link.erase(link.end() - 1);
		}
		AddEscapeCharacter(link);
		GenerateVector(link, single_url_set_, history_url_set_);
	}
	sort(single_url_set_.begin(), single_url_set_.end());
	single_url_set_.erase(unique(single_url_set_.begin(), single_url_set_.end()), single_url_set_.end());
    std::cout << single_url_set_.size() << std::endl;
	sort(history_url_set_.begin(), history_url_set_.end());
	history_url_set_.erase(unique(history_url_set_.begin(), history_url_set_.end()), history_url_set_.end());
}
