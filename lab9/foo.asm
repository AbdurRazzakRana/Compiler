# MIPS CODE GENERATED BY Compliler Class

.data
_L0: .asciiz    "hello" 
_L1: .asciiz    "world" 

.align 2
x: .space 4 # global varaible
A: .space 400 # global varaible

.text

main:			# function definition
	move $a1, $sp		# Activation Record Carve out copy SP
	subi $a1, $a1, 8		# Activation Record carve out copy size of function
	sw $ra, ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record


	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall		# Call write string


	la $a0, _L1		# The string address
	li $v0, 4		# About to print a string
	syscall		# Call write string


	lw $ra ($sp)		# restore old environment RA
	lw, $sp 4($sp)		# Return from function store SP

	li $v0 10		# Exit from Main, we are done
	syscall		# Exit everything
