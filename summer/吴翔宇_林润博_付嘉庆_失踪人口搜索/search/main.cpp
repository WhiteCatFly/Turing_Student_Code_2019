#include <iostream>
#include "PersonData.h"
using namespace std;

int main()
{
	cout<<"Content-type:text/html\n\n"<<endl;;
	cout<< "<meta charset=\"UTF-8\" />"<<endl;
    string s = getenv("QUERY_STRING");
	cout<<"<!DOCTYPE HTML>\n";
	cout<<"<html lang=\"zxx\">\n";
	cout<<"<head>\n";
	cout<<"<title>失踪人口查询系统</title>\n";
	cout<<"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
	cout<<"<meta charset=\"UTF-8\" />\n";
	cout<<"<meta name=\"keywords\" content=\"\"/>\n";
	cout<<"<link rel=\"stylesheet\" href=\"../css/style.css\" type=\"text/css\" media=\"all\" />	\n";
	cout<<"</head>\n";
	cout<<"<body>\n";
	cout<<"<!--header-->\n";
	cout<<"<h1>\n";
	cout<<"<span>M</span>issing\n";
	cout<<"<span>P</span>opulation\n";
	cout<<"<span>I</span>nquiry\n";
	cout<<"<span>S</span>ystem</h1>\n";
	cout<< "<h2>\n";
	cout<<"查询结果</h2>\n";
	
	cout<<"<!--//header-->\n";
	cout<<"<!-- content -->\n";
	cout<<"<div class=\"fotter\">\n";

	//string s("name=&sex=男&birthday=&lostday=&height=&birthplacefirst=&birthplacesecond=&lostplacefirst=福建省&lostplacesecond=&information=") ;
    //cout<<s<<endl;
	//string s("name=赵明伟&sex=&birthday=&lostday=&height=&birthplacefirst=&birthplacesecond=&lostplacefirst=&lostplacesecond=&information=");
	//cin >> s;
	vector<PersonData> data;
	store(data);
	ComplexQuery q(s);
	//cout << data.size() << endl;
	for (size_t i = 0; i < data.size(); i++)
		scorer(data[i], q);
	SortByScore(data);
	print(data, 5, 1);
	q.print();

	cout<<"</div>\n";
	

	cout<<"<!-- //content -->\n";
	cout<<"<!-- footer -->\n";
	cout<<"<div class=\"footer\">\n";
	cout<<"<p>Copyright &copy; 2019.林润博 付嘉庆 吴翔宇.</a></p>\n";
	cout<<"</div>\n";
	cout<<"<!-- //footer -->\n";
	cout<<"<!-- js -->\n";
	cout<<"<script src=\"js/jquery-2.1.4.min.js\"></script>\n";
	cout<<"<!-- date-->\n";
	cout<<"<link rel=\"stylesheet\" href=\"../css/jquery-ui.css\" />\n";
	cout<<"<script src=\"js/jquery-ui.js\"></script>\n";
	cout<<"<!-- //date -->\n";
	cout<<"<!-- time -->\n";
	cout<<"<script src=\"js/wickedpicker.js\"></script>\n";
	cout<<"<link href=\"../css/wickedpicker.css\" rel=\"stylesheet\" type='text/css' media=\"all\" />\n";
	cout<<"<!-- //time -->\n";
	cout<<"</body>\n";
	cout<<"</html>\n";

	return 0;
}