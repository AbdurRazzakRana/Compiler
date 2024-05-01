# MIPS CODE GENERATE by Compilers class

.data

.align 2
.text

.globl main

main:                           # function definition
        move $a1, $sp           # Activation Record carve out copy SP
        subi $a1 $a1 100                # Activation Record carve out copy size of function
        sw $ra , ($a1)          # Store Return address 
        sw $sp 4($a1)           # Store the old Stack pointer
        move $sp, $a1           # Make SP the current activation record

        li $a0, 100             # expression is a constant
        sw $a0 92($sp)          # Assign store RHS temporarily
        move $a0 $sp            # VAR local make a copy of stackpointer
        addi $a0 $a0 88         # VAR local stack pointer plus offset
        lw $a1 92($sp)          # Assign get RHS temporarily
        sw $a1 ($a0)            # Assign place RHS into memory
        move $a0 $sp            # VAR local make a copy of stackpointer
        addi $a0 $a0 88         # VAR local stack pointer plus offset
        lw $a0, ($a0)           # Expression is a VAR
        sw $a0 96($sp)          # Assign store RHS temporarily
        li $a0, 13              # expression is a constant
        move $a1, $a0           # VAR copy index array in a1
        sll $a1 $a1 2           # muliply the index by wordszie via SLL
        move $a0 $sp            # VAR local make a copy of stackpointer
        addi $a0 $a0 8          # VAR local stack pointer plus offset
        add $a0 $a0 $a1         # VAR array add internal offset
        lw $a1 96($sp)          # Assign get RHS temporarily
        sw $a1 ($a0)            # Assign place RHS into memory
        li $a0, 13              # expression is a constant
        move $a1, $a0           # VAR copy index array in a1
        sll $a1 $a1 2           # muliply the index by wordszie via SLL
        move $a0 $sp            # VAR local make a copy of stackpointer
        addi $a0 $a0 8          # VAR local stack pointer plus offset
        add $a0 $a0 $a1         # VAR array add internal offset
        lw $a0, ($a0)           # Expression is a VAR
        li $v0, 1               # About to print a number
        syscall                 # call write number

        li $a0, 0               # RETURN has no specified value set to 0
        lw $ra ($sp)            # restore old environment RA
        lw $sp 4($sp)           # Return from function store SP

        li $v0, 10              # Exit from Main we are done
        syscall                 # EXIT everything

                        # END OF FUNCTION
