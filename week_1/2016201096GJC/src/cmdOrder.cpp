#include "cmdOrder.h"

std::string countFiles(int road){
	std::string strroad, ordercount;
	strroad = std::to_string(road);
	ordercount = "ls -l ";
	std::string rootroad = "/home/jc/";
	ordercount = ordercount.append(rootroad);
	ordercount = ordercount.append(strroad);
	ordercount = ordercount.append("|grep \"^-\"|wc -l");
	return ordercount;
}

std::string htmlName(int i, int road){
	std::string strroad, htmlname;
	htmlname = std::to_string(i);
	strroad = std::to_string(road);
	std::string rootroad = "/home/jc/";
	rootroad.append(strroad);
	rootroad.append("/");
	htmlname = rootroad.append(htmlname);
    htmlname = htmlname.append(".html");
	return htmlname;
}

std::string mkDir(int road){
	int roadadd = road+1;
	std::string mkdir = "mkdir ";
	std::string strroadadd = std::to_string(roadadd);
    return strroadadd;
}

inline std::string downloadurllink(std::string url){
	std::string order = "curl ";
	order = order.append(url);
	order = order.append(" >> ");
	order = order.append("/home/jc/");
	return order;
}

std::string downloadHtml(std::string strroadadd, int j, std::string url){
	std::string htmlnamesub, order;
	htmlnamesub = std::to_string(j);
	htmlnamesub = htmlnamesub.append(".html");
	order = downloadurllink(url);
	order = order.append(strroadadd);
	order = order.append("/");
	order = order.append(htmlnamesub);
	return order;
}
