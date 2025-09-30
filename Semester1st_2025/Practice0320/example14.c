#include <stdio.h>
#include <malloc.h>

typedef struct square {
	int width;
	int height;
	int area;
} sqr;

void get_area(sqr* pmy)
{
	// ������ ���ϴ� �Լ�
	pmy->area = pmy->width * pmy->height;
}

void display_sqr(sqr* pmy)
{
	// ����Լ�
	printf("�簢���� ���� : %d\n", pmy->area);
}

int main(void)
{
	// �簢�� ����
	// sqr my = { 10, 20 };
	sqr* p = (sqr*) malloc(sizeof(sqr)); // ���� �޸� �Ҵ�

	p->width = 10;
	p->height = 20;

	get_area(p);
	display_sqr(p);

	return 0;
}