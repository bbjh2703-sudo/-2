#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define MAX_HISTORY 100
#define PI 3.14159265358979323846
#define EPSILON 1e-9 


typedef struct {
    char shapeName[50];
    double area;
    double perimeter;
    char method[20];
    char inputData[150];
} Record;

typedef struct {
    double x;
    double y;
} Point;

Record history[MAX_HISTORY];
int historyCount = 0;


void clearBuffer() {
    while (getchar() != '\n');
}


double getLength(const char* prompt) {
    double val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &val) != 1) {
            printf("[오류] 숫자를 입력해주세요.\n");
            clearBuffer();
        }
        else if (val <= 0) {
            printf("[오류] 길이는 0보다 커야 합니다.\n");
        }
        else {
            return val;
        }
    }
}


double getCoord(const char* prompt) {
    double val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &val) != 1) {
            printf("[오류] 숫자를 입력해주세요.\n");
            clearBuffer();
        }
        else {
            return val;
        }
    }
}


double calculateDistance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


void saveRecord(const char* name, double area, double perimeter, const char* method, const char* data) {
    if (historyCount < MAX_HISTORY) {
        strcpy(history[historyCount].shapeName, name);
        history[historyCount].area = area;
        history[historyCount].perimeter = perimeter;
        strcpy(history[historyCount].method, method);
        strcpy(history[historyCount].inputData, data);
        historyCount++;
    }
}


void shapeFirstMode() {
    int shapeChoice, methodChoice;

    printf("\n[어떤 도형을 계산할까요?]\n");
    printf("1. 사각형  2. 삼각형  3. 다각형(오각형 이상)  4. 원\n선택: ");
    if (scanf("%d", &shapeChoice) != 1 || shapeChoice < 1 || shapeChoice > 4) {
        printf("[오류] 1~4 사이의 번호를 입력하세요.\n");
        clearBuffer(); return;
    }

    printf("\n[입력 방식 선택]\n1. 치수(길이) 입력  2. 좌표 입력\n선택: ");
    if (scanf("%d", &methodChoice) != 1 || (methodChoice != 1 && methodChoice != 2)) {
        printf("[오류] 1 또는 2를 입력하세요.\n");
        clearBuffer(); return;
    }

    double area = 0, perimeter = 0;
    char detail[150] = "";
    char* methodStr = (methodChoice == 1) ? "치수" : "좌표";

    if (shapeChoice == 1) {
        if (methodChoice == 1) {
            double w = getLength("가로 길이: ");
            double h = getLength("세로 길이: ");
            area = w * h;
            perimeter = 2 * (w + h);
            sprintf(detail, "가로 %.2f, 세로 %.2f", w, h);
        }
        else {
            Point p1, p2;
            printf("대각선 끝점 1\n");
            p1.x = getCoord("  x: "); p1.y = getCoord("  y: ");
            printf("대각선 끝점 2\n");
            p2.x = getCoord("  x: "); p2.y = getCoord("  y: ");

            double w = fabs(p2.x - p1.x);
            double h = fabs(p2.y - p1.y);
            if (w < EPSILON || h < EPSILON) { printf("[오류] 넓이가 0입니다.\n"); return; }

            area = w * h;
            perimeter = 2 * (w + h);
            sprintf(detail, "P1(%.1f,%.1f), P2(%.1f,%.1f)", p1.x, p1.y, p2.x, p2.y);
        }
        saveRecord("사각형", area, perimeter, methodStr, detail);
    }
    else if (shapeChoice == 2) {
        if (methodChoice == 1) {
            double a = getLength("변 1: "), b = getLength("변 2: "), c = getLength("변 3: ");
            if (a + b <= c || a + c <= b || b + c <= a) {
                printf("[오류] 삼각형 성립 조건 위반입니다.\n");
                return;
            }
            
            double s = (a + b + c) / 2.0;
            area = sqrt(s * (s - a) * (s - b) * (s - c));
            perimeter = a + b + c;
            sprintf(detail, "세 변: %.2f, %.2f, %.2f", a, b, c);
        }
        else {
            Point p[3];
            for (int i = 0; i < 3; i++) {
                printf("점 %d\n", i + 1);
                p[i].x = getCoord("  x: "); p[i].y = getCoord("  y: ");
            }
            
            area = 0.5 * fabs(p[0].x * (p[1].y - p[2].y) + p[1].x * (p[2].y - p[0].y) + p[2].x * (p[0].y - p[1].y));
            if (area < EPSILON) { printf("[오류] 세 점이 일직선상에 있습니다.\n"); return; }
            perimeter = calculateDistance(p[0], p[1]) + calculateDistance(p[1], p[2]) + calculateDistance(p[2], p[0]);
            sprintf(detail, "좌표 3개 입력");
        }
        saveRecord("삼각형", area, perimeter, methodStr, detail);
    }
    else if (shapeChoice == 3) { 
        int n = 0;
        int nChoice;

        printf("\n[다각형 추론 방식]\n");
        printf("1. 꼭짓점 개수 직접 입력 (예: 5)\n");
        printf("2. 한 내각의 크기로 추론 (예: 108도)\n");
        printf("3. 내각의 총합으로 추론 (예: 540도)\n선택: ");

        if (scanf("%d", &nChoice) != 1) { clearBuffer(); return; }

        if (nChoice == 1) {
            n = (int)getLength("꼭짓점의 개수: ");
        }
        else if (nChoice == 2) {
            double angle = getLength("정다각형의 한 내각(도): ");
            double calcN = 360.0 / (180.0 - angle);
            n = (int)(calcN + 0.5); 
            double idealAngle = 180.0 * (n - 2) / n;

            
            if (n < 3 || fabs(angle - idealAngle) > 1.0) {
                printf("[오류] 정다각형의 내각으로 부적합합니다.\n");
                return;
            }
            printf("\n=> 약 %.2f도이므로 '정%d각형'으로 계산합니다.\n", angle, n);
        }
        else if (nChoice == 3) {
            double sum = getLength("내각의 총합(도): ");
            double calcN = (sum / 180.0) + 2.0;
            n = (int)(calcN + 0.5);
            if (n < 3 || fabs(calcN - n) > 0.1) {
                printf("[오류] 올바른 내각의 합이 아닙니다.\n");
                return;
            }
            printf("\n=> 총합이 %.0f도이므로 '%d각형'으로 계산합니다.\n", sum, n);
        }

        if (n < 3) { printf("[오류] 다각형은 꼭짓점이 3개 이상이어야 합니다.\n"); return; }

        if (methodChoice == 1) {
            double s = getLength("한 변의 길이: ");
            area = (n * pow(s, 2)) / (4 * tan(PI / n));
            perimeter = n * s;
            sprintf(detail, "정%d각형, 한 변 %.2f", n, s);
            char name[30]; sprintf(name, "정%d각형", n);
            saveRecord(name, area, perimeter, methodStr, detail);
        }
        else {
            Point* pts = (Point*)malloc(sizeof(Point) * n);
            printf("\n[안내] %d각형의 꼭짓점을 테두리 순서대로 입력하세요.\n", n);
            for (int i = 0; i < n; i++) {
                printf("점 %d\n", i + 1);
                pts[i].x = getCoord("  x: ");
                pts[i].y = getCoord("  y: ");
            }

            
            double s1 = 0, s2 = 0;
            perimeter = 0;
            for (int i = 0; i < n; i++) {
                int next = (i + 1) % n;
                s1 += pts[i].x * pts[next].y;
                s2 += pts[i].y * pts[next].x;
                perimeter += calculateDistance(pts[i], pts[next]);
            }
            area = fabs(s1 - s2) / 2.0;

            char name[30]; sprintf(name, "일반 %d각형", n);
            saveRecord(name, area, perimeter, methodStr, "좌표 입력");
            free(pts);
        }
    }
    else if (shapeChoice == 4) {
        double r;
        if (methodChoice == 1) {
            r = getLength("반지름: ");
        }
        else {
            Point p1, p2;
            printf("중심점\n"); p1.x = getCoord("  x: "); p1.y = getCoord("  y: ");
            printf("원주 위의 점\n"); p2.x = getCoord("  x: "); p2.y = getCoord("  y: ");
            r = calculateDistance(p1, p2);
        }
        area = PI * r * r;
        perimeter = 2 * PI * r;
        saveRecord("원", area, perimeter, methodStr, "원 계산");
    }
    printf("\n>>> 결과: 면적 %.4f, 둘레 %.4f <<<\n", area, perimeter);
}

void autoInferenceMode() {
    int numPoints;
    printf("\n[좌표 자동 추론 모드]\n입력할 좌표 개수: ");
    if (scanf("%d", &numPoints) != 1 || numPoints < 2) {
        clearBuffer(); return;
    }

    Point* pts = (Point*)malloc(sizeof(Point) * numPoints);
    for (int i = 0; i < numPoints; i++) {
        printf("점 %d\n", i + 1);
        pts[i].x = getCoord("  x: ");
        pts[i].y = getCoord("  y: ");
    }

    if (numPoints == 3) {
        double area_tri = 0.5 * fabs(pts[0].x * (pts[1].y - pts[2].y) + pts[1].x * (pts[2].y - pts[0].y) + pts[2].x * (pts[0].y - pts[1].y));
        if (area_tri < EPSILON) {
            printf("[오류] 세 점이 일직선에 있습니다.\n");
        }
        else {
            double v1x = pts[0].x - pts[1].x, v1y = pts[0].y - pts[1].y;
            double v2x = pts[2].x - pts[1].x, v2y = pts[2].y - pts[1].y;

            double mag1 = sqrt(v1x * v1x + v1y * v1y);
            double mag2 = sqrt(v2x * v2x + v2y * v2y);

            double cosTheta = (v1x * v2x + v1y * v2y) / (mag1 * mag2);
            if (cosTheta > 1.0) cosTheta = 1.0;
            if (cosTheta < -1.0) cosTheta = -1.0;

            double angle_deg = acos(cosTheta) * (180.0 / PI);

            
            double calcN = 360.0 / (180.0 - angle_deg);
            int n = (int)(calcN + 0.5);

            double idealAngle = (n >= 3) ? (180.0 * (n - 2) / n) : 0;

            int isRegularPolygon = (n >= 3 && fabs(angle_deg - idealAngle) <= 1.0);

            printf("\n[분석] 가운데 점의 끼인각: %.2f도 (정%d각형의 내각은 %.2f도)\n", angle_deg, n, idealAngle);
            printf("1. 그냥 삼각형으로 계산하기\n");
            if (isRegularPolygon) {
                printf("2. 정%d각형의 일부분으로 간주하고 확장 계산하기 (오차 인정)\n", n);
            }

            printf("선택: ");
            int confirm; scanf("%d", &confirm);
            if (confirm == 2 && isRegularPolygon) {
                double s = (mag1 + mag2) / 2.0;
                double area_poly = (n * pow(s, 2)) / (4 * tan(PI / n));
                double p_poly = n * s;
                saveRecord("정다각형(추론)", area_poly, p_poly, "각도 추론", "성공");
                printf(">>> 정%d각형 면적: %.4f, 둘레: %.4f <<<\n", n, area_poly, p_poly);
            }
            else {
                double p = mag1 + mag2 + calculateDistance(pts[0], pts[2]);
                saveRecord("삼각형", area_tri, p, "좌표 추론", "기본 계산");
                printf(">>> 삼각형 면적: %.4f, 둘레: %.4f <<<\n", area_tri, p);
            }
        }
    }
    else {
        printf("\n추가적인 다각형 로직 생략 (기록 완료)\n");
    }

    free(pts);
}


void viewHistory() {
    if (historyCount == 0) {
        printf("\n저장된 계산 기록이 없습니다.\n");
        return;
    }
    printf("\n-------------------------------------------------\n");
    printf("%-5s | %-15s | %-10s | %-10s\n", "번호", "도형 이름", "면적", "둘레");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < historyCount; i++) {
        printf("%-5d | %-15s | %-10.4f | %-10.4f\n",
            i + 1, history[i].shapeName, history[i].area, history[i].perimeter);
    }
    printf("-------------------------------------------------\n");
}

int main(void) {
    int menu;
    while (1) {
        printf("\n========== [도형 면적 계산기] ==========\n");
        printf("1. 도형 선택 후 계산\n");
        printf("2. 좌표 입력으로 도형 자동 추론\n");
        printf("3. 계산 기록 조회\n");
        printf("4. 프로그램 종료\n");
        printf("========================================\n");
        printf("메뉴를 선택하세요: ");

        if (scanf("%d", &menu) != 1) {
            printf("[오류] 숫자를 입력해주세요.\n");
            clearBuffer();
            continue;
        }

        if (menu == 1) {
            shapeFirstMode();
        }
        else if (menu == 2) {
            autoInferenceMode();
        }
        else if (menu == 3) {
            viewHistory();
        }
        else if (menu == 4) {
            printf("\n프로그램을 종료합니다. 수고하셨습니다!\n");
            break;
        }
        else {
            printf("[오류] 올바른 메뉴 번호를 입력하세요.\n");
        }
    }
    return 0;
}