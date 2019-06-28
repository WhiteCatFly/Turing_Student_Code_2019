#include "search_engine.h"
#include <iostream>
#include <stdio.h>

SearchEngine master_SEA;

char keyword[2333];

int main(){
    
    FILE *fp = fopen("result.out", "r");
    master_SEA.Initialize();
    master_SEA.LoadData(fp);
    while(1){
        fprintf(stderr, "input word for searching (中文 only) : ");
        scanf("%s", keyword);
        master_SEA.Search(keyword);
        fprintf(stderr, "\n\n\n\n\n");
    }
 //   master.TEST();
}