int x4[100];

int f (int z){
 write "inside f\n";
 write z;
 write "\n";
 return z + 1;
}

void main(void){
 int g;
 int x;
 x = 5;
 g=2;
 g = f(x+2);
 write "\nshould have written 8\n";
 write g;
}