# MIPS CODE GENERATE by Compilers class

.data

.align 2
.text


.globl main


f:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 20		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record


	sw $t0 8($sp)		# Paramater store start of function


	li $a0, 9		# expression is a constant
	sw $a0 16($sp)		# Assign store RHS temporarily
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a1 16($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 12		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	jr $ra			# return to the caller
	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	jr $ra			# return to the caller

			# END OF FUNCTION



main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 12		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




			# Setting Up Function Call
			# evaluate  Function Parameters
	li $a0, 3		# expression is a constant
	sw $a0, 8($sp)		# Store call Arg temporarily

			# place   Parameters into T registers
	lw $a0, 8($sp)		# pull out stored  Arg 
	move $t0, $a0		# move arg in temp 

	jal f			# Call the function


	li $v0, 1		# About to print a number
	syscall			# call write number


	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



