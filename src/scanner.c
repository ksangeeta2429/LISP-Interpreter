/*********************************************************************************
 ** FILENAME        :  scanner.c
 **
 ** DESCRIPTION     :  This file defines the functions to build a lexical analyzer 
 **                    which prints the atoms and parentheses in the input file                   
 ** Revision History:
 ** DATE           NAME                REASON
 ** ------------------------------------------------------------------------------
 ** Jan 18 2016    Sangeeta Kumari     PL Project
 ** Jan 26 2016
 ********************************************************************************/

#include"header.h"             

 /*********************************************************************************
 ** EXTERN VARIABLES
 ********************************************************************************/
extern char **tokenArray;
extern char **typeArray;
extern char *data;
extern char current[MAX];
extern int next = 0;

/*********************************************************************************
 ** FUNCTION NAME : init
 **
 ** DESCRIPTION   : gets the first token
 **
 ** RETURNS       : NIL
 ********************************************************************************/
void init()
{
   strcpy(current,getNextToken(tokenArray));
}

/*********************************************************************************
 ** FUNCTION NAME : MoveToNext
 **
 ** DESCRIPTION   : moves to the next token
 **
 ** RETURNS       : NIL
 ********************************************************************************/
void MoveToNext()
{
   strcpy(current,getNextToken(tokenArray));
}

/*********************************************************************************
 ** FUNCTION NAME : GetCurrent
 **
 ** DESCRIPTION   : returns the current token
 **
 ** RETURNS       : current token
 ********************************************************************************/
char * GetCurrent()
{
   return current;
}

/*********************************************************************************
 ** FUNCTION NAME : getNextToken
 **
 ** DESCRIPTION   : returns the next token
 **
 ** RETURNS       : next token
 ********************************************************************************/
char * getNextToken(char **tokenArray)
{
   next = next+1;
   return (tokenArray[next-1]);
}

char * getType(char **typeArray)
{
   return (typeArray[next-1]);
}
/*********************************************************************************
 ** FUNCTION NAME : saveTokens
 **
 ** DESCRIPTION   : saves the tokens in an array
 **
 ** RETURNS       : NIL
 ********************************************************************************/
void saveTokens(char **tokenArray, char *words, int *arrayLen)
{
   int i = 0, j = 0;
   int start = 0;         /* Determines position in the line from where we need to start scanning again */
   int total = 0;
   char *type;            /* Type has 5 possible values: OP(Open Parentheses) CP(Closing Parentheses) L(Literal) N(Numeral) E(Error) */
   char *token;           /* saves the token */

   type = (char *)malloc(TYPE_SIZE * sizeof(char));
   token = (char *)malloc(MAX * sizeof(char));

   if(type == NULL || token == NULL)
   {
      printf("%s\n","Memory allocation for pointers lArray/type failed!");
      exit(0);
   }

      start = 0;            
      do
      {       
        token = getTokens(words,&start,type);
        //printf("%s\n",token ); 
        total = total + 1;
        tokenArray[i] = (char *)malloc(MAX_BUFFER * sizeof(char));
        typeArray[i] = (char *)malloc(MAX_BUFFER * sizeof(char));
         if(MAX < total)
         {
            /* Reallocationg memory of tokenArray with increase in no of tokens */
            tokenArray = (char **)realloc(tokenArray, total*2*sizeof(char *));
            typeArray = (char **)realloc(typeArray, total*2*sizeof(char *));
            if(tokenArray == NULL)
            {
               printf("Realloc failed!\n");
               exit(0);
            }
         }

          /* Storing the tokens in tokenArray */
          strcpy(tokenArray[i],token);
          strcpy(typeArray[i],type);
          i++;

         if(strcmp(token,"EOF")!=0)
         {
            /* If there is error */
            if(strcmp(type,"E")==0)
            {
               printf("ERROR: Invalid Token! %s\n",token);
               exit(0);
            }
            else
            {
               /* If the token is '(' */
               if(strcmp(type,"OP")==0)
                  openParen = openParen + 1;
               /* If the token is ')' */
               else if(strcmp(type,"CP")==0)
                  closeParen = closeParen + 1;
               /* If the token is a numeric atom */
               else if(strcmp(type,"N")==0)
               {
                  nAtom = nAtom + 1;
                  sum = sum + atoi(token);
               }
               /* If the token is a literal atom */
               else if(strcmp(type,"L")==0)
              {
                 lAtom = lAtom + 1;
              }
           }
         }/* end of if(strcmp(token,"EOF")!=0) */
      }while(strcmp(token,"EOF")!=0);

      *arrayLen = i;

/*    Output in the file:output.txt 
    printf("\n%s\n","----------------OUTPUT--------------");
    printf("LITERAL ATOMS: %d\n",lAtom);
    printf("NUMERIC ATOMS: %d %d\n",nAtom,sum);
    printf("OPEN PARENTHESES: %d\n",openParen);
    printf("CLOSING PARENTHESES: %d\n",closeParen);*/

    free(token);
    free(type);
    token = NULL;
    type = NULL;
}
/*********************************************************************************
 ** FUNCTION NAME : getTokens
 **
 ** DESCRIPTION   : Forms the next token in the input file
 **
 ** RETURNS       : token
 ********************************************************************************/

char * getTokens(char *line, int *start, char *type)
{ 
   int tokenSize = 4;                    /* Initial memory of token; gets reallocated dynamically */
   int i = *start, j =0;
   char *msg = (char *)malloc(sizeof(char)*50);
   char *token = (char *)malloc(sizeof(char)*tokenSize);

   if((line == NULL) || (line[i] == '$'))
   { 
     strcpy(token,"EOF");
     return token;
   }

   if(isspace(line[i]) || (line[i] == '\n') || (line[i] == '\r'))
   {
      for( ; (isspace(line[i]) || (line[i] == '\n') || (line[i] == '\r')); i++);
      if((line[i] == '$') || (line == NULL))
      {
        *start = 0;
        strcpy(token,"EOF");
        return token;
      }
      else
      {
        *start = i; 
      }
   }


   if(line[i] == ')')
   {
     *start = i + 1;
     strcpy(type,"CP");
     strcpy(token,")");
     return token;
   }


   if(line[i] == '(')
   {
     *start = i + 1;
     strcpy(type,"OP");
     strcpy(token,"(");
     return token;
   }


   if(isalpha(line[i]))
   {
      for(j = 0; line[i] != ')' && line[i] != '(' && (isspace(line[i]) == 0 && line[i] != '\0') ; i++, j++)
      {
        if(strlen(token) >= tokenSize)
          reallocation(token, &tokenSize);
        token[j] = line[i];
      }
      token[j] = '\0';
      *start = i;
      strcpy(type,"L");
      return token;
   }

   if(isdigit(line[i]))
   {
      for(j = 0; line[i] != ')' && line[i] != '(' && (isspace(line[i]) == 0 && line[i] != '\0') ; i++, j++)
      {
         if(strlen(token) >= tokenSize)
           reallocation(token, &tokenSize);
         token[j] = line[i];
      }
      token[j] = '\0';
      * start = i;
      for(j = 0; j < strlen(token); j++)
      {
        if(isalpha(token[j]))
        {
           strcpy(type,"E");
           return token;
        }
        else
        {
           strcpy(type,"N");
           return token;
        }   
     }/* end of for */
   }/* end of if */   
}/* end of function getNextToken() */

/*********************************************************************************
 ** FUNCTION NAME : reallocation
 **
 ** DESCRIPTION   : Reallocates memory of a string
 **
 ** RETURNS       : Nil
 ********************************************************************************/

void reallocation(char *str, int *newSize)
{
   /* Double the allocation and re-allocate */
   *newSize = (*newSize) * 2;
   str = (char *)realloc(str,sizeof(char)* (*newSize));
   if (str == NULL)
   {
      printf("Out of memory!\n");
      exit(0);
    }
}

