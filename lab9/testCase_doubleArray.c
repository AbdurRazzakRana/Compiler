int main(void)
{
  int A[10];
  int B[10];
  write " Simple Array Checking \n";
  A[0] = 1;
  A[1] = 2;
  B[5] = 1;
  A[B[5]] = 10;
  write "This should print out 10\n";
  write A[1];
  write "\n";
}