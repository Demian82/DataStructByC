#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

typedef struct queueType
{
	int data[MAX_SIZE];
	int front; // ���� ��ġ(�ε���)
	int rear; // ���� ��ġ(�ε���)
} queueType;

queueType* linear_queue_init(void)
{
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	// ť�� �ʱ�ȭ (ť�� �������)
	queue->front = -1;
	queue->rear = -1;
	return queue;
}


int linear_queue_delete(queueType* queue)
{
	int delitem;
	// ť���� �׸��� ����

	if (queue->front == queue->rear)
	{
		printf("Queue is empty\n");
		return -1;
	}
	queue->front++;
	delitem = queue->data[queue->front];
	return delitem;
}

void linear_queue_insert(queueType* queue, int item)
{
	// ť�� ����
	// ������ : ���� �� �ִ� ���¿��� ������ �ϰ� ���ʿ� ���ڸ��� �ִ���
	// rear�� ������ ��Ҹ� ����Ű�Ƿ� ���̻� ������ �� ����
	
	// ť�� ������ �ִ� ���
	if (queue->rear == MAX_SIZE - 1)
	{
		printf("Queue is Full\n");
		return;
	}

	queue->rear++;
	queue->data[queue->rear] = item;
}

void linear_queue_display(queueType* queue)
{
	int index;
	// ť ���
	// rear�� �׻� ������ �׸��� ��ġ
	// front�� ù��° �׸��� �տ� ��ġ
	printf("Linear Queue = [");
	for (index = queue->front + 1; index <= queue->rear; index++)
	{
		printf("%d", queue->data[index]);
		if (index != queue->rear) // �������� �ƴ϶��
			printf(", "); // �޸��� ����
	}
	printf("]\n");
}

void linear_queue_menu(queueType* queue)
{
	int menu;
	int delitem;
	int item;

	while (1){
		printf("Linear Queue 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Input Item ? ");
			scanf_s("%d", &item);
			linear_queue_insert(queue, item);
		}
		else if (menu == 2)
		{
			delitem = linear_queue_delete(queue);
			if (delitem>0)
				printf("Deleted item : %d\n", delitem);
		}
		else if (menu == 3)
		{
			linear_queue_display(queue);
		}
		else if (menu == 4)
		{
			printf("Exit\n");
			break;
		}
		else {
			printf("menu error\n");
		}
	}
	
}


// �迭�� ����� ť(Queue)
// FIFO (First In First Out)
int main(void)
{
	queueType* queue = linear_queue_init();
	linear_queue_menu(queue);
	free(queue);
	
	return 0;
}