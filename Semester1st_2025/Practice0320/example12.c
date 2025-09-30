#include <stdio.h>

// ����ü(structure)
// ���� �ٸ� ������ �����͸� ��� �����ϴ� ���
// ����� �ڷ����� ����

// ���赵(�߻�ȭ)
typedef struct sample {
	// �⺻ �ڷ������� ����� ����
	int a;
	double b;
	char c;
} sample;

// typedef struct sample sample;

void test1(void)
{
	struct sample my; // = { 10, 3.14, 'K' };
	// ����ü ������ ����� �����ϴ� ���
	// ����ü����.���
	my.a = 10;
	my.b = 3.14;
	my.c = 'K';

	printf("size : %d\n", sizeof(struct sample)); // 24byte

	printf("%d\n", my.a);
	printf("%.1f\n", my.b);

}

void test2(void)
{
	// �ڷ����� ������
	typedef int suji;
	suji a = 10;
	printf("%d\n", a);

}

void test3(void)
{
	sample my = { 100, 12.3, 'C' };
	printf("%d\n", my.a);

}

int main(void)
{
	test3();
	return 0;
}