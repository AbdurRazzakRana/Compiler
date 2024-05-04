// Author: Abdur Razzak
// Lab: Lab 9
// Date: May 3, 2024
// Semester: Spring 2024
/*
This file will prototype all the required functions to emit asm code to the target file.
Also mention some code printing helper structure and variable
*/

#include "ast.h"

struct FunctionInfo
{
 // This data structure is to keep track of function name and call period
 char *functionName; // to generate code based on main or other function at return statement time
 int isCallingFunc;  // keep track wether var is used in function call to help array param passing

 // function return type matching is turned down after discussing with professor
 // int returnType;  // burf if type mismatch between function return type and return statement
 // int isReturnStmtFound;  // burf if the function has INT return type, however no return statement found
};

struct BreakContinueInfo
{
 // This data structure is to keep track of label to jump for break and continue
 // So that it will help to jump into the write label;
 char *breakLevel;    // keep track of break label
 char *continueLevel; // keep track of continue label
};

/*
Example case:
int f(int A[]){
 int B[10];
 B[2]=10;
 write A[3] + B[2];
}
int main(void){
 int A[5];
 A[3] = 23;
 f(A);
}
*/
// We need to differentiate arrays that comes as parameter and locally declared
// Because locally declared arrays carve out the spaces in memory and they are identifiable by sp + offset
// However parameter array comes with only one Array pointer
// We need to access the address first before adding offset
char parameterArray[100][100]; // This array will store the array names that come through parameter
int parameterArrayCounter;     // this will keep track how many parameter array received

struct FunctionInfo *fi;       // pointer to FunctionInfo object
struct BreakContinueInfo *bci; // pointer to BreakContinueInfo object

char *CreateTempLabel(); // To generate new Label for asm file

void emit_expr(ASTnode *p, FILE *fp);                                 // helper function to print expressions in asm file
void emit_function(ASTnode *p, FILE *fp);                             // helper function to print function code in asm
void emit_write(ASTnode *p, FILE *fp);                                // helper function to write the write statements into asm
void emit_read(ASTnode *p, FILE *fp);                                 // helper function for read
void emit_var(ASTnode *p, FILE *fp);                                  // helper function for variable
void emit_assign(ASTnode *p, FILE *fp);                               // helper function for assignment statement
void emit_while(ASTnode *p, FILE *fp);                                // helper function for while loop
void emit_if(ASTnode *p, FILE *fp);                                   // helper funcction for if else
void emit_args(ASTnode *p, FILE *fp);                                 // helper function to generate asm code for funcion arguments
void store_args_into_t(ASTnode *p, FILE *fp, int tempReigsterNumber); // helper function to move args value into temp registers
void emit_params(ASTnode *p, FILE *fp, int tempReigsterNumber);       // helper function to get parameter values from t0 and set them into their offset
void emit_return(ASTnode *p, FILE *fp);                               // helper function to print the return asm codes
void emit_break(ASTnode *p, FILE *fp);                                // helper function to print break asm codes
void emit_continue(ASTnode *p, FILE *fp);                             // helper function to print continue asm codes

void func_name_wise_code(char *funcName, FILE *fp); // helper function to print functionname wise code