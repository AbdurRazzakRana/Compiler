// Author: Abdur Razzak
// Lab: Lab 9
// emit_private.c implements functions from emit_private.h
// Resonpsible to emits the MIPS code


#include<string.h>
#include "ast.h"
#include "emit_private.h"
#include "emit.h"

int GTEMP_LABEL=0;  /* Global Temp counter */

// PRE:   Assume one up global variable GTEMP
// POST:  Returns string with the format _t%d and increments the global vairbal
// USAGE:   creates a variable name that is used to hold temporary, intermediate
//         values in the runtime enviroment

char * CreateTempLabel()
{    
 char hold[100];
 char *s;
 sprintf(hold,"_L%d",GTEMP_LABEL++);
 s=strdup(hold);
 return (s);
}


// PRE: PTR to AST, PTR to FILE
// POST: prints out MIPS code into file, using helper functions
void EMIT_GLOBALS(ASTnode* p, FILE* fp){
 if(p == NULL 
  || p->type == A_FUNCTION_PROTO 
  || p->type == A_FUNCTIONDEC) 
  return;
 printf("%s %d\n", p->name, p->my_data_type);
 fprintf(fp, "%s: .space %d # global varaible\n", p->name, p->symbol->mysize * WSIZE);
 EMIT_GLOBALS(p->next, fp);
}



// PRE: PTR to the top of AST, PTR to FILE
// POST: prints out MIPS code into file, prints MIPS based strill into fil
void EMIT_STRINGS(ASTnode* p, FILE* fp){
 if(p == NULL) return;
 if(p->type == A_WRITE && p->name != NULL){
  fprintf(fp,"%s: .asciiz    \%s \n", CreateTempLabel(), p->name);
 }
 EMIT_STRINGS(p->s1, fp);
 EMIT_STRINGS(p->s2, fp);
 EMIT_STRINGS(p->next, fp);
}