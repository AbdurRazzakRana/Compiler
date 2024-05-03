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
 A_FUNCTION_COMMON, //0
 A_FUNCTIONDEC, //1  // usrd
 A_FUNCTION_PROTO, //2
 A_VARDEC, //3  //done
 A_VARUSE, //4  // done
 A_COMPOUND, //5
 A_WRITE, //6  // done
 A_PARAMS, //7 // half done // array left
 A_NUM, //8  // done
 A_EXPR, //9  // done
 A_EXPR_STAT, //10  // done
 A_WHILE_STAT, //11  //done
 A_IF, //12  // done
 A_IFBODY, //13  //done
 A_READ, //14  //done
 A_FUNC_CALL, //15
 A_ARG, //16  // done
 A_ASSGN_STAT, //17  //done
 A_RETURN_STAT, //18  // done
 A_BREAK, //19  //done
 A_CONTINUE //20

};
// Math Operators
enum AST_OPERATORS
{
 A_PLUS,  //0
 A_MINUS,  //1
 A_TIMES,  //2
 A_DEVIDE,  //3
 A_MOD,  //4
 A_LESSEQUAL,  //5
 A_LESSTHAN,  //6
 A_GREATERTHAN,  //7
 A_GREATEREQUAL,  //8
 A_EQUAL,  //9
 A_NOTEQUAL,  //10
 A_UNIRY_MINUS  //11
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
 char* label;  // for lab9 only, to keep track of label in data space.
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
