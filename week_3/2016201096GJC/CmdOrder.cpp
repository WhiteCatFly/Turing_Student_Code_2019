#include "CmdOrder.h"


string downloadurllink(string url){
	std::string order = "curl ";
	order = order.append(url);
	order = order.append(" >> ");
	order = order.append("/home/jc/");
    return order;
}


string downloadHtml(string strroadadd, int j, string url){
    string htmlnamesub, order;
	htmlnamesub = std::to_string(j);
	htmlnamesub = htmlnamesub.append(".html");
	order = downloadurllink(url);
	order = order.append(strroadadd);
	order = order.append("/");
	order = order.append(htmlnamesub);
	return order;
}

string getCmdResult(const std::string& strCmd){
	char buf[10240] = {0};
	FILE *pf = NULL;
	if( (pf = popen(strCmd.c_str(), "r")) == NULL ){
		return "";
	}
	string strResult;
    while(fgets(buf, sizeof buf, pf)){
	    strResult += buf;
	}
	pclose(pf);
	unsigned int iSize =  strResult.size();
	if(iSize > 0 && strResult[iSize - 1] == '\n'){
		strResult = strResult.substr(0, iSize - 1);
	}
	return strResult;
}


string CountFiles(int road){
	string strroad, ordercount;
	strroad = std::to_string(road);
	ordercount = "ls -l ";
	string rootroad = "/home/jc/";
    ordercount = ordercount.append(rootroad);
	ordercount = ordercount.append(strroad);
	ordercount = ordercount.append("|grep \"^-\"|wc -l");
	return ordercount;
}


