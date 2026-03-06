#include <stdio.h>

int main_for(void)
{
	/*printf("Hello world\n");*/

	// ++
	/*int I = 1;
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);
	printf("Hello World %d\n", I++);*/

	//반복문
	//for while do while

	//for (선언; 조건; 증감)
	/*for (int I = 1; I <= 10; I++)
	{
		printf("Hello world %d\n", I);
	}*/


	// while (조건) {  }
	//int I = 1;
	//while (I <= 10)
	//{
	//	printf("Hello world %d\n", I++);
	//	//I++
	//}
	
	// do (  ) while (조건);
	/*int I = 1;
	do {
		printf("Hello world %d\n", I++);
	} while (I <= 10);*/

	// 2중 반복문
	/*for (int I = 1; I <= 3; I++)
	{
		printf("첫 번째 반복문 : %d\n", I);

		for (int j = 1; j <= 5; j++)
		{
			printf("   두 번째 반복문 : %d\n", j);
		}

	}*/

	//구구단 만들기
	for (int i = 2; i <= 9; i++)
	{
		printf("%d단 계산\n", i);
		for (int j = 1; j <= 9; j++)
		{
			printf("  %d x %d = %d\n", i, j, i*j);
		}
	}

	//피라미드 만들기
	
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}*/

	/*for (int i = 0; i < 5; i++)
	{
		for (int j = i; j < 5 - 1; j++)
		{
			printf(" ");
		}
		for (int k = 0; k <= i; k++)
		{
			printf("*");
		}
		printf("\n");
	}*/

	/*int floor;
	printf("몇 층으로 쌓겠느냐?");
	scanf_s("%d", &floor);
	for (int i = 0; i < floor; i++)
	{
		for (int j = i; j < floor - 1; j++)
		{
			printf(" ");
		}
		for (int k = 0; k < i * 2 + 1; k++)
		{
			printf("*");
		}
		printf("\n");
	}*/





	return 0;

}