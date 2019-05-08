#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <malloc.h>
#include <cstring>
#include <cstdio>

#include "parser.h"
using std::string;

void Parser::out(std::ostream &out_)
{
    if (father_ != NULL)
    out_ << "head:" << head_ << "\n\tfather:" << (*father_).head_ << "\n\tbody:" << body_ << "\n" << std::endl;
    else
    {
        out_ << "head:" << head_ << "\n\tfather:NULL" << "\n\tbody:" << body_ << "\n" << std::endl;
    }
    
    for(int i = 0; i < son_.size(); i++)
    {
        (*son_[i]).out(out_);
    }
}

bool is_false(int place, string &str)
{
    return str[place + 1] == '!';
}

bool is_body(int place, string &str)
{
    bool flag1, flag2;
    for (int i = place - 1; i >= 0; i--)
    {
        if(str[i] == '<' || str[i] == '>')
        {
            flag1 = (str[i] == '>');
            break;
        }
    }
    for (int i = place + 1; i < str.length(); i++)
    {
        if(str[i] == '<' || str[i] == '>')
        {
            flag2 = (str[i] == '<');
            break;
        } 
    }
    return flag1 & flag2;
}

int get_right(int place, string &str)
{
    int cnt = 1;
    while (place < str.length() - 1)
    {
        place++;
        if (str[place] == '<') cnt++;
        if (str[place] == '>') cnt--;
        if (cnt == 0) break;
    }
    if(cnt) return str.length();
    return place;
}

void Parser::get_father(Parser* father)
{
    father_ = father;
}

void Parser::get_son(Parser* son)
{
    son_.push_back(son);
}

void Parser::get_body(string &body)
{
    body_ += body;
}

void Parser::get_head(string &head)
{
    head_ = head;
}

Parser* build_from_string(string &text)
{
    std::stack<Parser*> stack_;
    Parser* Root = NULL;
    for (int now_place = 0 ; now_place < text.length(); now_place++)
    {
        if (text[now_place] == '<')
        {
            if (is_false(now_place, text) == true)
            {
                int right = get_right(now_place, text);
                if (right == text.length()) break;
                now_place = right;
            }
            else
            {
                int right = get_right(now_place, text); 
                if (right == text.length()) break;
                if (text[now_place + 1] == '/')
                {
                    if (stack_.empty() == false)
                    stack_.pop();
                    now_place = right;
                }
                else
                {
                    Parser* new_node = new Parser();
                    if (!stack_.empty())
                    {
                        Parser &top_ = *stack_.top();
                        (*new_node).get_father(&top_);
                        top_.get_son(new_node);
                    }
                    string head;
                    for (int i = now_place + 1; i < right; i++)
                    {
                        head += text[i];
                    }
                    new_node -> get_head(head);
                    if (text[right - 1] != '/')
                    {
                        if (stack_.empty() == true) Root = new_node;
                        stack_.push(new_node);
                    }
                    now_place = right;
                }
            }
        }
        else
        {
            int right = text.length();
            for (int i = now_place; i < text.length(); i++)
            {
                if (text[i] == '<')
                {
                    right = i;
                    break;
                }
            }
            if (right == text.length()) break;
            string body;
            for (int i = now_place; i < right; i++)
            body += text[i];
            if (!stack_.empty())
            {
                Parser &top_ = *stack_.top();
                top_.get_body(body);
            }
            now_place = right - 1;
        }
    }
    return Root;
}

Parser* build_from_stream(std::istream &in_)
{
    string text;
    char ch;
    while ((ch = in_.get()) != EOF)
    {
        text += ch;
    }
    return build_from_string(text);
}

Parser* Parser::parser_title()
{
    string head = this -> head();
    if (head.find("title", 0) != string::npos)
    {
        return this;
    }
    for (int i = 0 ; i < son_.size(); i++)
    {
        Parser* ret = son_[i] -> parser_title();
        if (ret != NULL) return ret;
    }
    return NULL;
}

void Parser::parser_link(std::ostream &out)
{
    int pos = head_.find("href", 0);
    if (pos != string::npos)
    {
        // out << head_ << ":\n";
        int place = pos;
        while (head_[place] != '=') place++;
        place ++;
        while (head_[place] == ' ' || head_[place] == '\t' || head_[place] == '\n') place++;
        bool flag1 = false, flag2 = false;
        if (head_[place] == '\'') flag1 = true, place ++;
        else if (head_[place] == '\"') flag2 = true, place ++;
        if (flag1 | flag2)
        {
            char begin = head_[place - 1];
            while (head_[place] != begin && place < head_.length())
            {
                out << head_[place];
                place++;
            }
            out << std::endl;
        }
        else
        {
            while (head_[place] != '\n' && head_[place] != ' ' && head_[place] != '\t' && head_[place] != '>' && place < head_.length())
            {
                out << head_[place];
                place++;
            }
            out << std::endl;
        }
    }
    for (int i = 0; i < son_.size(); i++)
    {
        (*son_[i]).parser_link(out);
    }
}

void Parser::parser_body(std::ostream &out)
{
    out << body_ << std::endl;
    for (int i = 0; i < son_.size(); i++)
    {
        (*son_[i]).parser_body(out);
    }
}

void Parser::free()
{
    for (int i = 0; i < son_.size(); i++)
    {
        (*son_[i]).free();
    }
}