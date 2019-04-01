#include "htmlParse.h"

bool htmlParse(std::string htmlname, std::vector<std::string>& single_url_set, std::vector<std::string>& history_url_set){
	std::string tmp,html;
	std::ifstream inhtml;
	inhtml.open(htmlname);
	while(getline(inhtml,tmp)){
		tmp += '\n';
		html += tmp;
	}
	std::regex linkxp("a href=\"(.*?)\"");
	for (std::sregex_iterator it(html.begin(), html.end(), linkxp), end;
			it != end;
			++it){
		std::string strurl;
		strurl = it->str();
		for(int i=0; i<8; i+=1){
			strurl.erase(0,1);
		}
        strurl.erase(strurl.end()-1);
		
		if(strurl.rfind("php")>0||strurl.rfind("html")>0){
		    if(strurl.find("http")!=std::string::npos){
			    if(strurl.find("http://info.ruc.edu.cn")!=std::string::npos){
					std::vector<std::string>::iterator it;
					it=find(history_url_set.begin(),history_url_set.end(),strurl);
					if(it==history_url_set.end()){
						single_url_set.push_back(strurl);
						history_url_set.push_back(strurl);
				    }
			    }
		    }else{
			    std::string title = "http://info.ruc.edu.cn/";
			    strurl = title.append(strurl);

				std::vector<std::string>::iterator it2;
				it2=find(history_url_set.begin(),history_url_set.end(),strurl);
				if(it2==history_url_set.end()){
					single_url_set.push_back(strurl);
					history_url_set.push_back(strurl);
				}
		    }
        }      
	}
	sort(single_url_set.begin(),single_url_set.end());
	single_url_set.erase(unique(single_url_set.begin(), single_url_set.end()), single_url_set.end());
    std::cout << single_url_set.size()<<std::endl;
	
	sort(history_url_set.begin(),history_url_set.end());
	history_url_set.erase(unique(history_url_set.begin(), history_url_set.end()), history_url_set.end());
	return true;
}
