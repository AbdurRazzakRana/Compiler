%{
/*
	Author: Abdur Razzak
	Date: Feb 28, 2024
	Lab: Lab 5
	Modifications:
		Imported mydebug and linecount from lex file
		Updated yyerror() such that it prints the error along with the global lineno;
		Only one shift/reduce error exist
		If there any T_ID: printing the name of the variable, rule name and the line number
		All the non_terminals are Camel Cased
		As a Grad Student, added rule for functino prototype, break and continue
		Added all the 30 rules mentioned in C_Minus_EBNF_Revised 2022.pdf
		Has run the code on cs machine

		Input: This file will take tokens as input
		Output: Will apply Grammer based on token sequence
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>

// prototying yylex to get ride of compilation waring
int yylex();

// mydebug and linecount are declared in lex file and the yacc file is 
// just using them, therefore, they are declared as extern
extern int mydebug;
extern int linecount;


// when error occurs, it prints the line number
void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("Error: %s, In line: %d\n", s, linecount);
}


%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start Program

%union {
	int value;
	char * string;
}

// Declaring all the necessary tokens that is required in Lab 5
%token <value> T_NUM
%token <string> T_ID
%token	T_INT
%token T_VOID
%token T_IF
%token T_ELSE
%token T_WHILE
%token T_RETURN
%token T_READ
%token T_WRITE
%token T_STRING
%token T_LE
%token T_LT
%token T_GE
%token T_GT
%token T_EQ
%token T_NE

/*Grad Student: added token for break and continue*/
%token T_BREAK
%token T_CONTINUE

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'

%%	/* end specs, begin rules */

/* Extended BNF Grammar for C Minus */

/*1. program → declaration-list*/
Program: Declaration_List
	;

/*2. declaration-list → declaration { declaration }*/
Declaration_List: Declaration
	| Declaration Declaration_List
	;
/*3. declaration → var-declaration | fun-declaration*/
Declaration : Fun_Declaration
	|	Var_Declaration
	| Break_Continue
	;
/*3. GRAD STUDENT: rule for break and continue*/
Break_Continue: T_BREAK ';' {printf("Grad Student-break\n");}
	| T_CONTINUE ';' {printf("Grad Student-continue\n");}

/*4. var-declaration → type-specifier var-list ;*/
Var_Declaration : Type_Specifier Var_List ';'
	;

/*5. var-list → ID [ [ NUM ] ]+ { , ID [ [ NUM ] ]+ }*/
// Also printing the T_ID as instructed
Var_List: T_ID { printf("%s with value %s on line %d\n", "Var_List", $1, linecount); }
	| T_ID '[' T_NUM ']' { printf("%s with value %s on line %d\n", "Var_List", $1, linecount); }
	| T_ID ',' Var_List { printf("%s with value %s on line %d\n", "Var_List", $1, linecount); }
	| T_ID '[' T_NUM ']' ',' Var_List { printf("%s with value %s on line %d\n", "Var_List", $1, linecount); }
	;

//6. type-specifier → int | void
Type_Specifier: T_INT 
	| T_VOID
	;

// 7. fun-declaration →type-specifier ID ( params ) compound-stmt
// Also for Grad Student: Added rule for function prototyping
Fun_Declaration: Type_Specifier T_ID '(' Params ')' Compound_Stmt { printf("%s with value %s on line %d\n", "Fun_Declaration", $2, linecount); }
	| Type_Specifier T_ID '(' Params ')' ';' 
	{// Grad Student function function prototyping case. 
		printf("Grad Student-Function Prototyping: %s with value %s on line %d\n", "Fun_Declaration", $2, linecount); 
		}
	;

// 8. params → void | param-list
Params: T_VOID
	| Param_List
	;
// 9. param-list → param { , param }
Param_List: Param
	| Param ',' Param_List
	;

//10. param → type-specifier ID [ [] ]+
Param: Type_Specifier T_ID Square_Braces 
	{ printf("%s with value %s on line %d\n", "Param", $2, linecount); }
	;

Square_Braces: 
	| Square_Braces '[' ']'
	;

// 11. compound-stmt → { local-declarations statement-list }
Compound_Stmt: '{' Local_Declarations Statement_List '}'
	;

// 12. local-declarations → { var-declaration }
Local_Declarations: Var_Declaration Local_Declarations
	|
	;

// 13. statement-list → { statement }
Statement_List : Statement Statement_List
	|
	;

// 14. Rule for the statement
Statement: Expression_Stmt
	| Compound_Stmt
	| Selection_Stmt
	| Iteration_Stmt
	| Assignment_Stmt
	| Return_Stmt
	| Read_Stmt
	| Write_Stmt
	;

// 15. expression-stmt → expression ; | ;
Expression_Stmt: Expression ';'
	| ';'
	;

// 16. selection-stmt → if ( expression ) statement [ else statement ] +
Selection_Stmt: T_IF '(' Expression ')' Statement
	| T_IF '(' Expression ')' Statement T_ELSE Statement

// 17. iteration-stmt → while ( expression ) statement
Iteration_Stmt: T_WHILE '(' Expression ')' Statement
	;

// 18. return-stmt
Return_Stmt: T_RETURN ';'
	| T_RETURN Expression ';'

// 19. read-stmt → read var ;
Read_Stmt: T_READ Var ';'
	;

// 20. write-stmt
Write_Stmt: T_WRITE Expression ';'
	| T_WRITE T_STRING ';'
	;

// 21. assignment-stmt → var = simple-expression ;
Assignment_Stmt: Var '=' Simple_Expression ';'
	;

// 22. var → ID [ [ expression ] ] +
Var: T_ID { printf("%s with value %s on line %d\n", "Var", $1, linecount); }
	| T_ID More_Dimention { printf("%s with value %s on line %d\n", "Var", $1, linecount); }
	;

More_Dimention: '[' Expression ']'
	| '[' Expression ']' More_Dimention
	;

// 23. expression → simple-expression
Expression: Simple_Expression
	;

// 24. simple-expression
Simple_Expression: Additive_Expression
	| Additive_Expression Relop Simple_Expression
	;

// 22. relop → <= | < | > | >= | == | !=
Relop: T_LE
	| T_LT
	| T_GT
	| T_GE
	| T_EQ
	| T_NE
	;

// 23. additive-expression → term { addop term }
Additive_Expression: Term
	| Additive_Expression Addop Term
	;

// 24. addop → + | -
Addop : '+'
	| '-'
	;

// 25. term → factor { multop factor }
Term: Factor
	| Factor Multop Term
	;

// 26. multop → * | /
Multop: '*'
	| '/'
	;

// 27. factor → ( expression ) | NUM | var | call | - factor
Factor : '(' Expression ')'
	| T_NUM
	| Var
	| Call
	| '-' Factor
	;

// 28. call → ID ( args )
Call : T_ID '(' Args ')' { printf("%s with value %s on line %d\n", "Call", $1, linecount); }
	;

// 29. args → arg-list | empty
Args : Arg_List
	|
	;

// 30. arg-list → expression { , expression }
Arg_List: Expression
	| Expression ',' Arg_List
	;
%%	/* end of rules, start of program */

int main()
{ yyparse();
}
