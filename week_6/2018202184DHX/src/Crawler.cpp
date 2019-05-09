#include "Crawler.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <regex>

int Crawler::count = 0;

Crawler::Crawler() {
    root = "http://econ.ruc.edu.cn/";   
    save_path = "./";		
}

Crawler::Crawler(const std::string url):SetFile("Set.out"),QueueFile("Queue.out")
{
	root = url;
	save_path = "./";
}

Crawler::Crawler(const std::string url, const std::string path):SetFile("Set.out"),QueueFile("Queue.out")
{
	root = url;
	save_path = path;
}

Crawler::~Crawler() {

}

std::string Crawler::GetPageToFile(const std::string url, const std::string path,int count) {
    //get system instruction to use wget
    std::string file_name = std::to_string(count);
    file_name += ".html";
    std::string instruction_name = "wget -O " + path + file_name + " \"" + url + "\"" + " -a down.log";
    const char *key = instruction_name.c_str();
    system(key);
    return file_name;  
}

void Crawler::ReadFile(const std::string file_name, const std::string path, std::string &content) {
    //open file
    std::ifstream file_to_be_read;
    file_to_be_read.open(path + file_name);		

    std::string temp;
    while(getline(file_to_be_read, temp))
        content += temp;
    //close file
    file_to_be_read.close();

	return;
}

void Crawler::ParseOnePage(std::string &current_url, std::string &content, std::queue<std::string> &url_to_be_crawled) {
        const std::string BlackList[100] = {
    "@", "google", "csdn.", "pku", "ccf.org", "rss.", "math.ruc", "challenger.", "vedio_detail", "str = str+",
    ".doc", ".ppt", ".PPT", ".zip", ".rar", ".xls", ".pdf", ".css", ".txt", ".jpg", ".JPG", ".png", "bmp", ".jpeg", 
    ".js", ".flv", ".mp4", ".avi", "words_end"
	};

    std::regex pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    std::smatch url;
    std::string::const_iterator iterStart = content.begin();
    std::string::const_iterator iterEnd = content.end();
    while(regex_search(iterStart, iterEnd, url, pattern)) {
        std::string temp = url[2].str();

        if(temp[0] == '\'' || temp[0] == '\"') {
            temp.erase(0, 1);
            temp.erase(temp.size() -1,1);
        }
    	if(temp == "index.php" || temp == "\\") {
            iterStart = url[0].second;
            continue;
        }   		
    	if(temp.find("http") != temp.npos && temp.find("econ.ruc") == temp.npos) {
            iterStart = url[0].second;
            continue;
        }              
        if(temp.empty()) {
            iterStart = url[0].second;
            continue;
        } 
    	bool flag = true;
        for(int i = 0; BlackList[i] != "words_end"; ++ i) {
                if(temp.find(BlackList[i]) != temp.npos) {
    			flag = false;
    			break;
    		}
    	}        
    	if(flag){
    		if(temp.find("http") == temp.npos && current_url.find("en") != temp.npos && temp.find("/en") == temp.npos && temp != "/en")
    			temp = root + "en/" + temp;

    		if(temp.find("http") == temp.npos)
    			temp = root + temp;
    		url_to_be_crawled.push(temp);
            QueueFile.Output(temp.c_str());
    	}
        iterStart = url[0].second;
    }   
}

void Crawler::Core() {
    if(url_to_be_crawled.empty())
    {
        url_to_be_crawled.push(root);
        QueueFile.Output(root.c_str());
    }
	while(!url_to_be_crawled.empty()) {
    	std::string current_url = url_to_be_crawled.front();
        url_to_be_crawled.pop();
    	if(url_already_be_crawled.find(current_url) != url_already_be_crawled.cend())
    		continue;

        count ++;
    	url_already_be_crawled.insert(current_url);
        SetFile.Output(current_url.c_str());
        //std::cout << count << "\n" << current_url << std::endl;
        //std::cout << "left: " << url_to_be_crawled.size() << std::endl;
    	std::string file_name = GetPageToFile(current_url, save_path, count);
    	std::string content;
    	ReadFile(file_name, save_path, content);
    	ParseOnePage(current_url, content, url_to_be_crawled);
    }
    //std::cout << "OK" << std::sendl;
};

void Crawler::REset(const char *SetFilename,const char* QueueFileName)
{
    std::string ReadLine;
    int count_size = 0;

    std::ifstream set_file;
    set_file.open(SetFilename,std::ifstream::in);
    while(getline(set_file,ReadLine))
    {
        url_already_be_crawled.insert(ReadLine);
        ReadLine.clear();
        count_size ++;
    }
    set_file.close();

    std::ifstream queue_file;
    queue_file.open(QueueFileName,std::ifstream::in);
    while(getline(queue_file,ReadLine))
    {
        url_to_be_crawled.push(ReadLine);
        ReadLine.clear();
    }
    queue_file.close();
    for(count_size ;count_size >= 0 ;count_size --)
    {
        url_to_be_crawled.pop();
    }
    return;
};

OUTFILE::~OUTFILE() {
    fclose(fout);
};

OUTFILE::OUTFILE()
{
    fout = NULL;
    std::cout << "File Opened Error"<< std::endl;
    system("pause");
};

OUTFILE::OUTFILE(const std::string outfilename)
{
    const char *name = outfilename.c_str();
    fout = fopen(name,"a+");
};

void OUTFILE::Output(const char* content){
    fwrite(content,sizeof(content),1,fout);
    fwrite("/r/n",1,2,fout);
    return;
};