# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "enter X "
_L1: .asciiz	 "\n"
.align 2
.text


.globl main


main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 60		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	li $a0, 0		# expression is a constant
	sw $a0 32($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a1 32($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
_L2:			# # WHILE TOP target
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 36($sp)		# expression store LHS temporarily
	li $a0, 5		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 36($sp)		# expression restore LHS from memory
	slt $a0, $a0, $a1		# #EXPR Lessthan
	beq $a0 $0 _L3		# #WHILE branch out
	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	add $a0 $a0 $a1		# VAR array add internal offset
	li $v0, 5		# about to read in value
	syscall		#  read in value $v0 now has the read in value
	sw $v0, ($a0)		# store read in value to memory


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 40($sp)		# expression store LHS temporarily
	li $a0, 1		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 40($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	sw $a0 44($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a1 44($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	j _L2		# #WHILE Jump back
_L3:			# # End of WHILE 
	li $a0, 0		# expression is a constant
	sw $a0 40($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a1 40($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
_L4:			# # WHILE TOP target
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 44($sp)		# expression store LHS temporarily
	li $a0, 5		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 44($sp)		# expression restore LHS from memory
	slt $a0, $a0, $a1		# #EXPR Lessthan
	beq $a0 $0 _L5		# #WHILE branch out
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	add $a0 $a0 $a1		# VAR array add internal offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 48($sp)		# expression store LHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# VAR copy index array in a1
	sll $a1 $a1 2		# muliply the index by wordszie via SLL
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	add $a0 $a0 $a1		# VAR array add internal offset
	lw $a0, ($a0)		# Expression is a VAR
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 48($sp)		# expression restore LHS from memory
	mult $a0 $a1		# #EXPR MULT
	mflo $a0		# #EXPR MULT
	li $v0, 1		# About to print a number
	syscall			# call write number


	la $a0, _L1		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 52($sp)		# expression store LHS temporarily
	li $a0, 1		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 52($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	sw $a0 56($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 28		# VAR local stack pointer plus offset
	lw $a1 56($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	j _L4		# #WHILE Jump back
_L5:			# # End of WHILE 
	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



