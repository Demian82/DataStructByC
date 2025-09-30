#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

int main(void)
{
	// 배열을 사용한 스택
	int data[MAX_SIZE]; // 스택으로 사용할 배열
	int top; // 스택에서 맨 위에 있는 데이터 위치
	int index;
	int popItem;


	// 스택의 초기화 (비어있음)
	top = -1;

	// push 10
	top++; // top = top + 1
	data[top] = 10;

	// push 20
	top++;
	data[top] = 20;

	// push 30
	top++;
	data[top] = 30;

	// pop
	popItem = data[top];
	top--;

	// display
	printf("Linear Stack = [");
	for (index = 0; index <= top; index++)
	{
		printf("%d", data[index]);
		if (index != top)
			printf(" | ");
	}
	return 0;
}