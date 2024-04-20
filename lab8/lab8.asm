# Name: Abdur Razzak
# Date: April 15, 2024
# Lab: LAB8 MIPS with MARS simulator
# Purpose: This is a basic assembly code practice that will take a number 
#       from user and will print sum of squares from 1 to that number. 


# All the print strings in the data components
# They are all labeled from L1 to L4. NL is just a new line
.data
L1: .asciiz "Please enter value: "
L2: .asciiz "The number read was "
L3: .asciiz "sum of squares from 1 to "
L4: .asciiz " is : "
NL: .asciiz "\n"

.align 2 # 2 byte machine
buffer: .space 8 # we need this to read in values an then we can store them
 .text  # directive that we are in the code segment

main:
        subu $a0, $sp, 12 # We want 4 mem locations for main SP, RA, i , s
        sw $ra, 4($a0)  # we need to store the RA in the Activation record
        sw $sp, ($a0) # store SP
        move $sp, $a0  # adjust SP


        #Prints the prompt2 string
	li $v0,  4      # setting 4 at register v0 for print
	la $a0, L1      # L1 is set at a0
	syscall         # syscall will find v0 as 4, then look at a0 to print a string

        #reads one integer from user and saves in sp with 8 offset
	li $v0, 5       # setting 5 to look for a number
	syscall         # will wait for user input
	sw $v0 8($sp)   # storing the number at sp with 8 offset
	
	# sprint it back out string
	li $v0, 4       # set to print a string
	la $a0, L2      # will print whatever inside Label L2
	syscall         # start printing

        # print out the number
	li $v0, 1       # set 1 to write a number
	lw $a0,8($sp)   # loading value into a0 from 8($sp)
	syscall         # will printout the number

        # just to print a new line
	li $v0, 4       # set to print new line
	la $a0, NL      # NL label has only a \n
	syscall         # print the new line

        lw $t5, 8($sp)  # loading into t5, the user input from 8($sp).
                        # This t5 will be used for upper loop bound.

        sw $0, 8($sp)   # store 0 into memory -- counting variable 
        sw $0, 16($sp)  # store 0 into memory -- accumulating variable
 
# This loop will run from 0 (t0) to user input number (t5)
# For example, if user input is 2, loop will run for 0, 1 and 2

loop:
        lw $t6, 8($sp)  # load i
        mul $t7, $t6, $t6       # t7 = i * i
        lw $t8, 16($sp)         # load s to t8
        addu $t9, $t8, $t7      # t9 = s + i*i
        sw $t9, 16($sp)         # storing updated s (t9) in the accumulating area
        lw $t6, 8($sp)          # load i 
        addu $t0, $t6, 1        # i+1
        sw $t0, 8($sp)          # storing i = i + 1
        ble $t0, $t5, loop      # branch loop will be taken until t0 less than equal t5
        nop   # 

        sw $t5, 8($sp)          # stroing t5 into 8($sp) just to ease while printing
        
        la $a0, L3              # Load L3
        li $v0 4                # set to print a string
        syscall                 # printing
        nop                     # No Operation

        # print out the user input number 
	li $v0, 1               # set 1 to write a number
	lw $a0,8($sp)           # load the x  
	syscall                 # print

        la $a0, L4              # Load L4
        li $v0 4                # set to print the string
        syscall                 # print
        nop                     # No Operation
        
        lw $a0, 16($sp)         # Loading the accumulated number s
        li $v0 1                # set 1 to write a number
        syscall                 # Print the number
        
       
        lw $ra, 4($sp)          # RA in the Activation record
        lw $sp , ($sp)          # put backl Ra and SP
        
        li $v0, 10              # set 10 to exit main
        syscall                 #  exit for MAIN only
        
  .data
        .align 0

        
