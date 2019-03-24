#include <ctime>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <sys/time.h>

#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

std::string homepage = "info.ruc.edu.cn";
timeval start_time, now_time;

int main()
{
	gettimeofday(&start_time, NULL);
	if (system("mkdir pages"))
	{
		std::cerr << "directory \"pages\" already exists." << "\n";
	}
	extern void bfs();
	bfs();
	return 0;
}

