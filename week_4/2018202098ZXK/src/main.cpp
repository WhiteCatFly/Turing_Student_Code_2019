#include "HTMLParser.h"
using namespace std;

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	string fileName;
	ifstream ifile;
	cout << "Please input fileName\n";
	cin >> fileName;
	ifile.open(fileName);
	if(!ifile){
		cout << "Error in opening the file " << fileName << endl;
		return -1;
	}
	HTMLParser test(ifile);
	cout << "title: " << test.getTitle() << endl;
	cout << "texts: " << test.getTexts() << endl;
	cout << "links: " << test.getLinks() << endl;

	cout << "Test find(a)\n";
	Tag* tg = test.find("a");
	for(auto x: tg->attrs){
		cout << x.first <<" : " << x.second << endl;
	}
	
	cout << "\nTest find_all(a)\n";
	std::vector<Tag*> v;
	test.find_all("a", v);
	for(auto mTag: v){
		for(auto x: mTag->attrs){
			cout << x.first <<" : " << x.second << endl;
		}
		cout << endl;
	}
}
