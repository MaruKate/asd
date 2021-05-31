#include <stdio.h>
#include <math.h>


int main()
{
int n;
int i;
int j;
double counter1 = 1;
double S = 0;
int counter2=0;
printf("Enter n: ");
scanf_s("%d", &n);
for ( i=1; i<=n; i++) {
    for ( j = 1; j <= i; j++) {
    counter1 *= (sin(j));
    counter2+=4;
    }	
		S += (sin(i)+2) / (i + counter1);
		counter1=1;
	counter2+=7;

	}
	printf("%d", counter2);
    printf("\n");
    printf("S=%10.7f\n", S);
    return 0;
	
}
