#include <stdio.h>

void main(void)
{
	// ������
	// ���� : 'A', "hello"
	// ���� : ����, �Ǽ�
	// � �����͸� ���α׷����� ���
	// �����ʹ� �޸� ������ �־�� ��
	// �����͸� ���� �޸� ������ �Ҵ�
	// ���� �޸� ������ �Ҵ� : int (4byte)
	// �Ǽ� �޸� ������ �Ҵ� : double (8byte)
	// ���� : �޸� ������ �Ҵ� �ް� �̸��� ���� ��
	int number1 = 10;
	int number2 = 20;
	int add = number1 + number2;
	printf("add = %d\n", add);
	// %d : ���� ����
}