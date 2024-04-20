http://epaperpress.com/lexandyacc/Links to an external site. (has an example that creates an ast. Click on calculator on the left)

 

VIDEO LINKS



Lab6 PART 1

Lab6 PART 2

Lab6 PART 3

 

You can run my lab 6 like

 

%    ~scooper/lab6 < inputfile.c

Background:  from our previous lab we know we can check a program for syntax correctness.  With an Abstract Syntax Tree (AST), we can store the structure of the input program in a data structure (called an Intermediate Representation - IR), which allows us to perform multiple passes on the source information to improve the performance of the code.  A final pass over the AST allows us to generate target (assembly language).  Our ultimate goal is to generate Assembly code and run the assembly (usually on a simulator).

 

Our task is to program YACC such that the result at the end of parsing (after yyparse() ), is to have a pointer to a data structure which, when properly traversed, represent our parsed program.  For us to do this, we must add additional information to our YACC program which constructs an AST during the shift/reduce processes used in YACC.  Basically, at the end of each production rule, we will need to add Semantic action to: create a node, plumb the newly created node and to ensure that the information is attached to the yylval companion stack.  The AST node will have different node types to distinguish what that node is representing.


The objective is after yyparse() completes, your main() program needs to print out the AST.   The print out should be such that the output formatting indicates the structure of the program your read in.  My input file HERE  Download HEREgenerated the output file HERE Download HERE.

 

Things that you will likely need to do

 

1)  Create a separate ast.c and ast.h file which will contain all your Abstract Syntax Tree code.  You can use what I have created HERE  Download HEREand HERE  Download HEREto give you guidance.  The provided code will work, but is only meant to give you ideas on what to do.

2) Add semantic actions to every production rule in your CMINUS+ submission from the previous LAB.

3)  You DO NOT have to check for variable declarations being done prior to the use of the NAME.  The next LAB will be the inclusion of SYMBOL table.

4) Create a function ASTprint() which will be used to print the structure of Tree with proper indentation using a level variable to print a number of spaces.

5)  You MUST use AST*() directives as presented in class

6)  You MUST document all major differences from your previous lab (especially if you change your production rules)

7)  We may ask you to explain your code in person

8)  Your AST MUST use a "next" field in the ASTnode and this field is to be used to connect Declarations, Parameters, Local Declaration, Statement list and Args list ONLY! 20% deduction if you do not use next appropriately.

9)  Your YACC code shall be from your LAB 5 submission. This means there should be no changes to your non-terminal and terminal names.

10)  Your AST can only use s1,s2 and next as pointers to other ASTnodes.  You may NOT add additional pointers, nor use substitute names.  They all must be lowercase.

11)  You cannot "#include yy.lex.c" in your YACC file.  Automatic 15% off.  Rather you need to include the compile of the file in your Makefile

12)  Your output should be similar (not exact) to mine (including the indentation).

13)  AST enumerated Node types shall start with "A_" prefix.   Token names from LEX shall start with the "T_" prefix.  Not using these naming conventions will results in 10% deduction.

14)  You can ONLY next connect Declaration_List, Param_List, Local_Declarations, Statement_List, Arg_list,

15) The elements of Arg_LIST are expressions, you need to create a superior node A_ARG for Arg List

16) Var_List shall be s1 connected

17)  Your ASTprint may only have calls to p->next if that node has a potential next connection (you cannot blindly call ASTPRINT on nodes).

18)  ASTprint may only use PT(level) call in each case statement, no calls to PT() outside of case statements.

19)  Graduate Students (CS466 students) must also enhance the language to allow for prototypes.

 

20)   Make all your arthimetic nodes one name A_EXPR and use operator to distinguish.  This will make your code much simpler

 

Deliverables

1)  A copy of your well documented source files.  Functions need meaningful PRE and POST comments.

2)  The output of your parse for the following INPUT given HERE Download HERE.

3)  The ZIP file will create a lowercase lab6 folder and all source files will be in the immediate directory (no subdirectories under lab6).  The folder will be lower case lab6.  Your output will be in "lab6.output".   Any deviations will have penalty.

 

Create a ZIP

Note:  We may ask you to demonstrate your code.