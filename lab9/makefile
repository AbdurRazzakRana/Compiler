# Lab9 CS466 Spring 2024
# Author: Abdur Razzak
# Date: May 3, 2024
# Lab: Makefile for Lab9

all:	lab9

lab9: lab9.y lab9.l ast.c ast.h symtable.h symtable.c prototype.c prototype.h emit.c emit.h emit_private.h emit_private.c
	lex lab9.l
	yacc -d lab9.y
	gcc lex.yy.c y.tab.c ast.c symtable.c prototype.c emit.c emit_private.c -o lab9

clean:
	rm -f lab9
