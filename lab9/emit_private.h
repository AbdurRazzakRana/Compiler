// Author: Abdur Razzak
// Lab: Lab 9
// Semester: Spring 2024
// Purpose:

#include "ast.h"


struct FunctionInfo
{  
// This data structure is to keep track of function name and return type
// In order to match the function name and return type at emit_return
 char * functionName;  // to generate code based on main or other function at return statement time
 int returnType;  // burf if type mismatch between function return type and return statement
 int isReturnStmtFound;  // burf if the function has INT return type, however no return statement found
};

struct BreakContinueInfo
{  
// This data structure is to keep track of label to jump for break and continue
// So that it will help to jump into the write label;
 char * breakLevel;  //keep track of break label
 char * continueLevel; // keep track of continue label
};

struct FunctionInfo * fi;  // pointer to FunctionInfo object
struct BreakContinueInfo * bci;  // pointer to BreakContinueInfo object

char * CreateTempLabel(); // Togenerate new Label for asm file
void EMIT_GLOBALS(ASTnode* p, FILE* fp); // to prints global
void EMIT_STRINGS(ASTnode* p, FILE* fp); // to prints strings on asm file
void EMIT_AST(ASTnode* p, FILE* fp); // emit ast on asm file

void emit_expr(ASTnode * p, FILE *fp);  // helper function to print expressions in asm file
void emit_function(ASTnode * p, FILE *fp);  // helper function to print function code in asm
void emit_write(ASTnode * p, FILE *fp);  // helper function to write the write statements into asm
void emit_read(ASTnode * p, FILE *fp); // helper function for read
void emit_var(ASTnode * p, FILE *fp); // helper function for var
void emit_assign(ASTnode * p, FILE *fp); // helper function for assignment statement
void emit_while(ASTnode * p, FILE *fp); // helper function for while loop
void emit_if(ASTnode * p, FILE *fp);  //helper funcction for if else
void emit_args(ASTnode * p, FILE *fp);  //helper function to generate asm code for funcion arguments
void store_args_into_t(ASTnode * p, FILE *fp, int tempReigsterNumber);  // helper function to move args value into temp registers
void emit_params(ASTnode * p, FILE *fp, int tempReigsterNumber);  // helper function to get parameter values from t0 and set them into their offset
void emit_return(ASTnode * p, FILE *fp);  // helper function to print the return asm codes
void emit_break(ASTnode * p, FILE *fp);  // helper function to print break asm codes
void emit_continue(ASTnode * p, FILE *fp);  // helper function to print continue asm codes

void print_structure(ASTnode* p);  // print structure
void func_name_wise_code(char * funcName, FILE* fp);  // helper function to print functionname wise code