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

void linked_list_insert(listType* list)
{
	node* newNode = NULL;
	node* nptr = NULL;
	int index, pos;

	// 맨 앞에 삽입
	newNode = (node*)malloc(sizeof(node)); // 새 노드 생성
	newNode->data = 40;
	// 뒤에서부터 연결
	newNode->link = list->head;
	list->head = newNode;
	list->length++;

	// 마지막에 삽입
	newNode = (node*)malloc(sizeof(node)); // 새 노드 생성
	newNode->data = 50;
	newNode->link = NULL;

	// 현재 마지막 노드를 가리키는 포인터
	// nptr이 마지막 노드로 이동
	nptr = list->head;
	/*while (nptr->link != NULL)
	{
		nptr = nptr->link;
	} */
	
	for(index = 1; index < list->length; index++)
	{
	    nptr = nptr->link;
	}

	newNode->link = nptr->link; // NULL;
	nptr->link = newNode;
	list->length++;

	// 중간(position)에 삽입
	pos = 3;
	newNode = (node*)malloc(sizeof(node)); // 새 노드 생성
	newNode->data = 60;

	nptr = list->head;
	// 삽입할 위치의 앞으 노드로 nptr 이동
	for (index = 1; index < pos-1; index++)
	{
		nptr = nptr->link;
	}
	newNode->link = nptr->link;
	nptr->link = newNode;
	list->length++;
}

int main(void)
{
	listType* list;
	node* newNode1;
	node* newNode2;
	node* newNode3;
	int index;
	

	// 헤더 노드의 생성
	list = (listType*)malloc(sizeof(listType));
	// 헤더 노드의 초기화
	list->length = 0;  // 0개
	list->head = NULL;  // 가리키는 노드가 없다

	// 첫 번째 노드 정의
	newNode1 = (node*)malloc(sizeof(node));
	newNode1->data = 10;
	newNode1->link = NULL;
	list->head = newNode1;  // 헤더가 첫 번째 노드를 가리킴
	list->length++;

	// 두 번째 노드 정의
	newNode2 = (node*)malloc(sizeof(node));
	newNode2->data = 20;
	newNode2->link = NULL;
	newNode1->link = newNode2;
	list->length++;

	// 세 번째 노드 정의
	newNode3 = (node*)malloc(sizeof(node));
	newNode3->data = 30;
	newNode3->link = NULL;
	newNode2->link = newNode3;
	list->length++;

	linked_list_display(list);

	linked_list_insert(list);
	linked_list_display(list);

	linked_list_free(list);
	linked_list_display(list);
	
	// 헤더노드를 삭제
	free(list);
	return 0;
}