#include "analyseurlex.h"
//Next token
void Sym_Suiv(){
    Sym_Cour = analyseurLexical();
}

//Error token : TODO Make it print errors depending on error codes
Erreur(){
    printf("Error while parsing\n");
}

//Function that test id a symbole equals the expected token 
void Test_Symbole(CODES_LEX cl){
    if(Sym_Cour->Code == cl){
        Sym_Suiv();
    }
    else{
     Erreur();}
}
//All the program
void Prog(){
    if(Sym_Cour->Code == DEF_TOKEN){
        //Function
        FUNC();
        Prog();
    }
    else if(Sym_Cour->Code==TYPEDEF_TOKEN){
        //Type Def
        TYPE_DEF();
        PROG();
    }
    else{
        if(Sym_Cour->Code != FIN_TOKEN ) {
            Erreur();
        }
    }
}
//Functions
void FUNC(){
    // Declaring a function
    Test_Symbole(DEF_TOKEN);
    Test_Symbole(ID_TOKEN);
    Test_Symbole(PO_TOKEN);
    int i=0;
    while (Sym_Cour->Code != PF_TOKEN && Sym_Cour->Code != FIN_TOKEN )
    {
        if(i!=0){
            Test_Symbole(VIR_TOKEN);
        }
        TYPE();
        Test_Symbole(ID_TOKEN);
        i=1;
    }
    //Found EOF token before )
    if(Sym_Cour->Code == FIN_TOKEN){
        Erreur();
        return;
    }
    Test_Symbole(PF_TOKEN);
    Test_Symbole(DEC_TOKEN);
    TYPE();
    Test_Symbole(ACO_TOKEN);
    EXPRESSIONS();
    Test_Symbole(ACF_TOKEN);

    
}
//typdef
void TYPE_DEF(){
    Test_Symbole(TYPEDEF_TOKEN);
    Test_Symbole(ID_TOKEN);
    Test_Symbole(ACO_TOKEN);
    int i=0;
    do
    {
        if(i!=0) Test_Symbole(VIR_TOKEN);
        TYPE();
        Test_Symbole(ID_TOKEN);
        i=1;
    } while (Sym_Cour->Code != ACF_TOKEN && Sym_Cour->Code != FIN_TOKEN );
    
    if(Sym_Cour->Code == FIN_TOKEN){
        Erreur();
        return;
    }
    Test_Symbole(ACF_TOKEN);
}
//Checks expressions
void EXPRESSIONS(){
    if(Sym_Cour->Code == DO_TOKEN || Sym_Cour->Code == UNTIL_TOKEN ) LOOP();
    else if(Sym_Cour->Code == PO_TOKEN ) COND();
    else if(Sym_Cour->Code == FOR_TOKEN ) FOR();
    else if( Sym_Cour->Code == ID_TOKEN || Sym_Cour->Code == IN_TOKEN || Sym_Cour->Code == OUT_TOKEN ){ 
        EXP();
        EXPRESSIONS();
        }
}
//Checks typing
void TYPE(){
    //int
    if(Sym_Cour->Code == TYPE_INT_TOKEN ) {
        
        Test_Symbole(TYPE_INT_TOKEN);
        //array
        if(Sym_Cour->Code == CRO_TOKEN){
            Test_Symbole(CRO_TOKEN);
            Test_Symbole(NUM_TOKEN);
            Test_Symbole(CRF_TOKEN);
        }
        return;
    }
    //Float
    if(Sym_Cour->Code == TYPE_FLOAT_TOKEN ) {
        
        Test_Symbole(TYPE_FLOAT_TOKEN);
        //array
        if(Sym_Cour->Code == CRO_TOKEN){
            Test_Symbole(CRO_TOKEN);
            Test_Symbole(NUM_TOKEN);
            Test_Symbole(CRF_TOKEN);
        }
        return;
    }
    //CHAR
    if(Sym_Cour->Code == TYPE_CHAR_TOKEN ) {
        
        Test_Symbole(TYPE_CHAR_TOKEN);
        //array
        if(Sym_Cour->Code == CRO_TOKEN){
            Test_Symbole(CRO_TOKEN);
            Test_Symbole(NUM_TOKEN);
            Test_Symbole(CRF_TOKEN);
        }
        return;
    }
    //BOOLEAN
    if(Sym_Cour->Code == TYPE_BOOL_TOKEN ) {
        Test_Symbole(TYPE_BOOL_TOKEN);
        return;
    }

    if(Sym_Cour->Code == TYPE_STRING_TOKEN ) {
        Test_Symbole(TYPE_STRING_TOKEN);
        return;
    }
    Test_Symbole(ID_TOKEN);

}