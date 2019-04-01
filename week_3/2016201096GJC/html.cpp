#include "html.h"

Html::Html(int i, int road){
	_i = i;
	_road = road;
	_htmlname = std::to_string(i);
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

/*
string Html::CountFiles(int road){
	string strroad, ordercount;
    strroad = std::to_string(road);
	ordercount = "ls -l ";
	string rootroad = "/home/jc/";
    ordercount = ordercount.append(rootroad);
	ordercount = ordercount.append(strroad);
	ordercount = ordercount.append("|grep \"^-\"|wc -l");
	return ordercount;
}
*/

void Html::GenerateVector(string strurl){
	if(strurl.rfind("php")>0||strurl.rfind("html")>0){
	    if(strurl.find("http")!=string::npos){
		    if(strurl.find("http://econ.ruc.edu.cn")!=string::npos){
				vector<string>::iterator it;
				it=find(_history_url_set.begin(),_history_url_set.end(),strurl);
				if(it==_history_url_set.end()){
					_single_url_set.push_back(strurl);
					_history_url_set.push_back(strurl);
			    }
		    }
	    }else{
		    string title = "http://econ.ruc.edu.cn/";
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

void Html::ReduplictionRemoving(){
	sort(_single_url_set.begin(),_single_url_set.end());
	_single_url_set.erase(unique(_single_url_set.begin(), _single_url_set.end()), _single_url_set.end());
    std::cout << _single_url_set.size() << std::endl;
	sort(_history_url_set.begin(),_history_url_set.end());
	_history_url_set.erase(unique(_history_url_set.begin(), _history_url_set.end()), _history_url_set.end());
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
		strurl.erase(0, RegularExperssion.size() - 6);
        strurl.erase(strurl.end() - 1);
		GenerateVector(strurl);
		/*
		if(strurl.rfind("php")>0||strurl.rfind("html")>0){
		    if(strurl.find("http")!=string::npos){
			    if(strurl.find("http://econ.ruc.edu.cn")!=string::npos){
					vector<string>::iterator it;
					it=find(_history_url_set.begin(),_history_url_set.end(),strurl);
					if(it==_history_url_set.end()){
						_single_url_set.push_back(strurl);
						_history_url_set.push_back(strurl);
				    }
			    }
		    }else{
			    string title = "http://econ.ruc.edu.cn/";
			    strurl = title.append(strurl);
				vector<string>::iterator it2;
				it2=find(_history_url_set.begin(),_history_url_set.end(),strurl);
				if(it2==_history_url_set.end()){
					_single_url_set.push_back(strurl);
					_history_url_set.push_back(strurl);
				}
		    }
        }
        */		
	}
	//sort(_single_url_set.begin(),_single_url_set.end());
	//_single_url_set.erase(unique(_single_url_set.begin(), _single_url_set.end()), _single_url_set.end());
    //std::cout << _single_url_set.size()<<std::endl;
	//sort(_history_url_set.begin(),_history_url_set.end());
	//_history_url_set.erase(unique(_history_url_set.begin(), _history_url_set.end()), _history_url_set.end());
    ReduplictionRemoving();
}

/*
void Html::MakeDir(int road) const{
	string mk = "mkdir ";
	mk = mk.append(std::to_string(road + 1));
	system(mk.c_str());
}
*/

void Html::ShowCount() const{
	std::cout << "There are " << count << "htmls in total" << std::endl;
}
