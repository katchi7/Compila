# Grammar

```
PROG          := FUNC PROG 
                 | TYPE_DEF PROG
                 | epsilon 

FUNC          := def ID ([ TYPE ID , TYPE ID , ...]) : type {EXPRESSIONS}

PRINT         := out << VALUE

READ          := in >> ID


EXPRESSIONS   := LOOP 
                | COND 
                | EXP $ EXPRESSIONS 
                | epsilon 
                

TYPE_DEF      := typdef ID { TYPE ID  [, TYPE ID , ... ] }

EXP      := ID EXP'

EXP'     := ([ TYPE ID , TYPE ID , ...]) 
            | AFF_DEC 
            | DEC

AFF_DEC  := = VALUE AFF_DEC'

AFF_DEC' := DEC | epsilone

DEC           := : TYPE 

LOOP          := until ( BOOLOP ) { EXPRESSIONS } 
                | do { EXPRESSIONS } until ( BOOLOP ) 

FOR           := for ( ID in RANGE ) { EXPRESSIONS } 

RANGE         := ID RANGE'
                | NUMBER to NUMBER  

RANGE'        := to ID 
                | epsilon

COND          := (BOOLOP) -> { EXPRESSIONS } [else -> { EXPRESSIONS }] 


VALUE         := EXPR OP | STR

OP := RELOP EXPR | epsilon

BOOLOP := EXPR RELOP EXPR

RELOP := == | <> | < | > | <= | >= | != | and | or 

EXPR := TERM EXP'

EXP'   := ADDOP TERM  |  RELOP TERM | epsilon

ADDOP := + | -

TERM := FACT { MULOP FACT }

MULOP := * | /

FACT := ID ARG | NUMBER | ( EXPR ) | BOOL | REAL

ARG  := ([ TYPE ID , TYPE ID , ...]) | epsilon


ID            := LETTRE [LETTRE | CHIFFRE] 

NUMBER        := CHIFFRE [ CHIFFRE ] 

REAL          := NUMBER . NUMBER

CHIFFRE       := 0|..|9 

LETTRE        := a|b|..|z|A|..|Z 

TYPE          := int ['[NUMBER]'] 
                | boolean 
                | float ['[NUMBER]'] 
                | char ['[NUMBER]']
                | String
                | ID
STR           := " SIGMA* "
```
