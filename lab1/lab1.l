     /*  This lex routine uses a counting array to match alphabeticstrings 
         and make a frequency count.
  
         The real item to notice is that yywrap() is called at EOF and then is run
         to do what we need to do.   yywrap() returns true when we have a successful 
         end to the program.  We may want to return false (0) if we want to lexing process 
         to fail 

        Shaun Cooper
        January 2015

	Modified by: Abdur Razzak
	Lab Title: Lab 1 -- using UNIX and lex
	Date: Jan 19, 2024
	Modification: Adding lex rule to count the number of numbers on extra variable.
   */
	int lgths[100];
	int counter=0; /* counter variable to count the number of numbers*/

/*
First Rule: to count the alphabetic string
Second Rule: is count the number of numbers
*/
%%
[a-zA-Z]+	lgths[yyleng]++;
[0-9]+	counter++;
.	|
\n	;
%%
int yywrap()
{
	int i;
	printf("Length  No. words\n");
	for (i=1; i<100; i++) {
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}
	/* Printing the number of numbers from the counter variable */
	printf("Total Numbers: %d\n", counter);
	return(1);
}

void main()
{  yylex();

}
