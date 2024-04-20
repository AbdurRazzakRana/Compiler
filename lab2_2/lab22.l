/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015

	Modified By: Abdur Razzak
	Date: Jan 26, 2024
	Lab: Lab 2.2
	Modifications:
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

[a-z]		{if (mydebug) fprintf(stderr,"Letter found\n"); 
                       yylval=*yytext-'a'; return(VARIABLE);}
[0-9][0-9]*	{if (mydebug) fprintf(stderr,"Digit found\n"); 
                       yylval=atoi((const char *)yytext); return(INTEGER);}
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}

[()=\-+*/%&|]	{ /* Added parenthesis rule here*/
		if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}
\n		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


