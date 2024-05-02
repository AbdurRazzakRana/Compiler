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

// PRE:   ASTnode
// POST:  priniting the items of the box, will be remain same after the printing
void printStructure(ASTnode* p){
 printf("\n");
 if (p==NULL) {
  printf("p is null\n");
  return;
 }
 printf("p name: %s\n", p->name);
 printf("p type: %d\n", p->type);
 printf("p operator: %d\n", p->operator);
 printf("p data type: %d\n", p->my_data_type);
 printf("p s1: %d\n", p->s1 == NULL ? 0: 1);
 printf("p s2: %d\n", p->s2 == NULL ? 0: 1);
 printf("p next: %d\n", p->next == NULL ? 0: 1);
 printf("p value: %d\n", p->value);
 printf("p symbol: %d\n", p->symbol == NULL ? 0: 1);
 
 if(p->symbol != NULL){
  printf("p symbol name: %s\n", p->symbol->name);
  printf("p symbol offset: %d\n", p->symbol->offset);
  printf("p symbol subType: %d\n", p->symbol->SubType);
 }
 printf("\n");
}

// PRE: PTR to ASTNode A_FUNCTIONDEC
// POST: MIPS code in fp
void emit_function(ASTnode * p, FILE *fp){
 char s[100];
 emit(fp, p->name, "", "function definition");

 // Carve out the stack for activation record
 emit(fp, "", "move $a1, $sp", "Activation Record Carve out copy SP");
 sprintf(s,"subi $a1 $a1 %d", p->symbol->offset*WSIZE);
 emit(fp, "", s, "Activation Record carve out copy size of function");
 emit(fp, "", "sw $ra, ($a1)", "Store Return address ");
 sprintf(s, "sw $sp %d($a1)", WSIZE);
 emit(fp, "", s, "Store the old Stack pointer");
 emit(fp, "", "move $sp, $a1", "Make SP the current activation record");
 fprintf(fp, "\n");
 // copy the parameters to the formal from registers $t0 et
 // generate the compound statement
 EMIT_AST(p->s2, fp);
 // create an implicit return depending on if we are main or not

 // restore RA and SP before we return
 // lw $ra ($sp)
 // lw $sp $($sp)
 emit(fp, "", "li $a0, 0", "RETURN has no specified value set to 0");
 emit(fp, "", "lw $ra ($sp)", "restore old environment RA");
 sprintf(s, "lw $sp %d($sp)",  WSIZE);
 emit(fp, "", s, "Return from function store SP");
 fprintf(fp, "\n");

 if (strcmp(p->name, "main") == 0){ // exit the system
  emit(fp, "", "li $v0, 10", "Exit from Main, we are done");
  emit(fp, "", "syscall", "Exit everything");

 }
 else { // jump back to caller

 }
 sprintf(s, "END OF FUNCTION %s",  p->name);
 emit(fp, "", "", s);
 fprintf(fp, "\n");
}

// PRE: PTR to ASTNode A_VAR
// POST: $a0 has exact memory location (L-value) of VAR
void emit_var(ASTnode * p, FILE *fp){
 char s[100];
 //Task: handle internal offset if array
 printf("emit_var\n");
 printStructure(p);
 if (p->s1 != NULL){  // variable is an array
  emit_expr(p->s1, fp);  // a0 has the expression
  printf("emit_var: index expr calculated\n");
  emit(fp,"", "move $a1, $a0", "VAR copy index array in a1");
  // sprintf(s, "sll $a1 $a1 %d", p->s1->value);
  sprintf(s, "sll $a1 $a1 2");
  emit(fp,"", s, "Muliply the index by wordszie via SLL");
 }

 if (p->symbol->level == 0){  //global variable
  sprintf(s, "la $a0, %s", p->name);  // get the direct access of global variable
  emit(fp, "", s, "EMIT Var global variable");
 }
 else {  //local variable
  // stack pointer plus offset
  emit(fp, "", "move $a0 $sp", "VAR local make a copy of stackpointer");
  sprintf(s, "addi $a0 $a0 %d", p->symbol->offset * WSIZE);
  emit(fp, "", s, "VAR local stack pointer plus offset");

  if (p->s1 != NULL){ // need to add additional offset for array
   emit(fp, "", "add $a0 $a0 $a1", "VAR array add internal offset");
  }
 }
} // end of emit_var


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
 printStructure(p);
 switch (p->type)
 {
 case A_NUM:
  sprintf(s, "li $a0, %d", p->value);
  emit(fp, "", s, "Expression is a constant");
  return;
  break;

 case A_VARUSE:
  emit_var(p, fp);  // $a0 is the memory location
  emit(fp, "", "lw $a0, ($a0)", "Expression is a VAR");
  return;
  break;
 case A_EXPR:
  printf("Expression\n");
  if(p->operator == A_UNIRY_MINUS){ // handle unary minus case

  }
  else {  //other regular case
   emit_expr(p->s1, fp);  // a0 pointing to exact mem location
   sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
   emit(fp, "", s, "LHS of expression stored into temp memory");
   emit_expr(p->s2, fp); // for RHS simple expression or term, a0 holds the mem location
   
   // at this moment we have both LHS AND RHS, now load them into two registers
   emit(fp, "", "move $a1, $a0", "RHS on a1");
   sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);
   emit(fp, "", s, "Getting LHS into a0 from mem");

   // no we have LHS in a0, OPERATOR, RHS in a1
   switch (p->operator)
   {
   case A_PLUS:
    emit(fp, "", "add $a0, $a0, $a1", "Add Expression and keeping value in a0");
    return;
   // case A_MINUS:
    
   //  return;

   // case A_DEVIDE:
    
   //  return;
   // case A_TIMES:
    
   //  return;
   //  break;

   // case A_MOD:
    
   //  return;
   //  break;
   // case A_LESSEQUAL:
    
   //  return;
   //  break;
   
   case A_LESSTHAN:
    emit(fp, "", "slt $a0, $a0, $a1", "Expression Less Than");
    return;
    break;

   // case A_GREATERTHAN:
    
   //  return;
   //  break;
   // case A_GREATEREQUAL:
    
   //  return;
   //  break;

   // case A_EQUAL:
    
   //  return;
   //  break;
   
   // case A_NOTEQUAL:
    
   //  return;
   //  break;

   
   default:
    printf("EXPRESSION OPERATION NOT WRITTEN YET, ASAP FIX\n");
    exit(1);
    return;
    break;
    
   } 

  }
  return;
  break;
 
 default:
  printf("emit_expr switch NEVER SHOULD BE HERE\n");
  exit(1);
  break;
 }
} // end of emit_expr

// PRE: PTR to ASTNode with A_ASSGN_STAT
// POST: MIPS code for the assignment instructions into the given file
void emit_assign(ASTnode * p, FILE *fp){  // for example x = 10;
 if (p == NULL) return; // we know assignment statement is not NULL, just to make sure the 11th commendment
 char s[100];
 
 // get the simple expression code generation first for RHS, 10 in the example
 emit_expr(p->s2, fp);  //a0 is loaded with the value
 sprintf(s ,"sw $a0 %d($sp)", p->symbol->offset*WSIZE);
 emit(fp, "", s, "Assign store RHS temporarily");

 emit_var(p->s1, fp); // get the lhs var, after this a0 is pointint to exact mem pointer of x

 // assign the RHS into LHS
 sprintf(s ,"lw $a1 %d($sp)", p->symbol->offset*WSIZE);
 emit(fp, "", s, "Assign get RHS temporarily");
 emit(fp, "", "sw $a1 ($a0)", "Assign the RHS into the memory of LHS");
 fprintf(fp, "\n\n");
} // end of emit_assign


// PRE: PTR to ASTNode A_WHILE_STAT
// POST: MIPS code to write on the file
void emit_while(ASTnode * p, FILE *fp){  // p is not null for sure
 char s[100];
 char loopin[100];
 char loopout[100];
 printf("WHILE ENCHELADA start\n");

 //sprintf(s ,"sw $a0 %d($sp)", p->symbol->offset*WSIZE);
 //emit(fp, "", s, "Assign store RHS temporarily");
 // Labels for the loop
 sprintf(loopin ,"%s", CreateTempLabel());
 sprintf(loopout ,"%s", CreateTempLabel());

 // Loop will be running at least one time therefore creating first block
 sprintf(s, "%s:", loopin);
 fprintf(fp, "%s\t\t#While Loop START\n", s); // to ensure the indentation
 // emit(fp, "", s, "While loop level, loop START");

 emit_expr(p->s1, fp);  //expression of while condition, a0 has the value of condition

 sprintf(s, "beq $a0 $0 %s", loopout);  // go to loop out level if the condition is false
 emit(fp, "", s, "WHILE branch out taking decision");

 //while body, if loopout branch not taken
 EMIT_AST(p->s2, fp);

 sprintf(s, "j %s", loopin);   //Jump to loop level again
 emit(fp, "", s, "Jump to loop level again, loop continue");

 // sprintf(s, "%s:", loopout);
 // emit(fp, "", s, "Level of While loop END");

 sprintf(s, "%s:", loopout);
 fprintf(fp, "%s\t\t#While Loop END\n", s);  // printing directly to maintain indentation

 printf("WHILE ENCHELADA end\n");
} // end of emit_while

// PRE: PTR to AST, PTR to FILE
// POST: prints out MIPS code into file, using helper functions
void EMIT_GLOBALS(ASTnode* p, FILE* fp){
 if(p == NULL) return;   // return when p is null
 if (p->type == A_FUNCTION_PROTO 
  || p->type == A_FUNCTIONDEC){
   // do nothing when its function dec or prototype,
   //do not return to show variables afterwords
  }   
 else   //its a global varialbe
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
 printf("%s %d\n", p->name, p->type);
 switch (p->type) {
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

  case A_ASSGN_STAT:
   emit_assign(p, fp);
   EMIT_AST(p->next, fp); // for the same level next assignment
   break;

  case A_WHILE_STAT:
   emit_while(p, fp);
   EMIT_AST(p->next, fp); // while is next connected
   break;

  default:
   printf("EMIT_AST case %d not implemented\n", p->type);
   printf("WE SHOULD NEVER BE HERE\n");
   break;
 } // end of swtich

}