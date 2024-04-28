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
void EMIT_GLOBALS(ASTnode* p, FILE* fp);
void EMIT(ASTnode* p, FILE* fp);
// #endif