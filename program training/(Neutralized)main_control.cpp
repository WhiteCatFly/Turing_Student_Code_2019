#include <vector>
#include <string>
#include <iostream>
#include "searchengine.h"
/* 
这里需要注意：
姓名
性别
年龄必须为数字                          不合法数字 <0 或者 >100 返回为不详
地点1
地点2
丢失年月日，一定要数字空格数字空格数字    不合法年份 <1900 或者 >2019 返回为不详
身高，以厘米为单位的数字                 不合法身高 <0    或者 >300  返回为不详
细节特征，用于精确搜索

返回时会多给一个链接

以上我提到的数字啥的必须是数，可以为负数也可以为小数，不是数程序会爆炸。如果用户留空你可以输入不太合法的数字。
这个版本的程序可以给你用于调试，多个数据文件(.txt)编码均为UTF-8，程序应该也没有大问题。

具体估值函数会精细调教，还有cy的后续数据我再做适配，应该是整个已经结束了。
三个数据文件：data_ex.txt synonyms.txt stop_words.utf8 需要放在程序同目录下

将来修改会有估值和释放内存这样子，但是应该不会太大qwq

*/
std::string find[8] = {"" , "" , "" , "" , "" , "" , "" , "牛肉拉面"};

int main(int argc, char **argv){
    std::vector<std::vector<std::string>> v;
    SearchEngine excellent;
//    excellent.Initialize();
    excellent.Initialize2();
    v = excellent.Search(find);
    for(auto i = v.begin(); i != v.end(); i++){
        for(auto j = i -> begin(); j != i -> end(); j++)
            std::cerr << *j << std::endl;
        std::cerr <<""<<std::endl;
    }
    return 0;
}