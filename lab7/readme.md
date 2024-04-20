In this lab you are to add the provided symbol table code to your semantic action set.  The goal is to ensure that used variables have been declared.
Additionally, you will assign new temporary symbols to intermediate values in expressions.  This will allow us to allocate memory for the intermediate expressions in lab9. Finally, we will add rudimentary type checking so that we don't mix VOID and INT type

There are a number of details required in this lab.  You will need to maintain how and when to add to the symbol table, when to remove from the symbol table, how to maintain offset values, and how to determine types.

The rules for insertion are as follows:

a)  You need to maintain a static scope (global) counter, called "level" in your grammar (YACC) as a global variable
b)  Each time you enter a compound statement, you need to increment level
c)  Each time you exit a compound statement you need to decrement the level,  whenever you exit a compound statement, you need to remove all the symbols defined at that level and reset your offset by the amount of memory words you removed with the deletion.  Here are some sample code that may help

You should look at the implementation of Delete(int level) as it now deletes everything in the symbol table that it is at that level or higher and returns the number words that the deletion makes.


Some of my semantic action for FUNDEC on exit is....

                      offset-=Delete(1);  /* remove all the symbols from what we put in from the function call*/
                      level=0;  /* reset the level */
                      offset=goffset;



My semantic action for end of compound statement

                      {  $$=ASTCreateNode(A_COMPOUND);
                         $$->s1=$2;
                         $$->s2=$3;
                        Display();  /* display symbol table as per requirement */
                        offset-=Delete(level);  /* decrease the offset count by the size of values allocated at level */
                        level--;  /* down one level */
                       }
d)  Whenever a variable is declared, it must not have been declared before at that level.
  -- if a variable is "new" to this level, then you need to insert the variable into the symbol table, along
    with the level and its size.
e)  each variable insertion also comes with a stored offset.  The offset is initially set to 0 and indicates how far into the runtime stack the variable will be found.   The offset is incremented by the size of the variable.  1 for scalars, the size of an array for arrays, and 0 for functions.
f)  the offset starts at 0 for  the start of a function and the function parameters start taking up offset.  When the function is done, we must reset the main offset to a stored global offset ( I call mine goffset ).

The rules for use of variables are:
a)  Whenever a variable is used, it must occur at your level, or any level less, in a decreasing manner.  Search() has these features built in.
b)  If a variable is not defined, then error.
c)  If a variable is either scalar, array or function,  then variable name must be used in the correct context.  This means that you cannot have a variable name as an INT be used as a function -- this is a form of type checking in that the variable name has to be used in the correct context.

For example

void main(void)
{
   int x;
  x[0] =  1;  -- is illegal since x is not an array
  x= x(10);  -- is illegal (x is not a function)
}


To make your symbol table work, you will need to update the actions in AT LEAST the following production rules:
VARDEC
FUNDEC
PARAMS
Wherever ID occurs.


Rules for Type checking:
1) an expression inherits its type from the operations that occurs.  You should NOT allow things like

int x;
void y;
x= x + y;

2)  Each Number is an integer.  Each ID has its declared type.  Remember that if the ID is a function, then it has a type.  
3)  Each of the formal parameters of a function should match the length and type of argument list of the function.
4)  Types have to agree for assignment statements.


REMINDERS

When you add semantic actions in the middle of a Right Hand side, remember to increment your $$/$1 references so you are still referencing the return values from the subordinate production rules



Symbol Table changes

1) 

   The provided Symbol Table captures much of what you need to deal with. You need to study the Search() and Insert() prototypes

    The Search uses "level" which can handle multiple definitions of the same variable at different levels.  Similarly, level is used to search the symbol table for variables used outside your current compound statement level.  The idea is that level increments by one whenever we walk into a compound statement and then decrements when we end a compound statement.  

   
 
2)  You will need to add a SymbTab element to your ASTnode so that you can reference symbol table elements in your AST. This should be set to the symbol table structure that matches the ID returned by Search(). 

 

Type Checking.

 

For Type checking we have a simple set of rules.    T

1) The type is set on terminals for Var, Call, NUM.   

2) For any operation ,all of the operands need to be the same type.  If they are not, generate an error.  If they are the same, then the synthesized type of the node is that of the operaands.

3)  Assignment variable needs to be the same type of the expression,

4) for EACH operation and each ARG of CALL, we will generate a temporary variable to hold the result of the operations.  This is necessary for Lab9 to operate correctly.  You will need to write a CREATE_TEMP() function which provides a name and inserts into the symbol table.


Requirements

1)   Modify your YACC file to include symbol table.  
1a)  Symbol table insert should  generate a semantic error when the same name is declared at the same level
1b)  On completion of a compound statement, print out all variables defined in that context via Display() , and then remove via Delete() them from the symbol table
1c)  Whenever an ID occurs, you need to check that the name has been defined.  You need to ensure the correct form is used properly (ie as  a function, scalar, or array).  For Grad students, this is more difficult because Call arguments can be array names; you should not worry about this until you are attempting to complete the highest level in lab9.
1d)  You need to implement rudimentary type inheritance.
1e)  Symbol entries need to maintain level.  Level =0 for global variables and function names.  level=1 for function parameter names and the primary compound statement of the function.  level is incremented by one each time a new compound statement is encountered.  level is decremented by one each time the compound statement is exited

int x;
int z;
int f( int x, int z[])
   {
          int y;
          {
             int y;
          }
      }
int t;

 

would result in something like:


int x;  -- level 0 offset 0
int z;  -- level 0 offset 1
int f  --- level 0 offset NA   (we will use a register for return values instead of memory)
   ( int x,  level 1, offset 0
     int z[]   level 1,  offset 1
   )
   {

           int y  -- level 1 offset 2
           {
                 int y -- level 2 offset 3
           }
   }
int t;   level 0 offset 2 -- we are at global variables now






2)  Submission
a)  Your entire project with all supporting files as a ZIP
b)  The output of the symbol table for EACH time a compound statement ends AND the symbol table at the end of the parse.
c)  ZIP file
d)  Must create "lab7" folder ALL lower case, no camel or upper case
e)  Target executable is "lab7".  All lower case

This INPUT  Download INPUTshould generate something close to this OUTPUTDownload OUTPUT


This FILE  Download FILEhas a number of type errors.  You should use it and iteratively remove the error lines from the file.  When your code runs without errors, check the file to see if missed one of the errors. 

This is your TEST INPUT Download TEST INPUT, please provide your output in submission


 

Requirements:
1)  All code must be documented , with focus on explaining the actions you add to make symbol table and type checking work.  All functions need PRE/POST

 

2)  Submit your Lex, Yexx, AST, and symbol_table code.  You need to also include your AST.h, symbol_table.h

3)  Your YACC code should be an enhancement from your prior submission.  Major changes (which include changes in the non-terminals and terminals in the YACC code) need to be indicated and APPROVED.  I expect your YACC code from the prior lab to be your starting point.

4) You must perform type checking and length checking for formal and actual parameter checking.

 

 

CHECK PARAMETERS CHECKING TEST EXAMPLES

 

1)

int f(void) {  f(1); }   // fail length

 

2)
int f(void y) {  f(1); }   // fail  type mismatch

3)

int f(int y) {void x;  f(x); }   // fail  type mismatch

 

4) GRAD Students

int f(int A[]) {  int b;  f(b);}  // fail not an array

4a)

int f(int A) {  int b[100];  f(b);}  // fail should be array

4b)

int f(int A[]) {  int b[100];  f(b);}  // succeed

4c)

int f(int A[]) {  int b[100];  f(b[2]);}  // fail -- array not passed

4d

int f(int A[]) {  int b[100];  f(2 + b);}  // fail -- cannot array arrays and scalar