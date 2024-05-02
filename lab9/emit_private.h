// Author: Abdur Razzak
// Lab: Lab 9
// Semester: Spring 2024
// Purpose:

#include "ast.h"
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
void printStructure(ASTnode* p);