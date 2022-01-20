#include "analyseurlex.h"
#include "analyseursyn.h"

//Next token
void Sym_Suiv(){
    Sym_Cour = analyseurLexical();
}

void parse(){
    
    Sym_Suiv();
    PROG();
    if(ERROR){
        printf("\033[0;31m\nParsing failed\n\033[0;37m");
    }else{
        printf("\033[0;32m\nParsing succeed\n\033[0;37m");
    }
}

//Function that test id a symbole equals the expected token 
void Test_Symbole(CODES_LEX cl ){
    
    if(Sym_Cour->Code == cl){
        Sym_Suiv();
    }
    else{
        
     Erreur(cl );}
}
//All the program
void PROG(){
    
    if(Sym_Cour->Code == DEF_TOKEN){
        
        //Function
        
        FUNC();
        
        PROG();
    }
    else if(Sym_Cour->Code==TYPEDEF_TOKEN){
        //Type Def
        TYPE_DEF();
        PROG();
    }
    else{
        if(Sym_Cour->Code != FIN_TOKEN ) {
            Erreur(FIN_TOKEN);
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
        Erreur(FIN_TOKEN);
        
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
        Erreur(FIN_TOKEN);
        return;
    }
    Test_Symbole(ACF_TOKEN);
}
//Checks expressions
void EXPRESSIONS(){
    if(Sym_Cour->Code == DO_TOKEN || Sym_Cour->Code == UNTIL_TOKEN ){  LOOP();EXPRESSIONS();}
    else if(Sym_Cour->Code == PO_TOKEN ){  COND();EXPRESSIONS();}
    else if(Sym_Cour->Code == FOR_TOKEN ){ FOR();EXPRESSIONS();}
    else if( Sym_Cour->Code == ID_TOKEN || Sym_Cour->Code == IN_TOKEN 
    || Sym_Cour->Code == OUT_TOKEN || Sym_Cour->Code == RETURN_TOKEN 
    || Sym_Cour->Code == BREAK_TOKEN || Sym_Cour->Code == CONTINUE_TOKEN 
    ||  Sym_Cour->Code == EXIT_TOKEN ){ 
        
        EXP();
        
        Test_Symbole(DOLLAR_TOKEN);
        
        EXPRESSIONS();
        
        
         
        }
}
//Checks typing
void TYPE(){
    //int
    if(Sym_Cour->Code == TYPE_INT_TOKEN ) {
        
        Test_Symbole(TYPE_INT_TOKEN);
        //array
        while(Sym_Cour->Code == CRO_TOKEN  && Sym_Cour->Code != FIN_TOKEN ){
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
        while(Sym_Cour->Code == CRO_TOKEN  && Sym_Cour->Code != FIN_TOKEN ){
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
        while(Sym_Cour->Code == CRO_TOKEN  && Sym_Cour->Code != FIN_TOKEN ){
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
    //String
    if(Sym_Cour->Code == TYPE_STRING_TOKEN ) {
        Test_Symbole(TYPE_STRING_TOKEN);
        return;
    }
    //VOID
    if(Sym_Cour->Code == TYPE_VOID_TOKEN ) {
        Test_Symbole(TYPE_VOID_TOKEN);
        return;
    }
    Test_Symbole(ID_TOKEN);

}
//Boucles
void LOOP(){
    //until(BOOLOP){EXPRESSIONS}
    if(Sym_Cour->Code == UNTIL_TOKEN){
        Test_Symbole(UNTIL_TOKEN);
        Test_Symbole(PO_TOKEN);
        BOOLOP();
        Test_Symbole(PF_TOKEN);
        Test_Symbole(ACO_TOKEN);
        EXPRESSIONS();
        Test_Symbole(ACF_TOKEN);
    }
    else{
        Test_Symbole(DO_TOKEN);
        Test_Symbole(ACO_TOKEN);
        EXPRESSIONS();
        Test_Symbole(ACF_TOKEN);
        Test_Symbole(UNTIL_TOKEN);
        Test_Symbole(PO_TOKEN);
        BOOLOP();
        Test_Symbole(PF_TOKEN);
    }
    
}
void COND(){
    //(BOOLOP)->{EXPRESSIONS}[else->{EXPRESSIONS}]
    
    Test_Symbole(PO_TOKEN);
    
    BOOLOP();
    Test_Symbole(PF_TOKEN);
    
    Test_Symbole(THEN_TOKEN);
    Test_Symbole(ACO_TOKEN);
    EXPRESSIONS();
    Test_Symbole(ACF_TOKEN);
    //else
    if( Sym_Cour->Code == ELSE_TOKEN ){
        Test_Symbole(ELSE_TOKEN);
        Test_Symbole(THEN_TOKEN);
        Test_Symbole(ACO_TOKEN);
        EXPRESSIONS();
        Test_Symbole(ACF_TOKEN);
    }
}
void FOR(){
    Test_Symbole(FOR_TOKEN);
    Test_Symbole(PO_TOKEN);
    Test_Symbole(ID_TOKEN);
    Test_Symbole(IN_TOKEN);
    RANGE();
    Test_Symbole(PF_TOKEN);
    Test_Symbole(ACO_TOKEN);
    EXPRESSIONS();
    Test_Symbole(ACF_TOKEN);
}
void EXP(){
    
    
    if(Sym_Cour->Code == ID_TOKEN){
        
        Test_Symbole(ID_TOKEN);
        
        EXP_();
       
        return;
    }if(Sym_Cour->Code == IN_TOKEN){
        READ();
        return;
    }
    if(Sym_Cour->Code == RETURN_TOKEN){
        
        Test_Symbole(RETURN_TOKEN);
        VALUE();
        return;
    }
    if( Sym_Cour->Code == CONTINUE_TOKEN ){
        Test_Symbole(CONTINUE_TOKEN);
        return;
    }
    if( Sym_Cour->Code == BREAK_TOKEN ){
        Test_Symbole(BREAK_TOKEN);
        return;
    }
    if( Sym_Cour->Code == EXIT_TOKEN ){
        Test_Symbole(EXIT_TOKEN);
        return;
    }
    PRINT();
}
void EXP_(){
    
    if(Sym_Cour->Code == PO_TOKEN ) {
        Test_Symbole(PO_TOKEN);
        int i=0;
        while ( Sym_Cour->Code != PF_TOKEN &&  Sym_Cour->Code != FIN_TOKEN )
        {
            if(i!=0){
                Test_Symbole(VIR_TOKEN);
                
            }
            VALUE();
            i++;
        }
        if(Sym_Cour->Code == FIN_TOKEN){
            return;
        }
        Test_Symbole(PF_TOKEN);
        return;
    }
    if(Sym_Cour->Code == AFF_TOKEN || Sym_Cour->Code == PT_TOKEN  || Sym_Cour->Code ==  CRO_TOKEN ){
        
        
        AFF_DEC();
        
         
        return;
    }
    if(Sym_Cour->Code == DEC_TOKEN){
        DEC();
    }
}

void AFF_DEC(){
    if(Sym_Cour->Code == AFF_TOKEN){
        
        Test_Symbole(AFF_TOKEN);
        
        VALUE();
        
        AFF_DEC_();
        return;
        
    }
    if(Sym_Cour->Code == CRO_TOKEN){
        
        Test_Symbole(CRO_TOKEN);
        
        EXPR();
        OP();
        Test_Symbole(CRF_TOKEN);
        
        AFF();
    }else{
        Test_Symbole(PT_TOKEN);
        Test_Symbole(ID_TOKEN);
        AFF();
    }
    
}

void AFF(){
    
    if(Sym_Cour->Code == AFF_TOKEN){
        
        
        Test_Symbole(AFF_TOKEN);
        
        VALUE();
        
        return;
    }
    if(Sym_Cour->Code == CRO_TOKEN){
        Test_Symbole(CRO_TOKEN);
        EXPR();
        OP();
        Test_Symbole(CRF_TOKEN);
        AFF();
        return;
    }
    else{
        Test_Symbole(PT_TOKEN);
        Test_Symbole(ID_TOKEN);
        AFF();
    }
}

void AFF_DEC_(){
    if(Sym_Cour->Code == DEC_TOKEN){
        DEC();
        return;
    }

}

void DEC(){
    Test_Symbole(DEC_TOKEN);
    TYPE();
}

void READ(){
    Test_Symbole(IN_TOKEN);
    Test_Symbole(READ_TOKEN);
    Test_Symbole(ID_TOKEN);
    ARG_();
}
void PRINT(){
    Test_Symbole(OUT_TOKEN);
    Test_Symbole(WRITE_TOKEN);
    VALUE();
}
void RANGE(){
    
     BOUND();
     if(Sym_Cour->Code == TO_TOKEN){
        Test_Symbole(TO_TOKEN);
        BOUND();
    
     }
     
}

void BOUND(){

    if (Sym_Cour->Code == ID_TOKEN){
        Test_Symbole(ID_TOKEN);
        while(Sym_Cour->Code == PT_TOKEN){
            Test_Symbole(PT_TOKEN);
            Test_Symbole(ID_TOKEN);
        }
        return;
    }
    if(Sym_Cour->Code == NUM_TOKEN ){
        Test_Symbole(NUM_TOKEN);
        return;
    }

}

void VALUE(){
    
    if(Sym_Cour->Code == TXT_TOKEN){
        STR();
        return;
    }else if(Sym_Cour->Code == CHAR_TOKEN){
        
        Test_Symbole(CHAR_TOKEN);
        return;
        
    }
    else{
        
        EXPR();
        
        OP();
        
    }
}
void OP(){
    if(isRELOP()){
        Sym_Suiv();
        EXPR();
    }
}


int isRELOP(){
    return (Sym_Cour->Code == EQ_TOKEN || Sym_Cour->Code == DIFF_TOKEN 
    || Sym_Cour->Code == DIFF2_TOKEN || Sym_Cour->Code == SUP_TOKEN 
    || Sym_Cour->Code == INF_TOKEN || Sym_Cour->Code == SUPEG_TOKEN 
    || Sym_Cour->Code == INFEG_TOKEN || Sym_Cour->Code == AND_TOKEN 
    || Sym_Cour->Code == OR_TOKEN );
}


void EXPR(){
    
    TERM();
    
    EXPR_();
}
void TERM(){
    FACT();
    
    if(isMULOP()){
        Sym_Suiv();
        FACT();
    }
}
int isMULOP(){
    return (Sym_Cour->Code == MULT_TOKEN || Sym_Cour->Code == DIV_TOKEN );
}
void EXPR_(){
    
    if(isADDOP() || isRELOP()){
        Sym_Suiv();
        TERM();
    }
}
int isADDOP(){
    return (Sym_Cour->Code == MOINS_TOKEN || Sym_Cour->Code == PLUS_TOKEN );
}
void FACT(){

    
    if(Sym_Cour->Code == ID_TOKEN){

        Test_Symbole(ID_TOKEN);
        
        ARG();
        
        return;
    }
    if(Sym_Cour->Code == NUM_TOKEN){
        Test_Symbole(NUM_TOKEN);
        if(Sym_Cour->Code == PT_TOKEN){
            Test_Symbole(PT_TOKEN);
            Test_Symbole(NUM_TOKEN);
        }

        return;
    }
    if(Sym_Cour -> Code == PO_TOKEN ){
        Test_Symbole(PO_TOKEN);
        EXPR();
        Test_Symbole(PF_TOKEN);
        return;
    }
    if(Sym_Cour -> Code == CHAR_TOKEN ){
        Test_Symbole(CHAR_TOKEN);
        
        return;
    }
    if(isBOOL()){
        Sym_Suiv();
        return;
    }
    Erreur(ID_TOKEN);

}

int isBOOL(){
    return (Sym_Cour->Code == BOOLEAN_TRUE_TOKEN || Sym_Cour->Code == BOOLEAN_FALSE_TOKEN);
}

void BOOLOP(){
    
    EXPR();
    /*
    if(isRELOP){
        
        Sym_Suiv();
        
        EXPR();
        
    }
    else{
        Test_Symbole(EQ_TOKEN);
    }
    */
        
}
void ARG(){
    if(Sym_Cour->Code == PO_TOKEN){
        Test_Symbole(PO_TOKEN);
        int i=0;
        while ( Sym_Cour->Code != PF_TOKEN && Sym_Cour ->Code != FIN_TOKEN )
        {
            if(i!=0) Test_Symbole(VIR_TOKEN);
            
            Test_Symbole(ID_TOKEN);
            i++;
        }
        if(Sym_Cour->Code == FIN_TOKEN) return;

        Test_Symbole(PF_TOKEN);
        ARG_(); 
        return;
            
    }
        
    if( Sym_Cour->Code == PT_TOKEN ){
            
            Test_Symbole(PT_TOKEN);
            Test_Symbole(ID_TOKEN);
            ARG_();
            return;
    }
    if(Sym_Cour->Code == CRO_TOKEN ){
        
        Test_Symbole(CRO_TOKEN);
        EXPR();
        OP();
        Test_Symbole(CRF_TOKEN);
        if(Sym_Cour->Code == CRO_TOKEN || Sym_Cour->Code == PT_TOKEN )
        ARG_();
        
        
        return;
    }
    
}

void ARG_(){
    if( Sym_Cour->Code == PT_TOKEN ){
            
        Test_Symbole(PT_TOKEN);
        Test_Symbole(ID_TOKEN);
        ARG_();
        
    }if(Sym_Cour->Code == CRO_TOKEN ){
        
        Test_Symbole(CRO_TOKEN);
        EXPR();
        OP();
        Test_Symbole(CRF_TOKEN);
        ARG_();
        return;
    }
}

void STR(){
    
    fprintf(stderr,"STR : %s " , Sym_Cour->NOM);
    Test_Symbole(TXT_TOKEN);
}