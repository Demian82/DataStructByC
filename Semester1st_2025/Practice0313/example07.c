#include <stdio.h>

// call by value : ���� ���� ����
void swap1(int num1, int num2)
{
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

// �ּҸ� ���޹������� ������ ������ ����
// call by reference
void swap2(int* pa, int* pb)
{
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

int main(void)
{
	// swap(��ȯ)
	int a = 10;
	int b = 20;
	
	swap1(a, b);
	printf("%d, %d\n", a, b);
	
	// �ּҸ� ����
	swap2(&a, &b);
	printf("%d, %d\n", a, b);

	return 0;
}