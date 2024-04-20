MIPS Simulator.

MIPS is a reduced instruction set architecture.  MIPS comes with its own assembly language.  We are going to emit MIPS assembly code from our compiler.  This lab is to get you oriented around the MIPS simulator

 


Direct Download from CANVAS HEREDownload Direct Download from CANVAS HERE

Link to command line options (optional)Links to an external site.
Links to an external site.
You can always run the mars simulator on the linux machines with the following command line
java  -jar /usr/local/lib/Mars4_5.jar sm $ASM_FILE
Where $ASM_FILE is your MIPS file.  The "sm" option says start at the label "main

The MARS  MIPS simulator and documentation is available HERELinks to an external site.

This lab should be fairly straight forward.  The goals of this lab are:

 

1)  To ensure that you are able to run a MIPS simulator

2)  For you to understand the basics of the MIPS instruction set

3)  For you to know where to look for information on the MIPS instruction set.

 

In general, we are going to use a very small subset of the MIPS instruction set.  You can find a really detailed description of MIPS on Wikipedia. (Links to an external site.) 

Additionally the following resources will be handy for this exercise along with the final portion of our compiler.

 

MIPS op code  HERE Download HEREPreview the documentand HEREPreview the document  Download HERE (two different presentations of the same information)

Additionally, here is a easy web site for the syscall function for calling READ and WRITE.

 http://logos.cs.uic.edu/366/notes/mips%20quick%20tutorial.htm (Links to an external site.)

 Reminders on the simulator:

A) You will have Assemble each time you make changes

 

Your tasks:

You are given 2 files.  One file calculates the sum of squares of integers to 100.  The second file read and writes numbers.   The files are:


sum100.asm    and  Download sum100.asm    and readwrite.asmDownload readwrite.asm

The sum of squares looks like

main()
{  int i; int s;

      i =0;
     s = 0;
repeat
     {    s = s + i*i;
           i = i + 1;
}   until i > 100

print "the sum of squares is"
print s

}

You are to run and understand each one.   You are to create a new program which calculates the sum of squares of the number that is read in by the user.  To accomplish this you will need to

 

1)  Start with the sum of squares program

2)  Increase the activation record by one word (4 bytes)

3)  Ask the user to input a number

4)  Store that number in the new SP+offset location probably 16($sp)

5)  Use that number instead of the hard coded 100.  This will mean you have to load the value into a register and use that register for comparison.

You are to upload 2 files,  The new ASM with good comments, and a screen shot of your output