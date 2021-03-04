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
    /*
    while (CHAR_COUR != EOF)
    {
        OUTPUT *out = analyseurLexical();
        printf("Token %d : %s ---->>>%s \n",out->Code,REVERSE_ENUM[out->Code],out->NOM);
    }
    */
    parse();
    /*
    if (Sym_Cour->Code ==FIN_TOKEN) printf("BRAVO: le programme est Correcte");
    else printf ("PAS BRAVO: fin de programme erronée! ");
*/
    
    return 0;
}

