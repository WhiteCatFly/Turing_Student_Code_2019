#include "html.h"

Html::Html(int i, int road, string starturl){
	_i = i;
	_road = road;
	_htmlname = std::to_string(i);
	_starturl = starturl;
}

void Html::HtmlName(){
	string strroad;
	_htmlname = std::to_string(_i);
	strroad = std::to_string(_road);
	string rootroad = "/home/jc/";
	rootroad.append(strroad);
	rootroad.append("/");
	_htmlname = rootroad.append(_htmlname);
	_htmlname = _htmlname.append(".html");
}

void Html::GenerateVector(string strurl){
	if(strurl.rfind("php")!=string::npos||strurl.rfind("html")!=string::npos){
	    if(strurl.find("http")!=string::npos){
		    if(strurl.find(_starturl)!=string::npos){
				vector<string>::iterator it;
				it=find(_history_url_set.begin(),_history_url_set.end(),strurl);
				if(it==_history_url_set.end()){
					_single_url_set.push_back(strurl);
					_history_url_set.push_back(strurl);
			    }
		    }
	    }else{
			string title = _starturl;
		    if(strurl.substr(0, 1) != "/"){
                title = title.append("/");
			}
		    strurl = title.append(strurl);
			vector<string>::iterator it2;
			it2=find(_history_url_set.begin(),_history_url_set.end(),strurl);
			if(it2==_history_url_set.end()){
				_single_url_set.push_back(strurl);
				_history_url_set.push_back(strurl);
			}
	    }
    }      
}

void Html::HtmlParse(string RegularExperssion){
	string tmp,htmls;
	std::ifstream inhtml;
	inhtml.open(_htmlname);
	while(getline(inhtml,tmp)){
		tmp += '\n';
		htmls += tmp;
	}
	std::regex linkxp(RegularExperssion);
	for (std::sregex_iterator it(htmls.begin(), htmls.end(), linkxp), end;
			it != end;
			++it){
		string strurl;
		strurl = it->str();
		strurl.erase(0, 5);
		if (strurl.find("\"")!=string::npos || strurl.find("\'")!=string::npos){
            strurl.erase(0, 1);
			strurl.erase(strurl.end() - 1);
		}
		AddEscapeCharacter(strurl);
		GenerateVector(strurl);
	}
	sort(_single_url_set.begin(),_single_url_set.end());
	_single_url_set.erase(unique(_single_url_set.begin(), _single_url_set.end()), _single_url_set.end());
    std::cout << _single_url_set.size()<<std::endl;
	sort(_history_url_set.begin(),_history_url_set.end());
	_history_url_set.erase(unique(_history_url_set.begin(), _history_url_set.end()), _history_url_set.end());
	inhtml.close();
}

void Html::ShowCount() const{
	std::cout << "There are " << _history_url_set.size() << "htmls in total" << std::endl;
}
