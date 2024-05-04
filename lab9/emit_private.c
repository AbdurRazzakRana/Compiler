// Author: Abdur Razzak
// Lab: Lab 9
// Date: May 3,2024
// emit_private.c implements functions from emit_private.h
// This file is responsible to print all the asm machine code
// Input: AST tree
// Output: machine code into given file

#include <string.h>
#include "ast.h"
#include "emit_private.h"
#include "emit.h"

int GTEMP_LABEL = 0; /* Global Temp counter */

// PRE:   Assume one up global variable GTEMP_LABEL
// POST:  Returns string with the format _L%d and increments the global vairbal
// This label will be used to mark label in asm code
char *CreateTempLabel()
{
  char hold[100];
  char *s;
  sprintf(hold, "_L%d", GTEMP_LABEL++); // creating the label for global data space
  s = strdup(hold);
  return (s);
}

// PRE: PTR to the function name and file pointer
// POST: Generate machine code based on it is main or not.
// Specially few function ending code for main and others are common,
// they are mentioned here to avoid repeated code
void func_name_wise_code(char *funcName, FILE *fp)
{
  if (strcmp(funcName, "main") == 0) // for main function
  {                                  // exit the system
    emit(fp, "", "li $v0, 10", "Exit from Main, we are done");
    emit(fp, "", "syscall", "Exit everything");
  }
  else // for other callee functions
  {    // jump back to caller
    emit(fp, "", "jr $ra", "Jump to the caller address");
  }
}

// PRE: PTR to ASTNode A_FUNCTIONDEC
// POST: MIPS code in fp
// This function responsible to generate all mips code for function declarations,
// activation curve out, initial processing for stact pointers
void emit_function(ASTnode *p, FILE *fp)
{
  char s[100];
  emit(fp, p->name, "", "function definition");

  fi->functionName = p->name;
  parameterArrayCounter = 0; // initialize the counter;
  // Function reuturn type checking is turned off after discussing with professor
  //  fi->returnType = p->my_data_type;
  //  fi->isReturnStmtFound = 0;

  // Carve out the stack for activation record
  emit(fp, "", "move $a1, $sp", "Activation Record Carve out copy SP");
  sprintf(s, "subi $a1 $a1 %d", p->symbol->offset * WSIZE);
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

  parameterArrayCounter = 0; // out of function parameter use scope, no need, resetting;

  /* return type checking is off*/
  //  if(!fi->isReturnStmtFound && p->my_data_type == A_INTTYPE){
  //   printf("BARF: Function %s should return an INT, NO RETURN STMT FOUND\n", p->name);
  //   exit(1);
  //  }

  emit(fp, "", "li $a0, 0", "RETURN has no specified value set to 0"); // implicit return
  emit(fp, "", "lw $ra ($sp)", "restore old environment RA");          // restoring RA before return
  sprintf(s, "lw $sp %d($sp)", WSIZE);
  emit(fp, "", s, "Return from function store SP"); // restoring SP before reutrn
  fprintf(fp, "\n");

  func_name_wise_code(p->name, fp); // function ending code for main or other
  sprintf(s, "END OF FUNCTION %s", p->name);
  emit(fp, "", "", s);
  fprintf(fp, "\n");
}

// PRE: PTR to ASTNode A_VAR use
// POST: $a0 has exact memory location (L-value) of VAR
// This function will produce all the mips code for variable use;
void emit_var(ASTnode *p, FILE *fp)
{
  char s[100];
  if (p->s1 != NULL)
  {                       // variable is an array
    emit_expr(p->s1, fp); // a0 has the expression
    emit(fp, "", "move $a1, $a0", "VAR copy index array in a1");
    sprintf(s, "sll $a1 $a1 2");
    emit(fp, "", s, "Muliply the index by wordszie via SLL"); // multiply the offset with word side
  }

  if (p->symbol->level == 0)
  {                                              // global variable
    sprintf(s, "la $a0, %s", p->name);           // get the direct access of global variable
    emit(fp, "", s, "EMIT Var global variable"); // load the variable using name
    if (p->s1 != NULL)
    {                                                                   // variable is an array
      emit(fp, "", "add $a0 $a0 $a1", "VAR array add internal offset"); // adding additional offset for array
    }
  }
  else
  {                                                                        // local variable, stack pointer plus offset
    emit(fp, "", "move $a0 $sp", "VAR local make a copy of stackpointer"); // taking stack pointer
    sprintf(s, "addi $a0 $a0 %d", p->symbol->offset * WSIZE);
    emit(fp, "", s, "VAR local stack pointer plus offset"); // adding the offset for the var

    if (p->s1 != NULL)
    {                                // need to add additional offset for array
      if (parameterArrayCounter > 0) // Need to check if the var is a parameter arrray
      {
        int isFound = 0, i;
        for (i = 0; i < parameterArrayCounter; i++)
        { // Looking through the stored parameter array
          if (strcmp(p->name, parameterArray[i]) == 0)
          {
            isFound = 1; // marking as found
            break;
          }
        }
        // IF Array has recieved as paramer in other function, hence needs to acess the *A address first
        // before looking for internal offset access
        if (isFound)
          emit(fp, "", "lw $a0 ($a0)", "Array address accessed as it passed as params in func");
      }
      emit(fp, "", "add $a0 $a0 $a1", "VAR array add internal offset"); // adding the array internal offset
    }
  }
} // end of emit_var

// PRE: PTR to ASTNode A_READ
// POST: MIPS code to read in a value and place it in the VAR of READ
void emit_read(ASTnode *p, FILE *fp)
{
  char s[100];
  emit_var(p->s1, fp);                                                    // $a0 will be the location of the variable
  emit(fp, "", "li $v0, 5", "about to read in value");                    // setting up for read
  emit(fp, "", "syscall", "read in value $v0 now has the read in value"); // syscall to read
  emit(fp, "", "sw $v0, ($a0)", "store read in vlaue to memory");         // store the value
  fprintf(fp, "\n\n");

} // end of emit_read

// PRE: PTR to ASTNode A_WRITE
// POST: MIPS code in fp
// This funciton will write asm code for a write operation
void emit_write(ASTnode *p, FILE *fp)
{
  char s[100];
  if (p->name != NULL)
  { // Label to print
    // load address with the label and call print string
    sprintf(s, "la $a0, %s", p->label);
    emit(fp, "", s, "The string address"); // load the label
    emit(fp, "", "li $v0, 4", "About to print a string");
    emit(fp, "", "syscall", "Call write string"); // syscall to print
    fprintf(fp, "\n\n");
  }
  else
  {                       // expression to print
    emit_expr(p->s1, fp); // for the expression and $a0 has the expression value
    emit(fp, "", "li $v0, 1", "About to print a Number");
    emit(fp, "", "syscall", "Call write number"); // sys call to print
    fprintf(fp, "\n\n");
  }
} // end of emit_write

// PRE: PTR to ASTNode A_ARGS
// POST: MIPS code in fp for arguments processing, return the number of args
void emit_args(ASTnode *p, FILE *fp)
{
  if (p == NULL) // Arguments could be NULL
    return;
  char s[100];
  // argument expression
  emit_expr(p->s1, fp); // a0 holds the output
  sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
  emit(fp, "", s, "Store arg into memory offset location"); // Store arg into sp+offset pos
  emit_args(p->next, fp);                                   // next argument
} // end of emit_args

// PRE: PTR to ASTNode A_ARGS
// POST: MIPS code in fp for arguments to store into temporary varaibles t
void store_args_into_t(ASTnode *p, FILE *fp, int tempReigsterNumber)
{
  if (p == NULL) // Arguments could be NULL
    return;
  char s[100];

  // correspondent arguments values are loaded from sp + their offset and set into a0
  sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);
  emit(fp, "", s, "Previously stored arg Load into a0"); // load from sp + offset

  sprintf(s, "move $t%d, $a0", tempReigsterNumber);
  emit(fp, "", s, "Arg to temp"); // Arguments to temp register with proper counter

  tempReigsterNumber++;                               // next argument will be in next t register
  store_args_into_t(p->next, fp, tempReigsterNumber); // next argument with incremented t register
} // end of store_args_into_t

// PRE: PTR to ASTNode A_PARAMS
// POST: MIPS code in fp to fetch the data from t registers and set them into function sp+offset
void emit_params(ASTnode *p, FILE *fp, int tempReigsterNumber)
{
  if (p == NULL) // Arguments could be NULL
    return;
  char s[100];

  // correspondent t registers values are stored into sp + their offset
  sprintf(s, "sw $t%d %d($sp)", tempReigsterNumber, p->symbol->offset * WSIZE);
  emit(fp, "", s, "Store value from temp registers into funcion sp + offset pos"); // store from t to from sp + offset

  if (p->value == -1)
  {                                                         // array as params
    strcpy(parameterArray[parameterArrayCounter], p->name); // keeping the name into a list of parameter array
    parameterArrayCounter = parameterArrayCounter + 1;      // incrementing the counter,
    // will be used when need to differentiate parameter array vs local array
  }
  tempReigsterNumber++;                         // next argument will be in next t register
  emit_params(p->next, fp, tempReigsterNumber); // next argument to process with incremented register
} // end of emit_params

// PRE: PTR to a family of expressions
// POST: MIPS code in fp
// This funciton will write asm code for a expression operation
void emit_expr(ASTnode *p, FILE *fp)
{
  char s[100];
  // printStructure(p);  //debug print to see the structure scenario
  switch (p->type)
  {
  case A_NUM: // when its a number
    sprintf(s, "li $a0, %d", p->value);
    emit(fp, "", s, "Expression is a constant"); // load immidiate
    return;
    break;

  case A_VARUSE:                                                   // variable in use
    emit_var(p, fp);                                               // $a0 is the memory location
    if (fi->isCallingFunc == 1 && p->symbol->SubType == SYM_ARRAY) // variable is used in func call and its an array
    {
      // No need to load a0 address in this case, becaseu a0 itself the address of array
    }
    else
      emit(fp, "", "lw $a0, ($a0)", "Expression is a VAR"); // perform load operation when its a variable
    return;
    break;

  case A_EXPR:                       // when its an expression
    if (p->operator== A_UNIRY_MINUS) // perform unary minus operation
    {
      emit(fp, "", "li $a0, -1", "For Unary Operation, load -1 first"); // load -1 to a0

      sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
      emit(fp, "", s, "Store -1 to the appropriate offset memory"); // Storing -1 into offset mem

      emit_expr(p->s1, fp); // at this moment a0 has the answer
      // move a0 to a1, to keep a0 avaialble to hold the other operands which is -1 in this case
      emit(fp, "", "move $a1, $a0", "Move Right factor value into a1");

      // load the -1 that we stored earliner into a0
      sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);
      emit(fp, "", s, "Getting previously stored -1 into a0");

      // Doing multiplication operation between a0 and a1
      // And keeping the final output into a0
      emit(fp, "", "mult $a0 $a1", "Multiply Expression");
      emit(fp, "", "mflo $a0", "Setting low 32 bits into a0 after multiply");
    }
    else
    {                       // other regular case
      emit_expr(p->s1, fp); // a0 pointing to exact mem location
      sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
      emit(fp, "", s, "LHS of expression stored into temp memory"); // store lhs using offset
      emit_expr(p->s2, fp);                                         // for RHS simple expression or term, a0 holds the mem location

      // at this moment we have both LHS AND RHS, now load them into two registers
      emit(fp, "", "move $a1, $a0", "RHS on a1"); // ao -> a1
      sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);
      emit(fp, "", s, "Getting LHS into a0 from mem"); // loading left side into a0

      // no we have LHS in a0, OPERATOR, RHS in a1
      switch (p->operator)
      {
      case A_PLUS:
        emit(fp, "", "add $a0, $a0, $a1", "Add Expression and keeping value in a0"); // add operation
        return;
      case A_MINUS:
        emit(fp, "", "sub $a0, $a0, $a1", "Subtraction Expression and keeping value in a0"); // subtraction
        return;

      case A_TIMES:
        emit(fp, "", "mult $a0 $a1", "Multiply Expression");                    // multiply opps
        emit(fp, "", "mflo $a0", "Setting low 32 bits into a0 after multiply"); // taking low bits
        return;

      case A_DEVIDE:
        emit(fp, "", "div $a0 $a1", "Devide Expression");                     // devide opps
        emit(fp, "", "mflo $a0", "Setting low 32 bits into a0 after devide"); // setting low bits
        return;

      case A_MOD:
        emit(fp, "", "div $a0 $a1", "Mod Expression, devide first");               // devide opps
        emit(fp, "", "mfhi $a0", "Among the 64 bits, high 32 keeps the reminder"); // keeping the reminder bits
        return;

      case A_LESSEQUAL:
        emit(fp, "", "add $a1, $a1, 1", "Less Than Equal Expr, incrementing RHS by one"); // incrementing rhs by 1
        emit(fp, "", "slt $a0, $a0, $a1", "Now check is the LHS is less than RHS");       // performing less than opps
        return;

      case A_LESSTHAN:
        emit(fp, "", "slt $a0, $a0, $a1", "Expression Less Than"); // less than operation
        return;

      case A_GREATERTHAN:
        emit(fp, "", "slt $a0, $a1, $a0", "Greater Than check is same chekcing LT reverse"); // performing less than opps in opposite direction
        return;

      case A_GREATEREQUAL:
        emit(fp, "", "add $a1, $a1, 1", "Greater Than Equal Expr, incrementing RHS by one"); // adding 1 to rhs
        emit(fp, "", "slt $a0, $a1, $a0", "Now check is the RHS is less than LHS");          // perform less than opps
        return;

      case A_EQUAL:
        emit(fp, "", "slt $t0, $a0, $a1", "To check equal, taking less than of a0<a1");          // if ao is less than a1
        emit(fp, "", "slt $t1, $a1, $a0", "Now check a1<a0 and store another temp var");         // if a1 less than a0
        emit(fp, "", "nor $a0, $t0, $t1", "Nor gate will show the proper output");               // neither of these case will be the equal equal case
        emit(fp, "", "andi $a0, 1", "And to make sure the answer value is only 1 at 0th index"); // AND to nesure the final ans is 1 or 0 in 1 bit
        return;

      case A_NOTEQUAL:
        emit(fp, "", "slt $t0, $a0, $a1", "To check NOT equal, taking less than of a0<a1");      // if ao is less than a1
        emit(fp, "", "slt $t1, $a1, $a0", "Now check a1<a0 and store another temp var");         // if a1 less than a0
        emit(fp, "", "or $a0, $t0, $t1", "OR gate will show the result of Not Equal");           // either of the cases are NOT EQUAL case
        emit(fp, "", "andi $a0, 1", "And to make sure the answer value is only 1 at 0th index"); // AND to nesure the final ans is 1 or 0 in 1 bit
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

  case A_FUNC_CALL:        // for function call
    fi->isCallingFunc = 1; // scope of function call
    emit_args(p->s1, fp);  // process the argument first before function call
    fi->isCallingFunc = 0;
    // store them into temporary registers t
    store_args_into_t(p->s1, fp, 0); // move all args into appropriate temp registers
    sprintf(s, "jal %s", p->name);
    emit(fp, "", s, "Function Call"); // Now ready to call the function
    fprintf(fp, "\n");
    return;

  default:
    printf("emit_expr switch NEVER SHOULD BE HERE\n");
    exit(1);
    break;
  }
} // end of emit_expr

// PRE: PTR to ASTNode with A_ASSGN_STAT
// POST: MIPS code for the assignment statement into the given file
void emit_assign(ASTnode *p, FILE *fp)
{ // for example x = 10;
  if (p == NULL)
    return; // we know assignment statement is not NULL, just to make sure the 11th commendment
  char s[100];

  // get the simple expression code generation first for RHS, 10 in the example
  emit_expr(p->s2, fp); // a0 is loaded with the value
  sprintf(s, "sw $a0 %d($sp)", p->symbol->offset * WSIZE);
  emit(fp, "", s, "Assign store RHS temporarily"); // storing into appropritte memory with offset

  emit_var(p->s1, fp); // get the lhs var, after this a0 is pointint to exact mem pointer of x

  // assign the RHS into LHS
  sprintf(s, "lw $a1 %d($sp)", p->symbol->offset * WSIZE);
  emit(fp, "", s, "Assign get RHS temporarily");                         // load the mem address with offset
  emit(fp, "", "sw $a1 ($a0)", "Assign the RHS into the memory of LHS"); // store the answer
  fprintf(fp, "\n\n");
} // end of emit_assign

// PRE: PTR to ASTNode A_WHILE_STAT
// POST: MIPS code to write on the file for while loop
void emit_while(ASTnode *p, FILE *fp)
{ // p is not null for sure
  char s[100];
  char loopin[100];  // keep track of loopin label
  char loopout[100]; // keep track of loop label

  //  create Labels for the loop
  sprintf(loopin, "%s", CreateTempLabel());
  sprintf(loopout, "%s", CreateTempLabel());
  bci->breakLevel = loopout;   // keeping the loop exit label to break when needed
  bci->continueLevel = loopin; // keeping the loop in label to continue when needed

  // Loop will be running at least one time therefore creating first block
  sprintf(s, "%s:", loopin);
  fprintf(fp, "%s\t\t#While Loop START\n", s); // to ensure the indentation

  emit_expr(p->s1, fp); // expression of while condition, a0 has the value of condition

  sprintf(s, "beq $a0 $0 %s", loopout);
  emit(fp, "", s, "WHILE branch out taking decision"); // go to loop out level if the condition is false

  EMIT_AST(p->s2, fp); // while body, if loopout branch not taken

  sprintf(s, "j %s", loopin);
  emit(fp, "", s, "Jump to loop level again, loop continue"); // Jump to loop level again

  sprintf(s, "%s:", loopout);
  fprintf(fp, "%s\t\t#While Loop END\n", s); // printing directly to maintain indentation
} // end of emit_while

// PRE: PTR to ASTNode A_IF
// POST: MIPS code to perform if else condition
void emit_if(ASTnode *p, FILE *fp)
{ // As the p is A_IF, it is not NULL
  char s[100];
  char elsebody[100]; // temp var to hold the label name
  char endif[100];    // temp var to hold the label name

  sprintf(elsebody, "%s", CreateTempLabel()); // create the label
  sprintf(endif, "%s", CreateTempLabel());    // create the label
  emit_expr(p->s1, fp);                       // for expression condition, a0 has the branch deciding value
  sprintf(s, "beq $a0 $0 %s", elsebody);
  emit(fp, "", s, "IF branch decision, taken to else condidion or continue to if body"); // if branch taking
  EMIT_AST(p->s2->s1, fp);                                                               // for the if statement
  sprintf(s, "j %s", endif);
  emit(fp, "", s, "As else is not taken, jump to loop end"); // jump to the loop end

  sprintf(s, "%s:", elsebody);
  fprintf(fp, "%s\t\t#Else target level if the branch is taken\n", s); // printing directly to maintain indentation
  if (p->s2->s2 != NULL)
  {                          // check if else statement exist
    EMIT_AST(p->s2->s2, fp); // for else statement
  }

  sprintf(s, "%s:", endif);
  fprintf(fp, "%s\t\t# End of If Scope\n", s); // printing directly to maintain indentation

} // end of emit_read

// PRE: PTR to ASTNode A_BREAK
// POST: MIPS Code to perform break asm lines
void emit_break(ASTnode *p, FILE *fp)
{ // p is at A_BREAK, not NULL
  char s[100];
  sprintf(s, "j %s", bci->breakLevel);
  emit(fp, "", s, "Break the loop and jump to Loop End"); // jump to break label
} // end of emit_break

// PRE: PTR to ASTNode A_CONTINUE
// POST: MIPS Code to perform continue asm lines
void emit_continue(ASTnode *p, FILE *fp)
{ // p is at A_CONTINUE, not NULL
  char s[100];
  sprintf(s, "j %s", bci->continueLevel);
  emit(fp, "", s, "Continue to the loop begin and skip rest part of the loop "); // jump to continue label
} // end of emit_continue

// PRE: PTR to ASTNode A_RETURN_STAT
// POST: MIPS code to perform return statement
void emit_return(ASTnode *p, FILE *fp)
{ // As the p is A_RETURN_STAT box, it is not NULL
  char s[100];

  emit(fp, "", "", "Return Statement explicitely mentioned");

  if (p->s1 == NULL) // return without an expression
  {                  // Return mismatch is turned off

    // if (fi->returnType == A_INTTYPE){
    //  printf("BURF: Return type mismatch in Function %s!!\n", fi->functionName);
    //  exit(1);
    // }
    // fi->isReturnStmtFound = 0;

    emit(fp, "", "li $a0, 0", "RETURN has no specified value set to 0");
    emit(fp, "", "lw $ra ($sp)", "restore old environment RA");
    sprintf(s, "lw $sp %d($sp)", WSIZE);
    emit(fp, "", s, "Return from function store SP");
    fprintf(fp, "\n");
  }
  else
  { // return has an expression

    // Return type mismatch is turned off
    //  if (fi->returnType != p->s1->my_data_type){
    //   printf("BURF: Return type mismatch in Function %s!!\n", fi->functionName);
    //   exit(1);
    //  }
    //  fi->isReturnStmtFound = 1;
    emit_expr(p->s1, fp); // for the expression

    emit(fp, "", "lw $ra ($sp)", "Load the old environment RA");         // load old return address
    emit(fp, "", "lw $sp 4($sp)", "Return from function stack pointer"); // load the stack pointer
    fprintf(fp, "\n");
  }
  func_name_wise_code(fi->functionName, fp); // print function ending code based on function name
} // end of emit_return
