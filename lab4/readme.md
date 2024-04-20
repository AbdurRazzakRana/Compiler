This mini-project combines several concepts of compilation.  In particular you will learn how to use more complex data types for the YACC stack.  You will also incorporate the symbol table we worked with in the last assignment into this project.

Project::  Enhance Lab2.2 by including a symbol table into the system, changing the register names to allow any valid name, require that variable names be defined before use, and assign memory locations to each named variable.

 

In analyzing your lab2.2 project, you will see that the system allows for 26 registers named 'a' through 'z'.  Think of these as variable names.  In lab2.2, the system uses ASCII math to make 'a' - 'z' be 0 - 25, index into memory "regs"  We wish to have variable names with longer names, and we wish to require our users to declare the variable names before use.

In order to do this, we need to extend the Context Free Grammar for our calculator, change your LEX program to match variable names, change our YACC directives to either store names in our symbol table, or find their address value when in use.

 

Your calculator will now require the following:

int V1;
int V2;...
int Vn;

expr \n | Vi=expr \n

 

You may want to consult http://www.tldp.org/HOWTO/Lex-YACC-HOWTO-6.htmlLinks to an external site.

To accomplish this, you most likely need to do the following:

 

 

1) Extend the context free grammar of the calculator

P -> DECLS list

DECLS -> DECLS DECL | empty

DECL -> int VARIABLE ';' '\n'

 

1a)   Make the start symbol of the grammar P instead of list

2) update the lex program to match variable names instead of just single lower case characters

3) create a %UNION type in YACC to allow LEX to return integer or "char *"


%union {
      int value;
      char * string;

}

 

  3a) define each multi-valied token in the CFG to be either one of the types in the union

%token <value> INTEGER
%token  <string> VARIABLE
%token  INT
%type <value> expr stat

4) in lex, use strdup() to copy yytext to yylval.string so that YACC can have a copy of the variable name whenever a VARIABLE matches

4a)  update the rule for INTEGER to be  yylval.value=atoi(....

5) insert semantic directives (C-code) to deal with when a VARIABLE is matched

   5a)  When you are in the declaration mode, you need to ensure that the name is not a copy, if not a copy, insert into symbol table.

   5b)  when a Variable is in an expression, fetch its value by getting the ADDR component out of the symbol table

   5c)  when a VARIABLE is on the left hand side, set the value in the memory (regs) based on the assigned slot from the symbol table

6)  You will most likely need to modify symbol.Insert(char *).  I created a FetchAddr(char *) to get the assigned slot for a label to help me solve this problem

 

Deliverables: 

Mainly, you have to submit your working directory for lab4 (ZIP folder), and make sure you have the following files in it:

1. -- purposefully missing --  removed ---

2. Your LEX code

3. Your YACC code

3.5 Your Makefile

4. Your Symbol Table CODE. 

5. (Optional) test file(s).

6.  Your YACC file MAY NOT include lex.yy.c.   You must remove the include and compile the files correctly

7. A PDF file of screen shots that demonstrates that your code works with following cases, make sure to list the case followed by its corresponding screenshot:

       a)  Show that if you define more than the MAX number of variables, then you error

       b) Show that you cannot declare a variable more than once

       c)  Show that you cannot use a variable that is not defined

       d) Show that a declared variable can be set and used (left and right hand side).

Failing to meet any of these requirements will cause you loosing points.

8: upload:  lab4.y. lab4.c Lex, Yacc, Makefile (which creates lab4 executable), Symtable files, PDF screen shots  as a ZIP which creates a lab4 folder with all files inside of the folder