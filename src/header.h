#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdarg.h>

#define MAX 200                  /* Initial value for memory of lArray; which is reallocated dynamically if needed */                  
#define TYPE_SIZE 3              /* Since type can be only OP, CP, L, N or E */             
#define MAX_BUFFER 1024

typedef struct tree{
  char data[50];
  char type[10];
  int length;
  struct tree *left;
  struct tree *right;
}tree;

extern char current[MAX];
extern char **tokenArray;
extern tree *dList;
static int openParen = 0;
static int closeParen = 0;
static int lAtom = 0;
static int nAtom = 0;
static int sum = 0;
static int cOpen = 0;
static int cClose = 0;
extern int next;

int getLine(char **, int);
void reallocation(char *, int *);
void saveTokens(char **, char *, int *);
char * getTokens(char *, int *, char *);
char * getNextToken(char **);
void init();
char * GetCurrent();
void MoveToNext();
void expr(tree *);
tree * eval(tree *, tree *, tree **);
tree * apply(tree *, tree *, tree *, tree *);
tree * evcon(tree *, tree *, tree *);
tree * evlist(tree *, tree *, tree *);
tree * bound(tree *, tree *);
tree * getval(tree *, tree *);
tree * addPairs(tree *, tree *, tree *);
int checkFunc(tree *);
int mem(char *, tree *);
int length(tree *);
tree * isInt(tree *);
tree * car(tree *);
tree * cdr(tree *);
tree * cond(tree *);
tree * atom(tree *);
tree * isNull(tree *);
tree * plus(tree *, tree *);
tree * minus(tree *, tree *);
tree * less(tree *, tree *);
tree * times(tree *, tree *);
tree * greater(tree *, tree *);
tree * eq(tree *, tree *);
tree * cons(tree *, tree *);