int x, y, z, A[100];
void test_read_write_global(void)
{
  write "\n-->FUNC START: test_read_write_global\n";
  write "This function will read an variable and set to global array index and print from there\n";
  write "enter X ";
  read x;
  write "Should print x, that is in A[10]\n";
  A[10] = x;
  write A[10];
  write "\n";
  write "-->FUNC END\n";
}

void test_while_loop(void)
{
  int i, j;
  write "\n-->FUNC START: test_while_loop\n";
  write "This function will run a nested loop, outer loop for 3 and an inner loop for 3\n";

  i = 0;
  j = 0;
  while (i < 3)
  {
    j = 0;
    while (j < 3)
    {
      write i;
      write " ";
      write j;
      write "\n";
      j = j + 1;
    }
    i = i + 1;
  }
  write "\n-->FUNC END\n";
}

void test_read_write_array_global(void)
{
  int i;
  write "\n-->FUNC START: test_read_write_array_global\n";
  write "This function will read 5 numbers into global array and print sqare of them\n";
  i = 0;
  while (i < 5)
  {
    write "enter X ";
    read A[i];
    i = i + 1;
  }

  i = 0;

  while (i < 5)
  {
    write "\n";
    write A[i] * A[i];
    i = i + 1;
  }
  write "\n-->FUNC END\n";
}

void test_double_array(void)
{
  int i;
  int C[10];
  int B[10];
  write "\n-->FUNC START: test_double_array\n";
  write "This function will show double array use cases such as A[B[5]]\n";
  write " Simple Array Checking \n";
  C[0] = 1;
  C[1] = 2;
  B[5] = 1;
  C[B[5]] = 10;
  write "This should print out 10\n";
  write C[1];
  write "\n";
  write "\n-->FUNC END\n";
}

void test_array_passing(int a, int arr[], int b)
{
  int i;
  int B[10];
  write "\n-->FUNC START: test_array_passing\n";
  write "This function will receives array as parameter and collaborate with local array\n";
  B[2] = 10;
  write "should print 63\n";
  write arr[3] + B[2] + a + b;
  write "\n-->FUNC END\n";
}

int f(void)
{
  return -10;
}
void test_unary(void)
{
  int a;
  write "\n-->FUNC START: test_array_passing\n";
  write "This function will test unary operations\n";
  a = 21;
  write "\nwill print -21\n";
  write - a;
  write "\n";
  write "\nwill print -5\n";
  write - 5;
  write "\n";
  write "\nwill print -10\n";
  write f();
  write "\n";
  write "\nwill print 10\n";
  write - f();
  write "\n";
  write "\n-->FUNC END\n";
}

int test_break_continue(int c)
{
  int i, j;

  write "\n-->FUNC START: test_break_continue\n";
  write "This function will test break, contine, 4 will not print for continue, after 6 break the loop\n";

  i = 0;

  while (i <= c)
  {
    i = i + 1;
    if (i == 4)
      continue;
    if (i > 6)
      break;
    write i;
    write "\n";
  }
  write "\n-->FUNC END\n";
}

void test_if_else(void)
{
  int i, sum;
  write "\n-->FUNC START: test_if_else\n";
  write "This function will show if else, if loop value is even it will sum them, else print the number\n";
  i = 0;
  sum = 0;
  while (i < 10)
  {
    if (i % 2 == 0)
    {
      sum = sum + i;
    }
    else
    {
      write i;
      write " ";
    }
    i = i + 1;
  }

  write "\nSum is: ";
  write sum;
  write "\n-->FUNC END\n";
}

void main(void)
{
  int arr[5];

  write "\n ####  MAIN FUNC START ####\n";
  test_read_write_global();
  test_if_else();
  test_while_loop();
  test_read_write_array_global();
  test_unary();

  arr[3] = 23;
  test_array_passing(10, arr, 20);
  test_break_continue(10);

  write "\n ####  MAIN FUNC END ####\n";
}
int p;