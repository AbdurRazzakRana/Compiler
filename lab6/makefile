# Lab5 CS466 Spring 2024
# Author: Abdur Razzak
# Date: March 23, 2024
# Lab: Makefile for Lab6

all:	lab6

lab6: lab6.y lab6.l ast.c ast.h
	lex lab6.l
	yacc -d lab6.y
	gcc lex.yy.c y.tab.c ast.c -o lab6

clean:
	rm -f lab6
