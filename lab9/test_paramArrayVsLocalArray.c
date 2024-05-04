int f(int A[]){
 int B[10];
 B[2]=10;
 write "should print 33";
 write"\n";
 write A[3] + B[2];
}
int main(void){
 int A[5];
 A[3] = 23;
 f(A);
}