#include <stdio.h>
#include <windows.h>
int main(void)

{
	int min;
	
	printf("이번 쿼터는 몇 분간 진행할까요? : \n");
	scanf_s("%d", &min);

	printf("GAME START\n");

	do {
		
		printf("남은 시간 : %d\n", min);
		Sleep(1000);
		min--;

	} while (min >= 0);
	printf("경기 종료\n");


	return 0;
}