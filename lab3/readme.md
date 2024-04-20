This assignment deals with working with a symbol table.  The code HERE Download HEREis from the web site http://forgetcode.com/C/101-Symbol-tableLinks to an external site..    -- Make sure you get this running and understand it.  You will be using this on your next assignment.

Your task is the following:

1) Properly indent, and comment the code,.  The header of your code should be a description of the code, where it was pulled from and changes you made.  Each function needs a PRE condition, POST condition and any assumptions.  Each function needs to detail out how the function approaches the output.   Minimal documentation will receive minimal points.

2a) remove all occurrences of "label".  (keep symbol)
     change "symbol[10]" to char * symbol;

      Update your code to support these changes.

 

2b) Change the following functions to have these prototypes

struct SymbTab * Insert(char *symbol, int address);   PRE:   PTr to character string, POST, PTR  to structure new symbol. Error message and exit if already present.

struct SymbTab * Search(char *symbol );  PRE Ptr character string, POST:  PTR to matching structure or NULL

This means you will have to change main() to collect information instead of these functions themselves.  You may have to update the other functions as well.

In  Insert(), you MUST "strdup() the character string, otherwise you will get weird results.

3)  Create a symbtab.h files which exposes the Insert() and Search() and struct{} definition

4)  include your symbtab.h in your *.c file

5) Demonstrate that you understand the code by testing the functionality of the interface.  A screen shot of at least 4 actions is required

6) Describe the main data structure in this code.  What is it's name?  What are the fields and how is the structure built

7) What does "malloc()" do?  Why do we use malloc()?

 

8)  You must create a *.h file which include all your prototypes

 

8a)  the only place user input shall be input is in main().   No user input shall be made in any other function

 

9)  YOU NEED TO MAKE SURE YOU UNDERSTAND THIS PROGRAM.  YOU WILL SEE IT ON THE EXAMs and in your project

 

10)  ZIP file with H, C, Makefile and PDF output seperately.

 

If user input is made outside of main(), then ZERO is applied to the submission

 

 

A simple Check list

1)   Did you indent and comment each function header?
2)   Did you comment the insertion process and how first and last are updated?
3)  Did you remove the label component from the struct?
4)  Did you move all user input to main() and update the functions to take additional paramaters?
5)  Did you create a "*.h" file that defines the prototypes of Insert and Search and Delete.
6)   Do your C and H files have header comments
7)  Does your makefile work properly, commented properly?
8)   Do you have   lab3.pdf screen shot , etc?
9)  Do all the functions have PRE and POST condition comments?
10)  Does every complex while/if/for statement have comment explanation
11)  Is the "symbol" defined as a char * in the struct?
12)  Are you using strdup() to make heap copies of input data?
13)  Your main should have an input char S[100] or some other similar variable?

This check list is not exhaustive