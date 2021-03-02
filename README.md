# Grammar

```
PROG          := FUNC PROG 
                 | TYPE_DEF PROG
                 | epsilon 
TYPE_DEF      := typedef ID { TYPE ID  [, TYPE ID , ... ] }

FUNC          := def ID ([ TYPE ID , TYPE ID , ...]) : TYPE {EXPRESSIONS}

EXPRESSIONS   := LOOP EXPRESSIONS 
                | COND EXPRESSIONS 
                | FOR EXPRESSIONS 
                | EXP $ EXPRESSIONS 
                | epsilon 
                
TYPE          := int ['[NUMBER]'] 
                | boolean 
                | float ['[NUMBER]'] 
                | char ['[NUMBER]']
                | String
                | void
                | ID
                

LOOP          := until ( BOOLOP ) { EXPRESSIONS } 
                | do { EXPRESSIONS } until ( BOOLOP ) 

FOR           := for ( ID in RANGE ) { EXPRESSIONS } 




EXP      := ID EXP' | READ | PRINT | return VALUE | break | continue | exit

EXP'     := ([ID , ID , ...]) 
            | AFF_DEC 
            | DEC

AFF_DEC  := = VALUE AFF_DEC' | . ID AFF

AFF_DEC' := DEC | epsilone

AFF := . ID AFF | = VALUE 

DEC           := : TYPE 


PRINT         := out << VALUE

READ          := in >> ID


RANGE         := BOUND to BOUND

BOUND        := ID [.ID] | NUMBER
COND          := (BOOLOP) -> { EXPRESSIONS } [else -> { EXPRESSIONS }] 


VALUE         := EXPR OP | STR

OP := RELOP EXPR | epsilon
========================================================================
BOOLOP := EXPR

RELOP := == | <> | < | > | <= | >= | != | and | or 

EXPR := TERM EXPR'

EXPR'   := ADDOP TERM | RELOP TERM  | epsilon

ADDOP := + | -

TERM := FACT { MULOP FACT }

MULOP := * | /

FACT := ID ARG | NUMBER [ . NUMBER ] | ( EXPR ) | BOOL  

ARG  := ([ ID , ID , ...])| . ID[. ID ...]  | epsilon


ID            := LETTRE [LETTRE | CHIFFRE] 

NUMBER        := CHIFFRE [ CHIFFRE ] 



BOOL          := true | false 

CHIFFRE       := 0|..|9 

LETTRE        := a|b|..|z|A|..|Z 

STR           := " SIGMA* "
```
