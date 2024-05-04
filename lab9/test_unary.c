int f(void){
  return -10;
}
int main(void){
  int x;
  x = 21;
  write -x;
  write "\n";
  write -5;
  write "\n";
  write f();
  write "\n";
  write -f();
  write "\n";
}