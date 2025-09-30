#include <stdio.h>
#include <malloc.h>

typedef struct node {
	int data; // ������
	struct node* link; // �ڽŰ� �Ȱ��� �ڷᱸ���� ����Ŵ
} node;

// ��� ���
typedef struct listType {
	int length;  // ����� ����
	struct node* head;  // ù ��° ��带 ����Ű�� ������
} listType;

void circular_list_insert(listType* list, int pos, int item)
{
	node* newNode = NULL;
	node* nptr = NULL;
	int index;

	// position�� ��� ���
	if (pos < 1 || pos > list->length + 1)
	{
		printf("position out of range\n");
		return;
	}

	newNode = (node*)malloc(sizeof(node));
	newNode->data = item;

	// ù ���� ���� ������ ��� ���� �����ʹ� �̵��� �ʿ䰡 ����
	if (pos == 1)
	{

	}
	else
	{
		nptr = list->head;
		// ���� ��ġ�� 
	}
	list->length++;
}

void circular_list_free(listType* list)
{
	// 1. ������ ������ ������ ����
	// 2. ù��° ������ �ڷ� ����
	// 3. �ι�° ������ �ڷ� ����
	node* nptr = list->head;
	while (nptr != NULL)
	{
		// ��尡 1���� ���
		if (nptr == nptr->link) // �ڱ� �ڽ��� link�� �ڱ� �ڽ��� ����Ŵ
			list->head = NULL;
		// ��尡 2�� �̻��� ���
		else
		{
			// 2��° ������ ����
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
	/* ���̸� �̿��� for��
	printf("Circular List = [");
	for (index = 1; index < list->length; index++)
	{
		printf("%d", nptr->data); // ���
		nptr = nptr->link; // �̵�
		if (nptr != list->head) // �˻�
			prinft("->");
	}*/
	
	// length�� ���� ��� while�� �ݺ�
	printf("Circular List = [");
	// ������ nptr != list->head �� �Ѵٸ� �������ڸ��� ����
	while (nptr != NULL)
	{
		printf("%d", nptr->data); // ���
		nptr = nptr->link; // �̵�
		if (nptr != list->head) // �˻� (ù��° ��尡 �ƴϸ�)
			printf("->");
		else
			nptr = NULL;
	}

	/*
	do
	{
		if (nptr == NULL) // ��尡 ���� ���
			break;
		printf("%d", nptr->data); // ���
		nptr = nptr->link; // �̵�
		if (nptr != list->head) // �˻� (ù��° ��尡 �ƴϸ�)
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
	// ������ �ʱ�ȭ
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