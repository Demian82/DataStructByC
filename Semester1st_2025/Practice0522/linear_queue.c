#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

typedef struct queueType
{
	int data[MAX_SIZE];
	int front; // 삭제 위치(인덱스)
	int rear; // 삽입 위치(인덱스)
} queueType;

queueType* linear_queue_init(void)
{
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	// 큐의 초기화 (큐가 비어있음)
	queue->front = -1;
	queue->rear = -1;
	return queue;
}


int linear_queue_delete(queueType* queue)
{
	int delitem;
	// 큐에서 항목을 삭제

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
	// 큐에 삽입
	// 문제점 : 가득 차 있는 상태에서 삭제를 하고 앞쪽에 빈자리가 있더라도
	// rear가 마지막 요소를 가리키므로 더이상 삽입할 수 없음
	
	// 큐가 가득차 있는 경우
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
	// 큐 출력
	// rear는 항상 마지막 항목의 위치
	// front는 첫번째 항목의 앞에 위치
	printf("Linear Queue = [");
	for (index = queue->front + 1; index <= queue->rear; index++)
	{
		printf("%d", queue->data[index]);
		if (index != queue->rear) // 마지막이 아니라면
			printf(", "); // 콤마를 삽입
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


// 배열을 사용한 큐(Queue)
// FIFO (First In First Out)
int main(void)
{
	queueType* queue = linear_queue_init();
	linear_queue_menu(queue);
	free(queue);
	
	return 0;
}