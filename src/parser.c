/*********************************************************************************
 ** FILENAME        :  parser.c
 **
 ** DESCRIPTION     :  This file defines the functions for parsing and builds a syntax tree
 **                  
 ** Revision History:
 ** DATE           NAME                REASON
 ** ------------------------------------------------------------------------------
 ** Jan 26 2016    Sangeeta Kumari     PL Project
 ********************************************************************************/

#include"header.h"

 /*********************************************************************************
 ** EXTERN VARIABLES
 ********************************************************************************/
extern int next;
extern char **tokenArray;
extern char **typeArray;

/*********************************************************************************
 ** FUNCTION NAME : expr()
 **
 ** DESCRIPTION   : Implements the production <Expr> ::= atom | (<List>)
 **
 ** RETURNS       : tree node
 ********************************************************************************/
void expr(tree *root)
{
    tree *node;
    if(root == NULL)
        return;
    if(isalpha(current[0]) || isdigit(current[0]))
    {
        root->right = NULL;
        root->left = NULL;
        strcpy(root->data,current);
        return;
	}
    else if(strcmp(GetCurrent(),"(") == 0)
	{
        cOpen++;
        strcpy(root->data,".");
		MoveToNext();
        while(strcmp(GetCurrent(),")") != 0)
        {
            if((cOpen != cClose) && (strcmp(current,"EOF") == 0))
            {
                printf("%s\n ERROR: Parse Error!\n");
                exit(0);
            }
                root->left = (tree *)malloc(sizeof(tree));
                expr(root->left);
                root->right = (tree *)malloc(sizeof(tree));
                root = root->right;
                strcpy(root->data,".");
                MoveToNext();
        }
        
        //root->right = (tree *)malloc(sizeof(tree));
        //root = root->right;
        cClose++;
        strcpy(root->data,"NIL");
        root->left = NULL;
        root->right = NULL;
        return;
	}
	else
	{
		printf("%s\n ERROR: Parse Error!\n");
		exit(0);
	}
    return;
}
/*********************************************************************************
 ** FUNCTION NAME : inorder()
 **
 ** DESCRIPTION   : inorder traversal of the binary tree
 **
 ** RETURNS       : NIL
 ********************************************************************************/
void inorder(tree *root)
{
    if(root != NULL)
    {
        if(root->left == NULL && root->right == NULL){
                printf("%s",root->data);
        }
        else{
            printf("(");
            inorder(root->left);
            printf(" %s ",root->data);
            inorder(root->right);
            printf(")");
        }
    }
}

