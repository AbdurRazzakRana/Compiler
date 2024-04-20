Consider the definition of CMINUS+  from HEREDownload HERE

Starting Video HERE

This test code HEREDownload HERE
Produced this expected output HEREDownload HERE

 

YOU SHOULD HAVE EXACTLY ONE SHIFT/REDUCE message

Your task is to create YACC and LEX routines which will PARSE (check syntax only) input that matches the language definition (read this is that your program should be able to take syntactically  correct code and say yes, otherwise report errors giving at least the first line number). 

Notes:
All boldface elements come from your lexer as a single character or as a TOKEN. All tokens will have the prefix "T_".  For example "if" will be the token "T_IF" .   For the T_ID token you need to set yylval.string=strdup(yytext).

 

If you have an optional rule like   var-list -> T_ID [ '[' NUM ']' ] { , T_ID [ '[' NUM ']' ] }

 

You should write this as

var-list ->   T_ID
            |    T_ID '[' NUM ']'
            |    T_ID ',' var-list
            |    T_ID '[' NUM ']' ',' var-list

 

If you have  parms -> parm { ',' parm}

write this is    parms -> parm | parm ',' parms     YES make them right recursive

 

 

 

 

 

Requirements

0) 

We are going to let the LEX file hold the declaration of mydebug and linecount

int mydebug=0;

int linecount=1;

 

In any other file that needs these variables, use the "extern" directive which says I want to use it, but someone else declared

extern int mydebug;

extern int linecount;

1)  Update yyerror() such that it prints the error along with the global lineno;

2)  All tokens coming from LEX shall be single characters or upper case and start with "T_" .  For example reserved word "return" shall be returned as T_RETURN.

3)  Do NOT worry about the single shift/reduce error.  If you have more than one shift/reduce error you need to fix them.

4)  everywhere you have T_ID in your YACC file, you must print out the name of the variable in YACC  along with an indication of which rule produced ALONG with the line it was used.

5)  Non Terminals SHALL be Camel Case :   like Function_Declaration


 

You may use my executable ~scooper/lab5   to test input like:


%   ~scooper/lab5 < input_file

 

 

 

 

 

 

 

 

Deliverables: A zipped folder that has all your working directory for lab5. If you miss including file(s) that stop the TA from executing your code, you will be penalized. Mainly, your zipped folder has to have:

0) Your ZIP file Must create and store all files in subfolder "lab5"   -- lower case  15% for not

1) Your well documented (with your name and date) YACC code

2) Your well documented LEX code

3)  Your output when run with the test code.

4) Your makefile with proper documentation.  "make all" and "make clean" must work

5)  If your makefile does not work or your program does not compile, the result will be 0.

6)  There shall be no GCC compiler errors or warnings when compiled on the Suse Linux Computer Science platforms.  The only warning is the Shift/Reduce error from YACC. -25%

7)  If you copied the YACC and LEX from previous assignments, you need to clean up unused components by REMOVING them -- not commenting them out.

 

8)  Makefile must have correct dependencies and ONLY recreate lab5 when one of the dependency files is changed 15%

 

9)  There should be NO mention of Calculator nor any support variables in your LAB5 work that are related to LAB4 calculator.   When in doubt, delete it.

9a)  If you copy from LAB2 or LAB4, you MUST remove all comments and support variables that do not apply to LAB5

 

10 GRAD STUDENTS Must add rule for prototype.   You must come up what it looks like and introduce it into your GRAMMAR.

10a)  Grad students introduce "break" and "continue" statements.