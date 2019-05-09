#include "html.h"

Html::Html(int i, int road, string starturl){
	i_ = i;
	road_ = road;
	htmlname_ = std::to_string(i);
	starturl_ = starturl;
}

void Html::HtmlName(){
	string strroad;
	htmlname_ = std::to_string(i_);
	strroad = std::to_string(road_);
	//string rootroad = "home/jc/";
	string rootroad = GetCmdResult("pwd");
	rootroad.append("/");
	rootroad.append(strroad);
	rootroad.append("/");
	htmlname_ = rootroad.append(htmlname_);
	htmlname_ = htmlname_.append(".html");
}

void Html::HtmlParse(){
	std::ifstream inhtml;
	inhtml.open(htmlname_);
	parser_ = HTMLParser(inhtml, starturl_);
	parser_.GetSubLinks(single_url_set_, history_url_set_);
	inhtml.close();
}

void Html::ShowCount() const{
	std::cout << "There are " << history_url_set_.size() << " htmls in total" << std::endl;
	std::cout << "There are " << single_url_set_.size() << "htmls in single" << std::endl;
}
