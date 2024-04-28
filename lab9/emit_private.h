// Author: Abdur Razzak
// Lab: Lab 9
// Semester: Spring 2024
// Purpose:
// #ifdef EMIT_H
// #define EMIT_H
#include "ast.h"
char * CreateTempLabel(); // Togenerate new Label for asm file
void EMIT_GLOBALS(ASTnode* p, FILE* fp); // to prints global
void EMIT_STRINGS(ASTnode* p, FILE* fp); // to prints strings on asm file
void EMIT_AST(ASTnode* p, FILE* fp); // emit ast on asm file
// #endif