# Lab2.1 CS466 Spring 2024
# Author: Abdur Razzak
# Date: Jan 26, 2024
# Lab: Makefile for Lab2.1
# Description: Under all it will find the target of lab21. lab21 target will look
#	for lab21.l file to check. Then it will run and execute the file. Finally
#	It will create the executable lab21. The clean target will remote the executable.

all:	lab21

lab21:	lab21.l
	lex lab21.l
	gcc lex.yy.c -o lab21

clean:
	rm -f lab21
