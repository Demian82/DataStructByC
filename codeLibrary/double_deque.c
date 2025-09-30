/*
deque : 데크(; 덱, 디큐)
    일반적인 큐는 뒤에서만 삽입이 이루어지고 앞에서만 인출이 가능한 데 비해,
	데크는 양쪽에서 모두 삽입/인출이 가능한 스택과 큐의 특징을 모두 가짐
*/

#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	struct node* llink; // 좌측의 링크드 노드
	int data;
	struct node* rlink; // 우측의 링크드 노드
} node;

typedef struct dequeType // 헤더 노드
{
	int length;
	node* front;
	node* rear;
} dequeType;

int double_deque_delete(dequeType* deque, int way)
{
	int delItem;
	node* nptr = NULL;

	// 큐가 비어 있을 경우
	if (deque->front == NULL)
	{
		printf("Deque is Empty\n");
		return -1;
	}

	// 노드가 1개인 경우 : 방향과 상관 없음
	// front와 rear가 모두 NULL인 경우
	// 즉 큐가 비어있는 경우와 노드가 1개인 경우가 구분이 안되는 경우
	// 오류가 발생할 가능성이 있음
	// 해결 : && 연산자를 통해 한번 더 체크해줌.
	if (deque->front != NULL && (deque->front == deque->rear))
	{
		nptr = deque->front; // deque->rear
		deque->front = NULL;
		deque->rear = NULL;
	}
	// 노드가 2개 이상인 경우
	else
	{
		// front에서 삭제
		if (way == 0)
		{
			nptr = deque->front;
			deque->front = nptr->rlink;
			nptr->rlink->llink = NULL;
		}
		// rear에서 삭제
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

	// 큐가 비어있을 경우 : 방향과 관께없음
	if (deque->front == NULL)
	{
		newNode->rlink = NULL;
		newNode->llink = NULL;
		deque->front = newNode;
		deque->rear = newNode;
	}
	// 1개 이상의 노드가 있을 경우
	else
	{
		// front에 삽입
		if (way == 0)
		{
			newNode->llink = NULL;
			newNode->rlink = deque->front;
			deque->front->llink = newNode;
			deque->front = newNode;
		}
		// rear에 삽입
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
	// front에서 rear까지 출력
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
	int way; // 삽입 방향(앞/뒤)

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