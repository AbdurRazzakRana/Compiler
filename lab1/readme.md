In this lab assignment, you will download a lex file HERE  Download HEREand place the file in your working directory (I would recommend that you create a directory for this course).

 

After saving the file, you need to run "lex" on the file.  Lex is a program which takes LEX directives and writes C programs.  You are to do the following

 

1)  lex lab1.l

  -- you should get a new file call lex.yy.c

 

2)  compile the new file

    gcc -o lab1 lex.yy.c

 

3)  you now have an executable called "lab1"

   execute lab1 as follows

     ./lab1 < /etc/passwd

  and examine the output.

 

4)  modify the original code to count the times a number occurs.  A number is defined as [0-9]+  

          You should declare one or more counting variable to accomplish the task

5) Create a MAKEFILE so that anytime you update your lex file, the MAKEFILE will run lex and compiler the lex result.

6)  Run the same command with your modified code on /etc/passwd

7)  YOUR CODE MAY NOT HAVE ANY WARNINGS WHEN IT COMPILES

 

Turn in a ZIP file

1) Your name, Lab title, date as comments in the LEX file

2) describe the changes you made to the original code in the LEX file in comments of the LEX file

3)  A screen shot of your results in PDF form called lab1output.pdf

4)  A ZIP file of your source file makefile, and PDF, which also creates a lab1 folder