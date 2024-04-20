         /* simple lex program which removes comments from a source program
            The main key is that a variable "comment" is set when the start of a comment
            is seen and then unset when the ending set is seen.  It is possible to have
            two starts closed by on end.

            Shaun Cooper
            January 2015

	Edited By: Abdur Razzak
	Date: Jan 26, 2024
	Lab Title: 2.1
	Modificattion: 
		Renamed the file to lab21.l
		Adding lex rule for line numeber.
		When the new line occurs, incremented the line_number by 1.
		Also printed out the new line.
		To see the output, set the debug flag to 1 and
		printed the line_number on possible nested comment. 
         */
        int comment = 0;
        int debug=1;  /* prints out debug statements if desired */

	// counter variable line_number too keep track the line number.
	int line_number = 1;
%%
"/*"	{
	// Printing the line_number variable
	if (comment && debug) fprintf(stderr,
		" >>>>>>>> line %d: Possible Nested comment <<<<<<<<<<\n", line_number);
	comment = 1;
	}

"*/"	{
          if (!comment) printf("%s",yytext); /*print out if it is not in a comment */
	  comment = 0;
	}
\n	{
	// Adding the rule for new line
	// When it occurs, incrementing the line_number counter and print the new line
	line_number++;
	printf("\n");
	}

.       { if (!comment) printf("%s",yytext);}

%%

int yywrap(void)
{ return 1;
}

// Adding int to get ride of warning.
int main()
{
  yylex();
  
}

