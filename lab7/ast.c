/* Abstract syntax tree code
This code is used to define an AST node,
routine for printing out the AST
defining an enumerated type so we can figure out what we need to
do with this. The ENUM is basically going to be every non-terminal
and terminal in our language.
Shaun Cooper Spring 2023
*/
/*
Updated By: Abdur Razzak
Date: April 14, 2024.
Lab: 7
Updates:
  Added check Params method to to check the length and type between formals and actuals
  Set sympol to Null while creation

*/
#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include "ast.h"
/* uses malloc to create an ASTnode and passes back the heap address of the newley
created node */
// PRE: Ast Node Type
// POST: PTR To heap memory and ASTnode set and all other pointers set to NULL
ASTnode *ASTCreateNode(enum ASTtype mytype)
{
 ASTnode *p;
 if (mydebug)
  fprintf(stderr, "Creating AST Node \n");
 p = (ASTnode *)malloc(sizeof(ASTnode));
 p->type = mytype;
 p->s1 = NULL;
 p->s2 = NULL;
 p->next = NULL;
 p->value = 0;
 p->symbol = NULL; //Set sympol to Null while creation
 return (p);
}
/* Helper function to print tabbing */
// PRE: Number of spaces desired
// POST: Number of spaces printed on standard output
void PT(int howmany)
{
  while(howmany--)
    printf(" ");
}

/*Helper function to check actual and formals length and type are same or not*/
// PRE: PTRS to actual and formals
// POST:
//  O if they are not same type and length
//  1 if they are
int check_params(ASTnode* actuals, ASTnode* formals){
  if (actuals == NULL && formals == NULL) return 1;
  if (actuals == NULL || formals == NULL) return 0;
  if (actuals->my_data_type != formals->my_data_type) return 0;
  if (actuals->symbol->SubType != formals->symbol->SubType ) return 0;
  return check_params(actuals->next, formals->next);
}


// PRE: A declaration type
// POST: A character string that is the name of the type
// This method will convert into an enum type into corresponding string
char *ASTtypeToString(enum AST_MY_DATA_TYPE mytype)
{
 if (mytype == A_INTTYPE){ // if the enum is int type return string INT
  return "INT";
 }
 if (mytype == A_VOIDTYPE){ // if the enum is VOID type return string VOID
  return "VOID";
 }
 printf("\n\nBurf: undefined type\n\n");
 return "";
}

/* Print out the abstract syntax tree */
// PRE: PRT to an ASTtree
// POST: indented output using AST order printing with indentation
void ASTprint(int level, ASTnode *p) {
 int i;
 if (p == NULL)
  return;
 switch (p->type) {    // Check the type of node
  case A_VARDEC:       // node is variable declaration type;
   PT(level);
   if(p->value == 0) 
   printf("Variable %s %s level %d offset %d\n", 
    ASTtypeToString(p->my_data_type),
    p->name,
    p->symbol->level,
    p->symbol->offset); // just a variable, printing the type, name, level and offset.
   else { // Array type declaration
    char pVal[30];
    sprintf(pVal, "%d", p->value);
    printf("Variable %s %s[%s] level %d offset %d\n", 
      ASTtypeToString(p->my_data_type), 
      p->name, 
      pVal,
      p->symbol->level,
      p->symbol->offset);
   }
   ASTprint(level, p ->s1); // variable list
   ASTprint(level, p ->next); // same lavel variables declarations
   break;
  
  case A_VARUSE:    // This case is for variable use such as x = 100.
   PT(level);
   printf("VARIABLE %s level %d offset %d\n", p->name, p->symbol->level, p->symbol->offset); // print the variable name
   if(p->value == 0)
    ASTprint(level, p ->s1); // variable list
   else {
    // array use
    PT(level +1);
    printf("[\n");  // for printing alignment, [] is printed 1 extra space without creating node
    
    ASTprint(level + 2, p->s1); // calling the inside expression with level 2 space to ensure print alignment.
    
    PT(level +1);
    printf("]\n");
   }
   break;

  case A_FUNCTIONDEC:    // case for function declaration, such as int func(){}
   PT(level);
   printf("Function %s %s level %d offset %d\n",
    ASTtypeToString(p->my_data_type), 
    p->name,
    p->symbol->level,
    p->symbol->offset);
   ASTprint(level + 1, p->s1);  // parameters
   ASTprint(level + 1, p->s2);  // compounds
   ASTprint(level, p->next);    // next pointer at the same level
   break;
  
  case A_COMPOUND:              // Compound Statement
   PT(level);
   printf("Compound Statement\n");
   ASTprint(level + 1, p->s1);  // local decs
   ASTprint(level + 1, p->s2);  // statement list
   ASTprint(level, p->next);    // Another statement with same level
   break;

  case A_IF:                    // If Statement
   PT(level);
   printf("IF STATEMENT\n");

   PT(level+1);
   printf("IF expression\n");
   ASTprint(level + 2, p->s1);  // if expression
  
   PT(level+1);
   printf("IF body\n");
   ASTprint(level + 2, p->s2->s1);  // if body
   if (p->s2->s2 != NULL) {
    PT(level+1);
    printf("ELSE body\n");
    ASTprint(level + 2, p->s2->s2);  // else body
   }

   ASTprint(level , p->next);   // another statement with at same level
   break;
  
  case A_WRITE:               // write statement such as write x;
   PT(level);
   if (p->name != NULL){
    printf("Write String %s\n", p->name);
   }
   else{
    printf("Write Expression\n");
    ASTprint(level +1, p->s1); // expression
   }
   ASTprint(level, p->next);    // Another statement at same level
   break;
  
  case A_READ:                // Read instruction, such as Read x;
    PT(level);
    printf("READ STATEMENT\n");
    ASTprint(level+1, p->s1); // variable
    ASTprint(level, p->next); // next pointer
    break;


  case A_PARAMS:                // case for function parameter
   PT(level);
   if (p!= NULL && p->name != NULL){
    if(p->value != 0) printf("Parameter %s %s[] level %d offset %d\n", 
      ASTtypeToString(p->my_data_type), 
      p->name,
      p->symbol->level,
      p->symbol->offset); // for array parameter
    else printf("Parameter %s %s level %d offset %d\n",
      ASTtypeToString(p->my_data_type), 
      p->name,
      p->symbol->level,
      p->symbol->offset);
    ASTprint(level, p->next); // same level variable
   }
   break;

  case A_NUM:             // number
   PT(level);
   printf("NUMBER value %d\n", p->value);
   break;


  case A_EXPR:              // Expression operator 
   PT(level);
   printf("EXPRESSION operator ");
   switch (p->operator)
   {
   case A_PLUS:       // for +
    printf("PLUS\n");
    break;

   case A_MINUS:        // for -
    printf("MINUS\n");
    break;

   case A_TIMES:        // for *
    printf("TIMES\n");
    break;

   case A_DEVIDE:       // for /
    printf("/\n");
    break;

   case A_MOD:          // for %
    printf("%c\n", 37);
    break;

   case A_UNIRY_MINUS:    // for unary minus
    printf("Unary-minus\n");
    break;
   
   case A_LESSEQUAL:      // for <=
    printf("<=\n");
    break;

   case A_LESSTHAN:       // for <
    printf("<\n");
    break;

   case A_GREATERTHAN:    // for >
    printf(">\n");
    break;

   case A_GREATEREQUAL:   // for >=
    printf(">=\n");
    break;

   case A_EQUAL:          // for =
    printf("==\n");
    break;

   case A_NOTEQUAL:       // for !=
    printf("!=\n");
    break;
   
   default:
    printf("nnknown operator in A_EXPR in ASTprint\n");
    break;
   }
   ASTprint(level+1, p->s1); // Additive expression
   ASTprint(level+1, p->s2); // term or simple_expression
   break;
  
  case A_EXPR_STAT:          // Expression Statement
    PT(level);
    printf("Expression STATEMENT\n");
    if(p->s1 != NULL) ASTprint(level+1, p->s1); // call the expression if it has
    ASTprint(level, p->next); 
    break;
  
  case A_FUNC_CALL:       // case for function call
    PT(level);
    printf("CALL STATEMENT function %s\n",p->name);

    PT(level+1);
    printf("(\n");

    if (p->s1 == NULL) {// just to match the print of NULL with LAB 7 video 1 42.27(time) output
      PT(level+2);
      printf("NULL\n");
    }
    else ASTprint(level+2, p->s1); // arguments
    
    PT(level+1);
    printf(")\n");
    break;

  case A_ARG:       // arguments of function
    PT(level);
    printf("CALL argument\n");
    ASTprint(level+1, p->s1); // expression
    ASTprint(level, p->next); // next arguments from the list on the same level
    break;

  
  case A_WHILE_STAT:        // While statement
    PT(level);
    printf("WHILE STATEMENT\n");

    PT(level + 1);
    printf("WHILE expression\n");
    ASTprint(level+2, p->s1); // while condition

    PT(level + 1);
    printf("WHILE body\n");
    ASTprint(level+2, p->s2); // while body
    
    ASTprint(level, p->next); // while statement is next connected
    break;

  case A_ASSGN_STAT:          // Assignment statement
    PT(level);
    printf("ASSIGNMENT STATEMENT\n");
    ASTprint(level+1, p->s1); // variable
    
    PT(level);
    printf("is assigned\n");
    
    ASTprint(level+1, p->s2);  // simpel expression
    ASTprint(level, p->next);  // next node with same level assignment statement
    break;

   case A_RETURN_STAT:          // return statement
    PT(level);
    printf("RETURN STATEMENT\n");
    if(p->s1 != NULL) ASTprint(level+1, p->s1); // if there any expression exist, call it
    ASTprint(level, p->next);  // same lavel return
    break;

   case A_BREAK:        // break statement
    PT(level);
    printf("BREAK STATEMENT\n");
    ASTprint(level, p->next);       // same level node
    break;

   case A_CONTINUE:     // continue statement
    PT(level);
    printf("CONTINUE STATEMENT\n");
    ASTprint(level, p->next); // same lavel node
    break;
   
   case A_FUNCTION_PROTO:     // function protototype
    PT(level);
    printf("Function PROTOTYPE %s %s level %d offset %d\n",
      ASTtypeToString(p->my_data_type), 
      p->name,
      p->symbol->level,
      p->symbol->offset);
    
    ASTprint(level+1, p->s1); // params
    ASTprint(level, p->next); // same level next node
    break;
  
  default:
   printf("unknown AST Node type %d in ASTprint\n", p->type);
 }
}