%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

   Shaun Cooper
    January 2015

   problems  fix unary minus, fix parenthesis, add multiplication
   problems  make it so that verbose is on and off with an input argument instead of compiled in

	Modified By: Abdur Razzak
	Date: Feb 18, 2024
	Lab: Lab 4
	Modifications:
		A. Lab 4 Specific Changes:
					1. Extending Context Free Grammer of calculator to support "int var;"
								Set the start symbol of the grammar P instead of list
					2. Creating Union type to allow lex to return integer or char *
					3. Defining multi-valid token in the CFG	to be either one of the type sin the union
					4. (5a) Inserted semantic directives to de3al with varaible declaration such as "int var;"
										Check NULL or already in the list or enough rooms in register, and finally
										Only inserted if all these cases passes.
					5. (5b) Inserted the expression case, such as a=b where b is used as an expression.
										Search if the variable is listed on Symboltable, if it exists, featch its address.
										Then get the value from register of that address and set it to the answer.
					6. (5c) Inserted code to support when a VARIABLE is on the left hand side, 
										set the value in the memory (regs) based on the assigned slot from the symbol table
										Searching the variable in symbol table, featch its address,
										setting the value to that register address.

		B. Previous Changes to the file
				For error and warning fixes:
					Inclusion of lex.yy.c is removed
					Prototyping yylex method
					Adding int in front of main
				Debugging:
					Added mydebug variable as an extern as it is defiend on lex file
					Added this checker before printing debug lines
				Task implementation:
					Unary minus - removed expr before 2nd minus as the first one 
						ensures the minus
					Parenthesis - The code is implemented here, just required lex 
						file editing to get the token
					Multiplication - Added rule for multiplication

	Input: This file will take lexical token as input
	Ouput: Based on different operations, it will produce a result and print on terminal 
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "symtable.h"

// Removed inclusion of lex.yy.c to avoid errors


// prototying yylex to get ride of compilation waring
int yylex();

// mydebug flag is defined in lex file, we are just using it here 
extern int mydebug;

// setting max limit for registers
#define LIMIT 2

float regs[LIMIT];
int base, debugsw;
int regs_counter = 0;

void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("%s\n", s);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

/*Setting the start symbol of the grammer to the new rule P*/
%start P

/* creating a %UNION type to allow LEX to return integer or "char *" */
%union {
	int value;
	char * string;
	float myfloat;
}


/* Defining multi-valid token in the CFG	to be either one of the type sin the union*/
%token <value> INTEGER
%token <string> VARIABLE
%token <myfloat> FLOAT
%token	T_INT
%token T_FLOAT
/* %type<value> expr */
%type <value> expr stat

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */
/* Extending the context free grammar of the calculator to support task 1 for int var;  */
P	:	DECLS list
	;
DECLS :	DECLS DECL_INT
	| DECLS DECL_FLOAT
	| /*empty*/
	;

DECL_FLOAT : T_FLOAT VARIABLE ';' '\n'
	{
		// (5a) Writing up the action if we find "int var;"
		if ($2 == NULL){
			// If the variable is null, Barf, no action.
			printf("\n----BARF------\nVariable is null\n");
		}
		else{
			// Variable is not null

			// Check the variabl is already listed in the table.
			struct SymbTab * is_var_on_symtable = Search($2);
			if(is_var_on_symtable != NULL){
				// Barf, because the variable is in the table, no need to insert again
				printf("\n----BARF------\nvariable %s is already declared, can not redeclare\n", $2);
			}
			else{
				// Variable not found in table, new varaible needs to be declared

				// Checking whether the register is full to insert or not
				if (regs_counter >= LIMIT){
					// registers are full, can not insert the variable
					printf("\n----BARF------\nSymbol table is full, can not insert variable %s\n", $2);
				}
				else {
					// There is enough room for the variable into the register, insert the variable.

					// Inserting the varaible into the reigster
					Insert($2, regs_counter);
					// Incrementing the register counter to keep track of availability
					regs_counter++;
				}
			}
		}
		// Display the current scenario of the symbol table after parsing Declaration.
		Display();
	}
DECL_INT	:	T_INT VARIABLE ';' '\n'
	{
		// (5a) Writing up the action if we find "int var;"
		if ($2 == NULL){
			// If the variable is null, Barf, no action.
			printf("\n----BARF------\nVariable is null\n");
		}
		else{
			// Variable is not null

			// Check the variabl is already listed in the table.
			struct SymbTab * is_var_on_symtable = Search($2);
			if(is_var_on_symtable != NULL){
				// Barf, because the variable is in the table, no need to insert again
				printf("\n----BARF------\nvariable %s is already declared, can not redeclare\n", $2);
			}
			else{
				// Variable not found in table, new varaible needs to be declared

				// Checking whether the register is full to insert or not
				if (regs_counter >= LIMIT){
					// registers are full, can not insert the variable
					printf("\n----BARF------\nSymbol table is full, can not insert variable %s\n", $2);
				}
				else {
					// There is enough room for the variable into the register, insert the variable.

					// Inserting the varaible into the reigster
					Insert($2, regs_counter);
					// Incrementing the register counter to keep track of availability
					regs_counter++;
				}
			}
		}
		// Display the current scenario of the symbol table after parsing Declaration.
		Display();
	}
	;

list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;

stat	:	expr
			{ fprintf(stderr,"the answer is %d\n", $1); }
	|	VARIABLE '=' expr
			{
				// (5c), support for a variable is on the left hand side such as a = 5 or a = b;

				// check if the variable is null.
				if ($1 == NULL){
					// Barfing, Variable is null, nothing to do
					printf("\n----BARF------\nVariable is null\n");
				}
				else{
					// Before setting any value into it, we need to check whether its a valid declared variable,
					if (Search($1) == NULL){
						// Variable is not in the list, means not declared earlier, barf.
						printf("\n----BARF------\nVariable %s is not in symble table\n", $1);
					}
					else{
						// Variable is declared earlier, therefore, found on the Symbol table.

						// getting the address of variable
						int var_addr = FeatchAddress($1);

						// setting the value of $3 to that address register
						regs[var_addr] = $3; 
					}
				}
			}
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '*' expr
			{
			/* Adding rule for multiplication */	 
			$$ = $1 * $3;
			}
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }

		/* remove expr before '-' to make Unary minus workable */
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	VARIABLE
			{
				// (5b) Supporting the action when a variable is used as an expression.
				// such as a=b, b is used here as an expression

				// Search if the variable is exist in the symbol table.
				if (Search($1) == NULL){
					// Barfing, Variable is not in the Symtable
					printf("\n----BARF------\nVariable %s is not on the list\n", $1);
					// setting 0 to the answer varialbe to avoid uneven values 
					$$=0;
				}
				else{
					// Address is listed in the symbol table

					// Featching the address of that variable
					int addr = FeatchAddress($1);
					
					// Setting the answer from the register of that address
					$$ = regs[addr];
				}

			/* only print if mydebug flag is on */ 
			if(mydebug)
				fprintf(stderr,"found a variable value =%s\n",$1); }
	|	INTEGER {$$=$1;

			/* only print if my debug flag is on */
			if(mydebug)
				fprintf(stderr,"found an integer\n");}
	| FLOAT {
		$$=(float) $1;
		// printf("FLOAT: %f\n", $$);
		if(mydebug)
				fprintf(stderr,"found an integer\n");
	}
	;



%%	/* end of rules, start of program */

// Adding int in front of main to remove error
int main()
{ yyparse();
}
