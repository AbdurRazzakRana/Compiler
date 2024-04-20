Lab 2.2

 

This is your first experience with using YACC and LEX together.  The job of LEX is provide TOKENs to YACC.  YACC asks for tokens and LEX returns TOKENs.

 

Your task is to copy LEX file HERE Download HEREand YACC file HEREDownload HERE

 

Your job is to

1)  yacc -d lab22.y  

2)  lex lab22.l

3)  gcc y.tab.c -o lab22

 

4)  Execute lab22 to see how it works

 

The provided program has 3 problems

a)  Unary minus does not work properly

b)  parenthesis does not work

c)  multiplication does not work

 

You are to fix these problems and demonstrate that you have fixed them via a screen shot of your system

 

Deliverables

ZIP
in directory "lab22:


each file source file your produce, you must adhere to proper documentation standards which include your name, date, purpose of the code, inputs, output, assumptions, etc.

Include in your comments

a) your Makefile with proper documentation and the answers to the following questions:

b) your YACC code with additional comments showing what changes you made

c) your LEX code with additional comments showing what you did

d) a screen shot of your calculator showing the unary minus, parenthesis and multiplication works   --- something like   -(3*9)  Screen shot  in "lab22.pdf"