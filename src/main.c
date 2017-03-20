/*********************************************************************************
 ** FILENAME        :  main.c
 **
 ** DESCRIPTION     :  This file defines the functions to for scanner and parser implementation
 **                   which prints the atoms and parentheses in the input file                   
 ** Revision History:
 ** DATE           NAME                REASON
 ** ------------------------------------------------------------------------------
 ** Jan 18 2016    Sangeeta Kumari     PL Project
 ** Jan 26 2016
 ********************************************************************************/

#include"header.h"

 /*********************************************************************************
 ** GLOBAL VARIABLES
 ********************************************************************************/
char current[MAX];
char **tokenArray;
char **typeArray;
tree *dList;

int main(void)
{
    int i = 0 , j = 0, k = 0;
    int arraySize;
    int size = MAX_BUFFER;
    memset(current,'0',MAX-1);
    int ch;
    char *buffer = (char *)malloc(sizeof(char)*size);
    tokenArray = (char **)malloc(MAX * sizeof(char *));
    typeArray = (char **)malloc(MAX * sizeof(char *));
    tree *root = NULL;
    root = (tree *)malloc(sizeof(tree));
    root->isList = 0;
    
    tree *aList = (tree *)malloc(sizeof(tree));
    aList->left = NULL;
    aList->right = NULL;
    strcpy(aList->data,"NIL");

    dList = (tree *)malloc(sizeof(tree));
    dList->left = NULL;
    dList->right = NULL;
    strcpy(dList->data,"NIL");

    if (buffer == NULL)
    {
      printf("\nOut of memory!\n");
      exit(0);
    }
    
    else
    {
        while((ch = fgetc(stdin)) != EOF)
        {
            if(size < k)
            {
                size = size * 2;
                buffer = (char *)realloc(buffer,size);
            }
            buffer[k] = ch;
            k++;
        }
        buffer[k] = '$';
    }

    saveTokens(tokenArray, buffer, &arraySize);

    if(strcmp(current,"EOF") == 0)
    {
        printf("%s\nEmpty String!\n");
        exit(0);
    }
    do
    {
        init();
        expr(root);
        if(strcmp(current,"EOF") != 0)
        {
            //inorder(eval(root, aList, &dList));
            //printf(" ");
            prettyPrint(eval(root, aList, &dList));
            printf("\n");
        }
    }while(strcmp(current,"EOF") != 0);

    //freeTree(root);
  
    /* Closing the output file */
    fclose(stdout);
   
    return 0;
}

