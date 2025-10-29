#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5

typedef struct queueType
{
	int data[MAX_SIZE];
	int front; // 삭제 위치(인덱스)
	int rear; // 삽입 위치(인덱스)
	int length; // 현재 큐에 있는 데이터의 개수
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
	// 큐의 초기화 (큐가 비어있음)
	queueType* queue = (queueType*)malloc(sizeof(queueType));
	// 큐의 마지막 위치
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
	// 큐에서 항목을 삭제

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
	// 큐에 삽입
	// 문제점 : 가득 차 있는 상태에서 삭제를 하고 앞쪽에 빈자리가 있더라도
	// rear가 마지막 요소를 가리키므로 더이상 삽입할 수 없음

	// 큐가 가득차 있는 경우
	if (queue->length == MAX_SIZE)
	{
		printf("Queue is Full\n");
		return;
	}

	queue->rear = (queue->rear + 1) % MAX_SIZE;
	// MAX_SIZE가 5일 경우
	// 인덱스가 0 1, 2, 3, 4, 5가 된 후에 다시 0으로 시작
	queue->data[queue->rear] = item;
	queue->length++;
}

void circular_queue_display(queueType* queue)
{
	// 원형 큐 출력
	// front의 위치가 rear보다 뒤에 올 수도 있음
	// 따라서 길이를 사용하는 것이 손 쉬움
	//
	int index; // 단순 반복을 위한 변수
	int qindex; // 큐의 항목을 접근하기 위한 인덱스

	printf("circular Queue = [");
	qindex = queue->front; // 첫 항목 이전 위치
	for (index = 0; index < queue->length; index++)
	{
		// 단순히 큐에 있는 데이터의 개수만큼 반복
		qindex = (qindex + 1) % MAX_SIZE; // 실재 큐의 인덱스
		printf("%d", queue->data[qindex]);
		if (index != queue->length-1) // 마지막이 아니라면
			printf(", "); // 콤마를 삽입
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


// 배열을 사용한 큐(Queue)
// FIFO (First In First Out)
int main(void)
{
	queueType* queue = circular_queue_init();
	circular_queue_menu(queue);
	free(queue);

	return 0;
}