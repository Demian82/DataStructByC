#include <stdio.h>

// �Լ��� �ڱ� �ڽ��� ������ ����
// �����͸� ���޹ޱ� ���� �Ű� ����(parameter)�� ����

int get_area(int w, int h)
{
	int area;
	area = w * h;
	printf("�簢�� ���� : %d\n", area);
	// ����� main���� �ǵ�����
	return area;
}

void main(void)
{
	// �簢�� ���� ���ϱ�
	int width = 10;
	int height = 20;
	int area; // ����

	// ������(�μ�)�� �Լ��� ����
	area = get_area(width, height);

	printf("�簢�� ���� : %d\n", area);

}