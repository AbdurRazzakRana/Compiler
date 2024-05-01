// program reads in several values and
// the prints the square of them out
void main(void) {
  int x[5];
  int i;
   i=0;
  while (i < 5 )
   {
      write "enter X ";
      read x[i];
      i = i + 1;
   }
 
   i=0;

  while (i < 5)
   {
      write x[i] * x[i];
      write "\n";
      i = i + 1;
   }

}
