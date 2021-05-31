#include <stdio.h> 
#include <windows.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}

int main(){

for (int i=0; i<12; i++){
	for (int j=159; j>=0; j--){
		if(j%2 != 0){
			if(i%2 == 0){
				gotoxy(j/2, i);
				printf("*");
				Sleep(10);	
			}
			else{
				gotoxy(79-j/2, i);
			    printf("*");
			    Sleep(10);	
			}
		}
		else{
			if(i%2 == 0){
				gotoxy(j/2,23-i);
			    printf("*");
			    Sleep(10);	
			}
			else{
				gotoxy(79-j/2,23-i);
			    printf("*");
			    Sleep(10);	
			}
		}	
	}

}
gotoxy(25,0);
Sleep(100000);
return 0;
}
