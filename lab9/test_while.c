int main(void){
 int i, j;
 i = 0;
 j = 0;
 while (i < 3){
  j = 0;
  while (j < 3){
   write i;
   write " ";
   write j;
   write "\n";
   j = j+1;
  }
  i = i+1;
 }
}