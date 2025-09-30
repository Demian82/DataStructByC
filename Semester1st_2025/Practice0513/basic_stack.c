#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

int main(void)
{
	// �迭�� ����� ����
	int data[MAX_SIZE]; // �������� ����� �迭
	int top; // ���ÿ��� �� ���� �ִ� ������ ��ġ
	int index;
	int popItem;


	// ������ �ʱ�ȭ (�������)
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