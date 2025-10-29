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
	node* front; // 삭제노드를 가리킴 ( 첫번째 노드)
	node* rear; // 삽입의 위치( 마지막 노드 )
} queueType;

int linked_queue_delete(queueType* queue)
{
	int delItem;
	node* nptr = NULL; // 삭제 노드 포인터

	if (queue->front == NULL)
	{
		printf("Queue is Empty\n");
		return -1;
	}

	nptr = queue->front;
	// front의 다음 노드를 가리킴
	queue->front = queue->front->link;

	// 삭제 후 노드가 없을 경우
	if (queue->front == NULL)
	{
		// rear도 NULL을 가리켜야 함
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

	// 노드가 하나도 없는 경우
	if (queue->rear == NULL)
	{
		// front, rear 모두 새로운 노드를 가리켜야 함
		queue->rear = newNode;
		queue->front = newNode;
	}
	else
	{
		// 노드가 1개 이상인 경우
		queue->rear->link = newNode;
		queue->rear = newNode;
		queue->length++;
	}
}

void linked_queue_display(queueType* queue)
{
	// display : front에서 rear까지
	node* nptr = queue->front;
	printf("Linded Queue = [");
	while (nptr != NULL)
	{
		printf("%d", nptr->data);
		nptr = nptr->link; // nptr 이동
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");
}

void linked_queue_free(queueType* queue)
{
	// free : 모든 노드 반환
	// 첫 번째 노드부터 차례로 삭제

	node * nptr = queue->front; // 삭제 노드
	while (nptr != NULL)
	{
		// front가 다음 노드를 가리킴
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
	// 큐 초기화
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