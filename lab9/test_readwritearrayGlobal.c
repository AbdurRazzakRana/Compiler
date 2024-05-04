// reads in 5 values 
// into an array and prints squaer out


  int x[5];
void main(void) {
  int i;
   i=0;
  while (i < 5) 
   {
      write "enter X ";
      read x[i];
      i = i + 1;
   }
 
   i=0;

  while (i < 5)
   {
      write "\n";
      write i;
      write "\n";
      write x[i] * x[i];
      write "\n";
      i = i + 1;
      
   }

}
