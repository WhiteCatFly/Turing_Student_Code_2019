#include "BigJob.h"
int main()
{
	int time,time_beg,time_end;
	string root;
	time_beg = clock();
	cout << "Please input the name of url that you are going to crawl" << endl;
	cin >> root;
	crawled website = crawled(root);
        time_end = clock();
        time = time_end-time_beg;
        cout << time << endl;
        return 0;
}

