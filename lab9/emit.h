// Author: Abdur Razzak
// Lab: Lab 9
// Semester: Spring 2024
// Purpose: Interface file for other entities to know about available functions
// provides connectivity to MIPS generating subroutines
// #ifdef EMIT_H
// #define EMIT_H
#include "ast.h"
void EMIT_GLOBALS(ASTnode* p, FILE* fp);
void EMIT(ASTnode* p, FILE* fp);
// #endif