/* 命令行解析器 */

#ifndef _CMD_H

#define _CMD_H

#include<string>
#include<iostream>

class CMDparser{
friend class GetContent;
private:
    std::string url;
    static std::string tries; //重连次数
    static std::string timeout; //连接限时
    static std::string filename; //结果输出到的文件名
    bool valid; 
public:
    CMDparser(){};
    ~CMDparser(){};
    CMDparser(const std::string&str); //从一行命令构造
    bool Valid() {return valid;};
    static std::string Filename(){return filename;};
};

class Helpmsg{ // 帮助信息
public:
    static void show();
};

#endif