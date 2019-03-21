#include "BigJob.h"
int number = 0;
string root  ;
string current_url ;
queue<string> url_to_be_crawled;
set<string> url_already_be_crawled;
int main()
{
	int time,time_beg,time_end;
	time_beg = clock();
	cout << "Please input the name of url that you are going to crawl" << endl;
	cin >> root;
	url_to_be_crawled.push(root);
        deep_search();
        time_end = clock();
        time = time_end-time_beg;
        cout << time << endl;
        return 0;
}

