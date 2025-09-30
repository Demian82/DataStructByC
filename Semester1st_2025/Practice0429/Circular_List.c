#include <stdio.h>
#include <malloc.h>

typedef struct node {
	int data; // 아이템
	struct node* link; // 자신과 똑같은 자료구조를 가리킴
} node;

// 헤더 노드
typedef struct listType {
	int length;  // 노드의 개수
	struct node* head;  // 첫 번째 노드를 가리키는 포인터
} listType;

void circular_list_insert(listType* list, int pos, int item)
{
	node* newNode = NULL;
	node* nptr = NULL;
	int index;

	// position을 벗어날 경우
	if (pos < 1 || pos > list->length + 1)
	{
		printf("position out of range\n");
		return;
	}

	newNode = (node*)malloc(sizeof(node));
	newNode->data = item;

	// 첫 번쨰 노드로 삽입할 경우 삽입 포인터는 이동할 필요가 없다
	if (pos == 1)
	{

	}
	else
	{
		nptr = list->head;
		// 삽입 위치의 
	}
	list->length++;
}

void circular_list_free(listType* list)
{
	// 1. 마지막 노드부터 앞으로 삭제
	// 2. 첫번째 노드부터 뒤로 삭제
	// 3. 두번째 노드부터 뒤로 삭제
	node* nptr = list->head;
	while (nptr != NULL)
	{
		// 노드가 1개인 경우
		if (nptr == nptr->link) // 자기 자신의 link가 자기 자신을 가리킴
			list->head = NULL;
		// 노드가 2개 이상인 경우
		else
		{
			// 2번째 노드부터 삭제
			nptr = list->head->link;
			list->head->link = nptr->link;
		}
		free(nptr);
		nptr = list->head;
	}
	list->length = 0;
	nptr = list->head;
}

void circular_list_display(listType* list)
{
	int index;
	node* nptr = list->head;
	/* 길이를 이용한 for문
	printf("Circular List = [");
	for (index = 1; index < list->length; index++)
	{
		printf("%d", nptr->data); // 찍고
		nptr = nptr->link; // 이동
		if (nptr != list->head) // 검사
			prinft("->");
	}*/
	
	// length가 없는 경우 while문 반복
	printf("Circular List = [");
	// 조건을 nptr != list->head 로 한다면 시작하자마자 멈춤
	while (nptr != NULL)
	{
		printf("%d", nptr->data); // 찍고
		nptr = nptr->link; // 이동
		if (nptr != list->head) // 검사 (첫번째 노드가 아니면)
			printf("->");
		else
			nptr = NULL;
	}

	/*
	do
	{
		if (nptr == NULL) // 노드가 없을 경우
			break;
		printf("%d", nptr->data); // 찍고
		nptr = nptr->link; // 이동
		if (nptr != list->head) // 검사 (첫번째 노드가 아니면)
			printf("->");
	} while (nptr != list->head);
	*/

	printf("]\n");
}

void circular_list_menu(listType* list)
{
	int menu, pos, item, delitem;

	while (1)
	{
		printf("Circular List 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input Menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			//circular_list_insert(list, pos, item);
		}
		else if (menu == 2)
		{
			printf("Delete Position ? ");
			scanf_s("%d", &pos);
			//delitem = circular_list_delete(list, pos);
			/*if (delitem > 0)
			{
				printf("Delete Item : %d\n", delitem);
			}*/
		}
		else if (menu == 3)
		{
			circular_list_display(list);
		}
		else if (menu == 4)
		{
			//circular_list_free(list);
			circular_list_display(list);
			break;
		}
		else
		{
			printf("MENU ERROR\n");
			break;
		}
	}
}

listType* circular_list_init(void)
{
	// 헤더노드 초기화
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	list->head = NULL;
	return list;
}


int main(void)
{
	listType* list = circular_list_init();
	circular_list_menu(list);
	free(list);
	return 0;
}