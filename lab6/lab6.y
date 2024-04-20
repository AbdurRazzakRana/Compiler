%{
/*
	Author: Abdur Razzak
	Date: March 27, 2024
	Lab: Lab 6
	Modifications:
		Added semantic actions in every production.
		SYMBOL table checking are skipped for this lab.
		next property is used to connect same level nodes and print with same indentation
		the yacc file is taken from LAB 5
		Only 3 address are used in each node: s1, s2 and next
		Corrected the indectation in call sequence
		All tokens starts with T_ and node types are A_
		next is only 5 required time used.
		Var_LIST are all s1 connected
		All the PT() called are from inside case:statement
		As a grad student, prototyping is supported, also break and continue statement.
		A_EXPR node is only defiend now, all the other cases are written inside
		May be tomorrow and all of the expression are 

		Input: This file will take tokens as input
		Output: Will apply Grammer based on token sequence
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "ast.h"

ASTnode *PROGRAM;
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

/*  defining type of allowed nonterminal objects */
%union {
	int value;
	char * string;
	ASTnode *node;
	enum AST_MY_DATA_TYPE d_type;
	enum AST_OPERATORS operators;
}

// Declaring all the necessary tokens, node and operator type that is required in Lab 6
%token <value> T_NUM
%token <string> T_ID T_STRING
%type <node> Declaration_List Declaration Var_Declaration Var_List Fun_Declaration Compound_Stmt
%type <node> Local_Declarations Statement_List Statement Write_Stmt Params Param Param_List Expression Simple_Expression
%type <node> Term Additive_Expression Factor Var Call
%type <node> Iteration_Stmt
%type <node> Selection_Stmt
%type <node> Read_Stmt
%type <node> Expression_Stmt Arg_List Args
%type <node> Assignment_Stmt Return_Stmt
%type <node> Break_Continue_Stmt
%type <d_type> Type_Specifier
%type <operators> Addop Relop Multop
%token	T_INT
%token T_VOID
%token T_IF
%token T_ELSE
%token T_WHILE
%token T_RETURN
%token T_READ
%token T_WRITE
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
/*
Rule applied: return to program whatever node Declaration_List is pointing at.
*/
Program: Declaration_List {PROGRAM = $1;}
	;

/*2. declaration-list → declaration { declaration }*/
/*
Declaration_List has multiple options:
For only Declaration: pointing to whatever inside Declaration node.
For Declaration Declaration_List: Declaration_List will be repeatative 
	and ended up multiple Declaration, all of them are neighbour of each other
	on the same level, therefore, they are tied up using next.
*/
Declaration_List: Declaration {$$ = $1;}
	| Declaration Declaration_List {
		$$ = $1;
		$$ -> next= $2;
	}
	;
/*3. declaration → var-declaration | fun-declaration*/
/* 
For two options Fun_Declaration and Var_Declaration, Declaration
will pointing to each one of the node
*/
Declaration : Fun_Declaration {$$ = $1;}
	|	Var_Declaration {$$ = $1;}
	;

/*4. var-declaration → type-specifier var-list ;*/
/*
for variable declaration, it could be int x,y,p[100],...;
	therefore we need to link all the vars in variable list and set their
	type as whatever inside Type Specifier.
*/
Var_Declaration : Type_Specifier Var_List ';' 
				{
					// populate the s1 connected list with the defined type via $1;
					ASTnode *p = $2;
					while(p != NULL){
						p->my_data_type = $1;
						p = p->s1;
					}
					// pointing to the first pointer
					$$ = $2;
				}
	;

/*5. var-list → ID [ [ NUM ] ]+ { , ID [ [ NUM ] ]+ }*/
/*
creating variable declaration type node for variable or array
*/
Var_List: T_ID 
				{ 
					$$ = ASTCreateNode(A_VARDEC);
					$$->name = $1;
				}
	| T_ID '[' T_NUM ']' 
				{
					$$ = ASTCreateNode(A_VARDEC);
					$$->name = $1;
					$$->value = $3;
				}
	| T_ID ',' Var_List 
				{
					$$ = ASTCreateNode(A_VARDEC);
					$$->name = $1;
					$$->s1 = $3;
				}
	| T_ID '[' T_NUM ']' ',' Var_List 
				{
					$$ = ASTCreateNode(A_VARDEC);
					$$->name = $1;
					$$->value = $3;
					$$->s1 = $6;
				}
	;

//6. type-specifier → int | void
/*
Type specifier of function or varialbe. reutrn corresponding enum type
*/
Type_Specifier: T_INT {$$ = A_INTTYPE;}
	| T_VOID {$$ = A_VOIDTYPE;}
	;

// 7. fun-declaration →type-specifier ID ( params ) compound-stmt
// Function declaration: will set the name to T_ID, data type to Type_Specifier
// and two child node, first one is parameters and the the function body as compound statement
Fun_Declaration: Type_Specifier T_ID '(' Params ')' Compound_Stmt 
				{ 
					$$ = ASTCreateNode(A_FUNCTIONDEC);
					$$->name = $2;
					$$->s1 = $4;
					$$->s2 = $6;
					$$->my_data_type = $1;
				}
	| Type_Specifier T_ID '(' Params ')' ';' 
				{// Grad Student function function prototyping case.
					$$ = ASTCreateNode(A_FUNCTION_PROTO);
					$$->name = $2;
					$$->s1 = $4;
					$$->my_data_type = $1;
				}
	;

// 8. params → void | param-list
// Parameters could be void or a list of parameters
Params: T_VOID {$$ = NULL;}
	| Param_List {$$ = $1;}
	;

// 9. param-list → param { , param }
/* paramenters could be one or more with comma separated,
 set the other ones in next to identy them as same level*/ 
Param_List: Param {$$ = $1;}
	| Param ',' Param_List 
				{
					$$ = $1;
					$$->next = $3;
				}
	;

//10. param → type-specifier ID [ [] ]+
/*
parameter could be array or just a variable, if its a variable value should be 0
for array it will be -1 to identify that array node.
*/
Param: Type_Specifier T_ID '[' ']' 
				{
					$$ = ASTCreateNode(A_PARAMS);
					$$->my_data_type = $1;
					$$->name = $2;
					$$->value = -1;
				}
	| Type_Specifier T_ID 
				{
					$$ = ASTCreateNode(A_PARAMS);
					$$->my_data_type = $1;
					$$->name = $2;
				}
	;

// 11. compound-stmt → { local-declarations statement-list }
/*
Compound statement structure, will set left recursion to local declaration and right recursion
to statement list.
*/
Compound_Stmt: '{' Local_Declarations Statement_List '}' 
				{
					$$ = ASTCreateNode(A_COMPOUND);
					$$->s1 = $2;
					$$->s2 = $3;					
				}
	;

// 12. local-declarations → { var-declaration }
/*
varaible decralations, there could be multiple one after another
marking them as next to identify as same level
*/
Local_Declarations: Var_Declaration Local_Declarations 
				{
					$$ = $1;
					$$->next = $2;
				}
	| {$$ = NULL;}
	;

// 13. statement-list → { statement }
/*
Rules for statement list, there could be multiple statement, 
same level statements are marked as next
*/
Statement_List : 
	Statement Statement_List 
				{
					$$ = $1;
					$$->next = $2;
				}
	| {$$ = NULL;}
	;

// 14. Rule for the statement
/*
Rule for 8 type of statements and point to that satatement node
*/
Statement: Expression_Stmt {$$ = $1;}
	| Compound_Stmt {$$ = $1;}
	| Selection_Stmt {$$ = $1;}
	| Iteration_Stmt {$$ = $1;}
	| Assignment_Stmt {$$ = $1;}
	| Return_Stmt {$$ = $1;}
	| Read_Stmt {$$ = $1;}
	| Write_Stmt {$$ = $1;}
	| Break_Continue_Stmt {$$ = $1;}
	;

// 15. expression-stmt → expression ; | ;
/*
Expression statement can have expression or empty, set rules for both of them
*/
Expression_Stmt: Expression ';' 
				{
					$$ = ASTCreateNode(A_EXPR_STAT);
					$$->s1 = $1;
				}
	| 
	';' {$$ = ASTCreateNode(A_EXPR_STAT);}
	;

// 16. selection-stmt → if ( expression ) statement [ else statement ] +
/*
Setting rules for selection statement.
if else statement could be if (){} or if (){} else {}
*/
Selection_Stmt: T_IF '(' Expression ')' Statement
				{
					$$ = ASTCreateNode(A_IF); 
					$$->s1 = $3;

					$$->s2 = ASTCreateNode(A_IFBODY);
					$$->s2->s1 = $5;
				}
	| T_IF '(' Expression ')' Statement T_ELSE Statement 
				{
					$$ = ASTCreateNode(A_IF);    
					$$->s1 = $3;	// setting expression to the first child of IF Condition

					$$->s2 = ASTCreateNode(A_IFBODY);
					$$->s2->s1 = $5;
					$$->s2->s2 = $7;				// else statment is set ot first child of else body
				}
	;

// 17. iteration-stmt → while ( expression ) statement
/*
Setting rule for while statement, for priting prupose, while condition and while body is created
Expression is set to first child node of while condition
Statement is set to first child node of while body
*/
Iteration_Stmt: T_WHILE '(' Expression ')' Statement 
				{
					$$ = ASTCreateNode(A_WHILE_STAT);
					$$->s1 = $3;
					$$->s2 = $5;
				}
	;
// 18. return-stmt
/*
Return statement could be empty return or returning an expression.
settig rule for both of them
*/
Return_Stmt: T_RETURN ';' 
				{
					$$ = ASTCreateNode(A_RETURN_STAT);
				}
	| T_RETURN Expression ';'
				{
					$$ = ASTCreateNode(A_RETURN_STAT);
					$$->s1 = $2;
				}

// 19. read-stmt → read var ;
/*
Creating read statement. child node set to Var
*/
Read_Stmt: T_READ Var ';' 
				{
					$$ = ASTCreateNode(A_READ);
					$$->s1 = $2;
				}
	;

// 20. write-stmt
/*
Write Statement can be an expression or a name
*/
Write_Stmt: T_WRITE Expression ';' 
				{
					$$ = ASTCreateNode(A_WRITE);
					$$->s1 = $2;
				}
	| T_WRITE T_STRING ';' 
				{	
					$$ = ASTCreateNode(A_WRITE);
					$$->name = $2;
				}
	;

// 21. assignment-stmt → var = simple-expression ;
/*
Assignment Statement node will have two child: left child is the variable and 
right child will be simple_expression
*/
Assignment_Stmt: Var '=' Simple_Expression ';'
				{
					$$ = ASTCreateNode(A_ASSGN_STAT);
					$$->s1 = $1;
					$$->s2 = $3;
				}
	;

// 22. var → ID [ [ expression ] ] +
/*
Varaible can be just an id or or array erxpresion
*/
Var: T_ID 
				{
					$$ = ASTCreateNode(A_VARUSE);
					$$->name = $1;
				}
	| T_ID '[' Expression ']' 
				{
					$$ = ASTCreateNode(A_VARUSE);
					$$->name = $1;
					$$->s1 = $3;
					$$->value = -1;
				}
	;

// 23. expression → simple-expression
// Expression is poinint to simple expression
Expression: Simple_Expression {$$ = $1;}
	;

// 24. simple-expression
/*
Simple expression could be Aditive expression
or comparing expression
*/
Simple_Expression: Additive_Expression {$$ = $1;}
	| Additive_Expression Relop Simple_Expression 
				{
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
				}
	;

// 22. relop → <= | < | > | >= | == | !=
/*
Returning relop comparison enum operator
*/
Relop: T_LE {$$ = A_LESSEQUAL;}
	| T_LT {$$ = A_LESSTHAN;}
	| T_GT {$$ = A_GREATERTHAN;}
	| T_GE {$$ = A_GREATEREQUAL;}
	| T_EQ {$$ = A_EQUAL;}
	| T_NE {$$ = A_NOTEQUAL;}
	;


// 23. additive-expression → term { addop term }
/*
Additive Expression can be multipe factors or Addtive operations
*/
Additive_Expression: Term 
				{$$ = $1;}
	| Additive_Expression Addop Term 
				{
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
				}
	;

// 24. addop → + | -
// Returning enum type for plus and minus
Addop : '+' {$$ = A_PLUS;}
	| '-' {$$ = A_MINUS;}
	;

// 25. term → factor { multop factor }
/*
Term can be an simple expression or multi operations expression
*/
Term: Factor {$$ = $1;}
	| Term Multop Factor 
				{
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
				}
	;

// 26. multop → * | /
// Return enum type for multiply, devide or mod
Multop: '*' {$$ = A_TIMES;}
	| '/' {$$ = A_DEVIDE;}
	| '%' {$$ = A_MOD;}
	;

// 27. factor → ( expression ) | NUM | var | call | - factor
/*
Factor can be expression, a number, variable, a function call output or unary 
*/
Factor : '(' Expression ')' {$$ = $2;}
	| T_NUM 
				{
					$$ = ASTCreateNode(A_NUM);
					$$->value = $1;
				}
	| Var 		{$$ = $1;}
	| Call 	{$$ = $1;}
	| '-' Factor 
				{
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $2;
					$$->operator = A_UNIRY_MINUS;
				}
	;

// 28. call → ID ( args )
/*
Rule for function call, setting arguments as the child nodes 
*/
Call : T_ID '(' Args ')' 
				{
					$$ = ASTCreateNode(A_FUNC_CALL);
					$$->name = $1;
					$$->s1 = $3;
				}
	;

// 29. args → arg-list | empty
// arguments can be a list of arguments
Args : Arg_List {$$ = $1;}
	| {$$ = NULL;}
	;

// 30. arg-list → expression { , expression }
/*
Argument list can be a single expression or multi expression, if there are multiple expression
they all are set to same level nodes.
*/
Arg_List: Expression 
				{
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1;
				}
	| Expression ',' Arg_List 
				{
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1;
					$$->next = $3;
				}
	;

/* GRAD STUDENT: rule for break and continue*/
/*
Creating statements for break or continue.
*/
Break_Continue_Stmt: T_BREAK ';' 
				{
					$$ = ASTCreateNode(A_BREAK);
				}
	| T_CONTINUE ';'
				{
					$$ = ASTCreateNode(A_CONTINUE);
				}
	;
%%	/* end of rules, start of program */

int main()
{ 
	yyparse();
	printf("\nFinished Parsing\n\n\n");
	ASTprint(0, PROGRAM);
}
