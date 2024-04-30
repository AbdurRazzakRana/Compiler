# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "enter X"
_L1: .asciiz	 " x is "
_L2: .asciiz	 "\n"
.align 2
.text


.globl main


main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 12		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	li $v0, 5		# about to read in value
	syscall		#  read in value $v0 now has the read in value
	sw $v0, ($a0)		# store read in value to memory


	la $a0, _L1		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	move $a0 $sp		# VAR local make a copy of stackpointer
	addi $a0 $a0 8		# VAR local stack pointer plus offset
	lw $a0, ($a0)		# Expression is a VAR
	li $v0, 1		# About to print a number
	syscall			# call write number


	la $a0, _L2		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



