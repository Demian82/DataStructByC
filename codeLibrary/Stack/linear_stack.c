#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

typedef struct stackType {
	int data[MAX_SIZE]; // �������� ����� �迭
	int top; // ���ÿ��� �� ���� �ִ� ������ ��ġ
} stackType;

void linear_stack_display(stackType* stack)
{
	int index;
	// display
	printf("Linear Stack = [");
	for (index = 0; index <= stack->top; index++)
	{
		printf("%d", stack->data[index]);
		if (index != stack->top)
			printf(" | ");
	}
	printf("]\n");
}

int linear_stack_pop(stackType* stack)
{
	int popItem;
	
	// ���ÿ��� ���� ���� �ִ� �����͸� ������
	// top�� ���� ������

	// ������ ������� ���
	if (stack->top == -1)
	{
		printf("Stack is Empty\n");
		return -1;
	}
	popItem = stack->data[stack->top];
	stack->top--;
	return popItem;
}

void linear_stack_push(stackType* stack, int item)
{
	// push ����
	// ������ top�� ������Ų �� top�� ��ġ�� item�� ����

	// ������ ���� á�� ���
	if (stack->top == MAX_SIZE - 1)
	{
		printf("Stack is Full\n");
		return;
	}

	stack->top++;
	stack->data[stack->top] = item;

}

void linear_stack_menu(stackType* stack)
{
	int menu, item, popItem;

	while (1)
	{
		printf("Linear Stack 1.Push, 2.POP, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);
		
		if (menu == 1)
		{
			printf("Push Item ? ");
			scanf_s("%d", &item);
			linear_stack_push(stack, item);
		}
		else if (menu == 2)
		{
			popItem = linear_stack_pop(stack);
			if (popItem >= 0)
			{
				printf("Pop Itme : %d\n", popItem);
			}
		}
		else if (menu == 3)
		{
			linear_stack_display(stack);
		}
		else if (menu == 4)
		{
			printf("Exit\n");
			break;
		}
		else
		{
			printf("menu Error\n");
		}
	}
}

stackType* linear_stack_init(void)
{
	stackType* stack = (stackType*)malloc(sizeof(stackType));
	stack->top = -1;
	return stack;
}

int main(void)
{
	// �迭�� ����� ����
	stackType* stack = linear_stack_init();
	linear_stack_menu(stack);
	free(stack);

	return 0;
}