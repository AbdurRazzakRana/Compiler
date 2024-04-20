/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015

	Modified By: Abdur Razzak
	Date: Feb 18, 2024
	Lab: Lab 4
	Modifications:
		A. Lab4 Specific changes:
						1. Edited variable rule to have variable names longer instead of single character.
						2. Used strdup() to copy varialbe name into yylval.string
						3. Used atoi() to convert integer string into yylval.value
		B. Previoous Changes:
						Set mydebug to 0 to avoid extra print lines
						Added () along  with the other characters to get identified 
						And to have token for that.
			
	Input: This file will take characters as input
	Output: Based on rules, it will generate tokens
*/
%{

// set 0 to debag tag to hide the extra debug
int mydebug=0;
#include "y.tab.h"
%}


%%
"int"	{return (T_INT);}
"float" {return (T_FLOAT);}
[a-zA-Z][a-zA-Z0-9_]*		{/* Lab4: updating the rule to match variable names instead of just single lower case characters */
																							if (mydebug) fprintf(stderr,"VARIABLE found\n"); 
																							// Used strdup() to copy varialbe name into yylval.string
																							yylval.string=strdup(yytext);
                       //yylval=*yytext-'a'; 
																							return(VARIABLE);}
[0-9][0-9]*	{if (mydebug) fprintf(stderr,"Digit found\n"); 
                       // Used atoi() to convert integer string into yylval.value
																							yylval.value = atoi((const char *)yytext);
																							//atoi((const char *)yytext); 
																							return(INTEGER);
																							}
[+-]?[0-9]*[.][0-9]+	{if (mydebug) fprintf(stderr,"float found\n"); 
																							yylval.myfloat = atof((const char *)yytext);
																							printf("float lex file: %f\n", yylval.myfloat);
																							//atoi((const char *)yytext); 
																							return(FLOAT);
																							}
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}

[;()=\-+*/%&|]	{ /* Added semicolon to support for yacc. Added parenthesis rule here*/
		if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}
\n		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


