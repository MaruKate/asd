#include <stdio.h>

#define M 10
#define N 8

int matrix[10][8] = {
        { -2, 1, 4, 7, 10, 13, 17, 20 },
		{ -2, 1, 4, 7, 10, 13, 17, 20 },
		{ -2, 1, 4, 7, 10, 14, 17, 20 },
		{ -2, 2, 5, 7, 11, 14, 17, 20 },
		{ -2, 2, 5, 8, 11, 14, 18, 21 },
		{ -2, 2, 5, 8, 11, 14, 18, 21 }, 
		{ -2, 2, 5, 8, 11, 15, 18, 21 }, 
		{ -2, 2, 5, 8, 11, 15, 18, 21 },
		{ -2, 2, 5, 8, 11, 15, 18, 21 },                                               
        { -2, -2, -2, -2, -2, -2, -2, -2 }};
		
int BinarSearch(int arr[M][N], int rows, int cols, int key)
{

int first,last,mid,temp;
 
  for (int i=0; i<rows; i++) {
    first = 0;
    last = cols - 1;
    printf("last %d \n", last);
    
    while (first < last) {
        
         mid = (first + last) / 2;
         printf("mid %d \n", mid);
 
        if (key <= arr[i][mid]) {
            last = mid;
            printf("Last: %d \n", last);
        }
        else {
            first = mid + 1;
            printf("First: %d \n", first);
        }
    }
     if ( arr[i][last] == key) {
        printf("Found value, coordinates: [%d, %d] \n", i, last);
        break;
        goto stop;
        
    } else {
       printf("Value not found \n");
     goto stop;
    }
 
    stop: printf("Jumped to stop \n" );
}

}
int main(void) {

    
  BinarSearch(matrix, 10, 8, 1);  

    return 0;
}
