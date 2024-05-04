// Author: Abdur Razzak
// Lab: Lab 9
// Semester: Spring 2024
// Purpose: Interface file for other entities to know about available functions
// provides connectivity to MIPS generating subroutines
// #ifdef EMIT_H
// #define EMIT_H
#include "ast.h"
#define WSIZE 4
#define LOG_WSIZE 2


void emit(FILE * fp, char* label, char* command, char* comment);

void EMIT(ASTnode* p, FILE* fp);  //Emit the code first called up method
void EMIT_GLOBALS(ASTnode* p, FILE* fp); // to prints global
void EMIT_STRINGS(ASTnode* p, FILE* fp); // to prints strings on asm file
void EMIT_AST(ASTnode* p, FILE* fp); // emit ast on asm file
// #endif