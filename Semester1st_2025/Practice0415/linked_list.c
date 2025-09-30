#include <stdio.h>
#include <malloc.h>

// 노드의 구조
typedef struct node {
	int data; // 아이템
	struct node* link; // 자신과 똑같은 자료구조를 가리킴
} node;

// 헤더 노드
typedef struct listType {
	int length;  // 노드의 개수
	struct node* head;  // 첫 번째 노드를 가리키는 포인터
} listType;

void linked_list_display(listType* list)
{
	// 노드의 탐색
	// 출력 : Linked List = [10->20->30]
	node* nptr;  // 노드를 가리키는 탐색 포인터
	nptr = list->head;
	printf("Linked List = [");
	// 탐색 포인터가 NULL아니면 탐색
	while (nptr != NULL) {  // if(nptr)
		printf("%d", nptr->data);
		nptr = nptr->link;  // 탐색포인터 이동
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");
}

void linked_list_free(listType* list)
{
	// 모든 노드를 차례로 삭제 ( 노드의 메모리 반환 )
	// 앞에서부터 하나씩 삭제 후 헤더노드 삭제

	// 삭제할 노드를 가리키는 포인터 정의
	node* nptr = list->head;
	// 반복하여 마지막 노드까지 삭제한다(NULL 값이 확인될 때 까지)
	while (nptr != NULL)
	{
		// 연결 후 삭제
		list->head = list->head->link; // nptr->link;
		free(nptr);
		// nptr이 다음 노드로 이동
		nptr = list->head;
	}
	list->length = 0;
}

void linked_list_insert(listType* list, int pos, int item)
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
	// 헤더노드를 정리
	if (pos == 1)
	{
		newNode->link = list->head;
		list->head = newNode;
	}
	// 2번째 이상 삽입할 경우
	else
	{
		// 포인터를 삽입할 위치의 바로 앞으로 이동
		nptr = list->head;
		for (index = 1; index < pos - 1; index++)
		{
			nptr = nptr->link;
		}
		// 삽입을 위해 연결 (뒤에서 부터)
		newNode->link = nptr->link;
		nptr->link = newNode;
	}

	

	list->length++;
}

int linked_list_empty(listType* list)
{
	// 리스트가 비어있는지 검사
	if (list->length == 0)
	{
		printf("List is Empty\n");
		return -1;
	}
	return 0;

}

int linked_list_delete(listType* list, int pos)
{
	node* nptr = NULL;
	node* pptr = NULL;
	int index;
	int delitem;

	// 리스트가 비어있는 경우
	if (list->head == NULL) // list->length == 0;
	{
		printf("List is Empty\n");
		return -1;
	}

	// position을 벗어날 경우
	if (pos < 1 || pos > list->length)
	{
		printf("position out of range\n");
			return -1;
	}

	// 삭제 노드포인터
	nptr = list->head;

	// 첫 번째 노드를 삭제 (pos = 1)
	if (pos == 1)
	{
		list->head = list->head->link; // nptr->link
	}
	// pos이 2 이상인 경우
	else
	{
		// 삭제 위치(pos)로 이동
		for (index = 1; index < pos; index++)
		{
			pptr = nptr; // 삭제 이전 포인터
			nptr = nptr->link;
		}
	}

	pptr->link = nptr->link; // 삭제 노드를 제외하고 연결
	
	delitem = nptr->data;
	free(nptr);
	list->length--;
	return delitem;
}

void linked_list_menu(listType* list)
{
	int menu, pos, item, delitem;

	while (1)
	{
		printf("Linkde List 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Input Menu ? ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("Insert Item ? ");
			scanf_s("%d", &item);
			linked_list_insert(list, pos, item);
		}
		else if ( menu == 2)
		{
			// 비어있는지 검사
			if (linked_list_empty(list)==0)
			{
				printf("Delete Position ? ");
				scanf_s("%d", &pos);
				delitem = linked_list_delete(list, pos);
				if (delitem > 0)
				{
					printf("Delete Item : %d\n", delitem);
				}
			}
		}
		else if (menu == 3)
		{
			linked_list_display(list);
		}
		else if (menu == 4)
		{
			linked_list_free(list);
			linked_list_display(list);
			break;
		}
		else
		{
			printf("MENU ERROR\n");
			break;
		}
	}
}

listType* linked_list_init(void)
{
	// 헤더노드 초기화
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	list->head = NULL;
	return list;
}

int main(void)
{
	listType* list = linked_list_init();
	linked_list_menu(list);
	free(list);
	return 0;
}