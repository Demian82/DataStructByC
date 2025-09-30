#include <stdio.h>
#include "shape.h"

void shape_tri_area(shape* pmy)
{
	pmy->tri_area = (pmy->width * pmy->height) / 2.0;
	printf("삼각형 면적 : %.1f\n", pmy->tri_area);
}

void shape_squ_area(shape* pmy)
{
	pmy->squ_area = pmy->width * pmy->height;
	printf("사각형 면적 : %d\n", pmy->squ_area);
}

void shape_cir_area(shape* pmy)
{
	pmy->cir_area = pmy->radius * pmy->radius * pmy->pi;
	printf("원 면적 : % .1f\n", pmy->cir_area);
}

void shape_menu_area(shape* pmy)
{
	int menu;

	while (1) {
		printf("도형의 면적 구하기\n");
		printf("1.삼각형, 2.사각형, 3.원, 4.종료\n");
		printf("선택 : ");
		scanf_s("%d", &menu);

		if (menu == 1) {
			printf("삼각형 면적\n");
			printf("가로 : ");
			scanf_s("%d", &pmy->width);
			printf("높이 : ");
			scanf_s("%d", &pmy->height);
			shape_tri_area(pmy);
		}
		else if (menu == 2) {
			printf("사각형 면적\n");
			printf("가로 : ");
			scanf_s("%d", &pmy->width);
			printf("높이 : ");
			scanf_s("%d", &pmy->height);
			shape_squ_area(pmy);
		}
		else if (menu == 3) {
			printf("원 면적\n");
			printf("너비 : ");
			scanf_s("%d", &pmy->radius);
			shape_cir_area(pmy);
		}
		else if (menu == 4)
			break;
		else
			printf("잘못된 입력\n");
		printf("\n");
	}
}

shape* shape_init_area(void)
{
	shape* pmy = (shape*)malloc(sizeof(shape));
	pmy->pi = 3.14;
	return pmy;
}
