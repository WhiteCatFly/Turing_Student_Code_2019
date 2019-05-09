#include "Attribute.h"
#include <cstdlib>
using std::string;
Attribute::Attribute(){
	attrs["url"] = "";
	attrs["thread"] = "20";
	attrs["sleep"] = "300";
	attrs["tries"] = "2";
	attrs["timeout"] = "5";
	attrs["error"] = "Error.log";
	attrs["runlog"] = "RUN.log";
	attrs["reload"] = "";
	attrs["cookie"] = "";
	attrs["header"] = "";
}

string& Attribute::operator[](const string& key){
	static string nullstr("");
	if(attrs.count(key)){
		return attrs[key];
	}
	else{
		std::string key_error =  "key: " +  key +" does not exists";
		throw std::range_error(key_error);
	}
}

Attribute creatAttr(int argc, char const *argv[]){
	Attribute res;
	string key;
	string val;

	if(argc < 2){
		std::string argc_length = "arguments length is not enough";
		throw std::invalid_argument(argc_length);
	}

	res["url"] = argv[1];
	if(res["url"].back() != '/') res["url"] += "/";

	for(int i = 2; i+1 < argc; i+=2){
		key = argv[i];
		val = argv[i+1];
		if(key[0] != '-'){
			std::string key_error =  "invalid_keyword:" +  key;
			throw std::invalid_argument(key_error);
		}
		key.erase(0,1);
		res[key] = val;
	}
	
	return res;
}