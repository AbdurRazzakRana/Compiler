int x4[100];

int f (int z){
 write "inside f\n";
 write z;
 write "\n";
 return z + 1;
}
int main(void){
 int g;
 g = f(2);
 write g;
 write "\nshould have written 3\n";
}