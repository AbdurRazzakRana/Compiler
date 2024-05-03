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
void print_structure(ASTnode* p){
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

// PRE: Function name
// POST: Generate machine code based on it is main or not
void func_name_wise_code(char * funcName, FILE *fp){
  if (strcmp(funcName, "main") == 0){ // exit the system
  emit(fp, "", "li $v0, 10", "Exit from Main, we are done");
  emit(fp, "", "syscall", "Exit everything");

 }
 else { // jump back to caller
  emit(fp, "", "jr $ra", "Jump to the caller address");
 }
}
// PRE: PTR to ASTNode A_FUNCTIONDEC
// POST: MIPS code in fp
void emit_function(ASTnode * p, FILE *fp){
 char s[100];
 emit(fp, p->name, "", "function definition");
 
 fi->functionName = p->name;

 //Function reuturn type checking is turned off after discussing with professor
//  fi->returnType = p->my_data_type;
//  fi->isReturnStmtFound = 0;

 // Carve out the stack for activation record
 emit(fp, "", "move $a1, $sp", "Activation Record Carve out copy SP");
 sprintf(s,"subi $a1 $a1 %d", p->symbol->offset*WSIZE);
 emit(fp, "", s, "Activation Record carve out copy size of function");
 emit(fp, "", "sw $ra, ($a1)", "Store Return address ");
 sprintf(s, "sw $sp %d($a1)", WSIZE);
 emit(fp, "", s, "Store the old Stack pointer");
 emit(fp, "", "move $sp, $a1", "Make SP the current activation record");
 fprintf(fp, "\n");
 
 // copy the parameters to the formal from registers $t0 and so on
 // t0 to tn is already loaded by emit_args, need to fetch it and set them into sp+offset
 emit_params(p->s1, fp, 0);

 // generate the compound statement
 EMIT_AST(p->s2, fp);
 

 //At this point, after the compound statnemt, if the funciton return type is INT
 // and no return statement found, should barf
 // other funciton return type mismatches are covered inside emit_return
 // return type checking is off
//  if(!fi->isReturnStmtFound && p->my_data_type == A_INTTYPE){
//   printf("BARF: Function %s should return an INT, NO RETURN STMT FOUND\n", p->name);
//   exit(1);
//  }
 
 // create an implicit return depending on if we are main or not

 // restore RA and SP before we return
 // lw $ra ($sp)
 // lw $sp $($sp)
 emit(fp, "", "li $a0, 0", "RETURN has no specified value set to 0");
 emit(fp, "", "lw $ra ($sp)", "restore old environment RA");
 sprintf(s, "lw $sp %d($sp)",  WSIZE);
 emit(fp, "", s, "Return from function store SP");
 fprintf(fp, "\n");

 func_name_wise_code(p->name, fp);
 sprintf(s, "END OF FUNCTION %s",  p->name);
 emit(fp, "", "", s);
 fprintf(fp, "\n");
}

// PRE: PTR to ASTNode A_VAR
// POST: $a0 has exact memory location (L-value) of VAR
void emit_var(ASTnode * p, FILE *fp){
 char s[100];
 //Task: handle internal offset if array
 // printStructure(p);  //debug prints
 if (p->s1 != NULL){  // variable is an array
  emit_expr(p->s1, fp);  // a0 has the expression
  // printf("emit_var: index expr calculated\n");
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

// PRE: PTR to ASTNode A_ARGS
// POST: MIPS code in fp for arguments processing, return the number of args
void emit_args(ASTnode * p, FILE *fp){
 if (p == NULL)  //Arguments could be NULL
  return;
 char s[100];
 // argument expression
 emit_expr(p->s1, fp);  // a0 holds the output
 sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);  // Store arg into sp+offset pos
 emit(fp, "", s, "Store arg into memory offset location");

 emit_args(p->next, fp);  //next argument
} // end of emit_args

// PRE: PTR to ASTNode A_ARGS
// POST: MIPS code in fp for arguments to store into temporary varaibles t
void store_args_into_t(ASTnode * p, FILE *fp, int tempReigsterNumber){
 if (p == NULL)  //Arguments could be NULL
  return;
 char s[100];
 
 // correspondent arguments values are loaded from sp + their offset and set into a0
 sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);  // load from sp + offset
 emit(fp, "", s, "Previously stored arg Load into a0");

 sprintf(s, "move $t%d, $a0", tempReigsterNumber);  // Arguments to temp register with proper counter
 emit(fp, "", s, "Arg to temp");

 tempReigsterNumber++;  // next argument will be in next t register
 store_args_into_t(p->next, fp, tempReigsterNumber);
} // end of store_args_into_t


// PRE: PTR to ASTNode A_PARAMS
// POST: MIPS code in fp to fetch the data from t registers and set them into function sp+offset
void emit_params(ASTnode * p, FILE *fp, int tempReigsterNumber){
 if (p == NULL)  //Arguments could be NULL
  return;
 char s[100];
 
 // correspondent t registers values are stored into sp + their offset
 sprintf(s, "sw $t%d %d($sp)", tempReigsterNumber, p->symbol->offset * WSIZE);  // load from sp + offset
 emit(fp, "", s, "Store value from temp registers into funcion sp + offset pos");

 tempReigsterNumber++;  // next argument will be in next t register
 emit_params(p->next, fp, tempReigsterNumber);
} // end of emit_params

// PRE: PTR to a family of expressions
// POST: MIPS code in fp
// This funciton will write asm code for a expression operation
void emit_expr(ASTnode * p, FILE *fp){
 char s[100];
 // printStructure(p);  //debug print to see the structure scenario
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
  // printf("Expression\n");
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
   case A_MINUS:
    emit(fp, "", "sub $a0, $a0, $a1", "Subtraction Expression and keeping value in a0");
    return;

   case A_TIMES:
    emit(fp, "", "mult $a0 $a1", "Multiply Expression");
    emit(fp, "", "mflo $a0", "Setting low 32 bits into a0 after multiply");
    return;

   case A_DEVIDE:
    emit(fp, "", "div $a0 $a1", "Devide Expression");
    emit(fp, "", "mflo $a0", "Setting low 32 bits into a0 after devide");
    return;

   case A_MOD:
    emit(fp, "", "div $a0 $a1", "Mod Expression, devide first");
    emit(fp, "", "mfhi $a0", "Among the 64 bits, high 32 keeps the reminder");
    return;

   case A_LESSEQUAL:
    emit(fp, "", "add $a1, $a1, 1", "Less Than Equal Expr, incrementing RHS by one");
    emit(fp, "", "slt $a0, $a0, $a1", "Now check is the LHS is less than RHS");
    return;
   
   case A_LESSTHAN:
    emit(fp, "", "slt $a0, $a0, $a1", "Expression Less Than");
    return;

   case A_GREATERTHAN:
    emit(fp, "", "slt $a0, $a1, $a0", "Greater Than check is same chekcing LT reverse");
    return;

   case A_GREATEREQUAL:
    emit(fp, "", "add $a1, $a1, 1", "Greater Than Equal Expr, incrementing RHS by one");
    emit(fp, "", "slt $a0, $a1, $a0", "Now check is the RHS is less than LHS");
    return;

   case A_EQUAL:
    emit(fp, "", "slt $t0, $a0, $a1", "To check equal, taking less than of a0<a1");
    emit(fp, "", "slt $t1, $a1, $a0", "Now check a1<a0 and store another temp var");
    emit(fp, "", "nor $a0, $t0, $t1", "Nor gate will show the proper output");
    emit(fp, "", "andi $a0, 1", "And to make sure the answer value is only 1 at 0th index");
    return;
   
   case A_NOTEQUAL:
    emit(fp, "", "slt $t0, $a0, $a1", "To check NOT equal, taking less than of a0<a1");
    emit(fp, "", "slt $t1, $a1, $a0", "Now check a1<a0 and store another temp var");
    emit(fp, "", "or $a0, $t0, $t1", "OR gate will show the result of Not Equal");
    emit(fp, "", "andi $a0, 1", "And to make sure the answer value is only 1 at 0th index");
    return;

   default:
    printf("EXPRESSION OPERATION NOT WRITTEN YET, ASAP FIX\n");
    exit(1);
    return;
    break;
    
   }
  }
  return;
  break;

  case A_FUNC_CALL:
   emit_args(p->s1, fp);  // process the argument first before function call
   // store them into temporary registers t
   store_args_into_t(p->s1, fp, 0);  // move all args into appropriate temp registers
   sprintf(s, "jal %s", p->name);  // Now ready to call the function
   emit(fp, "", s, "Function Call");
   fprintf(fp, "\n");
   return;
 
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
 // printf("WHILE ENCHELADA start\n");

 //sprintf(s ,"sw $a0 %d($sp)", p->symbol->offset*WSIZE);
 //emit(fp, "", s, "Assign store RHS temporarily");
 // Labels for the loop
 sprintf(loopin ,"%s", CreateTempLabel());
 sprintf(loopout ,"%s", CreateTempLabel());
 bci->breakLevel = loopout;  // keeping the loop exit label to break when needed
 bci->continueLevel = loopin;  // keeping the loop in label to continue when needed

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

 // printf("WHILE ENCHELADA end\n");
} // end of emit_while


// PRE: PTR to ASTNode A_IF
// POST: MIPS code to perform if else condition
void emit_if(ASTnode * p, FILE *fp){  // As the p is A_IF, it is not NULL
 char s[100];
 char elsebody[100];
 char endif[100];

 sprintf(elsebody,"%s", CreateTempLabel());
 sprintf(endif,"%s", CreateTempLabel());
 emit_expr(p->s1, fp);  // for expression condition, a0 has the branch deciding value
 sprintf(s ,"beq $a0 $0 %s",elsebody);
 emit(fp, "", s, "IF branch decision, taken to else condidion or continue to if body");
 EMIT_AST(p->s2->s1, fp);  // for the if statement
 sprintf(s, "j %s", endif);
 emit(fp, "", s, "As else is not taken, jump to loop end");

 sprintf(s, "%s:", elsebody);
 fprintf(fp, "%s\t\t#Else target level if the branch is taken\n", s);  // printing directly to maintain indentation
 if (p->s2->s2 != NULL){  // check if else statement exist
  EMIT_AST(p->s2->s2, fp);  // for else statement
 }

 sprintf(s, "%s:", endif);
 fprintf(fp, "%s\t\t# End of If Scope\n", s);  // printing directly to maintain indentation

} // end of emit_read

// PRE: PTR to ASTNode A_BREAK
// POST: MIPS Code to perform break asm lines
void emit_break(ASTnode * p, FILE * fp){  // p is at A_BREAK, not NULL
 char s[100];
 sprintf(s, "j %s", bci->breakLevel);
 emit(fp, "", s, "Break the loop and jump to Loop End");
}  // end of emit_break

// PRE: PTR to ASTNode A_CONTINUE
// POST: MIPS Code to perform continue asm lines
void emit_continue(ASTnode * p, FILE * fp){  // p is at A_CONTINUE, not NULL
 char s[100];
 sprintf(s, "j %s", bci->continueLevel);
 emit(fp, "", s, "Continue to the loop begin and skip rest part of the loop ");
}  // end of emit_continue


// PRE: PTR to ASTNode A_RETURN_STAT
// POST: MIPS code to perform return statement
void emit_return(ASTnode * p, FILE *fp){  // As the p is A_RETURN_STAT box, it is not NULL
 char s[100];
 char elsebody[100];
 char endif[100];
 
 emit(fp, "", "", "Return Statement explicitely mentioned");

 if (p->s1 == NULL){  //return without any expression, return;
  // return type chekcing off 
  // if (fi->returnType == A_INTTYPE){
  //  printf("BURF: Return type mismatch in Function %s!!\n", fi->functionName);
  //  exit(1);
  // }
  // fi->isReturnStmtFound = 0;
  
  emit(fp, "", "li $a0, 0", "RETURN has no specified value set to 0");
  emit(fp, "", "lw $ra ($sp)", "restore old environment RA");
  sprintf(s, "lw $sp %d($sp)",  WSIZE);
  emit(fp, "", s, "Return from function store SP");
  fprintf(fp, "\n");
 } else{  // return has an expression
  // Return type checking off
  //  if (fi->returnType != p->s1->my_data_type){
  //   printf("BURF: Return type mismatch in Function %s!!\n", fi->functionName);
  //   exit(1);
  //  }
  //  fi->isReturnStmtFound = 1;
   emit_expr(p->s1, fp);

   emit(fp, "", "lw $ra ($sp)", "Load the old environment RA");
   emit(fp, "", "lw $sp 4($sp)", "Return from function stack pointer");
   fprintf(fp, "\n");
 }
 func_name_wise_code(fi->functionName, fp);
} // end of emit_return


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
 // printf("%s %d\n", p->name, p->type);
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

  case A_IF:
   emit_if(p, fp);
   EMIT_AST(p->next, fp); // while is next connected
   break;
  
  case A_EXPR_STAT:  // could be expr; or ;
   // printStructure(p);
   if (p->s1 != NULL)  // only call expr if p->s1 has an expression
    emit_expr(p->s1, fp);
   EMIT_AST(p->next, fp);  // next statement
   break;
  
  case A_RETURN_STAT:
   emit_return(p, fp);
   EMIT_AST(p->next, fp);  // next statement
   break;

  case A_BREAK:
   emit_break(p, fp);
   EMIT_AST(p->next, fp);  // next statement
   break;

  case A_CONTINUE:
   emit_continue(p, fp);
   EMIT_AST(p->next, fp);  // next statement
   break;

  default:
   printf("EMIT_AST case %d not implemented\n", p->type);
   printf("WE SHOULD NEVER BE HERE\n");
   break;
 } // end of swtich

}