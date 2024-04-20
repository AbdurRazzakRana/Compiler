# Lab2.2 CS466 Spring 2024
# Author: Abdur Razzak
# Date: Jan 26, 2024
# Lab: Makefile for Lab22
# Description: Check for any changes on lab22.l and lab22.y. Run and build those 2 together and create executable lab22

all:	lab22

lab22:	lab22.l lab22.y
	lex lab22.l
	yacc -d lab22.y
	gcc lex.yy.c y.tab.c -o lab22

clean:	rm -f lab22
