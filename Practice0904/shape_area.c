#include <stdio.h>
#include <malloc.h>

// 설계도 : 구조체(struct)
typedef struct shape {
	int width;
	int height;
	int radius;
	double pi;
	double triangle_area; // 삼각형 면적
	int square_area;   // 사각형 면적
	double circle_area; // 원 면적
} shape;

shape* shape_area_init(void)
{
	// shpae myshape; // 정적 할당
	// 동적 할당 : malloc(크기) -> 반환값 : 주소
	shape* myshape = (shape*)malloc(sizeof(struct shape));
	// 구조체 포인터를 사용하여 멤버에 접근하는 방법 : ->  연산자
	myshape->width = 10;
	myshape->height = 3;
	myshape->radius = 5;
	myshape->pi = 3.14;
}

void shape_area_triangle(shape* myshape)
{
	myshape->triangle_area = myshape->width * myshape->height / 2.0;
	printf("삼각형 면적 : %.1f\n", myshape->triangle_area);
}

void shape_area_square(shape* myshape)
{
	myshape->square_area = myshape->width * myshape->height;
	printf("사각형 면적 : %d\n", myshape->square_area);
}

void shape_area_circle(shape* myshape)
{
	myshape->circle_area = myshape->radius * 2 * myshape->pi;
	printf("원 면적 : %.1f\n", myshape->circle_area);
}

void shape_area_menu(shape* myshape)
{
	int menu;
	while (1) {
		printf("1. 삼각형, 2. 사각형, 3. 원, 4. 종료\n");
		printf("선택 : ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			shape_area_triangle(myshape);
		}
		else if (menu == 2)
		{
			shape_area_square(myshape);
		}
		else if (menu == 3)
		{
			shape_area_circle(myshape);
		}
		else if (menu == 4)
		{
			printf("프로그램 종료\n");
			break;
		}
		else
		{
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
		}
	}
}

int main(void)
{
	shape* myshape = shape_area_init(); // 동적 할당

	shape_area_menu(myshape);

	free(myshape); // 동적 할당 해제
	return 0;
}