#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

class HTMLparser
{
  private:
    std::string target;
    std::string content;
    std::string file;
    
    void getcontent();
  public:
    HTMLparser() = default;
    HTMLparser(std::string target_, int openway);
    ~HTMLparser();
    
    void extract_title();
    void extract_content();
    void extract_url();
};

#endif