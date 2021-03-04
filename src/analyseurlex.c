#include "analyseurlex.h"
/*
Erreurs MES_ERR[100]={{ERR_CAR_INC,"Uknown caracter"},{ERR_FICH_VID,"Empty File"},
                    {ERR_ID_LONG,"Long Id"},{PROGRAM_TOKEN,"Expected a Program token"},
                    {ID_ERR,"Expected an Id"},{PV_ERR,"; Expected"},{PT_ERR,". Expected"},{CONST_ERR,"CONST expected"},
                    {EQ_ERR,"Expected ="},{NUM_ERR,"A num expected"},{CONST_VAR_BEGIN_ERR,"Unexpected Token recieved"},
                    {VAR_BEGIN_ERR,"Unexpected Token recieved"},{VAR_ERR,"Expected a var"},{VIR_ERR,", Expected"},
                    {BEGIN_ERR,"Expected Begin token"},{END_ERR,"Expected an End token"},{INST_ERR,"Ecpected Inst token"},
                    {AFF_ERR,"Expected :="},{IF_ERR,"Expected If token"},{THEN_ERR,"Expected Then toke"},{WHILE_ERR,"Expected WHILE token"},
                    {DO_ERR,"Do token expected"},{WRITE_ERR,"Write token expected"},{PO_ERR,"( Expected"},{PF_ERR,") Expected"},
                    {READ_ERR,"Read token expected"},{RELOP_ERR,"got an unexpected token "},{FACT_ERR,"got an unexpected token "}};
*/

char *toLowerCase(char *s)
{
    int i = 0;
    for (i = 0; s[i]; i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

void LireChar()
{
    CHAR_COUR = fgetc(f);
}

OUTPUT *LireMot()
{
    int i = 0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    while ((CHAR_COUR >= 'A' && CHAR_COUR <= 'Z') || (CHAR_COUR >= 'a' && CHAR_COUR <= 'z') || (CHAR_COUR >= '0' && CHAR_COUR <= '9'))
    {
        if (i == TAILLE_OUTPUT)
        {
            output->Code = ERREUR_TOKEN;
            return output;
        }
        output->NOM[i] = CHAR_COUR;
        i++;
        LireChar();
    }
    fseek(f, -1, SEEK_CUR);
    output->NOM[i] = '\0';
    strcpy(output->NOM, toLowerCase(output->NOM));
    if (strcmp(output->NOM, "def") == 0)
    {
        output->Code = DEF_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "out") == 0)
    {
        output->Code = OUT_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "in") == 0)
    {
        output->Code = IN_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "until") == 0)
    {
        output->Code = UNTIL_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "do") == 0)
    {
        output->Code = DO_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "for") == 0)
    {
        output->Code = FOR_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "to") == 0)
    {
        output->Code = TO_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "else") == 0)
    {
        output->Code = ELSE_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "and") == 0)
    {
        output->Code = AND_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "or") == 0)
    {
        output->Code = OR_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "boolean") == 0)
    {
        output->Code = TYPE_BOOL_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "float") == 0)
    {
        output->Code = TYPE_FLOAT_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "int") == 0)
    {
        output->Code = TYPE_INT_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "typedef") == 0)
    {
        output->Code = TYPEDEF_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "char") == 0)
    {
        output->Code = TYPE_CHAR_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "void") == 0)
    {
        output->Code = TYPE_VOID_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "string") == 0)
    {
        output->Code = TYPE_STRING_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "true") == 0)
    {
        output->Code = BOOLEAN_TRUE_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "false") == 0)
    {
        output->Code = BOOLEAN_FALSE_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "return") == 0)
    {
        output->Code = RETURN_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "break") == 0)
    {
        output->Code = BREAK_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "continue") == 0)
    {
        output->Code = CONTINUE_TOKEN;
        return output;
    }
    if (strcmp(output->NOM, "exit") == 0)
    {
        output->Code = EXIT_TOKEN;
        return output;
    }

    output->Code = ID_TOKEN;

    return output;
}
OUTPUT *LireNum()
{
    int i = 0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    while ((CHAR_COUR >= '0' && CHAR_COUR <= '9'))
    {
        if (i == 12)
        {
            output->Code = ERREUR_TOKEN;
            return output;
        }
        output->NOM[i] = CHAR_COUR;
        i++;
        LireChar();
    }
    fseek(f, -1, SEEK_CUR);
    output->NOM[i] = '\0';
    output->Code = NUM_TOKEN;
    return output;
}
OUTPUT *Lire_Car()
{
    int i = 0;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    output->NOM[i] = CHAR_COUR;
    i++;
    switch (CHAR_COUR)
    {
    case '$':
        output->Code = DOLLAR_TOKEN;
        break;

    case '.':
        output->Code = PT_TOKEN;
        break;

    case '+':
        output->Code = PLUS_TOKEN;
        break;

    case '-':
        LireChar();
        if (CHAR_COUR == '>')
        {
            output->Code = THEN_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {
            output->Code = MOINS_TOKEN;
            fseek(f, -1, SEEK_CUR);
        }

        break;

    case '*':
        output->Code = MULT_TOKEN;
        break;

    case '/':
        output->Code = DIV_TOKEN;
        break;

    case ',':
        output->Code = VIR_TOKEN;
        break;

    case ':':

        output->Code = DEC_TOKEN;

        break;

    case '<':
        LireChar();
        if (CHAR_COUR == '=')
        {
            output->Code = INFEG_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else if (CHAR_COUR == '>')
        {
            output->Code = DIFF2_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else if (CHAR_COUR == '<')
        {
            output->Code = WRITE_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {
            output->Code = INF_TOKEN;
            fseek(f, -1, SEEK_CUR);
        }

        break;

    case '>':
        LireChar();
        if (CHAR_COUR == '=')
        {
            output->Code = SUPEG_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else if (CHAR_COUR == '>')
        {
            output->Code = READ_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {
            output->Code = SUP_TOKEN;
            fseek(f, -1, SEEK_CUR);
        }
        break;

    case '(':
        output->Code = PO_TOKEN;
        break;
    case '\'':
        LireChar();
        output->NOM[1] = CHAR_COUR;

        if (CHAR_COUR == '\'')
        {
            output->Code = CHAR_TOKEN;
            output->NOM[2] = CHAR_COUR;
            break;
        }
        LireChar();
        output->NOM[2] = CHAR_COUR;
        if (CHAR_COUR != '\'')
        {
            output->Code = ERREUR_TOKEN;
        }
        else
            output->Code = CHAR_TOKEN;
        break;

    case ')':
        output->Code = PF_TOKEN;
        break;
    case '{':
        output->Code = ACO_TOKEN;
        break;
    case '}':
        output->Code = ACF_TOKEN;
        break;
    case '[':
        output->Code = CRO_TOKEN;

        break;
    case ']':
        output->Code = CRF_TOKEN;
        break;
    case '"':
        output->Code = STR_TOKEN;
        break;
    case '=':
        LireChar();
        if (CHAR_COUR == '=')
        {
            output->Code = EQ_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {
            fseek(f, -1, SEEK_CUR);
            output->Code = AFF_TOKEN;
        }
        break;
    case '!':
        LireChar();
        if (CHAR_COUR == '=')
        {
            output->Code = DIFF_TOKEN;
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {
            fseek(f, -1, SEEK_CUR);
            output->Code = ERREUR_TOKEN;
        }

        break;
    case EOF:
        output->Code = FIN_TOKEN;
        break;
    default:
        output->Code = ERREUR_TOKEN;
        break;
    }
    output->NOM[i] = '\0';
    return output;
}

int CommentSymb()
{
    int i=0;
    while (CHAR_COUR == '"' )
    {
          
        LireChar();
        i++;
    }
    if(i<3 || CHAR_COUR==EOF  ){
        
        fseek(f,-i,SEEK_CUR);
        return 0;
    }
    
    return 1;
}

void LireComment()
{
    
    int i=0;
    while ( CHAR_COUR != EOF)
    {
        printf("CHAR ---> %c \n" ,CHAR_COUR);
        if(CommentSymb()){
            break;
        }
        LireChar();
        i++;
    }
}

//Passer les separateurs et les commentaires
void passer()
{
    while (CHAR_COUR == ' ' || CHAR_COUR == '\t' || CHAR_COUR == '\n' || CHAR_COUR == '#' )
    { //Passer les separateurs

        
        if (CHAR_COUR == '#')
        { //Ligne de commentaire
            while (CHAR_COUR != '\n' && CHAR_COUR != EOF)
            {
                LireChar();
            }
        }/*
        else
        {
            
            if (CHAR_COUR == '"')
            {
             
                if (CommentSymb())
                {
                       
                    LireComment();
                }
                else
                {
                    break;
                }
            }
        }*/
        LireChar();
        
    }
    if (CHAR_COUR == EOF)
    {
        //Erreur(ERR_FICH_VID);
    }
}

/*

void Erreur(CODES_ERREURS ERR){
    int ind_err = ERR;
    printf( "Erreur numéro %d, %s\n", ind_err,MES_ERR[ERR].mes);
    exit(1);
}

*/
OUTPUT *Lir_STR()
{
    int i = 1;
    OUTPUT *output = malloc(sizeof(OUTPUT));
    output->NOM[0] = CHAR_COUR;
    LireChar();
    //"Hello /"Aabane/" test "
    while (CHAR_COUR != '"' && CHAR_COUR != EOF)
    {

        if (i == TAILLE_OUTPUT - 1)
        {

            output->Code = ERREUR_TOKEN;
            return output;
        }
        if (CHAR_COUR == '\\')
        {
            LireChar();
            output->NOM[i] = CHAR_COUR;
            i++;
        }
        else
        {

            output->NOM[i] = CHAR_COUR;
            i++;
        }
        LireChar();
    }
    if (CHAR_COUR == EOF)
        output->Code = FIN_TOKEN;
    else
    {
        output->Code = TXT_TOKEN;
        output->NOM[i] = '"';
    }
    return output;
}

OUTPUT *analyseurLexical()
{
    OUTPUT *output = NULL;
    while (output == NULL)
    {
        //Separateur
        LireChar();
        passer();
        //MOT
        if ((CHAR_COUR >= 'A' && CHAR_COUR <= 'Z') || ((CHAR_COUR >= 'a' && CHAR_COUR <= 'z')))
        {
            output = LireMot();
        }
        else
        {
            //Numero
            if (CHAR_COUR >= '0' && CHAR_COUR <= '9')
            {
                output = LireNum();
            }
            else
            {
                if (CHAR_COUR == '"')
                {

                    output = Lir_STR();
                }
                else
                    output = Lire_Car();
            }
        }
    }
    return output;
}
