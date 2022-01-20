#ifndef N
#define N
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TAILLE_OUTPUT 255
//Structures

typedef enum{
    DEF_TOKEN,DEC_TOKEN,OUT_TOKEN,IN_TOKEN,WRITE_TOKEN,READ_TOKEN,TYPEDEF_TOKEN,UNTIL_TOKEN,DO_TOKEN,ACO_TOKEN,ACF_TOKEN,
    DOLLAR_TOKEN,PT_TOKEN,PLUS_TOKEN,MOINS_TOKEN,MULT_TOKEN,DIV_TOKEN,VIR_TOKEN,EQ_TOKEN,AFF_TOKEN,INF_TOKEN,INFEG_TOKEN,SUP_TOKEN,SUPEG_TOKEN,
    DIFF_TOKEN,DIFF2_TOKEN,PO_TOKEN,PF_TOKEN,FOR_TOKEN,ID_TOKEN,NUM_TOKEN,CRO_TOKEN,CRF_TOKEN,TO_TOKEN,THEN_TOKEN,ELSE_TOKEN,AND_TOKEN,OR_TOKEN,
    TYPE_BOOL_TOKEN,TYPE_FLOAT_TOKEN,TYPE_CHAR_TOKEN,TYPE_INT_TOKEN,TYPE_STRING_TOKEN,TYPE_VOID_TOKEN,FIN_TOKEN,STR_TOKEN,BOOLEAN_TRUE_TOKEN,BOOLEAN_FALSE_TOKEN,
    BREAK_TOKEN,CONTINUE_TOKEN,RETURN_TOKEN,EXIT_TOKEN,TXT_TOKEN,CHAR_TOKEN,ERREUR_TOKEN,
}CODES_LEX;
typedef struct {
    CODES_LEX Code;
    char NOM[TAILLE_OUTPUT];
}OUTPUT;
int ERROR;
//Variables globales
char CHAR_COUR;
OUTPUT *Sym_Cour;
FILE *f;
char REVERSE_ENUM [100][50];


//PROTYPES
char *toLowerCase(char *s);
void LireChar();
OUTPUT* LireMot();
OUTPUT* LireNum();
OUTPUT* Lire_Car();
void passer();
OUTPUT* analyseurLexical();
void PROGRAM();
OUTPUT *Lir_STR();
void Erreur( CODES_LEX cl );

#endif
