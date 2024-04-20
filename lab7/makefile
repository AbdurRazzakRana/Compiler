# Lab7 CS466 Spring 2024
# Author: Abdur Razzak
# Date: April 12, 2024
# Lab: Makefile for Lab7

all:	lab7

lab7: lab7.y lab7.l ast.c ast.h symtable.h symtable.c
	lex lab7.l
	yacc -d lab7.y
	gcc lex.yy.c y.tab.c ast.c symtable.c -o lab7

clean:
	rm -f lab7
