// Author: Abdur Razzak
// Lab: Lab 9
// emit_private.c implements functions from emit_private.h
// Resonpsible to emits the MIPS code


#include<string.h>
#include "ast.h"
#include "emit_private.h"
#include "emit.h"

int GTEMP_LABEL=0;  /* Global Temp counter */

// PRE:   Assume one up global variable GTEMP_LABEL
// POST:  Returns string with the format _t%d and increments the global vairbal
// USAGE:   creates a variable name that is used to hold temporary, intermediate
//         values in the runtime enviroment
char * CreateTempLabel() {
 char hold[100];
 char *s;
 sprintf(hold,"_L%d",GTEMP_LABEL++);
 s=strdup(hold);
 return (s);
}

// PRE: PTR to ASTNode A_FUNCTIONDEC
// POST: MIPS code in fp
void emit_function(ASTnode * p, FILE *fp){
 char s[100];
 emit(fp, p->name, "", "function definition");

 // Carve out the stack for activation record
 emit(fp, "", "move $a1, $sp", "Activation Record Carve out copy SP");
 sprintf(s,"subi $a1, $a1, %d", p->symbol->offset*WSIZE);
 emit(fp, "", s, "Activation Record carve out copy size of function");
 emit(fp, "", "sw $ra, ($a1)", "Store Return address ");
 sprintf(s, "sw $sp %d($a1)", WSIZE);
 emit(fp, "", s, "Store the old Stack pointer");
 emit(fp, "", "move $sp, $a1", "Make SP the current activation record");
 fprintf(fp, "\n\n");
 // copy the parameters to the formal from registers $t0 et
 // generate the compound statement
 EMIT_AST(p->s2, fp);
 // create an implicit return depending on if we are main or not


 // restore RA and SP before we return
 // lw $ra ($sp)
 // lw $sp $($sp)
 emit(fp, "", "lw $ra ($sp)", "restore old environment RA");
 sprintf(s, "lw, $sp %d($sp)",  WSIZE);
 emit(fp, "", s, "Return from function store SP");
 fprintf(fp, "\n");

 if (strcmp(p->name, "main") == 0){ // exit the system
  emit(fp, "", "li $v0 10", "Exit from Main, we are done");
  emit(fp, "", "syscall", "Exit everything");

 }
 else { // jump back to caller

 }
}

// PRE: PTR to ASTNode A_VAR
// POST: $a0 has exact memory location (L-value) of VAR
void emit_var(ASTnode * p, FILE *fp){
 char s[100];
 //Task: handle internal offset if array

 if (p->symbol->level == 0){  //global variable
  sprintf(s, "la $a0, %s", p->name);  // get the direct access of global variable
  emit(fp, "", s, "EMIT Var global variable");
 }
 else {  //local variable
  // stack pointer plus offset

 }
} // end of emit_read


// PRE: PTR to ASTNode A_READ
// POST: MIPS code to read in a value and place it in the VAR of READ
void emit_read(ASTnode * p, FILE *fp){
 char s[100];
 emit_var(p->s1, fp); // $a0 will be the location of the variable
 emit(fp, "", "li $v0, 5", "about to read in value");
 emit(fp, "", "syscall", "read in value $v0 now has the read in value");
 emit(fp, "", "sw $v0, ($a0)", "store read in vlaue to memory");
 fprintf(fp, "\n\n");
 
} // end of emit_read


// PRE: PTR to ASTNode A_WRITE
// POST: MIPS code in fp
// This funciton will write asm code for a write operation
void emit_write(ASTnode * p, FILE *fp){
 char s[100];
 if(p->name != NULL){
  // load address with the label and call print string
  sprintf(s ,"la $a0, %s", p->label);
  emit(fp, "", s, "The string address");
  emit(fp, "", "li $v0, 4", "About to print a string");
  emit(fp, "", "syscall", "Call write string");
  fprintf(fp, "\n\n");
 }
 else {
  emit_expr(p->s1, fp); // for the T_NUM expression and $a0 has the expression value
  emit(fp, "", "li $v0, 1", "About to print a Number");
  emit(fp, "", "syscall", "Call write number");
  fprintf(fp, "\n\n");
 }
} // end of emit_write


// PRE: PTR to a family of expressions
// POST: MIPS code in fp
// This funciton will write asm code for a expression operation
void emit_expr(ASTnode * p, FILE *fp){
 char s[100];
 switch (p->type)
 {
 case A_NUM:
  sprintf(s, "li $a0, %d", p->value);
  emit(fp, "", s, "Expression is a constant");
  return;
  break;

 case A_VARUSE:
  emit_var(p, fp);  // $a0 is the memory location
  emit(fp, "", "lw $a0 , ($a0)", "Expression is a VAR");
  return;
  break;
 
 default:
  printf("emit_expr switch NEVER SHOULD BE HERE\n");
  exit(1);
  break;
 }
} // end of emit_expr


// PRE: PTR to AST, PTR to FILE
// POST: prints out MIPS code into file, using helper functions
void EMIT_GLOBALS(ASTnode* p, FILE* fp){
 if(p == NULL 
  || p->type == A_FUNCTION_PROTO 
  || p->type == A_FUNCTIONDEC) 
  return;
 fprintf(fp, "%s: .space %d # global varaible\n", p->name, p->symbol->mysize * WSIZE);
 EMIT_GLOBALS(p->next, fp);
}



// PRE: PTR to the top of AST, PTR to FILE
// POST: prints out MIPS code into file, prints MIPS based strill into fil
void EMIT_STRINGS(ASTnode* p, FILE* fp){
 if(p == NULL) return;
 if(p->type == A_WRITE && p->name != NULL){
  p->label = CreateTempLabel();
  
  fprintf(fp,"%s: .asciiz    \%s \n", p->label, p->name);
 }
 EMIT_STRINGS(p->s1, fp);
 EMIT_STRINGS(p->s2, fp);
 EMIT_STRINGS(p->next, fp);
}


//PRE: PTR to ASTnode or NULL
//POST: MIPS code into the file for the tree
void EMIT_AST(ASTnode* p, FILE* fp){
 if(p == NULL) return;
 switch (p->type)
 {
 case A_VARDEC: // no real action
  EMIT_AST(p->next, fp);
  break;
 
 case A_FUNCTIONDEC:
  emit_function(p,fp);
  EMIT_AST(p->next, fp);  // functions are next connected
  break;

 case A_COMPOUND:  // no action for s1 vardec already in stack size
  EMIT_AST(p->s2, fp); // statements
  EMIT_AST(p->next, fp);  // compounds may has next compound
  break;

 case A_WRITE:  
  emit_write(p, fp);  // deal with using write helper function
  EMIT_AST(p->next, fp);  // write is only next connected
  break;

 case A_EXPR:
  emit_expr(p, fp);  // helper function to print on asm for expression
  EMIT_AST(p->s1, fp);  // Additive expression
  EMIT_AST(p->s2, fp);  // term or simple_expression
  break;

  case A_READ:
  emit_read(p, fp);  // helper function to print read
  EMIT_AST(p->next, fp);  // read is only next connected
  break;

 default:
  printf("EMIT_AST case %d not implemented\n", p->type);
  printf("WE SHOULD NEVER BE HERE\n");
  break;
 } // end of swtich

}