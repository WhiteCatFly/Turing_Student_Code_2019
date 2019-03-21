#include "BigJob.h"
int number = 0;
string root = "info.ruc.edu.cn";
string current_url = "info.ruc.edu.cn";
queue<string> url_to_be_crawled;
set<string> url_already_be_crawled;
int main()
{
	int time,time_beg,time_end;
	time_beg = clock();
	url_to_be_crawled.push(root);
        deep_search();
        time_end = clock();
        time = time_end-time_beg;
        cout << time << endl;
        return 0;
}

