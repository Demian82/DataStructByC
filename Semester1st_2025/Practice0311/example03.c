#include <stdio.h>
// c���� �Լ��� �����̴�
// C���α׷��� ������(����)
void main(void)
{
	// ����(variable)
	// �����ʹ� �޸� ������ �����ؾ� ó���� �� �ִ�.
	int a = 66; // ����(4byte)
	double b = 3.1415; // �Ǽ�(8byte)
	char c = 'A'; // ����(1byte)

	//������ �����͸� ����ϴ� ���
	printf("a = %d\n", a);
	printf("b = %.1f\n", b);
	printf("c = %c\n", c); // A
	printf("c = %d\n", c); // 65
	printf("a = %c\n", a);

	// �Լ��� ����
	// ����� ���� �Լ�
	// ���̺귯�� �Լ�
	printf("hello\n");

}
