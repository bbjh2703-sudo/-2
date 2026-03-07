#include <stdio.h>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    int q;
    printf("이번 쿼터는 몇 쿼터인가요?\n");
    scanf_s("%d", &q);
    printf("GAME START\n");

    int min = 720;
    int shot = 24;
    int shot_timing = rand() % 20 + 3;
    int choice;

    do {
        system("cls");
        printf("남은 시간 : %d, shot clock : %d\n", min, shot);
        
        if (shot == shot_timing) {
            int auto_choice = (rand() % 2 == 0) ? 2 : 3;
            printf("\nEDWARD SHOT %dPOINT\n", auto_choice);
            printf("\nSHOT CLOCK %dsec\n", shot);

            int chance = rand() % 100 + 1;
            if (chance <= 50) {
                printf("EDWARDS MONEY!!\n");
                shot = 24;
            }
            else {
                printf("NOT GOOD...\n");
                int rebound_val = rand() % 100 + 1;
                if (rebound_val <= 50) {
                    printf("공격 리바운드 성공!!\n");
                    shot = 14;
                }
                else {
                    printf("수비 리바운드 (공격권 교체)\n");
                    shot = 24;
                }
            }
            
            shot_timing = rand() % 20 + 3;
            Sleep(3000);
        }
        if (shot <= 0) {
            printf("SHOT CLOCK VIOLATION\n");
            shot = 24;

            Sleep(3000);
        }
        Sleep(400);
        min--;
        shot--;

    } while (min >= 0);

    printf("쿼터 종료\n");
    return 0;
}