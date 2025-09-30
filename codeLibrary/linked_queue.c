#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	int data;
	struct node* link;
} node;

typedef struct queueType
{
	int length;
	node* front; // ������带 ����Ŵ ( ù��° ���)
	node* rear; // ������ ��ġ( ������ ��� )
} queueType;

int linked_queue_delete(queueType* queue)
{
	int delItem;
	node* nptr = NULL; // ���� ��� ������

	if (queue->front == NULL)
	{
		printf("Queue is Empty\n");
		return -1;
	}

	nptr = queue->front;
	// front�� ���� ��带 ����Ŵ
	queue->front = queue->front->link;

	// ���� �� ��尡 ���� ���
	if (queue->front == NULL)
	{
		// rear�� NULL�� �����Ѿ� ��
		queue->rear == NULL;
	}

	delItem = nptr->data;
	free(nptr);
	queue->length--;
	return delItem;
}

void linked_queue_insert(queueType* queue, int item)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = item;
	newNode->link = NULL;

	// ��尡 �ϳ��� ���� ���
	if (queue->rear == NULL)
	{
		// front, rear ��� ���ο� ��带 �����Ѿ� ��
		queue->rear = newNode;
		queue->front = newNode;
	}
	else
	{
		// ��尡 1�� �̻��� ���
		queue->rear->link = newNode;
		queue->rear = newNode;
		queue->length++;
	}
}

void linked_queue_display(queueType* queue)
{
	// display : front���� rear����
	node* nptr = queue->front;
	printf("Linded Queue = [");
	while (nptr != NULL)
	{
		printf("%d", nptr->data);
		nptr = nptr->link; // nptr �̵�
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");
}

void linked_queue_free(queueType* queue)
{
	// free : ��� ��� ��ȯ
	// ù ��° ������ ���ʷ� ����

	node * nptr = queue->front; // ���� ���
	while (nptr != NULL)
	{
		// front�� ���� ��带 ����Ŵ
		queue->front = queue->front->link; // nptr->link
		free(nptr);
		nptr = queue->front;
	}
	queue->rear;
	queue->length = 0;
}

void linked_queue_menu(queueType* queue)
{
	int menu, delItem =-1, item;
	while (1)
	{
		printf("Linked Queue 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			linked_queue_insert(queue, item);
		}
		else if (menu == 2)
		{
			delItem = linked_queue_delete(queue);
			if (delItem >= 0)
				printf("Delete Item : %d\n", delItem);
		}
		else if (menu == 3)
		{
			linked_queue_display(queue);
		}
		else if (menu == 4)
		{
			linked_queue_free(queue);
			linked_queue_display(queue);
			printf("Exit\n");
			break;
		}
		else
		{
			printf("Menu Error\n");
		}
	}
}

queueType* linked_queue_init()
{
	// ť �ʱ�ȭ
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	queue->length = 0;
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

int main(void)
{
	queueType* queue = linked_queue_init();
	linked_queue_menu(queue);
	free(queue);

	
	return 0;
}