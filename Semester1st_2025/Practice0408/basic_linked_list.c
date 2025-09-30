#include <stdio.h>
#include <malloc.h>

// 노드의 구조
typedef struct node
{
	int data; // 아이템
	struct node* link; // 자신과 똑같은 자료구조를 가리킴
}  node;

// 헤더 노드
typedef struct listType
{
	int length; // 노드의 개수
	struct node* head; // 첫 번째 노드를 가리키는 포인터
} listType;

int main(void)
{
	listType* list;
	node* newNode1;
	node* newNode2;
	node* newNode3;
	int index;
	node* nptr; // 노드 탐색 포인터

	// 헤더 노드의 생성
	list = (listType*)malloc(sizeof(listType));
	// 헤더 노드의 초기화
	list->length = 0; // 0개
	list->head = NULL; // 가리키는 노드가 없다.

	// 첫 번쨰 노드 정의
	newNode1 = (node*)malloc(sizeof(node));
	newNode1->data = 10;
	newNode1->link = NULL;
	list->head = newNode1; // 헤더가 첫 번째 노드를 가리킴
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

	// 노드의 탐색
	// 출력 : Linked List = [10->20->30]
	// for문
	nptr = list->head; // 탐색포인터의 초기화 : 첫번째 노드를 가리킴
	printf("Linked list = [");
	for (index = 0; index < list->length; index++)
	{
		// 탐색 포인터를 활용하여 노드에 접근
		printf("%d", nptr->data); // 데이터 출력
		nptr = nptr->link; // 다음 노드로 이동
		// 중간에 '->' 표시
		if (index != list->length-1)
			printf("->");
	}
	printf("]\n");

	// while문
	nptr = list -> head;
	printf("Linked list = [");
	while (nptr != NULL) // if(nptr)
	{
		printf("%d", nptr->data);
		nptr = nptr->link; // 탐색포인터 이동
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");

	// 깔끔한 종료 : 헤더 노드와 일반노드의 메모리 반환
	// 앞에서부터 하나씩 삭제 후 헤더노드 삭제
	// 첫 번째 노드 삭제
	list->head = newNode2;
	free(newNode1);
	// 두 번쨰 노드 삭제
	list->head = newNode3;
	free(newNode2);
	// 세 번째 노드 삭제
	list->head = NULL;
	free(newNode3);
	// 헤더노드를 삭제
	free(list);


	return 0;
}