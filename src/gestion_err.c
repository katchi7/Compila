#include "gestion_err.h"

void Erreur( CODES_LEX cl ){
    ERROR = 1;
    fprintf(stderr,"Error while parsing  expected \"%s\"  found \"%s\"  \n",REVERSE_ENUM[cl],Sym_Cour->NOM);
}
