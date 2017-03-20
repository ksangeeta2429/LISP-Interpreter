/*********************************************************************************
 ** FILENAME        :  scanner.c
 **
 ** DESCRIPTION     :  This file defines the functions to build a lexical analyzer 
 **                    which prints the atoms and parentheses in the input file                   
 ** Revision History:
 ** DATE           NAME                REASON
 ** ------------------------------------------------------------------------------
 ** Feb 6 2016    Sangeeta Kumari     PL Project
 ********************************************************************************/

#include"header.h"

/*********************************************************************************
 ** FUNCTION NAME : eval
 **
 ** DESCRIPTION   : evaluates the top level S expression
 **
 ** RETURNS       : tree *
 ********************************************************************************/
tree * eval(tree *root, tree *aList, tree **dList){ 
	tree *node = NULL;
	tree *result = NULL;
    int len = length(root);
	if(strcmp(atom(root)->data,"T") == 0){
		if(strcmp(root->data,"NIL")==0 || strcmp(root->data,"T")==0 || strcmp(isInt(root)->data,"T") == 0){
			return root;
		}
		else if(strcmp(bound(root, aList)->data,"T") == 0){
			//printf("Inside bound of eval()\n");
			return getval(root, aList);
		}
		else{
			printf("\nERROR: Unbound variable: %s!\n",root->data);
			exit(0);
		}
	}
	else{
		if(strcmp(car(root)->data,"QUOTE") == 0){
			if(len != 2){
				printf("\nERROR: QUOTE is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return (car(cdr(root)));
		}
		else if(strcmp(car(root)->data,"COND") == 0){
			if(cdr(root) == NULL){
				printf("\nERROR: COND has empty condition!\n");
				exit(0);
			}
			root = evcon(cdr(root), aList, *dList);
			return root;
		}
		else if(strcmp(car(root)->data,"DEFUN") == 0){
			if(len != 4){
				printf("\nERROR: DEFUN is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			if(checkFunc(cdr(root))){
				*dList = cons(cons(car(cdr(root)), cons(car(cdr(cdr(root))), car(cdr(cdr(cdr(root)))))), *dList);
				return car(cdr(root));
			}
			else{
				printf("ERROR: Cannot define function with function name:%s\n",car(cdr(root))->data);
				exit(0);
			}	
		}
		else{
			//printf("Calling apply\n");
			return apply(car(root), evlist(cdr(root), aList, *dList), aList, *dList);
		}		
	}
}
/*********************************************************************************
 ** FUNCTION NAME : apply
 **
 ** DESCRIPTION   : evaluates the S expression
 **
 ** RETURNS       : tree *
 ********************************************************************************/
tree * apply(tree *root, tree *params, tree *aList, tree *dList){ 
	tree *node = NULL;
	tree *result = NULL;

    int len = length(params);
    //printf("Length of exp:%d\n",len);
	if(root->left == NULL && root->right == NULL){
		if(strcmp(root->data,"PLUS") == 0){
			if(len != 2){
				printf("ERROR: PLUS is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = plus(car(params), car(cdr(params)));
			return root;
		}
		else if(strcmp(root->data,"MINUS") == 0){
			if(len != 2){
				printf("ERROR: MINUS is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = minus(car(params) , car(cdr(params)));
			return root;		
		}
		else if(strcmp(root->data,"TIMES") == 0){
			if(len != 2){
				printf("ERROR: TIMES is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = times(car(params), car(cdr(params)));
			return root;			
		}
		else if(strcmp(root->data,"LESS") == 0){
			if(len != 2){
				printf("ERROR: LESS is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = less(car(params), car(cdr(params)));
			return root;			
		}
		else if(strcmp(root->data,"GREATER") == 0){
			if(len != 2){
				printf("ERROR: GREATER is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = greater(car(params), car(cdr(params)));
			return root;			
		}
		else if(strcmp(root->data,"EQ") == 0){
			if(len != 2){
				printf("ERROR: EQ is not defined for an expression of length less than 3!\n");
				exit(0);
			}
			root = eq(car(params), car(cdr(params)));
			return root;			
		}
		else if(strcmp(root->data,"ATOM") == 0){
			if(len != 1){
				printf("ERROR: ATOM is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return atom(car(params));
		}
		else if(strcmp(root->data,"INT") == 0){
			if(len != 1){
				printf("ERROR: INT is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return isInt(car(params));
		}
		else if(strcmp(root->data,"NULL") == 0){
			if(len != 1){
				printf("ERROR: NULL is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return isNull(car(params));
		}
		else if(strcmp(root->data,"CAR") == 0){
			if(len != 1){
				printf("ERROR: CAR is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return car(car(params));
		}
		else if(strcmp(root->data,"CDR") == 0){
			if(len != 1){
				printf("ERROR: CDR is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			return cdr(car(params));
		}
		else if(strcmp(root->data,"CONS") == 0){
			if(len != 2){
				printf("ERROR: CONS is not defined for an expression of length less than 2!\n");
				exit(0);
			}
			root = cons(car(params), car(cdr(params)));
			return root;			
		}
		else{
			if(strcmp(bound(root, dList)->data,"T") == 0){
				if(len != length(car(getval(root, dList)))){
					printf("ERROR: No of parameters do not match for function!\n");
					exit(0);
				}
			}
		 	else{
				printf("ERROR: Unbound Function name %s!\n",root->data);
				exit(0);
			}

			//printf("%s\nInside function call\n");
			//printf("%s\n",root->data);
			return eval(cdr(getval(root,dList)), addPairs(car(getval(root, dList)), params, aList), &dList);
		}
	}
	else{
		printf("ERROR: Apply Function Error!\n");
		exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : length
 **
 ** DESCRIPTION   : calculates the length of the list
 **
 ** RETURNS       : length
 ********************************************************************************/
int length(tree *root){
	int len = 0;
	if(root == NULL){
       return 0;
	}
	else if(strcmp(root->data,"NIL") == 0){
		return 0;
	}
	else{
		len = 1 + length(root->right);
	}
	return len;
}

/*********************************************************************************
 ** FUNCTION NAME : isInt
 **
 ** DESCRIPTION   : checks whether a list has a numeric atom
 **
 ** RETURNS       : tree * (with value T if it is integer and NIL if it's not)
 ********************************************************************************/
tree * isInt(tree *root){
    tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
    //printf("Inside isInt:%s\n",root->data);

	if(root->data[0] == '-'){
		if(isdigit(root->data[1])){
			strcpy(node->data,"T");
		}
		else{
			strcpy(node->data,"NIL");	
		}
	}
	else if(isdigit(root->data[0])){
		strcpy(node->data,"T");
	}
	else{
		strcpy(node->data,"NIL");	
	}
	return node;
}

/*********************************************************************************
 ** FUNCTION NAME : isNull
 **
 ** DESCRIPTION   : checks whether a list is empty
 **
 ** RETURNS       : tree * (with value T if it is NULL and NIL if it's not)
 ********************************************************************************/
tree * isNull(tree *root){
    tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;

	if((root->left == NULL) && (root->right == NULL) && (strcmp(root->data,"NIL") == 0)){
		strcpy(node->data,"T");		
	}
	else{
		strcpy(node->data,"NIL");	
	}
	return node;
}

/*********************************************************************************
 ** FUNCTION NAME : car
 **
 ** DESCRIPTION   : gets the left subtree of the expression
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * car(tree *root){
	int len = length(root);
	if((root->left == NULL) && (root->right == NULL)){
		printf("ERROR: Expression is an atom so car(s) is undefined\n");
		exit(0);
	}
/*	else
		printf("%s\n",root->left->data);*/
	return root->left;
}

/*********************************************************************************
 ** FUNCTION NAME : cdr
 **
 ** DESCRIPTION   : gets the right subtree of the expression
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * cdr(tree *root){
	int len = length(root);
	if((root->left == NULL) && (root->right == NULL)){
		printf("ERROR: Expression is an atom so cdr(s) is undefined\n");
		exit(0);
	}
	return root->right;
}

/*********************************************************************************
 ** FUNCTION NAME : cons
 **
 ** DESCRIPTION   : makes a tree with first argument as left subtree and second argument as right
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * cons(tree *left, tree *right){
    tree *node = (tree *)malloc(sizeof(tree));
    node->left = (tree *)malloc(sizeof(tree));
    node->right = (tree *)malloc(sizeof(tree));

	if(left == NULL && right == NULL){
		printf("\nERROR: Invalid inputs for CONS\n");
		exit(0);
	} 
	else if(left == NULL){
		node = right;
	} 
	else if(right == NULL){
		node = left;
	} 
	else{
		node->left = left;
		node->right = right;
	}
	return node;
}

/*********************************************************************************
 ** FUNCTION NAME : atom
 **
 ** DESCRIPTION   : checks whether the node is an atom
 **
 ** RETURNS       : tree * (with value T if it is NULL and NIL if it's not)
 ********************************************************************************/
tree * atom(tree *root){
    tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;

	if(root!= NULL && root->left == NULL && root->right == NULL){
		strcpy(node->data,"T");
	}
	else{
		strcpy(node->data,"NIL");	
	}
	return node;
}

/*********************************************************************************
 ** FUNCTION NAME : plus
 **
 ** DESCRIPTION   : adds the value of left and right subtree
 **
 ** RETURNS       : tree *
 ********************************************************************************/
tree * plus(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
    
	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside PLUS: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			int result = atoi(left->data) + atoi(right->data);
			sprintf(node->data, "%d" ,result);
			//printf("Inside PLUS: added value %s\n",node->data);
			return node;
		}
		else{
			printf("\nERROR: PLUS is not defined for non-integer values\n");
			exit(0);
		}
	}
	else{
			printf("\nERROR: PLUS is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : minus
 **
 ** DESCRIPTION   : subtracts the value of left and right subtree
 **
 ** RETURNS       : tree *
 ********************************************************************************/
tree * minus(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;

	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside MINUS: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			int result = atoi(left->data) - atoi(right->data);
			sprintf(node->data, "%d" ,result);
			//printf("Inside MINUS: added value %s\n",node->data);
			return node;
		}
		else{
			printf("\nERROR: MINUS is not defined for non-integer values\n");
			exit(0);
		}
	}
	else{
			printf("\nERROR: MINUS is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : times
 **
 ** DESCRIPTION   : multiplies the value of left and right subtree
 **
 ** RETURNS       : tree *
 ********************************************************************************/
tree * times(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;

	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside TIMES: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			int result = atoi(left->data) * atoi(right->data);
			sprintf(node->data, "%d" ,result);
			//printf("Inside TIMES: added value %s\n",node->data);
			return node;
		}
		else{
			printf("\nERROR: TIMES is not defined for non-integer values\n");
			exit(0);
		}
	}
	else{
			printf("\nERROR: TIMES is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : less
 **
 ** DESCRIPTION   : checks if the value of the left node is less than right nodes
 **
 ** RETURNS       : tree * (with value T if left node value is greater else it is NIL)
 ********************************************************************************/
tree * less(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	int result;

	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside LESS: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			if(atoi(left->data) < atoi(right->data))
				strcpy(node->data,"T");
			else
				strcpy(node->data,"NIL");
			//printf("Inside LESS: added value %s\n",node->data);
			return node;
		}
		else{
			printf("\nERROR: LESS is not defined for non-integer values\n");
			exit(0);
		}
	}
	else{
			printf("\nERROR: LESS is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : greater
 **
 ** DESCRIPTION   : checks if the value of the left node is greater than right nodes
 **
 ** RETURNS       : tree * (with value T if it is left node value is greater else it is NIL)
 ********************************************************************************/
tree * greater(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	int result;

	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside GREATER: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			if(atoi(left->data) > atoi(right->data))
				strcpy(node->data,"T");
			else
				strcpy(node->data,"NIL");
			//printf("Inside GREATER: added value %s\n",node->data);
			return node;
		}
		else{
			printf("\nERROR: GREATER is not defined for non-integer values\n");
			exit(0);
		}
	}
	else{
			printf("\nERROR: GREATER is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : eq
 **
 ** DESCRIPTION   : checks if the value of the left node is equal to that of right node
 **
 ** RETURNS       : tree * (with value T if the values are equal else it is NIL)
 ********************************************************************************/
tree * eq(tree *left, tree *right){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	int result;
	if((strcmp(atom(left)->data,"T") == 0) && (strcmp(atom(right)->data,"T") == 0)){
		//printf("Inside EQ: isInt() left and right %s %s\n",isInt(left)->data, isInt(right)->data);
		if((strcmp(isInt(left)->data,"T") == 0) && (strcmp(isInt(right)->data,"T") == 0)){
			if(atoi(left->data) == atoi(right->data))
				strcpy(node->data,"T");
			else
				strcpy(node->data,"NIL");
			//printf("Inside EQ: added value %s\n",node->data);
			return node;
		}
		else{
			if(strcmp(left->data,right->data)==0)
				strcpy(node->data,"T");
			else
				strcpy(node->data,"NIL");
			//printf("Inside EQ: added value %s\n",node->data);
			return node;
		}
	}
	else{
			printf("\nERROR: EQ is not defined for non-atomic values\n");
			exit(0);
	}
}

/*********************************************************************************
 ** FUNCTION NAME : evcon
 **
 ** DESCRIPTION   : checks if a condition is true and evaluates the expression corresponding to that
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * evcon(tree *root, tree *aList, tree *dList){
	if(strcmp(isNull(root)->data, "T") == 0) {
		printf("\nERROR: Empty condition for COND\n");
		exit(0);
	}
	else if(strcmp(eval(car(car(root)), aList, &dList)->data,"T") == 0) {
		return eval(car(cdr(car(root))), aList, &dList);
	}
	else{
		return evcon(cdr(root), aList, dList);
	}

/*	else if(strcmp(eval(car(car(root)))->data,"T") == 0){
		if(cdr(car(root)) == NULL){
			printf("\nERROR: Missing expression for TRUE evaluation in COND\n");
			exit(0);
		}
		//printf("Length inside cond:%d\n",length(cdr(car(root))));
		if(length(cdr(car(root))) == 1 && car(cdr(car(root))) == NULL)
			return eval(cdr(car(root)));
		else
			return eval(car(cdr(car(root))));
	}
	else{
		if(strcmp(cdr(root)->data,"NIL") == 0){
			printf("\nERROR: COND has no TRUE expression!\n");
			exit(0);
		}
		cond(cdr(root));
	}*/
}

/*********************************************************************************
 ** FUNCTION NAME : evlist
 **
 ** DESCRIPTION   : evaluates the list
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * evlist(tree *root, tree *aList, tree *dList) {
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	if(strcmp(isNull(root)->data, "T") == 0) {
		strcpy(node->data,"NIL");
		return node;
	} 
	else{
		return cons(eval(car(root), aList, &dList), evlist(cdr(root), aList, dList));
	}
}

/*********************************************************************************
 ** FUNCTION NAME : bound
 **
 ** DESCRIPTION   : checks if a variable is bound with a value
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
tree * bound(tree *root, tree *aList) {
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	if(strcmp(atom(root)->data,"T") == 0) {
		if(strcmp(isNull(aList)->data, "T") == 0) {
			strcpy(node->data,"NIL");
			return node;
		}
		else if(strcmp(eq(root->data, car(car(aList))->data)->data,"T") == 0) {
			strcpy(node->data,"T");
			return node;
		}
		else{
			return bound(root, cdr(aList));
		}
	}
	else{
		printf("\nERROR: In bound() function!\n");
		exit(0);		
	}
}

/*********************************************************************************
 ** FUNCTION NAME : getval
 **
 ** DESCRIPTION   : finds the first occurrence of the variable and returns its value
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
 tree * getval(tree *root, tree *aList){
	tree *node = (tree *)malloc(sizeof(tree));
	node->left = NULL;
	node->right = NULL;
	if(strcmp(atom(root)->data,"T") == 0) {
		//printf("Inside getval\n");
		if(strcmp(eq(root->data, car(car(aList))->data)->data,"T") == 0) {
			//printf("%s is present!\n",root->data);
			strcpy(node->data,"T");
			return cdr(car(aList));
		}	
		else{
			return getval(root, cdr(aList));
		}
	}
	else{
		printf("\nERROR: In getval() function!\n");
		exit(0);		
	}
}
 /*********************************************************************************
 ** FUNCTION NAME : addPairs
 **
 ** DESCRIPTION   : pairs up the formal and the actual parameters
 **
 ** RETURNS       : tree * 
 ********************************************************************************/
 tree * addPairs(tree *varList, tree *valList, tree *old){
 	//printf("Inside addPairs():\n");

	if(strcmp(isNull(varList)->data, "T") == 0) {
		return old;
	} 
	else{
		old = cons(cons(car(varList), car(valList)), addPairs(cdr(varList), cdr(valList), old));
		return old;
	}
}

 /*********************************************************************************
 ** FUNCTION NAME : checkFunc
 **
 ** DESCRIPTION   : checks if a user defined function is valid
 **
 ** RETURNS       : int
 ********************************************************************************/
int checkFunc(tree *root){
	int valid = 1;
	int i = 0;
	if(strcmp(atom(car(root))->data, "T") == 0){
		if(strcmp(isInt(car(root))->data, "T") == 0){
			printf("ERROR: Function name cannot be a numberic atom\n");
			exit(0);
		}
		char *lispDefined[] = {
									"T",
									"NIL",
									"QUOTE",
									"COND",
									"DEFUN",
									"PLUS",
									"MINUS",
									"TIMES",
									"LESS",
									"GREATER",
									"EQ",
									"ATOM",
									"INT",
									"NULL",
									"CAR",
									"CDR",
									"CONS"
							   };
		for(i=0 ; i<17; i++){
			if(strcmp(car(root)->data, lispDefined[i]) == 0){
				printf("ERROR: Function name cannot be same as pre-defined functions of LISP\n");
				exit(0);
			}
		}

		tree *temp = car(cdr(root));
		tree *tempList = temp;

		while(strcmp(isNull(tempList)->data, "NIL") == 0){
			//printf("%sInside isNull of checkFunc\n");
			tree *node = car(tempList);
			if(strcmp(atom(node)->data, "T") == 0){
				if(strcmp(isInt(node)->data, "T") == 0){
					printf("%sInside isInt of checkFunc\n");
					printf("ERROR: Formal parameter cannot be a numeric atom!\n");
					exit(0);
				}
				if((strcmp(node->data, "NIL") == 0) || (strcmp(node->data, "T") == 0)){
					printf("%sInside Nil and T check of checkFunc\n");
					printf("ERROR: Formal parameter cannot be T or NIL!\n");
					exit(0);					
				}
				if(mem(node->data, cdr(tempList))) {
					//printf("%sInside mem() check of checkFunc\n");
					//printf("%dDuplication test:\n",mem(node->data, cdr(tempList)));
					printf("ERROR: Duplicate variable names in formal list!\n");
					exit(0);
				}
			}
			tempList = cdr(tempList);
		}
	}
	else{
		printf("ERROR: Function name cannot be a List!\n");
		exit(0);
	}
	return valid;
}
 /*********************************************************************************
 ** FUNCTION NAME : mem
 **
 ** DESCRIPTION   : checks if an element is a member of the list passed as a parameter
 **
 ** RETURNS       : int
 ********************************************************************************/
 int mem(char *param, tree *root){
 	int isMember = 0;
    
    if(strcmp(isNull(root)->data, "NIL") == 0){
        if(strcmp(eq(param, car(root))->data, "T") == 0) {
        	isMember = 1;
        	return isMember;
        }
        else{
        	mem(param, cdr(root));
        }
    }
    return isMember;
 }
/*********************************************************************************
 ** FUNCTION NAME : prettyPrint
 **
 ** DESCRIPTION   : prints the tree using list notation
 **
 ** RETURNS       : NIL
 ********************************************************************************/
void prettyPrint(tree *root){
	if(root->left == NULL && root->right == NULL){
		printf("%s",root->data);
		return;
	}
	else{
		printf("(");
        prettyPrint(root->left);
		while(root->right != NULL && (strcmp(root->right->data, "NIL") != 0)) {
			root = root->right;
			
			if(root->left != NULL){
				printf(" ");
				prettyPrint(root->left);
			}
		}
		if(root->right != NULL){
			if((strcmp(root->data, ".") != 0) && (strcmp(root->right->data, "NIL") != 0)) {
				printf(".%s)",root->data);
				return;
			}
		}
		else if((strcmp(root->data, ".") != 0) && (strcmp(root->data, "NIL") != 0)) {
			printf(".%s)",root->data);
			return;
		}
		printf(")");
	}
	return;
}

