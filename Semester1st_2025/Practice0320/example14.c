#include <stdio.h>
#include <malloc.h>

typedef struct square {
	int width;
	int height;
	int area;
} sqr;

void get_area(sqr* pmy)
{
	// 면적을 구하는 함수
	pmy->area = pmy->width * pmy->height;
}

void display_sqr(sqr* pmy)
{
	// 출력함수
	printf("사각형의 면적 : %d\n", pmy->area);
}

int main(void)
{
	// 사각형 면적
	// sqr my = { 10, 20 };
	sqr* p = (sqr*) malloc(sizeof(sqr)); // 동적 메모리 할당

	p->width = 10;
	p->height = 20;

	get_area(p);
	display_sqr(p);

	return 0;
}