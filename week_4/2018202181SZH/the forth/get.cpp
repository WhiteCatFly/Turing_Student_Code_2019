#include"HTMLparser.h"
#include<regex>
using std::regex;
using std::smatch;
string sensitive_words[100]={
    ".com",".org",".ru",
    "comsenz","discuz","bbs","rdjjlt",".css",".doc",".docx",".xls",".xlsx",".txt",".jpg",".png","bmp",
    ".jpeg",".flv",".mp4",".avi","@ruc.edu.cn",".pdf","#",".zip",".ppt","javascript",
    ".7z",".rar",".CSS",".DOC",".DOCX","mailto",".XLS",".XLSX",".TXT",".JPG",".PNG","BMP","rar","@163",
    ".JPEG","file://",".FLV",".MP4",".AVI","@RUC.EUD.CN",".PDF",".ZIP",".7Z",".RAR","words_end"
};
void html::get_url()const{
    string temp_str = html_code;
    regex  pattern("(href=|HREF=)((\"(.*?)\")|(\'(.*?)\')|(([^\"\']*?)>))");
    smatch urls;
    
    while(regex_search(temp_str, urls, pattern)){
        string temp = urls[2].str();
        string root1 = "http://";
        string root2 = "https://";

        if(temp[0] == '\''||temp[0] == '\"')  //删除多余的“ ‘‘ “
       {
            int n = temp.size();
            temp.erase(n-1,1);temp.erase(0,1);
       }
        int flag = 0;
        for(int i = 0; sensitive_words[i] != "words_end"; i++){
           if(temp.find(sensitive_words[i]) != temp.npos){
               flag++;  break;
           }
        }
        if(!flag){
            ofstream fout;
            fout.open(store_place,std::ios::out|std::ios::app);
            if(!fout.is_open()){
                cout<<"Fail to open the store file! "<<endl;
                exit(1);
            }
            fout<<temp<<endl;
            fout.close();
        }
        temp_str = urls.suffix();
    }
}
void html::get_title()const{
    regex pattern_title("<title>.*</title>");
    string temp_str = html_code;
    smatch titles;
    regex_search(temp_str,titles,pattern_title);
    ofstream fout;
    fout.open(store_place,std::ios::out|std::ios::app);
    if(!fout.is_open()){
        cout<<"Fail to open the store file! "<<endl;
        exit(1);
    }
    fout<<"This website's title is :"<<endl;
    string temp = titles.str();
    fout<<temp<<endl;
    fout.close();
}
void html::get_main_txt()const{
    int i = 0, j = 0;
    string temp_body;
	while((i = html_code.find("<body", j)) != string::npos && (j = html_code.find("</body>", i)) != string::npos)
	{
	 // i ~ j-1
        temp_body = html_code.substr(i , j - i + 7 );
	}
    ofstream fout;
    fout.open(store_place,std::ios::out|std::ios::app);
    if(!fout.is_open()){
        cout<<"Fail to open the store file! "<<endl;
        exit(1);
    }
    fout<<"This website's main body is :"<<endl;
    fout<<temp_body<<endl;
    fout.close();
}
void html::get_certain_pattern(string &type)const{
    std::stringstream sout;
	int posnow = 0 ;
	int end ;
	int length = type.length() ;
	string first ;
	string second ;
	while ( html_code.find ( "<" + type , posnow + 1 ) != string::npos )
	{
		posnow = html_code.find ( "<" + type , posnow + 1 ) ;
		end = html_code.find ( ">" ,posnow) ;	
		first = html_code.substr ( posnow + length + 1 , end - posnow -length - 1 )  ;
		second = html_code.substr ( end + 1 , html_code.find ( "<" , posnow + 1 ) - end - 1) ;
		sout << first << ":" << endl << "  " <<second << endl;
	}
    string temp_type = sout.str();
    ofstream fout;
    fout.open(store_place,std::ios::out|std::ios::app);
    if(!fout.is_open()){
        cout<<"Fail to open the store file! "<<endl;
        exit(1);
    }
    fout<<"This website's "<<type<<" are :"<<endl;
    fout<<temp_type<<endl;
    fout.close();
}
void html::inter_face()const{
    cout << endl;
	cout << "1: get title" << endl;
	cout << "2: get urls" << endl;
	cout << "3: get main body" << endl;
	cout << "4: get files about certain type" << endl;
	cout << "5: exit" << endl;
	cout << "Please enter you option:" << endl;
    int opt;
	cin >> opt;
	cout << endl;
	switch (opt){
		case 1:{
			get_title();
			continue_interface();
			break;
		}
		case 2:{
			get_url();
			continue_interface();
			break;
		}
		case 3:{
			get_main_txt();
			continue_interface();
			break;
		}
		
		case 4:{
			cout << "Please enter the type you want to get:" << endl;
			string type;
			cin >> type;
			cout << endl;
			get_certain_pattern(type);
			continue_interface();
			break;
		}
		
		case 5:{
			exit(0);
		}
	}

}
void html::continue_interface() const{
	cout << endl;
	cout << "1: back to previous menu" << endl;
	cout << "2: exit" << endl;
	cout << "Please enter you option:" << endl;
	
	int opt;
	cin >> opt;
	cout << endl;
	if (opt == 1)
		inter_face();
}