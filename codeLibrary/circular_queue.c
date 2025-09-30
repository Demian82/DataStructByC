#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

typedef struct queueType
{
	int data[MAX_SIZE];
	int front; // ���� ��ġ(�ε���)
	int rear; // ���� ��ġ(�ε���)
	int length; // ���� ť�� �ִ� �������� ����
} queueType;

queueType* circulear_real_array(queueType* queue)
{
	int index;
	printf("[");
	for (index = 0; index < MAX_SIZE; index++)
	{
		printf("%d", queue->data[index]);
		if (index != MAX_SIZE - 1)
			printf(", ");
	}
	printf("]\n");
}

queueType* circular_queue_init(void)
{
	// ť�� �ʱ�ȭ (ť�� �������)
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	// ť�� ������ ��ġ
	int index;
	queue->front = MAX_SIZE-1;
	queue->rear = MAX_SIZE-1;
	queue->length = 0;

	/*for (index = 0; index < MAX_SIZE; index++)
	{
		queue->data[index] = 
	}*/
	return queue;
}

int circular_queue_delete(queueType* queue)
{
	int delitem;
	// ť���� �׸��� ����

	if (queue->length == 0)
	{
		printf("Queue is empty\n");
		return -1;
	}
	queue->front = (queue->front + 1) % MAX_SIZE;
	delitem = queue->data[queue->front];
	queue->length--;


	return delitem;
}

void circular_queue_insert(queueType* queue, int item)
{
	// ť�� ����
	// ������ : ���� �� �ִ� ���¿��� ������ �ϰ� ���ʿ� ���ڸ��� �ִ���
	// rear�� ������ ��Ҹ� ����Ű�Ƿ� ���̻� ������ �� ����

	// ť�� ������ �ִ� ���
	if (queue->length == MAX_SIZE)
	{
		printf("Queue is Full\n");
		return;
	}

	queue->rear = (queue->rear + 1) % MAX_SIZE;
	// MAX_SIZE�� 5�� ���
	// �ε����� 0 1, 2, 3, 4, 5�� �� �Ŀ� �ٽ� 0���� ����
	queue->data[queue->rear] = item;
	queue->length++;
}

void circular_queue_display(queueType* queue)
{
	// ���� ť ���
	// front�� ��ġ�� rear���� �ڿ� �� ���� ����
	// ���� ���̸� ����ϴ� ���� �� ����
	//
	int index; // �ܼ� �ݺ��� ���� ����
	int qindex; // ť�� �׸��� �����ϱ� ���� �ε���

	printf("circular Queue = [");
	qindex = queue->front; // ù �׸� ���� ��ġ
	for (index = 0; index < queue->length; index++)
	{
		// �ܼ��� ť�� �ִ� �������� ������ŭ �ݺ�
		qindex = (qindex + 1) % MAX_SIZE; // ���� ť�� �ε���
		printf("%d", queue->data[qindex]);
		if (index != queue->length-1) // �������� �ƴ϶��
			printf(", "); // �޸��� ����
	}
	printf("]\n");
	circulear_real_array(queue);
}

void circular_queue_menu(queueType* queue)
{
	int menu;
	int delitem;
	int item;

	while (1) {
		printf("Circular Queue 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Input Item ? ");
			scanf_s("%d", &item);
			circular_queue_insert(queue, item);
		}
		else if (menu == 2)
		{
			delitem = circular_queue_delete(queue);
			if (delitem > 0)
				printf("Deleted item : %d\n", delitem);
		}
		else if (menu == 3)
		{
			circular_queue_display(queue);
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
	queueType* queue = circular_queue_init();
	circular_queue_menu(queue);
	free(queue);

	return 0;
}