#include <stdio.h>

// �簢�� ���� ���ϱ�
// C���� �Լ��� �����̴�

// main()�� c����� ������(����)
// 

// vodi : �����ϴ� �����Ͱ� ����, ��ȯ�ϴ� �����Ͱ� ����
// �Լ����� �Ű������� �ּҸ� ���޹��� -> �����͸� ���

struct square
{
	int width;
	int height;
	int area; // ����
};

void get_area(struct square* pmy)
{
	pmy->area = pmy->width * pmy->height;
	// ����� main()���� ��ȯ
}

int main(void)
{
	// ����ü�� ����Ͽ� �����͸� ���� : ���ο� �ڷ���
	struct square my;
	my.width = 10;
	my.height = 3;


	get_area(&my); // �Լ� ȣ��, �����͸� ����
	// �Լ��κ��� ���� ��ȯ ����
	
	printf("�簢�� ���� : %d\n", my.area); // 30
	return 0;
}
