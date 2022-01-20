#include "analyseurlex.h"
#include "analyseursyn.h"

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf(">>> Enter file path : ");
    /*
    char path[100];
    
    scanf("%s",path);
     f= fopen(path,"r");
     */
    f= fopen("./tests/test5.txt","r");
    if(f==NULL){
        printf(">>>File not found!");
        exit(EXIT_FAILURE);
    }
   
    parse();
   
    
    return 0;
}

