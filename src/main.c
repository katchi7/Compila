#include "analyseurlex.h"

char REVERSE_ENUM [100][50]={"DEF_TOKEN","DEC_TOKEN","OUT_TOKEN","IN_TOKEN","WRITE_TOKEN","READ_TOKEN","TYPEDEF_TOKEN","UNTIL_TOKEN","DO_TOKEN","ACO_TOKEN","ACF_TOKEN",
   "DOLLAR_TOKEN","PT_TOKEN","PLUS_TOKEN","MOINS_TOKEN","MULT_TOKEN","DIV_TOKEN","VIR_TOKEN","EQ_TOKEN","AFF_TOKEN","INF_TOKEN","INFEG_TOKEN","SUP_TOKEN","SUPEG_TOKEN",
    "DIFF_TOKEN","DIFF2_TOKEN","PO_TOKEN","PF_TOKEN","FOR_TOKEN","ID_TOKEN","NUM_TOKEN","CRO_TOKEN","CRF_TOKEN","TO_TOKEN","THEN_TOKEN","ELSE_TOKEN","AND_TOKEN","OR_TOKEN","TYPE_BOOL_TOKEN","TYPE_FLOAT_TOKEN","TYPE_CHAR_TOKEN","TYPE_INT_TOKEN","TYPE_STRING_TOKEN","FIN_TOKEN","STR_TOKEN","ERREUR_TOKEN"};
int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    printf(">>> Enter file path : ");
    /*
    char path[100];
    
    scanf("%s",path);
     f= fopen(path,"r");
     */
    f= fopen("./tests/test1.txt","r");
    if(f==NULL){
        printf(">>>File not found!");
        exit(EXIT_FAILURE);
    }
    
    while (CHAR_COUR != EOF)
    {
        OUTPUT *out = analyseurLexical();
        printf("Token %d : %s ---->>>%s \n",out->Code,REVERSE_ENUM[out->Code],out->NOM);
    }
    /*
    if (Sym_Cour->Code ==FIN_TOKEN) printf("BRAVO: le programme est Correcte");
    else printf ("PAS BRAVO: fin de programme erronée! ");
*/
    
    return 0;
}

