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

// 구조체 변수의 주소를 포인터로 전달받음
void swap2(sample* pmy)
{
	// 구조체의 포인터로 멤버에 접근 : ->
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
	get_add(my); // 구조체 변수를 전달
	printf("%d\n", my.add);
	swap1(my);
	printf("%d, %d\n", my.num1, my.num2);
	swap2(&my);
	printf("%d, %d\n", my.num1, my.num2);

	return 0;
}