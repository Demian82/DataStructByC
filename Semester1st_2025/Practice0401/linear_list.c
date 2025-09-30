#include <stdio.h>
#include <malloc.h>
#define MAX_SIZE 5 // 치환

// 자료구조의 구조화
typedef struct listType
{
	int data[MAX_SIZE]; // 배열을 사용한 리스트
	int length; // 리스트의 아이템 개수
} listType;

void linear_list_display(listType* list)
{
	int index;
	//리스트의 탐색 및 출력

	printf("Linear List = [");
	for (index = 0; index < list -> length; index++) {
		printf("%d", list -> data[index]);
		// index가 마지막이 아니라면 ,를 붙여라
		if (index != list->length - 1)
			printf(", ");
	}
	printf("]\n");
}

void linear_list_insert(listType* list, int pos, int item)
{
	int index;

	// 리스트가 가득찰 경우
	if (list->length == MAX_SIZE)
	{
		printf("List is Full!!\n");
		return;
	}

	// 삽입 위체에 대한 예외처리
	if (pos < 1 || pos > list->length + 1)
	{
		printf("Postion out of range!!\n");
		return;
	}
	
	for (index = list->length - 1; index >= pos - 1; index--) {
		list->data[index + 1] = list->data[index];
	}
	list->data[pos - 1] = item;
	(list->length)++;
}

int linear_list_delete(listType* list, int pos)
{
	int index;
	int delItem;

	// 리스트가 비어 있을 경우
	if (list->length == 0)
	{
		printf("List is Empty!!\n");
		return -1; // 오류 정보
	}

	// 삭제 위치 문제
	if (pos<1 || pos > list->length)
	{
		printf("Position out of range!!\n");
		return -1;
	}

	delItem = list->data[pos - 1];
	for (index = pos - 1; index < list->length - 1; index++) {
		list->data[index] = list->data[index + 1];
	}
	(list->length)--; // 개수 감소
	return delItem;
}

void linear_list_menu(listType* list)
{
	int pos; //위치
	int delItem; // 삭제 값을 지정하기 위한 변수
	int item; // 삽입할 데이터
	int menu;

	// 메뉴화
	while (1)
	{
		printf("Linear List : 1.Insert, 2.Delete, 3.Display, 4.Exit\n");
		printf("Inuput menu : ");
		scanf_s("%d", &menu);

		if (menu == 1)
		{
			printf("Insert Position ? ");
			scanf_s("%d", &pos);
			printf("insert Item ? ");
			scanf_s("%d", &item);
			linear_list_insert(list, pos, item);
		}
		else if (menu == 2)
		{
			printf("Delete Position ? ");
			scanf_s("%d", &pos);
			delItem = linear_list_delete(list, pos);
			if (delItem >= 0)
			{
				printf("Delete Item : %d\n", delItem);
			}
		}
		else if (menu == 3)
		{
			linear_list_display(list);
		}
		else if (menu == 4)
		{
			printf("exit\n");
			break;
		}
		else
		{
			printf("menu error\n");
		}
	}

}

listType* linear_list_init(void)
{
	// 자료구조의 초기화
	// 동적 메모리 할당
	listType* list = (listType*)malloc(sizeof(listType));
	list->length = 0;
	
	return list;
}

int main(void)
{
	listType* list = linear_list_init();
	linear_list_menu(list);
	free(list);

	return 0;
}