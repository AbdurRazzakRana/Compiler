/*
	Modified By: Abdur Razzak
	Date: May 3, 2024
	Lab: Lab 9
	Modifications:
		We did not need to modify this file in this lab



	Input: This file will take characters as input
	Output: Based on rules, it will generate tokens
*/
%{
# include "ast.h"
// Declaring mydebug and linecount in lex file and will be used on yacc file
int mydebug=0;
int linecount=1;
#include "y.tab.h"
%}


%%
"int"	{/*Token for integer*/return (T_INT);}
"void"	{/*Token for void*/return(T_VOID);}
"read"	{/*Token for read*/return(T_READ);}
"write"	{/*Token for write*/return(T_WRITE);}
"if"	{/*Token for if*/return(T_IF);}
"else"	{/*Token for else*/return(T_ELSE);}
"return"	{/*Token for return*/return(T_RETURN);}
"while"	{/*Token for while*/return(T_WHILE);}
"<=" {/*Token for less than equal*/return(T_LE);}
"<"	{/*Token for less than*/return(T_LT);}
">="	{/*Token for greater than equal*/return(T_GE);}
">"	{/*Token for greater than*/return(T_GT);}
"=="	{/*Token for equal*/return(T_EQ);}
"!="	{/*Token for not equal*/return(T_NE);}

"break" {/*Grad Student: Token for break*/return(T_BREAK);}
"continue" {/*Grad Student: Token for continue*/return(T_CONTINUE);}

[a-zA-Z][a-zA-Z0-9_]*		{ /*Variable detected*/
																							if (mydebug) fprintf(stderr,"VARIABLE found\n"); 
																							// Used strdup() to copy varialbe name into yylval.string
																							yylval.string=strdup(yytext);
																							return(T_ID);}
[0-9][0-9]*	{										/*Variable numbber found*/
																							if (mydebug) fprintf(stderr,"Digit found\n"); 
                       // Used atoi() to convert integer string into yylval.value
																							yylval.value = atoi((const char *)yytext);
																							return(T_NUM);
																							}
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}

[,;()=\-+*/%&|{}\[\]]	{ /* Added semicolon, curley braces, square braces  to support for yacc. Added parenthesis rule here*/
																							if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);
																						}
\n		{ 																	if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext);
																							// incrementing line number when a new line is found
																							linecount++;
				}

\".*\"	{ 														/* Added to identify and return string such as "hello" */
            										if (mydebug) fprintf(stderr,"String found\n"); 
            										yylval.string=strdup(yytext); 
            										return(T_STRING);
        }

\/\/.*	{ 													/* Added to identify single line comment that starts with // */
            										if (mydebug) fprintf(stderr,"Comment found: %c\n", *yytext); 
        }
%%

int yywrap(void)
{ return 1;}


