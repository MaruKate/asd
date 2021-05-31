#include <stdio.h>

int main() {
  float x;
  int i;
  for ( i=0; i < 10; i++) {
    printf("x:");
    scanf_s("%f", &x);
    printf("result: \n");


  if ((x>-10 && x<=-5) || (x>5 && x<=15))
  printf("%f", x*x*x-6);
  
  else if (x>=25)
  printf("%f", 2*x*x*x-3*x+2);
  
  
	else printf("X is out of bounds. \n");
	printf("\n");



  }
  return 0;
}
