#include <stdio.h>

void get_area(int* pw, int* ph, int* pa)
{
	*pa = *pw * *ph;
}

void display_area(int* pa)
{
	printf("사각형의 면적 : %d\n", *pa);
}

int main(void)
{
	// 사각형 면적 구하기
	int width, height;
	int area;

	printf("가로 : ");
	scanf_s("%d", &width);

	printf("세로 : ");
	scanf_s("%d", &height);

	get_area(&width, &height, &area);
	display_area(&area);

	return 0;
}