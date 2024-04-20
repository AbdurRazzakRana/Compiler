/* Abstract syntax tree code
Header file
Shaun Cooper Spring 2023
You must add appropriate header code that describes what this does
*/
/*
Modified by: Abdur Razzak
Date: April 20, 2024.
Lab: 9
Updates:
 Added all the necessary enum type that are used in yacc and ast.c file
 Also added the Operators enum
*/
#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include "symtable.h"
#ifndef AST_H
#define AST_H
int mydebug;
/* define the enumerated types for the AST. THis is used to tell us what
sort of production rules */
enum ASTtype
{
 A_FUNCTION_COMMON,
 A_FUNCTIONDEC,
 A_FUNCTION_PROTO,
 A_VARDEC,
 A_VARUSE,
 A_COMPOUND,
 A_WRITE,
 A_PARAMS,
 A_NUM,
 A_EXPR,
 A_EXPR_STAT,
 A_WHILE_STAT,
 A_IF,
 A_IFBODY,
 A_READ,
 A_FUNC_CALL,
 A_ARG,
 A_ASSGN_STAT,
 A_RETURN_STAT,
 A_BREAK,
 A_CONTINUE

};
// Math Operators
enum AST_OPERATORS
{
 A_PLUS,
 A_MINUS,
 A_TIMES,
 A_DEVIDE,
 A_MOD,
 A_LESSEQUAL,
 A_LESSTHAN,
 A_GREATERTHAN,
 A_GREATEREQUAL,
 A_EQUAL,
 A_NOTEQUAL,
 A_UNIRY_MINUS
};
// data types
enum AST_MY_DATA_TYPE
{
 A_INTTYPE,
 A_VOIDTYPE
};
/* define a type AST node which will hold pointers to AST structs that will
allow us to represent the parsed code
*/
typedef struct ASTnodetype
{
 enum ASTtype type;  // type of the node
 enum AST_OPERATORS operator; // if there any additive, multiplicative or comparative operators
 char *name; // name of the node
 int value;  // value for array or integer
 enum AST_MY_DATA_TYPE my_data_type; /*used to identify the data types*/
 struct ASTnodetype *s1, *s2, *next; /* used for holding next pointers such as IF and WHILE
 components*/
 struct SymbTab *symbol;  // Added symbol field to keep track of item in symbol table
} ASTnode;
/* uses malloc to create an ASTnode and passes back the heap address of the newley
created node */
ASTnode *ASTCreateNode(enum ASTtype mytype);
void PT(int howmany);
/* Print out the abstract syntax tree */
void ASTprint(int level, ASTnode *p);

/* To check actual and formals length and type are same or not */
int check_params(ASTnode* actuals, ASTnode* foremals);
#endif // of AST_H
