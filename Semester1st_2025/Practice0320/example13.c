#include <stdio.h>

typedef struct sample {
	int num1;
	int num2;
	int add;
} sample;

void get_add(sample you)
{
	you.add = you.num1 + you.num2;
}

void swap1(sample my)
{
	int temp;
	temp = my.num1;
	my.num1 = my.num2;
	my.num2 = temp;
}

// ����ü ������ �ּҸ� �����ͷ� ���޹���
void swap2(sample* pmy)
{
	// ����ü�� �����ͷ� ����� ���� : ->
	int temp;
	temp = pmy->num1; // (*pmy).num1;
	// (*pmy).num1 = (*pmy).num2;
	pmy->num1 = pmy->num2;
	// (*pmy).num2 = temp;
	pmy->num2 = temp;
}

int main(void)
{
	sample my = { 10, 20 };
	get_add(my); // ����ü ������ ����
	printf("%d\n", my.add);
	swap1(my);
	printf("%d, %d\n", my.num1, my.num2);
	swap2(&my);
	printf("%d, %d\n", my.num1, my.num2);

	return 0;
}