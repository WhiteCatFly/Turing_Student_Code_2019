#include "crawler.h"

int main()
{
	crawler econ = crawler("http://econ.ruc.edu.cn", "crawler.out");
	econ._get_url();
	return 0;
}
