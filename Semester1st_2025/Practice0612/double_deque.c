/*
deque : ��ũ(; ��, ��ť)
    �Ϲ����� ť�� �ڿ����� ������ �̷������ �տ����� ������ ������ �� ����,
	��ũ�� ���ʿ��� ��� ����/������ ������ ���ð� ť�� Ư¡�� ��� ����
*/

#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	struct node* llink; // ������ ��ũ�� ���
	int data;
	struct node* rlink; // ������ ��ũ�� ���
} node;

typedef struct dequeType // ��� ���
{
	int length;
	node* front;
	node* rear;
} dequeType;

int double_deque_delete(dequeType* deque, int way)
{
	int delItem;
	node* nptr = NULL;

	// ť�� ��� ���� ���
	if (deque->front == NULL)
	{
		printf("Deque is Empty\n");
		return -1;
	}

	// ��尡 1���� ��� : ����� ��� ����
	// front�� rear�� ��� NULL�� ���
	// �� ť�� ����ִ� ���� ��尡 1���� ��찡 ������ �ȵǴ� ���
	// ������ �߻��� ���ɼ��� ����
	// �ذ� : && �����ڸ� ���� �ѹ� �� üũ����.
	if (deque->front != NULL && (deque->front == deque->rear))
	{
		nptr = deque->front; // deque->rear
		deque->front = NULL;
		deque->rear = NULL;
	}
	// ��尡 2�� �̻��� ���
	else
	{
		// front���� ����
		if (way == 0)
		{
			nptr = deque->front;
			deque->front = nptr->rlink;
			nptr->rlink->llink = NULL;
		}
		// rear���� ����
		else
		{
			nptr = deque->rear;
			deque->rear = nptr->llink;
			deque->rear->rlink = NULL; // nptr->link->rlink =NULL;
		}
	}
	delItem = nptr->data;
	free(nptr);
	deque->length--;
	return delItem;
}

void double_deque_insert(dequeType* deque, int way, int item)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = item;

	// ť�� ������� ��� : ����� ��������
	if (deque->front == NULL)
	{
		newNode->rlink = NULL;
		newNode->llink = NULL;
		deque->front = newNode;
		deque->rear = newNode;
	}
	// 1�� �̻��� ��尡 ���� ���
	else
	{
		// front�� ����
		if (way == 0)
		{
			newNode->llink = NULL;
			newNode->rlink = deque->front;
			deque->front->llink = newNode;
			deque->front = newNode;
		}
		// rear�� ����
		else
		{
			newNode->rlink = NULL;
			newNode->llink = deque->rear;
			deque->rear->rlink = newNode;
			deque->rear = newNode;
		}
	}
	
	deque->length++;
}

void double_deque_display(dequeType* deque)
{
	// front���� rear���� ���
	node* nptr = deque->front;
	printf("Double deque = [");
	while (nptr != NULL)
	{
		printf("%d", nptr->data);
		nptr = nptr->rlink;
		if (nptr != NULL)
		{
			printf("<->");
		}
	}
	printf("]\n");
}

void double_deque_menu(dequeType* deque)
{
	int menu, item, delitem = -1;
	int way; // ���� ����(��/��)

	while (1)
	{
		printf("Double Linked deque : 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Way (front(0), rear(1)) ? ");
			scanf_s("%d", &way);
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			double_deque_insert(deque, way, item);
		}
		else if (menu == 2)
		{
			printf("Delete Position ? ");
			scanf_s("%d", &way);
			delitem = double_deque_delete(deque, way);
			if (delitem > 0)
				printf("Delete Item : %d\n", delitem);
		}
		else if (menu == 3)
		{
			double_deque_display(deque);
		}
		else if (menu == 4)
		{
			printf("Exit\n");
			break;
		}
		else
		{
			printf("Menu Error\n");
		}
	}
}

dequeType* double_deque_init()
{
	dequeType* deque = (dequeType*)malloc(sizeof(dequeType));
	deque->length = 0;
	deque->front = NULL;
	deque->rear = NULL;
	return deque;
}

int main(void)
{
	dequeType* deque = double_deque_init();
	double_deque_menu(deque);
	free(deque);


	return 0;
}