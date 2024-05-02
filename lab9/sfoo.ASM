# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "True"
_L1: .asciiz	 "False"
.align 2
.text


.globl main


main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 12		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	li $a0, 5		# expression is a constant
	sw $a0, 8($sp)		# expression store LHS temporarily
	li $a0, 7		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 8($sp)		# expression restore LHS from memory
	slt $a0, $a1, $a0		# #EXPR Greaterthan
	beq $a0 $0 _L2		# #IF branch to else part

			#  the positive portion of IF
	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	j _L3		# #IF S1 end
_L2:			# # ELSE target

			#  the negative  portion of IF if there is an else
			#  otherwise just these lines
	la $a0, _L1		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


_L3:			# # End of IF 
	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION



