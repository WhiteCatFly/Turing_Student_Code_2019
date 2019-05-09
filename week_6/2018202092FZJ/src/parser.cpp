#include "crawler.h"

using namespace std;

const char *ESL = "END_OF_SINGLE_LABEL";
const char *SL[] = {"br", "hr", "img", "input", "param", "meta", "link", "!doctype", ESL};
set<string> Parser::Label_Key;

void Parser::Output(const string &code, int tabs, ostringstream &ostr){
    for(int i = 1; i <= tabs; i++){
        ostr << '\t';
    }
    ostr << code << endl;
}

string Parser::Big_Small_Same(string s){
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] += 'a' - 'A';
        }
    }
    return s;
}

Parser::Parser(const char *filename){
    ifstream fin(filename);
    string buf;
    while(getline(fin,buf)){
        Source_Code += buf + '\n';
    }
    fin.close();
    Process();
    string foutname = "Tree_Structure_";
    foutname += filename;
    foutname += ".out";
    ofstream fout(foutname.c_str());
    fout << Source_Code;
    fout.close();
}

Parser::Parser(const string &code){
	Source_Code = code;
	Process();
	ofstream fout("TreeStructure_User_Html_Code.out");
	fout << Source_Code;
	fout.close();
}

void Parser::Process(){
    stack<string> Stack_Of_Label;
    stack<string> Stack_Of_Unprocess;
    int depth = 0, Un_Process = 0;
    string label;
    bool Newline = false, In_Label = false;
    ostringstream osout;
    for(int i = 0; i < Source_Code.size(); i++){
        if(Un_Process > 0){
            if(Parser::Big_Small_Same(Source_Code.substr(i,Stack_Of_Unprocess.top().size())) == Stack_Of_Unprocess.top()){
                if(Source_Code[i] == '<'){
                    osout << endl;
                    for(int j = 1; j <= depth; j++){
                        osout << '\t';
                    }
                }
                Stack_Of_Unprocess.pop();
                Un_Process--;
            }
            osout << Source_Code[i];
        }
        else{
            if(Source_Code[i] == '\n' || Source_Code[i] == '\r' || Newline){
                osout << endl;
                for(int j = 1; j <= depth; j++){
                    osout << '\t';
                }        
                for(;Source_Code[i] == '\n' || Source_Code[i] == '\r' || Source_Code[i] == '\t' || Source_Code[i] == ' '; i++){
                    ;
                }
                i--;
                Newline = false;
            }
            else if(Source_Code[i] == '\'' || Source_Code[i] == '"'){
                osout << Source_Code[i];
                string Chart_Ostring = "";
                Chart_Ostring += Source_Code[i];
                Stack_Of_Unprocess.push(Chart_Ostring);
                Un_Process++;
            }
            else if(Source_Code[i] == '<' && Source_Code.size() - i >= 7 && Parser::Big_Small_Same(Source_Code.substr(i + 1, 6)) == "script"){
                osout << Source_Code[i];
                Stack_Of_Unprocess.push("</script>");
                Un_Process++;
            }
            else if(Source_Code[i] == '<' && Source_Code.size() - i >= 4 && Source_Code.substr(i + 1, 3) == "!--"){
				osout << Source_Code[i];
				Stack_Of_Unprocess.push("-->");
				Un_Process++;
			}
			else if(Source_Code[i] == '<' && Source_Code[i + 1] == '/' && Parser::Big_Small_Same(Source_Code.substr(i + 2, Stack_Of_Label.top().size())) == Stack_Of_Label.top()){
				osout << endl;
				for(int j = 1; j <= depth; j++){
                    osout << '\t';
                }
				osout << Source_Code[i];
				Stack_Of_Label.pop();
				depth--;
			}
			else if(In_Label && Source_Code[i] == '>'){
				osout << Source_Code[i];
				In_Label = false;
				Newline = true;
			}
			else if(Source_Code[i] == '<'){
				bool IsSL = false;
				for(int j = 0; strcmp(ESL, SL[j]) != 0; j++)
					if(Source_Code.size() - i >= strlen(SL[j]) + 1 && strcmp(SL[j] ,Parser::Big_Small_Same(Source_Code.substr(i + 1, strlen(SL[j]))).c_str()) == 0){
						IsSL = true;
						break;
					}
				if(IsSL) osout << Source_Code[i];
				else{
				    int j = i;
					for(; j < Source_Code.size() && Source_Code[j] != ' ' && Source_Code[j] != '>'; j++){
                        ;
                    }	
					Stack_Of_Label.push(Source_Code.substr(i + 1, j - i - 1));
					depth++;
					osout << Source_Code.substr(i, j - i + 1);
					i = j;
					if(Source_Code[j] == '>')
						Newline = true;
					else
						In_Label = true;
				}
			}
			else
				osout << Source_Code[i];
		}
	}
	Source_Code = osout.str();
}