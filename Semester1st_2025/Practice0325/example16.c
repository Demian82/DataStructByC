#include <stdio.h>
#include <malloc.h>
#include "shape.h"


int main(void)
{
	// ������ ���� ���ϱ� : �ﰢ��, �簢��, ��
	// ���α׷��� ���� : �Է°� ����� ��Ȯ
	// �Է� �޴�ȭ -> ��ɺ� �Լ��� ���� -> ���� �ڷ��� ����ȭ(�ڷᱸ��)
	//shape my;
	shape* pmy = shape_init_area();
	shape_menu_area(pmy);
	free(pmy);

	return 0;
}