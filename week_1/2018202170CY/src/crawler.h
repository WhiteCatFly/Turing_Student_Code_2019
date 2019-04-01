#ifndef CRAWLER
#define CRAWLER

bool check1(string s);

string get_url(string s);

bool is_url(string s);

void use_wget(string s, string s1);

string get_direction(string s);

bool solve_a_line(char *one_line, string direction);

void bfs(string s);

#endif
