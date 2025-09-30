#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	int data;
	struct node* link;
} node;

typedef struct stackType
{
	int length;
	node* top;
} stackType;

void linked_stack_free(stackType* stack)
{
	// ���� �ʱ�ȭ
	// ������ �����ϸ鼭 ��� ��带 ����
	node* nptr = stack->top;
	while (nptr != NULL) {
		stack->top = stack->top->link; // nptr->link
		free(nptr);
		nptr = stack->top;
	}
	stack->length = 0;
}

int linked_stack_pop(stackType* stack)
{
	int popItem;
	// pop ����
	// top�� ����Ű�� ��带 ����
	node* nptr = stack->top; // ���� ���
	// ���� ����� ���� ��带 ����Ŵ
	stack->top = stack->top->link; // nptr->link
	popItem = nptr->data;
	free(nptr);
	stack->length--;
	return popItem;
}

void linked_stack_push(stackType* stack, int item)
{
	// push
	// ���� �����ϴ� ��尡 ������ �� ���� ������
	// top�� �׻� ���ο� ��带 ����Ŵ

	node* newNode1 = (node*)malloc(sizeof(node));
	newNode1->data = item;
	newNode1->link = stack->top; // NULL;
	stack->top = newNode1;
	stack->length++;
}

void linked_stack_display(stackType* stack)
{
	// display
	node* nptr = stack->top;
	printf("Linked Stack = [");
	while (nptr != NULL)
	{
		printf("%d", nptr->data);
		nptr = nptr->link;
		if (nptr != NULL)
			printf(" | ");
	}
	printf("]\n");
}

stackType* linked_stack_init(void)
{
	// ������ �ʱ�ȭ
	stackType* stack = (stackType*)malloc(sizeof(stackType));
	stack->length = 0;
	stack->top = NULL;
	return stack;
}

void linked_stack_menu(stackType* stack)
{
	int menu, item, popItem = 0;
	while (1)
	{
		printf("Linked stack 1.Push, 2.Pop, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Push item ? ");
			scanf_s("%d", &item);
			linked_stack_push(stack, item);
		}
		else if (menu == 2)
		{
			popItem = linked_stack_pop(stack);
			if (popItem >= 0)
				printf("Pop Item : %d\n", popItem);
		}
		else if (menu == 3)
		{
			linked_stack_display(stack);
		}
		else if (menu == 4)
		{
			printf("Exit\n");
			linked_stack_free(stack);
			linked_stack_display(stack);

			break;
		}
		else
		{
			printf("Menu Error\n");
		}
	}
}

int main(void)
{
	stackType* stack = linked_stack_init();
	linked_stack_menu(stack);
	free(stack);

	return 0;
}