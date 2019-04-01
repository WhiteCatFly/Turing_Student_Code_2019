#include <set>
#include <queue>
#include <string>

const std::string sensitive_words[300]={".css", "weixin", "qq", ".doc", ".docx", ".xls", ".xlsx", ".txt", ".jpg", ".png", ".bmp", ".jpeg", ".flv", ".mp4", ".avi", "@", ".pdf", ".zip", ".rar", ".js", "renzheng", "javascript", "bbs", "mace", "xialingying", "upfile", "file", "account","words_end"};

class Web_Crawler{
	private:
		std::queue<std::string> url_queue;
		std::set<std::string> url_set;
		int total_website, successful_website, failed_website;
		std::string origin, current_url, current_html;
		void get_html();
		void find_next_url();
		void exit_status(int res);
	public:
		void Web_Crawler_BFS(const char* crawled_web);
		Web_Crawler();
};
