/* Abstract syntax tree header file
This file will prototype the types of AST Nodes, operators and data type.
Will also list possible items inside a node
And prototypeing few functions such as parameter chekcing, printing
*/
/*
Modified by: Abdur Razzak
Date: May 3, 2024.
Lab: 9
Lab 9 specific Updates:
 only 1 update: Added label to the node to keep track of label in data space.

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
 A_FUNCTION_COMMON, // 0
 A_FUNCTIONDEC,     // 1
 A_FUNCTION_PROTO,  // 2
 A_VARDEC,          // 3
 A_VARUSE,          // 4
 A_COMPOUND,        // 5
 A_WRITE,           // 6
 A_PARAMS,          // 7
 A_NUM,             // 8
 A_EXPR,            // 9
 A_EXPR_STAT,       // 10
 A_WHILE_STAT,      // 11
 A_IF,              // 12
 A_IFBODY,          // 13
 A_READ,            // 14
 A_FUNC_CALL,       // 15
 A_ARG,             // 16
 A_ASSGN_STAT,      // 17
 A_RETURN_STAT,     // 18
 A_BREAK,           // 19
 A_CONTINUE         // 20

};
// Math Operators
enum AST_OPERATORS
{
 A_PLUS,         // 0
 A_MINUS,        // 1
 A_TIMES,        // 2
 A_DEVIDE,       // 3
 A_MOD,          // 4
 A_LESSEQUAL,    // 5
 A_LESSTHAN,     // 6
 A_GREATERTHAN,  // 7
 A_GREATEREQUAL, // 8
 A_EQUAL,        // 9
 A_NOTEQUAL,     // 10
 A_UNIRY_MINUS   // 11
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
 enum ASTtype type;                  // type of the node
 enum AST_OPERATORS operator;        // if there any additive, multiplicative or comparative operators
 char *name;                         // name of the node
 int value;                          // value for array or integer
 enum AST_MY_DATA_TYPE my_data_type; /*used to identify the data types*/
 struct ASTnodetype *s1, *s2, *next; /* used for holding next pointers such as IF and WHILE
 components*/
 struct SymbTab *symbol;             // Added symbol field to keep track of item in symbol table
 char *label;                        // for lab9 only, to keep track of label in data space.
} ASTnode;
/* uses malloc to create an ASTnode and passes back the heap address of the newley
created node */
ASTnode *ASTCreateNode(enum ASTtype mytype);
void PT(int howmany);
/* Print out the abstract syntax tree */
void ASTprint(int level, ASTnode *p);

/* To check actual and formals length and type are same or not */
int check_params(ASTnode *actuals, ASTnode *foremals);
#endif // of AST_H
