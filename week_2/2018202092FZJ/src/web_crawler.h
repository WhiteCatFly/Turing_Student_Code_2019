#include <set>
#include <queue>
#include <string>

const std::string forbidden_words[200] = {".css", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@ruc.edu.cn", ".pdf", ".js", ".7z", ".rar", ".zip", "end"};

void get_html(const std::string &present_url, std::string &present_html, const int total);

void find_next_url(const std::string &present_url, const std::string &present_html, std::queue<std::string> &url_queue, std::set<std::string> &url_set);

void bfs();
