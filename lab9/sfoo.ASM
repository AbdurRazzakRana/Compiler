# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "Function f\n"
_L1: .asciiz	 " "
_L2: .asciiz	 "\n"
_L3: .asciiz	 "Function Main\n"
_L4: .asciiz	 " "
_L5: .asciiz	 "\n"
.align 2
.text


.globl main


f:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 40		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record


	sw $t0 8($sp)		# Paramater store start of function
	sw $t1 12($sp)		# Paramater store start of function


	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# expression is a constant
	sw $a0 20($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a1 20($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
_L6:			# # WHILE TOP target
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 24($sp)		# expression store LHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 24($sp)		# expression restore LHS from memory
	slt $a0, $a0, $a1		# #EXPR Lessthan
	beq $a0 $0 _L7		# #WHILE branch out
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0 28($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a0 ($a0)		# Get address of function array parameter
	add $a0 $a0 $a1		# VAR array add internal offset
	lw $a1 28($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a0 ($a0)		# Get address of function array parameter
	add $a0 $a0 $a1		# VAR array add internal offset
	lw $a0, ($a0)		# Expression is a VAR
	li $v0, 1		# About to print a number
	syscall			# call write number


	la $a0, _L1		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 32($sp)		# expression store LHS temporarily
	li $a0, 1		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 32($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	sw $a0 36($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 16		# VAR local stack pointer plus offset
	lw $a1 36($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	j _L6		# #WHILE Jump back
_L7:			# # End of WHILE 
	la $a0, _L2		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	jr $ra			# return to the caller

			# END OF FUNCTION



main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 84		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	li $a0, 19		# expression is a constant
	sw $a0 56($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 48		# VAR local stack pointer plus offset
	lw $a1 56($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
			# Setting Up Function Call
			# evaluate  Function Parameters
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 48		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 64($sp)		# Store call Arg temporarily

	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	sw $a0, 60($sp)		# Store call Arg temporarily

			# place   Parameters into T registers
	lw $a0, 64($sp)		# pull out stored  Arg 
	move $t0, $a0		# move arg in temp 
	lw $a0, 60($sp)		# pull out stored  Arg 
	move $t1, $a0		# move arg in temp 

	jal f			# Call the function


	la $a0, _L3		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# expression is a constant
	sw $a0 68($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 52		# VAR local stack pointer plus offset
	lw $a1 68($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
_L8:			# # WHILE TOP target
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 52		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 72($sp)		# expression store LHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 48		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 72($sp)		# expression restore LHS from memory
	slt $a0, $a0, $a1		# #EXPR Lessthan
	beq $a0 $0 _L9		# #WHILE branch out
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 52		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	add $a0 $a0 $a1		# VAR array add internal offset
	lw $a0, ($a0)		# Expression is a VAR
	li $v0, 1		# About to print a number
	syscall			# call write number


	la $a0, _L4		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 52		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 76($sp)		# expression store LHS temporarily
	li $a0, 1		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 76($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	sw $a0 80($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 52		# VAR local stack pointer plus offset
	lw $a1 80($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	j _L8		# #WHILE Jump back
_L9:			# # End of WHILE 
	la $a0, _L5		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



