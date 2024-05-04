%{
/*
	Author: Abdur Razzak
	Date: May 3, 2024
	Lab: Lab 9
	Input: This file will take tokens as input from lex file
	Output: Will apply Grammer based on token sequence and rule for syntax directed semantics

 Modifications:
		Fixes from Lab 7 submission comments:
			1. function parameter matching at function call
			2. correct implementation of unary minus
			3. fixed segmentation falut for function prototying before
				and function is implemented after the call
			4. Proper array passing
			5. Addition checking between scaller and array subtype
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "prototype.h"
#include "emit.h"

ASTnode *PROGRAM;
// prototying yylex to get ride of compilation waring
int yylex();

// mydebug and linecount are declared in lex file and the yacc file is 
// just using them, therefore, they are declared as extern
extern int mydebug;
extern int linecount;

int LEVEL = 0;  // global context variable to know how depth we are
int OFFSET = 0; // global variable to accumulate required runtime space
int GOFFSET = 0; // global variable to accumulate global variable offset
int maxoffset = 0;  // the largest offset needed of the current function
int proto_funcCounter=0; // function prototype counter; increases when prototype found, 
		//decereases when a progotyped functions has declaration

// when error occurs, it prints the line number
void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("YACC PARSE ERROR: %s on line number %d\n", s, linecount);
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
%type <node> Declaration_List Declaration Var_Declaration Var_List Grad_Fun_Common_Part Fun_Declaration Compound_Stmt
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
Program : Declaration_List {PROGRAM = $1;}
	;

/*2. declaration-list → declaration { declaration }*/
/*
Declaration_List has multiple options:
For only Declaration: pointing to whatever inside Declaration node.
For Declaration Declaration_List: Declaration_List will be repeatative 
	and ended up multiple Declaration, all of them are neighbour of each other
	on the same level, therefore, they are tied up using next.
*/
Declaration_List : Declaration {$$ = $1;}
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
						// check if varaible in the list if its already declared at same level
						if (Search(p->name, LEVEL, 0) != NULL) {
							// symbol already defined, should barf
							yyerror(p->name);
							yyerror("Symbol already defined");
							exit(1);
						}
						// symbol not declared at LEVEL
						if(p->value == 0) { // if its an integer
							p->symbol = Insert(p->name, p->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // sub type will be scalar
							OFFSET = OFFSET + 1; // 1 size added for the offset
						}
						else { // for the array
							p->symbol = Insert(p->name, p->my_data_type, SYM_ARRAY, LEVEL, p->value, OFFSET); // sub type is array
							OFFSET = OFFSET + p->value; // size of the array will be added in offset
						}

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
// this part is covered by Var_Declaration
Var_List : T_ID 
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
Type_Specifier : T_INT {$$ = A_INTTYPE;}
	| T_VOID {$$ = A_VOIDTYPE;}
	;

// 7. fun-declaration →type-specifier ID ( params ) compound-stmt
// Function declaration: will set the name to T_ID, data type to Type_Specifier
// and two child node, first one is parameters and the the function body as compound statement
// Grad_Fun_Common_Part will return function head part; such as int a(params)
Fun_Declaration : Grad_Fun_Common_Part Compound_Stmt 
				{ 
					// function declaration with compound statement
					$$ = ASTCreateNode(A_FUNCTIONDEC);
					$$->my_data_type = $1->my_data_type; // function type is from the declaration in function head part
					$$->name = $1->name; // name will be from head part described at Grad_Fun_Common_Part
					$$->s1 = $1->s1;
					$$->s2 = $2;
					$$->symbol = Search($1->name, LEVEL, 0);
					$$->symbol->offset = maxoffset;  // setting max offset as the offset for the function

					struct Func_Prototype * fp = Search_Proto($$->name);
					if(fp != NULL){
						if(fp->value != -1){ // just a safe chacking if a prototyped function is implemented but still in prototype in list
							yyerror($$->name);
							yyerror("Prototyping error");
							exit(1);
						}
						Delete_Proto(fp); // As the protytpe has a declaration, no need to keep in prototype list anymore
						proto_funcCounter--; // decreasing counter as one prototype has declaration
					}

					// During walkout from the function, set back the counters for global varaibles
					OFFSET = GOFFSET;
				}
	| Grad_Fun_Common_Part ';' 
				{// Grad Student function prototyping case.
					if(Search_Proto($1->name) != NULL){ // if there is the prototype of same funciton written again, barf
						yyerror($1->name);
						yyerror("attemping to prototyping twice on same funciton");
						exit(1);
					}
					$$ = ASTCreateNode(A_FUNCTION_PROTO);
					$$->my_data_type = $1->my_data_type;  //function type is described at Grad_Fun_Common_Part
					$$->name = $1->name; // same as previous
					$$->s1 = $1->s1;

					$$->symbol = Search($1->name, LEVEL, 0);
					$$->symbol->offset = maxoffset;  // setting max offset as the offset for the function

					Insert_Proto($1->name, LEVEL, -1); // inserting into the prototype table
					proto_funcCounter++;	// increasing the prototype counter
					
					// Even though we are not going into the function for prototyping case
					OFFSET = GOFFSET;
				}
	;

// As a grad student, need to implement function declarationa and prototype both
// however that introduce shift reduce and makes it ambigous for the compiler
// therefore, left factoring using Grad_Fun_Common_Part
Grad_Fun_Common_Part : Type_Specifier T_ID
				{
					// added Search_Proto checking, if a function was prototyped earlieer,
					// we need to allow this case for delcaration purpose
					if (Search($2, LEVEL, 0) != NULL && Search_Proto($2) == NULL) { // check if the function has been defined before
						yyerror($2);  // T_ID has alredy been used, should barf
						yyerror("function name already in use");
						exit(1);
					}

					// only insert if its not in symbol table
					if(Search($2, LEVEL, 0) == NULL)
						Insert($2, $1, SYM_FUNCTION, LEVEL, 0, 0);

					// At the time of walkin to the function resettting counters
					/*while chekcing assignment testcases, setting offset = 0 will match the outputs
					however, while matching with ~scooper/lab7 output, offset needs to be set 2
					In class, Prof. Cooper clarified that setting 0 or 2 to the offset, both works */
					GOFFSET = OFFSET;
					OFFSET = 2;
					maxoffset = OFFSET;
				}
 			'(' Params ')'
				{
					struct SymbTab *p = Search($2, LEVEL, 0);
					// if not delcared earier or declared but prototyped shoudl pass
					if (Search_Proto($2) != NULL && check_params(p->fparms, $5)==0){ 
						// previously declared prototype and current actuals does not match
						yyerror("Parameter mismatch: Prototype formals and declaration actuals ");
						exit(1);
					}
					p-> fparms = $5;  // setting pointer to the function parameters 

					$$ = ASTCreateNode(A_FUNCTION_COMMON); // setting up name, type and s1 for both prototype and func dec
					$$->my_data_type = $1;
					$$->name = $2;
					$$->s1 = $5;
				}
	;
// 8. params → void | param-list
// Parameters could be void or a list of parameters
Params : T_VOID {$$ = NULL;}
	| Param_List {$$ = $1;}
	;

// 9. param-list → param { , param }
/* paramenters could be one or more with comma separated,
 set the other ones in next to identy them as same level*/ 
Param_List : Param {$$ = $1;}
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
Param : Type_Specifier T_ID '[' ']' 
				{
					// check if name is already used
					// level+1 because varaibles in parameters will be used as child level inside function
					if (Search($2, LEVEL+1, 0) != NULL){
						// name already in the symbol table, can not have 2 varaibles with same name, barf
						yyerror($2);
						yyerror("Parameter already used");
						exit(1);
					}
					// varaible is not used before, creating node
					$$ = ASTCreateNode(A_PARAMS);
					$$->my_data_type = $1;
					$$->name = $2;
					$$->value = -1;

					// inserting the node into symbol table
					$$->symbol = Insert($$->name, $$->my_data_type, SYM_ARRAY, LEVEL+1, 1, OFFSET); // level +1 because they are at child level
					OFFSET = OFFSET + 1; // offset increased for insertion
				}
	| Type_Specifier T_ID 
				{
					// check if name is already used
					// level+1 because varaibles in parameters will be used as child level inside function
					if (Search($2, LEVEL+1, 0) != NULL){
						// name already in the symbol table, can not have 2 varaibles with same name, barf
						yyerror($2);
						yyerror("Parameter already used");
						exit(1);
					}
					// varaible is not used before, creating node
					$$ = ASTCreateNode(A_PARAMS);
					$$->my_data_type = $1;
					$$->name = $2;
					
					// inserting the node into symbol table
					$$->symbol = Insert($$->name, $$->my_data_type, SYM_SCALAR, LEVEL+1, 1, OFFSET); // ids are in child level; level + 1
					OFFSET = OFFSET + 1; // one up for the insertion
				}
	;

// 11. compound-stmt → { local-declarations statement-list }
/*
Compound statement structure, will set left recursion to local declaration and right recursion
to statement list.
*/
Compound_Stmt : '{' {LEVEL++;} Local_Declarations Statement_List '}' 
				{
					// Before walkin to the function, level +1
					$$ = ASTCreateNode(A_COMPOUND);
					$$->s1 = $3;
					$$->s2 = $4;
					if(mydebug) Display();
					// setting the maxoffset to the higher counter
					if (OFFSET > maxoffset)
						maxoffset = OFFSET;
					// we don't need the offset that are deleted
					OFFSET -= Delete(LEVEL);

					// at the time of walk out from the function, level -1 
					LEVEL--;
				}
	;

// 12. local-declarations → { var-declaration }
/*
varaible decralations, there could be multiple one after another
marking them as next to identify as same level
*/
Local_Declarations : Var_Declaration Local_Declarations 
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
Statement : Expression_Stmt {$$ = $1;}
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
Expression_Stmt : Expression ';' 
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
Selection_Stmt : T_IF '(' Expression ')' Statement
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
Iteration_Stmt : T_WHILE '(' Expression ')' Statement 
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
Return_Stmt : T_RETURN ';' 
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
Read_Stmt : T_READ Var ';' 
				{
					$$ = ASTCreateNode(A_READ);
					$$->s1 = $2;
				}
	;

// 20. write-stmt
/*
Write Statement can be an expression or a name
*/
Write_Stmt : T_WRITE Expression ';' 
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
Assignment_Stmt : Var '=' Simple_Expression ';'
				{

					if($1->my_data_type != $3->my_data_type){
						// type is not the same
						// printf("%s type: %d\n", $1->name, $1->my_data_type);
						// printf("%s type: %d\n", $3->name, $3->my_data_type);
						yyerror("Type Mismatch");
						exit(1);
					}

				// This case will protect the case x = y or 5 = y
    // where x is int and y is an array
    if(($1->symbol == NULL || $1->symbol->SubType == SYM_SCALAR)
     && ($3->symbol != NULL && $3->symbol->SubType == SYM_ARRAY)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("ARRAY can not be set to SCALAR");
     exit(1);
     }    
    // This case will protect the case y = x or y = 5
    // where x is int and y is an array
    if(($1->symbol != NULL && $1->symbol->SubType == SYM_ARRAY)
     && ($3->symbol == NULL || $3->symbol->SubType == SYM_SCALAR)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("SCALER can not be set to ARRAY");
     exit(1);
     }

					$$ = ASTCreateNode(A_ASSGN_STAT);
					$$->s1 = $1;
					$$->s2 = $3;

					$$->name = CreateTemp(); // creating temporary register to hold the operation
					$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1; // one up for the insertion
				}
	;

// 22. var → ID [ [ expression ] ] +
/*
Varaible can be just an id or or array erxpresion
*/
Var : T_ID 
				{
					struct SymbTab *p = Search ($1, LEVEL, 	1);
					if (p == NULL) {
						// reference variable is trying to used but not in sym table
						yyerror($1);
						yyerror("symbol used but not defined");
						exit(1);
					}
				// sub tuype can be array or scalar both, only barf for function type
					if(p->SubType == SYM_FUNCTION){
						// reference variable to a non scaler variable
						yyerror($1);
						yyerror("symbol must be either SCALAR or ARRAY");
						exit(1);
					}
					$$ = ASTCreateNode(A_VARUSE);
					$$->name = $1;
					$$->my_data_type = p->Declared_Type; // data type is declared at the begining; y[2] shold be int
					$$->symbol = p;
				}
	| T_ID '[' Expression ']' 
				{
					struct SymbTab *p = Search ($1, LEVEL,	1);
					if (p == NULL) {
						// reference variable is trying to used but not in sym table
						yyerror($1);
						yyerror("symbol used but not defined");
						exit(1);
					}

					if(p->SubType != SYM_ARRAY){
						// reference variable to an non array variable
						yyerror($1);
						yyerror("symbol must be a ARRAY");
						exit(1);
					}

					// p should be array here

					$$ = ASTCreateNode(A_VARUSE);
					$$->name = $1;
					$$->s1 = $3;
					$$->value = -1; // -1 to call the Expression in ast.c
					$$->symbol = p;
					$$->my_data_type = p->Declared_Type;
					
					// for the Grad case: f(int x){}    f(y[0])
					// though y is array, but the output y[0] type has to be integer and scaller.
					// if we change the $$->symbol->SubType to SCALAR, it chnages entire array type in the symbol table
					// because of the pointer.
					// hence to support this scenairo, careated a copy and changed the subtype into the coppied instance
					$$->symbol = (struct SymbTab*)malloc(sizeof(struct SymbTab));
					*($$->symbol) = *p;
					$$->symbol->SubType = SYM_SCALAR;
				}
	;

// 23. expression → simple-expression
// Expression is poinint to simple expression
Expression : Simple_Expression {$$ = $1;}
	;

// 24. simple-expression
/*
Simple expression could be Aditive expression
or comparing expression
*/
Simple_Expression : Additive_Expression {$$ = $1;}
	| Additive_Expression Relop Simple_Expression 
				{
					if($1->my_data_type != $3->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}

				// int x, y[100]; x * y or 5*y should not work
    if(($1->symbol == NULL || $1->symbol->SubType == SYM_SCALAR)
     && ($3->symbol != NULL && $3->symbol->SubType == SYM_ARRAY)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("ARRAY can not be relop with SCALAR");
     exit(1);
     }
    
    // int x, y[100]; y * x or y * 5 should not work
    if(($1->symbol != NULL && $1->symbol->SubType == SYM_ARRAY)
     && ($3->symbol == NULL || $3->symbol->SubType == SYM_SCALAR)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("SCALER can not be relop with ARRAY");
     exit(1);
     }

					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
					$$->my_data_type = $1->my_data_type;
					
					$$->name = CreateTemp(); // to hold the relop operation, using a register
					$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register 
					OFFSET = OFFSET + 1;
				}
	;

// 22. relop → <= | < | > | >= | == | !=
/*
Returning relop comparison enum operator
*/
Relop : T_LE {$$ = A_LESSEQUAL;}
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
Additive_Expression : Term {$$ = $1;}
	| Additive_Expression Addop Term 
				{
					// checking both of the operands are in same type
					if($1->my_data_type != $3->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}
	
				// int x, y[100]; x + y or 5+y should not work
    if(($1->symbol == NULL || $1->symbol->SubType == SYM_SCALAR)
     && ($3->symbol != NULL && $3->symbol->SubType == SYM_ARRAY)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("ARRAY can not be addop with SCALAR");
     exit(1);
     }
    
    // int x, y[100]; y + x or y + 5 should not work
    if(($1->symbol != NULL && $1->symbol->SubType == SYM_ARRAY)
     && ($3->symbol == NULL || $3->symbol->SubType == SYM_SCALAR)){
					if($3->name == NULL)
						yyerror("T_NUM");
					else
						yyerror($3->name);
     yyerror("SCALER can not be addop with ARRAY");
     exit(1);
     }

					// type is same, we can do the operation
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
					$$->my_data_type = $1->my_data_type;

					$$->name = CreateTemp(); // using register to hold the add operation
					$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1;
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
Term : Factor {$$ = $1;}
	| Term Multop Factor 
				{
					// checking both of the operands are in same type
					if($1->my_data_type != $3->my_data_type){
						// type is not the same
						yyerror("Type Mismatch");
						exit(1);
					}
					// we can do the operation
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $1;
					$$->s2 = $3;
					$$->operator = $2;
					$$->my_data_type = $1->my_data_type;

					$$->name = CreateTemp(); // using register to hold the result
					$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET); // inserting the register
					OFFSET = OFFSET + 1;
				}
	;

// 26. multop → * | /
// Return enum type for multiply, devide or mod
Multop : '*' {$$ = A_TIMES;}
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
					$$->my_data_type = A_INTTYPE; // number returns int
				}
	| Var 		{$$ = $1;}
	| Call 	{$$ = $1;}
	| '-' Factor 
				{
					$$ = ASTCreateNode(A_EXPR);
					$$->s1 = $2;
					$$->operator = A_UNIRY_MINUS;
				// synthensis  for unary minus type
					$$->my_data_type = $2->my_data_type;

					$$->name = CreateTemp(); // unary minus operation in register
					$$->symbol = Insert($$->name, $2->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					OFFSET = OFFSET + 1;
				}
	;

// 28. call → ID ( args )
/*
Rule for function call, setting arguments as the child nodes 
*/
Call : T_ID '(' Args ')' 
				{  // check is the function is in the symbol table
					struct SymbTab *p = Search($1, 0, 0);
					if(p == NULL){
						// symbol not found in table, can not call a function without declaring, barf
						yyerror($1);
						yyerror("function only prototyped, not defined");
						exit(1);
					}
					// name is  found in the table and its a function

					// check calling name is funciton type or not
					if (p->SubType != SYM_FUNCTION) {
						// symbol not defined as a function, barf
						yyerror($1);
						yyerror("is not defined as a function");
						exit(1);
					}

					// check to see that the formal and actual parameters are
					// same length and type
					if(check_params($3, p->fparms) == 0){
						// length and type did not match, should barf;
						yyerror($1);
						yyerror("Actual and Formals do not match");
						exit(1);
					}

					// As function can be prototyped earliner and declaration may
					// may showed up after the call, we need to store the call stack
					// and check if the declaration can be found later on. if not barf on line number
					Insert_Func_Call($1, linecount);

					// name found in the list, it defined as function and 
					// params are same type and length as well
					// creating node for function call
					$$ = ASTCreateNode(A_FUNC_CALL);
					$$->name = $1;
					$$->my_data_type = p->Declared_Type;
					$$->s1 = $3;
					$$->symbol = p;
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
Arg_List : Expression 
				{
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1;
					$$->my_data_type = $1->my_data_type;
					
					$$->name = CreateTemp();
					// insert with subtype
					// if subtype does not have such as T_NUM, insert scaler
					enum SYMBOL_SUBTYPE subType = $1->symbol != NULL ? $1->symbol->SubType : SYM_SCALAR;
					$$->symbol = Insert($$->name, $1->my_data_type, subType, LEVEL, 1, OFFSET); // final sub type will be whatever got from the expression
					OFFSET = OFFSET + 1;
				}
	| Expression ',' Arg_List 
				{
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1;
					$$->next = $3;
					$$->my_data_type = $1->my_data_type;

					$$->name = CreateTemp();
					// insert with subtype
					// if subtype does not have such as T_NUM, insert scaler
					enum SYMBOL_SUBTYPE subType = $1->symbol != NULL ? $1->symbol->SubType : SYM_SCALAR;
					$$->symbol = Insert($$->name, $1->my_data_type, subType, LEVEL, 1, OFFSET);// final sub type is form the expression 
					OFFSET = OFFSET + 1;
				}
	;

/* GRAD STUDENT : rule for break and continue*/
/*
Creating statements for break or continue.
*/
Break_Continue_Stmt : T_BREAK ';' 
				{
					$$ = ASTCreateNode(A_BREAK);
				}
	| T_CONTINUE ';'
				{
					$$ = ASTCreateNode(A_CONTINUE);
				}
	;
%%	/* end of rules, start of program */

int main(int argc, char* argv[])
{
	FILE *fp;
	char s[100];
	int i;
	//read our input arugments
	// option -d turn on debug
	// option -o next arugment is out output file name
	
	for(i =0;i<argc;i++){
		if(strcmp(argv[i], "-d")==0){
			mydebug = 1;
		}
		if(strcmp(argv[i], "-o")==0){
			// we have a file input
			strcpy(s, argv[i+1]);
			strcat(s, ".asm");
			if(mydebug) printf("File name is %s\n", s);
		}
	}

	// open the file that is referenced by s 
	fp = fopen(s, "w");
	if (fp == NULL){
		printf("can not open file %s\n",s);
		exit(1);
	}

	yyparse();
	if(mydebug) printf("\nFinished Parsing\n\n\n");

	// Function can be prototyped and may not be called at all, thats fine
	// However if a prototyped with no declaration can be found in called function list, we need to barf here
	if(proto_funcCounter > 0) {
		struct Func_Call * p = check_proto_gets_called(proto_funcCounter);
		if(p != NULL){
			yyerror(p->name);
			// As there is no need of linecount variable anymore, we are setting to func call where it called undeclared function
			// to print actual line number. as we dont want to modify yyerror function for this change.
			// also the program is exiting, so, changing linecount would not cause problem
			linecount = p->line_number;
			yyerror("Call to a function that is not delcared");
			exit(1);
		}
	}

	if(mydebug) Display();  // show global varaible functions
	if(mydebug) printf("\n\nAST PRINT\n\n");
	if(mydebug) ASTprint(0, PROGRAM);

	EMIT(PROGRAM, fp);
}