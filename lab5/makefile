# Lab5 CS466 Spring 2024
# Author: Abdur Razzak
# Date: Feb 28, 2024
# Lab: Makefile for Lab5

all:	lab5

lab5: lab5.y lab5.l
	lex lab5.l
	yacc -d lab5.y
	gcc lex.yy.c y.tab.c -o lab5

clean:
	rm -f lab5
