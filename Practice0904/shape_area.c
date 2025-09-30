#include <stdio.h>
#include <malloc.h>

// ���赵 : ����ü(struct)
typedef struct shape {
	int width;
	int height;
	int radius;
	double pi;
	double triangle_area; // �ﰢ�� ����
	int square_area;   // �簢�� ����
	double circle_area; // �� ����
} shape;

shape* shape_area_init(void)
{
	// shpae myshape; // ���� �Ҵ�
	// ���� �Ҵ� : malloc(ũ��) -> ��ȯ�� : �ּ�
	shape* myshape = (shape*)malloc(sizeof(struct shape));
	// ����ü �����͸� ����Ͽ� ����� �����ϴ� ��� : ->  ������
	myshape->width = 10;
	myshape->height = 3;
	myshape->radius = 5;
	myshape->pi = 3.14;
}

void shape_area_triangle(shape* myshape)
{
	myshape->triangle_area = myshape->width * myshape->height / 2.0;
	printf("�ﰢ�� ���� : %.1f\n", myshape->triangle_area);
}

void shape_area_square(shape* myshape)
{
	myshape->square_area = myshape->width * myshape->height;
	printf("�簢�� ���� : %d\n", myshape->square_area);
}

void shape_area_circle(shape* myshape)
{
	myshape->circle_area = myshape->radius * 2 * myshape->pi;
	printf("�� ���� : %.1f\n", myshape->circle_area);
}

void shape_area_menu(shape* myshape)
{
	int menu;
	while (1) {
		printf("1. �ﰢ��, 2. �簢��, 3. ��, 4. ����\n");
		printf("���� : ");
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
			printf("���α׷� ����\n");
			break;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
		}
	}
}

int main(void)
{
	shape* myshape = shape_area_init(); // ���� �Ҵ�

	shape_area_menu(myshape);

	free(myshape); // ���� �Ҵ� ����
	return 0;
}