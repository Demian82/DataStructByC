#include <stdio.h>
#include <malloc.h>

// ����� ����
typedef struct node {
	int data; // ������
	struct node* link; // �ڽŰ� �Ȱ��� �ڷᱸ���� ����Ŵ
} node;

// ��� ���
typedef struct listType {
	int length;  // ����� ����
	struct node* head;  // ù ��° ��带 ����Ű�� ������
} listType;

void linked_list_display(listType* list)
{
	// ����� Ž��
	// ��� : Linked List = [10->20->30]
	node* nptr;  // ��带 ����Ű�� Ž�� ������
	nptr = list->head;
	printf("Linked List = [");
	// Ž�� �����Ͱ� NULL�ƴϸ� Ž��
	while (nptr != NULL) {  // if(nptr)
		printf("%d", nptr->data);
		nptr = nptr->link;  // Ž�������� �̵�
		if (nptr != NULL)
			printf("->");
	}
	printf("]\n");
}

void linked_list_free(listType* list)
{
	// ��� ��带 ���ʷ� ���� ( ����� �޸� ��ȯ )
	// �տ������� �ϳ��� ���� �� ������ ����

	// ������ ��带 ����Ű�� ������ ����
	node* nptr = list->head;
	// �ݺ��Ͽ� ������ ������ �����Ѵ�(NULL ���� Ȯ�ε� �� ����)
	while (nptr != NULL)
	{
		// ���� �� ����
		list->head = list->head->link; // nptr->link;
		free(nptr);
		// nptr�� ���� ���� �̵�
		nptr = list->head;
	}
	list->length = 0;
}

void linked_list_insert(listType* list, int pos, int item)
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
	// �����带 ����
	if (pos == 1)
	{
		newNode->link = list->head;
		list->head = newNode;
	}
	// 2��° �̻� ������ ���
	else
	{
		// �����͸� ������ ��ġ�� �ٷ� ������ �̵�
		nptr = list->head;
		for (index = 1; index < pos - 1; index++)
		{
			nptr = nptr->link;
		}
		// ������ ���� ���� (�ڿ��� ����)
		newNode->link = nptr->link;
		nptr->link = newNode;
	}

	

	list->length++;
}

int linked_list_empty(listType* list)
{
	// ����Ʈ�� ����ִ��� �˻�
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

	// ����Ʈ�� ����ִ� ���
	if (list->head == NULL) // list->length == 0;
	{
		printf("List is Empty\n");
		return -1;
	}

	// position�� ��� ���
	if (pos < 1 || pos > list->length)
	{
		printf("position out of range\n");
			return -1;
	}

	// ���� ���������
	nptr = list->head;

	// ù ��° ��带 ���� (pos = 1)
	if (pos == 1)
	{
		list->head = list->head->link; // nptr->link
	}
	// pos�� 2 �̻��� ���
	else
	{
		// ���� ��ġ(pos)�� �̵�
		for (index = 1; index < pos; index++)
		{
			pptr = nptr; // ���� ���� ������
			nptr = nptr->link;
		}
	}

	pptr->link = nptr->link; // ���� ��带 �����ϰ� ����
	
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
			// ����ִ��� �˻�
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
	// ������ �ʱ�ȭ
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