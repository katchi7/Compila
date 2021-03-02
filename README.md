# Grammar

```
PROG          := FUNC PROG 
                 | TYPE_DEF PROG
                 | epsilon 
TYPE_DEF      := typedef ID { TYPE ID  [, TYPE ID , ... ] }

FUNC          := def ID ([ TYPE ID , TYPE ID , ...]) : TYPE {EXPRESSIONS}

EXPRESSIONS   := LOOP 
                | COND 
                | FOR
                | EXP $ EXPRESSIONS 
                | epsilon 
                
TYPE          := int ['[NUMBER]'] 
                | boolean 
                | float ['[NUMBER]'] 
                | char ['[NUMBER]']
                | String
                | ID
                

LOOP          := until ( BOOLOP ) { EXPRESSIONS } 
                | do { EXPRESSIONS } until ( BOOLOP ) 

FOR           := for ( ID in RANGE ) { EXPRESSIONS } 




EXP      := ID EXP' | READ | PRINT

EXP'     := ([ TYPE ID , TYPE ID , ...]) 
            | AFF_DEC 
            | DEC

AFF_DEC  := = VALUE AFF_DEC'

AFF_DEC' := DEC | epsilone

DEC           := : TYPE 


PRINT         := out << VALUE

READ          := in >> ID


RANGE         := ID RANGE'
                | NUMBER to NUMBER  

RANGE'        := to ID 
                | epsilon

COND          := (BOOLOP) -> { EXPRESSIONS } [else -> { EXPRESSIONS }] 


VALUE         := EXPR OP | STR

OP := RELOP EXPR | epsilon
========================================================================
BOOLOP := EXPR RELOP EXPR

RELOP := == | <> | < | > | <= | >= | != | and | or 

EXPR := TERM EXPR'

EXPR'   := ADDOP TERM  |  RELOP TERM | epsilon

ADDOP := + | -

TERM := FACT { MULOP FACT }

MULOP := * | /

FACT := ID ARG | NUMBER [ . NUMBER ] | ( EXPR ) | BOOL | REAL

ARG  := ([ TYPE ID , TYPE ID , ...]) | epsilon


ID            := LETTRE [LETTRE | CHIFFRE] 

NUMBER        := CHIFFRE [ CHIFFRE ] 



BOOL          := true | false 

CHIFFRE       := 0|..|9 

LETTRE        := a|b|..|z|A|..|Z 

STR           := " SIGMA* "
```
