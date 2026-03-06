#include <stdio.h>
int main(void)
{
	int score;
	printf("구구단 몇 단을 해볼까요?\n");
	scanf_s("%d", &score);
	
	{
		printf("%d단 계산\n", score);
		for (int j = 1; j <= 9; j++)
		{
			printf("  %d x %d = %d\n", score, j, score * j);
		}


	}
	return 0;
}



