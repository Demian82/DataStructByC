#include <stdio.h>

// call by value : 값에 의한 복사
void swap1(int num1, int num2)
{
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

// 주소를 전달받으려면 포인터 변수로 받음
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
	// swap(교환)
	int a = 10;
	int b = 20;
	
	swap1(a, b);
	printf("%d, %d\n", a, b);
	
	// 주소를 전달
	swap2(&a, &b);
	printf("%d, %d\n", a, b);

	return 0;
}