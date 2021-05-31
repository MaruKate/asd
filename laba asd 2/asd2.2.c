#include <stdio.h>
#include <math.h>
int main()
{
int n;
int i;
double counter1 = 1;
double S = 0;
int counter2 = 0;
printf("Enter n: ");
scanf_s("%d", &n);
for ( i = 1; i <= n; i++) {
	counter1 *= (sin(i));
    S += (sin(i)+2) / (i + counter1);
        counter2+=9;
    }
    printf("%d", counter2);  
    printf("\n");
    printf("S=%10.7f\n", S);
    return 0;
}
