main.cpp :
int main() : 运行

crawler.cpp :
bool check1(string s) : 检查 s 中是否有"http://info.ruc.edu.cn"
string get_url(string s) : 从 s 中找到一个"href=", 并返回后面引号中的字符串
bool is_url(string s) : 检查提取出来的字符串是否是合法网址
void use_wget(string s, string s1) : 使用wget得到网址 s 的内容，并保存到名为 s1 的文件中
string get_direction(string s) : 得到网址 s 的存储路径
bool solve_a_line(char *one_line, string direction) : 从一个网址的内容的一行 one_line 中得到一个网址， 当前网址的存储路径为 direction, 成功则返回true
void bfs(string s) : 以网址 s 为根展开搜索

